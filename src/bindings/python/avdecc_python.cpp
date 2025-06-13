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

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void bindCompileOptions(py::module_& m);
void bindBaseException(py::module_& m);
void bindMemoryBuffer(py::module_& m);
void bindMemoryBufferView(py::module_& m);
void bindLogger(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Module entry definition ----------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
PYBIND11_MODULE(la_avdecc, m)
{
    using namespace la::avdecc;

    m.doc() = "Python bindings for la::avdecc";

    m.def("getLibraryVersion", []() -> std::string { return internals::versionString; }, "Gets the library version string.");
    m.def("getLibraryName", []() -> std::string { return internals::applicationLongName; }, "Gets the full name of the library.");
    m.def("getLibraryCopyright", []() -> std::string { return internals::readableCopyright; }, "Gets the copyright string of the library.");
    m.def("getInterfaceVersion", &getInterfaceVersion, "Gets the interface version of the library.");

    bindCompileOptions(m);
    bindBaseException(m);
    bindMemoryBuffer(m);
    bindMemoryBufferView(m);
    bindLogger(m);

    bindEntity(m);
    bindEntityModelTypes(m);
    bindEntityModelProtocol(m);
    bindEntityModel(m);
    bindControllerEntity(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindCompileOptions(py::module_& m)
{
    using namespace la::avdecc;

    py::enum_<CompileOption>(m, "CompileOption", py::arithmetic())
        .value("Unset", CompileOption::None)
        .value("IgnoreInvalidControlDataLength", CompileOption::IgnoreInvalidControlDataLength)
        .value("IgnoreInvalidNonSuccessAemResponses", CompileOption::IgnoreInvalidNonSuccessAemResponses)
        .value("AllowGetAudioMapUnsol", CompileOption::AllowGetAudioMapUnsol)
        .value("AllowSendBigAecpPayloads", CompileOption::AllowSendBigAecpPayloads)
        .value("AllowRecvBigAecpPayloads", CompileOption::AllowRecvBigAecpPayloads)
        .value("EnableRedundancy", CompileOption::EnableRedundancy)
        .value("EnableJsonSupport", CompileOption::EnableJsonSupport)
        .export_values();

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
    py::register_exception<la::avdecc::Exception>(m, "BaseException", PyExc_RuntimeError);
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
        .value("FirstUserLayer", Layer::FirstUserLayer, "Starting point for user-defined logging layers.")
        .export_values();

    py::enum_<Level>(m, "LogLevel", "Enumeration of log severity levels.")
        .value("Trace", Level::Trace, "Very verbose debug information (typically disabled in release builds).")
        .value("Debug", Level::Debug, "Verbose debugging information (typically disabled in release builds).")
        .value("Info", Level::Info, "General informational messages.")
        .value("Warn", Level::Warn, "Indicates potential issues or non-critical problems.")
        .value("Error", Level::Error, "Indicates serious issues or failures.")
        .value("None", Level::None, "Disables all logging output.")
        .export_values();

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