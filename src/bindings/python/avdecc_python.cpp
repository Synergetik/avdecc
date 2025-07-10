/*
* Copyright (C) 2016-2025, L-Acoustics and its contributors

* This file is part of LA_avdecc.

* LA_avdecc is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* LA_avdecc is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.

* You should have received a copy of the GNU Lesser General Public License
* along with LA_avdecc.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file avdecc_python.cpp
 * @author Vitalij Mast
 */

#include "avdecc_python.hpp"
#include "avdecc_controller_python.hpp"
#include "avdecc_entity_python.hpp"
#include "avdecc_utils_python.hpp"

#include "config.hpp"
#include <la/avdecc/avdecc.hpp>
#include <la/avdecc/logger.hpp>
#include <la/avdecc/utils.hpp>
#include <la/avdecc/watchDog.hpp>

#include <atomic>
#include <shared_mutex>

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Globals --------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

static std::shared_mutex PythonShutdownAccessMutex;
static std::atomic<bool> PythonRuntimeAvailable{false};

std::optional<py::exception<la::avdecc::Exception>> AvdeccExceptionBinding{std::nullopt};

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void configureLibraryEnvironment(py::module_& m);
void bindCompileOptions(py::module_& m);
void bindBaseException(py::module_& m);
void bindMemoryBuffer(py::module_& m);
void bindMemoryBufferView(py::module_& m);
void bindLogger(py::module_& m);
void bindEndStation(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Module entry definition ----------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
PYBIND11_MODULE(la_avdecc, m)
{
    using namespace la::avdecc;

    configureLibraryEnvironment(m);

    m.doc() = "Python bindings for la::avdecc";
    m.def("getLibraryVersion", []() -> std::string { return internals::versionString; }, "Gets the library version string.");
    m.def("getLibraryName", []() -> std::string { return internals::applicationLongName; }, "Gets the full name of the library.");
    m.def("getLibraryCopyright", []() -> std::string { return internals::readableCopyright; }, "Gets the copyright string of the library.");
    m.def("getInterfaceVersion", &getInterfaceVersion, "Gets the interface version of the library.");

    // la/avdecc/avdecc.hpp
    bindCompileOptions(m);

    // la/avdecc/internals/exception.hpp
    bindBaseException(m);

    // la/avdecc/memoryBuffer.hpp
    bindMemoryBuffer(m);
    bindMemoryBufferView(m);

    // la/avdecc/logger.hpp
    bindLogger(m);

    bindEntity(m);
    bindEntityModelTypes(m);
    bindEntityModelProtocol(m);
    bindEntityModel(m);
    bindControllerEntity(m);

    // la/avdecc/internals/endStation.hpp
    bindEndStation(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void configureLibraryEnvironment(py::module_& m)
{
    // Configure WatchDog intercept hook to check if python debugger is attached.
    using WatchDog = la::avdecc::watchDog::WatchDog;

    WatchDog::IsCustomDebuggerPresent = std::make_shared<WatchDog::DebuggerPresenceCallback>([]() -> bool {
        // Acquire an exclusive lock to ensure thread-safe access
        // to the Python interpreter state. This prevents Python shutdown from
        // proceeding while this callback is potentially using Python APIs.
        std::unique_lock lock(PythonShutdownAccessMutex);

        // Check whether the Python runtime is still available. This flag is updated
        // just before the interpreter shuts down (via the atexit handler). If it's no
        // longer safe to use Python APIs, exit early to avoid undefined behavior.
        if (!PythonRuntimeAvailable.load(std::memory_order_acquire))
        {
            return false;
        }

        try
        {
            // Acquire the Global Interpreter Lock (GIL) to safely interact with Python code.
            // This ensures that any Python API calls in this block are thread-safe.
            py::gil_scoped_acquire gil;

            // Attempt to detect if a Python debugger is attached by inspecting sys.gettrace().
            // If gettrace is not None, a debugger (like pdb or PyCharm) is typically active.
            auto gettrace = py::module_::import("sys").attr("gettrace");
            return gettrace && !gettrace().is_none();
        } catch (...)
        {
            // Catch any exception that might occur during Python operations and
            // return false to fail safely without crashing the native thread.
            return false;
        }
    });

    // Bind the thread name change callback
    using namespace la::avdecc;

    m.def(
        "setThreadNameChangeCallback", [](std::function<void(std::string const&)> handler) { utils::OnSetCurrentThreadName = std::move(handler); },
        py::arg("handler"), "Registers a callback that is triggered whenever a thread's name is set.");

    // Register a Python cleanup function using the atexit module.
    // This ensures all Python-aware callbacks are deactivated before interpreter finalization.
    // It prevents native threads from attempting to interact with Python while it's shutting down.
    py::module_::import("atexit").attr("register")(py::cpp_function([]() {
        // Acquire an exclusive lock before starting the Python shutdown sequence.
        // This blocks until all other threads using Python (e.g., the watchdog thread)
        // have released their shared locks, ensuring no Python code is being executed concurrently.
        std::unique_lock lock(PythonShutdownAccessMutex);

        // Mark the Python runtime as unavailable. This prevents any further Python API
        // usage from native threads (such as the watchdog thread) once shutdown has started.
        PythonRuntimeAvailable.store(false, std::memory_order_release);

        // Clear any callback that may reference Python objects. This is critical
        // to avoid use-after-free or interpreter crashes once Python is finalized.
        WatchDog::IsCustomDebuggerPresent = nullptr;
        utils::OnSetCurrentThreadName     = nullptr;
    }));

    // Mark Python runtime as initialized and available for native threads.
    // This flag must be set after the atexit hook is registered and all callbacks are in place.
    PythonRuntimeAvailable.store(true, std::memory_order_release);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindCompileOptions(py::module_& m)
{
    using namespace la::avdecc;

    py::enum_<CompileOption>(m, "CompileOption", py::arithmetic())
        .value("Nothing", CompileOption::None)
        .value("IgnoreInvalidControlDataLength", CompileOption::IgnoreInvalidControlDataLength)
        .value("IgnoreInvalidNonSuccessAemResponses", CompileOption::IgnoreInvalidNonSuccessAemResponses)
        .value("AllowGetAudioMapUnsol", CompileOption::AllowGetAudioMapUnsol)
        .value("AllowSendBigAecpPayloads", CompileOption::AllowSendBigAecpPayloads)
        .value("AllowRecvBigAecpPayloads", CompileOption::AllowRecvBigAecpPayloads)
        .value("EnableRedundancy", CompileOption::EnableRedundancy)
        .value("EnableJsonSupport", CompileOption::EnableJsonSupport);

    bindEnumBitfield<CompileOption>(m, "CompileOptions");

    py::class_<CompileOptionInfo>(m, "CompileOptionInfo")
        .def(py::init<>())
        .def_readwrite("option", &CompileOptionInfo::option)
        .def_readwrite("shortName", &CompileOptionInfo::shortName)
        .def_readwrite("longName", &CompileOptionInfo::longName)
        .def(
            "__repr__",
            [](const CompileOptionInfo& info) {
                std::ostringstream oss;
                oss << "<CompileOptionInfo "
                    << "name='" << info.longName << "'>";
                return oss.str();
            },
            "Returns a string representation of the compile option info.");

    m.def("getCompileOptions", &getCompileOptions, "Gets the the library compile options.");
    m.def("getCompileOptionsInfo", &getCompileOptionsInfo, "Gets the the library compile option informations.");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindBaseException(py::module_& m)
{
    AvdeccExceptionBinding = py::register_exception<la::avdecc::Exception>(m, "AvdeccException", PyExc_RuntimeError);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMemoryBuffer(py::module_& m)
{
    using namespace la::avdecc;

    py::class_<MemoryBuffer>(m, "MemoryBuffer", "A raw memory buffer with utility methods for size and capacity management.")
        .def(py::init<>(), "Default constructor.")
        .def(py::init([](const std::string& str) { return MemoryBuffer(str); }), py::arg("string"), "Construct from a string.")
        .def(py::init([](py::bytes b) {
                 std::string raw = b;
                 return MemoryBuffer(raw.data(), raw.size());
             }),
             py::arg("bytes"), "Construct from bytes.")
        .def(py::init([](py::list l) {
                 std::vector<std::uint8_t> vec;
                 vec.reserve(py::len(l));
                 for (auto item : l)
                 {
                     vec.push_back(item.cast<std::uint8_t>());
                 }
                 return MemoryBuffer(vec);
             }),
             py::arg("list_of_bytes"), "Construct from a list of integers (0–255).")

        .def(py::self == py::self)
        .def(py::self != py::self)

        .def_property_readonly("size", &MemoryBuffer::size, "Returns the number of valid bytes.")
        .def_property_readonly("capacity", &MemoryBuffer::capacity, "Returns the allocated buffer size.")
        .def_property_readonly("empty", &MemoryBuffer::empty, "True if the buffer is empty.")
        .def_property_readonly("isValid", &MemoryBuffer::isValid, "True if the buffer is allocated.")

        .def("clear", &MemoryBuffer::clear, "Clears the buffer without deallocating memory.")
        .def("reserve", &MemoryBuffer::reserve, py::arg("capacity"), "Reserves buffer capacity.")
        .def("shrink_to_fit", &MemoryBuffer::shrink_to_fit, "Shrinks capacity to current size.")
        .def("set_size", &MemoryBuffer::set_size, py::arg("used_size"), "Sets the number of valid bytes in the buffer.")
        .def("consume_size", &MemoryBuffer::consume_size, py::arg("count"), "Removes bytes from the start of the buffer.")

        .def(
            "assign",
            [](MemoryBuffer& self, py::bytes b) {
                std::string raw = b;
                self.assign(raw.data(), raw.size());
            },
            py::arg("bytes"), "Assigns from Python bytes object.")

        .def(
            "append",
            [](MemoryBuffer& self, py::bytes b) {
                std::string raw = b;
                self.append(raw.data(), raw.size());
            },
            py::arg("bytes"), "Appends from Python bytes object.")

        .def(
            "append_byte", [](MemoryBuffer& self, std::uint8_t v) { self.append(v); }, py::arg("byte"), "Appends a single byte.")

        .def(
            "data", [](MemoryBuffer& self) { return py::bytes(reinterpret_cast<const char*>(self.data()), self.size()); },
            "Returns the buffer as Python bytes.")

        .def("__len__", &MemoryBuffer::size)
        .def("__bool__", &MemoryBuffer::isValid)
        .def("__bytes__", [](MemoryBuffer const& self) { return py::bytes(reinterpret_cast<const char*>(self.data()), self.size()); })
        .def(
            "__repr__",
            [](const MemoryBuffer& self) {
                std::ostringstream oss;
                oss << "<MemoryBuffer size=" << self.size() << " capacity=" << self.capacity() << " data=";

                const std::size_t preview_len = std::min(self.size(), static_cast<size_t>(32));
                const auto*       data_ptr    = self.data();

                for (std::size_t i = 0; i < preview_len; ++i)
                {
                    if (i > 0)
                    {
                        oss << ":";
                    }
                    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data_ptr[i]);
                }

                if (self.size() > 32)
                {
                    oss << " ...";
                }

                oss << ">";
                return oss.str();
            },
            "Returns a string representation of the MemoryBuffer (size, capacity, and first 32 bytes as hex).");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMemoryBufferView(py::module_& m)
{
    using namespace la::avdecc;

    py::class_<MemoryBufferView>(m, "MemoryBufferView", "A read-only view of a MemoryBuffer.")
        .def(py::init<>(), "Default constructor (empty view).")
        .def(py::init<const MemoryBuffer&>(), py::arg("buffer"), "Constructs a view of the entire buffer.")
        .def(py::init<const MemoryBuffer&, size_t>(), py::arg("buffer"), py::arg("offset"),
             "Constructs a view starting from an offset.\n"
             "Throws ValueError if offset is out of bounds.")
        .def(py::init([](const MemoryBuffer& buffer, size_t offset, size_t size) {
                 if (offset > buffer.size())
                     throw std::invalid_argument("Offset is out of buffer bounds");
                 if (size > buffer.size() - offset)
                     throw std::invalid_argument("Size is too big for the buffer");
                 return MemoryBufferView(buffer, offset, size);
             }),
             py::arg("buffer"), py::arg("offset"), py::arg("size"),
             "Constructs a view of a slice from offset and size.\n"
             "Throws ValueError if parameters are invalid.")

        .def(py::self == py::self)
        .def(py::self != py::self)

        .def_property_readonly("size", &MemoryBufferView::size, "The number of bytes in the view.")
        .def_property_readonly("empty", &MemoryBufferView::empty, "True if the view is empty.")
        .def_property_readonly("isValid", &MemoryBufferView::isValid, "True if the view is valid (i.e. points to data).")

        .def("__len__", &MemoryBufferView::size)
        .def("__bool__", &MemoryBufferView::isValid)
        .def(
            "__bytes__", [](const MemoryBufferView& self) { return py::bytes(reinterpret_cast<const char*>(self.data()), self.size()); },
            "Returns the view contents as Python bytes.")
        .def(
            "__repr__",
            [](const MemoryBufferView& self) {
                std::ostringstream oss;
                oss << "<MemoryBufferView size=" << self.size() << " data=0x";

                const std::size_t preview_len = std::min(self.size(), static_cast<size_t>(32));
                const auto*       data_ptr    = self.data();

                for (std::size_t i = 0; i < preview_len; ++i)
                {
                    if (i > 0)
                        oss << ":";
                    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data_ptr[i]);
                }

                if (self.size() > 32)
                {
                    oss << ":...";
                }

                oss << ">";
                return oss.str();
            },
            "Returns a string representation of the view with size and hex preview.");
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Logger bindings ------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
class PyLoggerObserver : public la::avdecc::logger::Logger::Observer
{
public:
    using la::avdecc::logger::Logger::Observer::Observer;
    using Level    = la::avdecc::logger::Level;
    using LogItem  = la::avdecc::logger::LogItem;
    using Observer = la::avdecc::logger::Logger::Observer;

    void onLogItem(Level level, const LogItem* item) noexcept override
    {
        PYBIND11_OVERRIDE_PURE(void, Observer, onLogItem, level, item);
    }
};

/*-------------------------------------------------------------------------------------------------------------------*/
void bindLogger(py::module_& m)
{
    using namespace la::avdecc::logger;

    py::enum_<Layer>(m, "LogLayer", "Enumeration of logging layers used throughout the system.")
        .value("Generic", Layer::Generic, "General-purpose logging layer.")
        .value("Serialization", Layer::Serialization, "Serialization and deserialization operations.")
        .value("ProtocolInterface", Layer::ProtocolInterface, "Protocol interface (transport, low-level).")
        .value("AemPayload", Layer::AemPayload, "AVDECC AEM payload-specific logic.")
        .value("Entity", Layer::Entity, "Entity-related logic.")
        .value("ControllerEntity", Layer::ControllerEntity, "Entity controller logic.")
        .value("ControllerStateMachine", Layer::ControllerStateMachine, "State machine logic for controllers.")
        .value("Controller", Layer::Controller, "Top-level controller behavior.")
        .value("JsonSerializer", Layer::JsonSerializer, "JSON serialization and introspection layer.")
        .value("FirstUserLayer", Layer::FirstUserLayer, "Starting point for user-defined logging layers.");

    py::enum_<Level>(m, "LogLevel", "Enumeration of log severity levels.")
        .value("Trace", Level::Trace, "Very verbose debug information (typically disabled in release builds).")
        .value("Debug", Level::Debug, "Verbose debugging information (typically disabled in release builds).")
        .value("Info", Level::Info, "General informational messages.")
        .value("Warn", Level::Warn, "Indicates potential issues or non-critical problems.")
        .value("Error", Level::Error, "Indicates serious issues or failures.")
        .value("Nothing", Level::None, "Disables all logging output.");

    py::class_<LogItem, std::shared_ptr<LogItem>>(m, "LogItem", "Base class for a log entry. Not constructible or subclassable in Python.")
        .def_property_readonly("layer", &LogItem::getLayer, "Returns the log layer associated with this log item.")
        .def_property_readonly("message", &LogItem::getMessage, "Returns the log message. Must be implemented by concrete subclasses.");

    py::class_<Logger::Observer, PyLoggerObserver>(m, "LogObserver", "Interface for receiving log items.")
        .def(py::init<>())
        .def("onLogItem", &Logger::Observer::onLogItem, py::arg("level"), py::arg("item"), "Called when a new log item is emitted.");

    py::class_<Logger, std::unique_ptr<Logger, py::nodelete>>(m, "Logger", "Logger singleton class.")
        .def_static("getInstance", &Logger::getInstance, py::return_value_policy::reference, "Returns the global logger instance.")
        .def("registerObserver", &Logger::registerObserver, py::arg("observer"), "Registers a logger observer.")
        .def("unregisterObserver", &Logger::unregisterObserver, py::arg("observer"), "Unregisters a logger observer.")
        .def("logItem", &Logger::logItem, py::arg("level"), py::arg("item"), "Logs a given LogItem at the specified log level.")
        .def_property("level", &Logger::getLevel, &Logger::setLevel, "Minimum log level.")
        .def("layerToString", &Logger::layerToString, py::arg("layer"), "Converts a log layer to its string representation.")
        .def("levelToString", &Logger::levelToString, py::arg("level"), "Converts a log level to its string representation.")
        .def(
            "__repr__",
            [](const Logger& self) {
                std::ostringstream oss;
                oss << "<AvdeccLogger level=" << self.levelToString(self.getLevel()) << ">";
                return oss.str();
            },
            "Returns a string representation of the Logger.");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEndStation(py::module_& m)
{
    using namespace la::avdecc;
    using namespace la::avdecc::protocol;

    auto endStation = py::class_<EndStation, std::shared_ptr<EndStation>>(m, "EndStation");

    py::enum_<EndStation::Error>(endStation, "Error")
        .value("NoError", EndStation::Error::NoError)
        .value("InvalidProtocolInterfaceType", EndStation::Error::InvalidProtocolInterfaceType)
        .value("InterfaceOpenError", EndStation::Error::InterfaceOpenError)
        .value("InterfaceNotFound", EndStation::Error::InterfaceNotFound)
        .value("InterfaceInvalid", EndStation::Error::InterfaceInvalid)
        .value("DuplicateEntityID", EndStation::Error::DuplicateEntityID)
        .value("InvalidEntityModel", EndStation::Error::InvalidEntityModel)
        .value("DuplicateExecutorName", EndStation::Error::DuplicateExecutorName)
        .value("UnknownExecutorName", EndStation::Error::UnknownExecutorName)
        .value("InternalError", EndStation::Error::InternalError);

    auto endStationException = py::register_exception<EndStation::Exception>(m, "EndStationException", AvdeccExceptionBinding->ptr());
    py::class_<EndStation::Exception>(static_cast<py::handle>(endStationException), "EndStationException")
        .def_property_readonly("error", &EndStation::Exception::getError);

    endStation
        .def(
            "addControllerEntity",
            [](EndStation& self, std::uint16_t progID, const UniqueIdentifier& entityModelID, entity::controller::Delegate* delegate) {
                return self.addControllerEntity(progID, entityModelID, nullptr, delegate);
            },
            py::arg("progID"), py::arg("entityModelID"), py::arg("delegate"), py::return_value_policy::reference,
            "Adds a ControllerEntity with an empty EntityModelTree.")
        .def_static(
            "create",
            [](const std::string& interfaceID, const std::optional<std::string>& executorName) -> std::shared_ptr<EndStation> {
                py::gil_scoped_release nogil{};

                auto instance = la::avdecc::EndStation::create(ProtocolInterface::Type::PCap, interfaceID, executorName);
                auto deleter  = instance.get_deleter();

                return {instance.release(), [deleter](EndStation* self) mutable {
                            py::gil_scoped_release nogil{};
                            deleter(self);
                        }};
            },
            py::arg("interfaceID"), py::arg("executorName") = std::nullopt,
            "Creates a new EndStation instance with the specified network interface ID and optional executor name.\n"
            "The protocol interface type is set to PCap (PCAP-based protocol interface).")
        .def("__repr__", [](const EndStation& self) {
            std::ostringstream oss;
            oss << "<EndStation at 0x" << &self << ">";
            return oss.str();
        });

    // TODO VM: add more methods to EndStation as needed
}