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
 * @file avdecc_entity_model_types_python.cpp
 * @author Vitalij Mast
 */

#include "avdecc_entity_python.hpp"

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void bindDescriptorType(py::module_& m);
void bindJackType(py::module_& m);
void bindClockSourceType(py::module_& m);
void bindMemoryObjectType(py::module_& m);
void bindMemoryObjectOperationType(py::module_& m);
void bindAudioClusterFormat(py::module_& m);
void bindAudioMapping(py::module_& m);
void bindTimingAlgorithm(py::module_& m);
void bindPtpPortType(py::module_& m);
void bindStandardControlTypeVendorID(py::module_& m);
void bindStandardControlType(py::module_& m);
void bindMsrpMapping(py::module_& m);
void bindAvdeccFixedString(py::module_& m);
void bindSamplingRate(py::module_& m);
void bindStreamFormat(py::module_& m);
void bindLocalizedStringReference(py::module_& m);
void bindControlValueUnit(py::module_& m);
void bindControlValueType(py::module_& m);
void bindBaseControlValues(py::module_& m);
void bindStreamIdentification(py::module_& m);
void bindMilanVersion(py::module_& m);
void bindProbingStatus(py::module_& m);
void bindMsrpFailureCode(py::module_& m);
void bindDefaultMediaClockReferencePriority(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityModelTypes(py::module_& m)
{
    // la/avdecc/internals/entityModelTypes.hpp
    bindDescriptorType(m);
    bindJackType(m);
    bindClockSourceType(m);
    bindMemoryObjectType(m);
    bindMemoryObjectOperationType(m);
    bindAudioClusterFormat(m);
    bindAudioMapping(m);
    bindTimingAlgorithm(m);
    bindPtpPortType(m);
    bindStandardControlTypeVendorID(m);
    bindStandardControlType(m);
    bindMsrpMapping(m);
    bindAvdeccFixedString(m);
    bindSamplingRate(m);
    bindStreamFormat(m);
    bindLocalizedStringReference(m);
    bindControlValueUnit(m);
    bindControlValueType(m);
    bindBaseControlValues(m);
    bindStreamIdentification(m);
    bindMilanVersion(m);
    bindProbingStatus(m);
    bindMsrpFailureCode(m);
    bindDefaultMediaClockReferencePriority(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindDescriptorType(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<DescriptorType>(m, "DescriptorType", py::arithmetic(), py::module_local())
        .value("Entity", DescriptorType::Entity)
        .value("Configuration", DescriptorType::Configuration)
        .value("AudioUnit", DescriptorType::AudioUnit)
        .value("VideoUnit", DescriptorType::VideoUnit)
        .value("SensorUnit", DescriptorType::SensorUnit)
        .value("StreamInput", DescriptorType::StreamInput)
        .value("StreamOutput", DescriptorType::StreamOutput)
        .value("JackInput", DescriptorType::JackInput)
        .value("JackOutput", DescriptorType::JackOutput)
        .value("AvbInterface", DescriptorType::AvbInterface)
        .value("ClockSource", DescriptorType::ClockSource)
        .value("MemoryObject", DescriptorType::MemoryObject)
        .value("Locale", DescriptorType::Locale)
        .value("Strings", DescriptorType::Strings)
        .value("StreamPortInput", DescriptorType::StreamPortInput)
        .value("StreamPortOutput", DescriptorType::StreamPortOutput)
        .value("ExternalPortInput", DescriptorType::ExternalPortInput)
        .value("ExternalPortOutput", DescriptorType::ExternalPortOutput)
        .value("InternalPortInput", DescriptorType::InternalPortInput)
        .value("InternalPortOutput", DescriptorType::InternalPortOutput)
        .value("AudioCluster", DescriptorType::AudioCluster)
        .value("VideoCluster", DescriptorType::VideoCluster)
        .value("SensorCluster", DescriptorType::SensorCluster)
        .value("AudioMap", DescriptorType::AudioMap)
        .value("VideoMap", DescriptorType::VideoMap)
        .value("SensorMap", DescriptorType::SensorMap)
        .value("Control", DescriptorType::Control)
        .value("SignalSelector", DescriptorType::SignalSelector)
        .value("Mixer", DescriptorType::Mixer)
        .value("Matrix", DescriptorType::Matrix)
        .value("MatrixSignal", DescriptorType::MatrixSignal)
        .value("SignalSplitter", DescriptorType::SignalSplitter)
        .value("SignalCombiner", DescriptorType::SignalCombiner)
        .value("SignalDemultiplexer", DescriptorType::SignalDemultiplexer)
        .value("SignalMultiplexer", DescriptorType::SignalMultiplexer)
        .value("SignalTranscoder", DescriptorType::SignalTranscoder)
        .value("ClockDomain", DescriptorType::ClockDomain)
        .value("ControlBlock", DescriptorType::ControlBlock)
        .value("Timing", DescriptorType::Timing)
        .value("PtpInstance", DescriptorType::PtpInstance)
        .value("PtpPort", DescriptorType::PtpPort)
        .value("Invalid", DescriptorType::Invalid)
        .def("asString", [](DescriptorType self) { return descriptorTypeToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindJackType(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<JackType>(m, "JackType", py::arithmetic(), py::module_local())
        .value("Speaker", JackType::Speaker)
        .value("Headphone", JackType::Headphone)
        .value("AnalogMicrophone", JackType::AnalogMicrophone)
        .value("Spdif", JackType::Spdif)
        .value("Adat", JackType::Adat)
        .value("Tdif", JackType::Tdif)
        .value("Madi", JackType::Madi)
        .value("UnbalancedAnalog", JackType::UnbalancedAnalog)
        .value("BalancedAnalog", JackType::BalancedAnalog)
        .value("Digital", JackType::Digital)
        .value("Midi", JackType::Midi)
        .value("AesEbu", JackType::AesEbu)
        .value("CompositeVideo", JackType::CompositeVideo)
        .value("SVhsVideo", JackType::SVhsVideo)
        .value("ComponentVideo", JackType::ComponentVideo)
        .value("Dvi", JackType::Dvi)
        .value("Hdmi", JackType::Hdmi)
        .value("Udi", JackType::Udi)
        .value("DisplayPort", JackType::DisplayPort)
        .value("Antenna", JackType::Antenna)
        .value("AnalogTuner", JackType::AnalogTuner)
        .value("Ethernet", JackType::Ethernet)
        .value("Wifi", JackType::Wifi)
        .value("Usb", JackType::Usb)
        .value("Pci", JackType::Pci)
        .value("PciE", JackType::PciE)
        .value("Scsi", JackType::Scsi)
        .value("Ata", JackType::Ata)
        .value("Imager", JackType::Imager)
        .value("Ir", JackType::Ir)
        .value("Thunderbolt", JackType::Thunderbolt)
        .value("Sata", JackType::Sata)
        .value("SmpteLtc", JackType::SmpteLtc)
        .value("DigitalMicrophone", JackType::DigitalMicrophone)
        .value("AudioMediaClock", JackType::AudioMediaClock)
        .value("VideoMediaClock", JackType::VideoMediaClock)
        .value("GnssClock", JackType::GnssClock)
        .value("Pps", JackType::Pps)
        .value("Expansion", JackType::Expansion)
        .def("asString", [](JackType self) { return jackTypeToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindClockSourceType(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<ClockSourceType>(m, "ClockSourceType", py::arithmetic(), py::module_local())
        .value("Internal", ClockSourceType::Internal)
        .value("External", ClockSourceType::External)
        .value("InputStream", ClockSourceType::InputStream)
        .value("Expansion", ClockSourceType::Expansion)
        .def("asString", [](ClockSourceType self) { return clockSourceTypeToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMemoryObjectType(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<MemoryObjectType>(m, "MemoryObjectType", py::arithmetic(), py::module_local())
        .value("FirmwareImage", MemoryObjectType::FirmwareImage)
        .value("VendorSpecific", MemoryObjectType::VendorSpecific)
        .value("CrashDump", MemoryObjectType::CrashDump)
        .value("LogObject", MemoryObjectType::LogObject)
        .value("AutostartSettings", MemoryObjectType::AutostartSettings)
        .value("SnapshotSettings", MemoryObjectType::SnapshotSettings)
        .value("SvgManufacturer", MemoryObjectType::SvgManufacturer)
        .value("SvgEntity", MemoryObjectType::SvgEntity)
        .value("SvgGeneric", MemoryObjectType::SvgGeneric)
        .value("PngManufacturer", MemoryObjectType::PngManufacturer)
        .value("PngEntity", MemoryObjectType::PngEntity)
        .value("PngGeneric", MemoryObjectType::PngGeneric)
        .value("DaeManufacturer", MemoryObjectType::DaeManufacturer)
        .value("DaeEntity", MemoryObjectType::DaeEntity)
        .value("DaeGeneric", MemoryObjectType::DaeGeneric)
        .def("asString", [](MemoryObjectType self) { return memoryObjectTypeToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMemoryObjectOperationType(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<MemoryObjectOperationType>(m, "MemoryObjectOperationType", py::arithmetic(), py::module_local())
        .value("Store", MemoryObjectOperationType::Store)
        .value("StoreAndReboot", MemoryObjectOperationType::StoreAndReboot)
        .value("Read", MemoryObjectOperationType::Read)
        .value("Erase", MemoryObjectOperationType::Erase)
        .value("Upload", MemoryObjectOperationType::Upload)
        .def("asString", [](MemoryObjectOperationType self) { return memoryObjectOperationTypeToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAudioClusterFormat(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<AudioClusterFormat>(m, "AudioClusterFormat", py::arithmetic(), py::module_local())
        .value("Iec60958", AudioClusterFormat::Iec60958)
        .value("Mbla", AudioClusterFormat::Mbla)
        .value("Midi", AudioClusterFormat::Midi)
        .value("Smpte", AudioClusterFormat::Smpte)
        .def("asString", [](AudioClusterFormat self) { return audioClusterFormatToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAudioMapping(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<AudioMapping>(m, "AudioMapping")
        .def(py::init<>())

        .def_readwrite("streamIndex", &AudioMapping::streamIndex)
        .def_readwrite("streamChannel", &AudioMapping::streamChannel)
        .def_readwrite("clusterOffset", &AudioMapping::clusterOffset)
        .def_readwrite("clusterChannel", &AudioMapping::clusterChannel)

        .def("__eq__", [](const AudioMapping& a, const AudioMapping& b) { return a == b; })
        .def("__ne__", [](const AudioMapping& a, const AudioMapping& b) { return a != b; })
        .def("__repr__",
             [](const AudioMapping& am) {
                 std::ostringstream oss;
                 oss << "AudioMapping(streamIndex=" << am.streamIndex << ", streamChannel=" << am.streamChannel << ", clusterOffset=" << am.clusterOffset
                     << ", clusterChannel=" << am.clusterChannel << ")";
                 return oss.str();
             })

        .def_property_readonly_static("size", [](const py::object&) { return AudioMapping::size(); });
}


/*-------------------------------------------------------------------------------------------------------------------*/
void bindTimingAlgorithm(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<TimingAlgorithm>(m, "TimingAlgorithm", py::arithmetic(), py::module_local())
        .value("Single", TimingAlgorithm::Single)
        .value("Fallback", TimingAlgorithm::Fallback)
        .value("Combined", TimingAlgorithm::Combined)
        .def("asString", [](TimingAlgorithm self) { return timingAlgorithmToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindPtpPortType(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<PtpPortType>(m, "PtpPortType", py::arithmetic(), py::module_local())
        .value("P2PLinkLayer", PtpPortType::P2PLinkLayer)
        .value("P2PMulticastUdpV4", PtpPortType::P2PMulticastUdpV4)
        .value("P2PMulticastUdpV6", PtpPortType::P2PMulticastUdpV6)
        .value("TimingMeasurement", PtpPortType::TimingMeasurement)
        .value("FineTimingMeasurement", PtpPortType::FineTimingMeasurement)
        .value("E2ELinkLayer", PtpPortType::E2ELinkLayer)
        .value("E2EMulticastUdpV4", PtpPortType::E2EMulticastUdpV4)
        .value("E2EMulticastUdpV6", PtpPortType::E2EMulticastUdpV6)
        .value("P2PUnicastUdpV4", PtpPortType::P2PUnicastUdpV4)
        .value("P2PUnicastUdpV6", PtpPortType::P2PUnicastUdpV6)
        .value("E2EUnicastUdpV4", PtpPortType::E2EUnicastUdpV4)
        .value("E2EUnicastUdpV6", PtpPortType::E2EUnicastUdpV6)
        .def("asString", [](PtpPortType self) { return ptpPortTypeToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStandardControlTypeVendorID(py::module_& m)
{
    using namespace la::avdecc;
    assert(UniqueIdentifierBinding.has_value());

    UniqueIdentifierBinding->def_property_readonly_static("StandardControlTypeVendorID", [](py::object) { return entity::model::StandardControlTypeVendorID; });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStandardControlType(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<StandardControlType>(m, "StandardControlType", py::arithmetic(), py::module_local())
        .value("Enable", StandardControlType::Enable)
        .value("Identify", StandardControlType::Identify)
        .value("Mute", StandardControlType::Mute)
        .value("Invert", StandardControlType::Invert)
        .value("Gain", StandardControlType::Gain)
        .value("Attenuate", StandardControlType::Attenuate)
        .value("Delay", StandardControlType::Delay)
        .value("SrcMode", StandardControlType::SrcMode)
        .value("Snapshot", StandardControlType::Snapshot)
        .value("PowLineFreq", StandardControlType::PowLineFreq)
        .value("PowerStatus", StandardControlType::PowerStatus)
        .value("FanStatus", StandardControlType::FanStatus)
        .value("Temperature", StandardControlType::Temperature)
        .value("Altitude", StandardControlType::Altitude)
        .value("AbsoluteHumidity", StandardControlType::AbsoluteHumidity)
        .value("RelativeHumidity", StandardControlType::RelativeHumidity)
        .value("Orientation", StandardControlType::Orientation)
        .value("Velocity", StandardControlType::Velocity)
        .value("Acceleration", StandardControlType::Acceleration)
        .value("FilterResponse", StandardControlType::FilterResponse)
        .value("Panpot", StandardControlType::Panpot)
        .value("Phantom", StandardControlType::Phantom)
        .value("AudioScale", StandardControlType::AudioScale)
        .value("AudioMeters", StandardControlType::AudioMeters)
        .value("AudioSpectrum", StandardControlType::AudioSpectrum)
        .value("ScanningMode", StandardControlType::ScanningMode)
        .value("AutoExpMode", StandardControlType::AutoExpMode)
        .value("AutoExpPrio", StandardControlType::AutoExpPrio)
        .value("ExpTime", StandardControlType::ExpTime)
        .value("Focus", StandardControlType::Focus)
        .value("FocusAuto", StandardControlType::FocusAuto)
        .value("Iris", StandardControlType::Iris)
        .value("Zoom", StandardControlType::Zoom)
        .value("Privacy", StandardControlType::Privacy)
        .value("Backlight", StandardControlType::Backlight)
        .value("Brightness", StandardControlType::Brightness)
        .value("Contrast", StandardControlType::Contrast)
        .value("Hue", StandardControlType::Hue)
        .value("Saturation", StandardControlType::Saturation)
        .value("Sharpness", StandardControlType::Sharpness)
        .value("Gamma", StandardControlType::Gamma)
        .value("WhiteBalTemp", StandardControlType::WhiteBalTemp)
        .value("WhiteBalTempAuto", StandardControlType::WhiteBalTempAuto)
        .value("WhiteBalComp", StandardControlType::WhiteBalComp)
        .value("WhiteBalCompAuto", StandardControlType::WhiteBalCompAuto)
        .value("DigitalZoom", StandardControlType::DigitalZoom)
        .value("MediaPlaylist", StandardControlType::MediaPlaylist)
        .value("MediaPlaylistName", StandardControlType::MediaPlaylistName)
        .value("MediaDisk", StandardControlType::MediaDisk)
        .value("MediaDiskName", StandardControlType::MediaDiskName)
        .value("MediaTrack", StandardControlType::MediaTrack)
        .value("MediaTrackName", StandardControlType::MediaTrackName)
        .value("MediaSpeed", StandardControlType::MediaSpeed)
        .value("MediaSamplePosition", StandardControlType::MediaSamplePosition)
        .value("MediaPlaybackTransport", StandardControlType::MediaPlaybackTransport)
        .value("MediaRecordTransport", StandardControlType::MediaRecordTransport)
        .value("Frequency", StandardControlType::Frequency)
        .value("Modulation", StandardControlType::Modulation)
        .value("Polarization", StandardControlType::Polarization)
        .def("asString", [](StandardControlType self) { return standardControlTypeToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMsrpMapping(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<MsrpMapping>(m, "MsrpMapping")
        .def(py::init<>())

        .def_readwrite("trafficClass", &MsrpMapping::trafficClass)
        .def_readwrite("priority", &MsrpMapping::priority)
        .def_readwrite("vlanID", &MsrpMapping::vlanID)

        .def("__eq__", [](const MsrpMapping& a, const MsrpMapping& b) { return a == b; })
        .def("__ne__", [](const MsrpMapping& a, const MsrpMapping& b) { return a != b; })

        .def("__repr__",
             [](const MsrpMapping& m) {
                 std::ostringstream oss;
                 oss << "MsrpMapping(trafficClass=" << static_cast<int>(m.trafficClass) << ", priority=" << static_cast<int>(m.priority)
                     << ", vlanID=" << m.vlanID << ")";
                 return oss.str();
             })

        .def_property_readonly_static("size", [](const py::object&) { return MsrpMapping::size(); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAvdeccFixedString(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<AvdeccFixedString>(m, "AvdeccFixedString")
        .def(py::init<>())
        .def(py::init<std::string const&>(), py::arg("string"))
        .def(py::init([](py::bytes raw, size_t size) {
                 std::string buffer = raw;
                 return AvdeccFixedString(static_cast<const void*>(buffer.data()), size);
             }),
             py::arg("data"), py::arg("size"))

        .def("assign", static_cast<void (AvdeccFixedString::*)(std::string const&)>(&AvdeccFixedString::assign), py::arg("string"))
        .def(
            "assignRaw",
            [](AvdeccFixedString& self, py::bytes raw, size_t size) {
                std::string buffer = raw;
                self.assign(static_cast<const void*>(buffer.data()), size);
            },
            py::arg("data"), py::arg("size"))

        .def_property_readonly("size", &AvdeccFixedString::size)
        .def_property_readonly("empty", &AvdeccFixedString::empty)
        .def_property_readonly("data", [](const AvdeccFixedString& self) { return py::bytes(self.data(), self.size()); })

        .def("__getitem__",
             [](const AvdeccFixedString& self, size_t i) {
                 if (i >= self.size())
                     throw py::index_error();
                 return self[i];
             })

        .def("__str__", [](const AvdeccFixedString& self) { return self.str(); })
        .def("__repr__",
             [](const AvdeccFixedString& self) {
                 std::ostringstream oss;
                 oss << "AvdeccFixedString(\"" << self.str() << "\")";
                 return oss.str();
             })

        .def("__eq__", [](const AvdeccFixedString& self, const AvdeccFixedString& other) { return self == other; })
        .def("__eq__", [](const AvdeccFixedString& self, const std::string& other) { return self == other; })
        .def("__ne__", [](const AvdeccFixedString& self, const AvdeccFixedString& other) { return self != other; })
        .def("__ne__", [](const AvdeccFixedString& self, const std::string& other) { return self != other; });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindSamplingRate(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<SamplingRate>(m, "SamplingRate")
        .def(py::init<>())
        .def(py::init<SamplingRate::value_type>(), py::arg("value"))
        .def(py::init<std::uint8_t, std::uint32_t>(), py::arg("pull"), py::arg("baseFrequency"))

        .def("setValue", &SamplingRate::setValue)
        .def("getValue", &SamplingRate::getValue)
        .def("getNominalSampleRate", &SamplingRate::getNominalSampleRate)
        .def("getPullBaseFrequency", &SamplingRate::getPullBaseFrequency)
        .def("getPull", &SamplingRate::getPull)
        .def("getBaseFrequency", &SamplingRate::getBaseFrequency)
        .def_property_readonly("isValid", &SamplingRate::isValid)

        .def_static("getNullSamplingRate", &SamplingRate::getNullSamplingRate)

        .def("__eq__", [](const SamplingRate& self, const SamplingRate& other) { return self == other; })
        .def("__ne__", [](const SamplingRate& self, const SamplingRate& other) { return self != other; })
        .def("__lt__", [](const SamplingRate& self, const SamplingRate& other) { return self < other; })
        .def("__int__", [](const SamplingRate& s) { return static_cast<SamplingRate::value_type>(s); })

        .def("__repr__", [](const SamplingRate& s) {
            std::ostringstream oss;
            oss << "SamplingRate(" << std::hex << s.getValue() << ")";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamFormat(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<StreamFormat>(m, "StreamFormat")
        .def(py::init<>())
        .def(py::init<StreamFormat::value_type>(), py::arg("value"))

        .def("setValue", &StreamFormat::setValue)
        .def("getValue", &StreamFormat::getValue)
        .def_property_readonly("isValid", &StreamFormat::isValid)

        .def_static("getNullStreamFormat", &StreamFormat::getNullStreamFormat)

        .def("__eq__", [](const StreamFormat& self, const StreamFormat& other) { return self == other; })
        .def("__ne__", [](const StreamFormat& self, const StreamFormat& other) { return self != other; })
        .def("__lt__", [](const StreamFormat& self, const StreamFormat& other) { return self < other; })
        .def("__int__", [](const StreamFormat& s) { return static_cast<StreamFormat::value_type>(s); })

        .def("__repr__", [](const StreamFormat& s) {
            std::ostringstream oss;
            oss << "StreamFormat(" << std::hex << s.getValue() << ")";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindLocalizedStringReference(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<LocalizedStringReference>(m, "LocalizedStringReference")
        .def(py::init<>())
        .def(py::init<LocalizedStringReference::value_type>(), py::arg("value"))
        .def(py::init<std::uint16_t, std::uint8_t>(), py::arg("offset"), py::arg("index"))

        .def("setValue", &LocalizedStringReference::setValue)
        .def("getValue", &LocalizedStringReference::getValue)
        .def("getGlobalOffset", &LocalizedStringReference::getGlobalOffset)
        .def("setOffsetIndex", &LocalizedStringReference::setOffsetIndex)
        .def("getOffsetIndex", &LocalizedStringReference::getOffsetIndex)
        .def_property_readonly("isValid", &LocalizedStringReference::isValid)

        .def_static("getNullLocalizedStringReference", &LocalizedStringReference::getNullLocalizedStringReference)

        .def("__eq__", [](const LocalizedStringReference& self, const LocalizedStringReference& other) { return self == other; })
        .def("__ne__", [](const LocalizedStringReference& self, const LocalizedStringReference& other) { return self != other; })
        .def("__lt__", [](const LocalizedStringReference& self, const LocalizedStringReference& other) { return self < other; })
        .def("__int__", [](const LocalizedStringReference& r) { return static_cast<LocalizedStringReference::value_type>(r); })

        .def("__repr__", [](const LocalizedStringReference& r) {
            std::ostringstream oss;
            if (r.isValid())
            {
                auto [offset, index] = r.getOffsetIndex();
                oss << "LocalizedStringReference(offset=" << offset << ", index=" << static_cast<int>(index) << ")";
            }
            else
            {
                oss << "LocalizedStringReference(<invalid>)";
            }
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindControlValueUnit(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    auto cls = py::class_<ControlValueUnit>(m, "ControlValueUnit");

    py::enum_<ControlValueUnit::Unit>(cls, "UnitDefs")
        .value("Unitless", ControlValueUnit::Unit::Unitless)
        .value("Count", ControlValueUnit::Unit::Count)
        .value("Percent", ControlValueUnit::Unit::Percent)
        .value("FStop", ControlValueUnit::Unit::FStop)
        .value("Seconds", ControlValueUnit::Unit::Seconds)
        .value("Minutes", ControlValueUnit::Unit::Minutes)
        .value("Hours", ControlValueUnit::Unit::Hours)
        .value("Days", ControlValueUnit::Unit::Days)
        .value("Months", ControlValueUnit::Unit::Months)
        .value("Years", ControlValueUnit::Unit::Years)
        .value("Samples", ControlValueUnit::Unit::Samples)
        .value("Frames", ControlValueUnit::Unit::Frames)
        .value("Hertz", ControlValueUnit::Unit::Hertz)
        .value("Semitones", ControlValueUnit::Unit::Semitones)
        .value("Cents", ControlValueUnit::Unit::Cents)
        .value("Octaves", ControlValueUnit::Unit::Octaves)
        .value("Fps", ControlValueUnit::Unit::Fps)
        .value("Metres", ControlValueUnit::Unit::Metres)
        .value("Kelvin", ControlValueUnit::Unit::Kelvin)
        .value("Grams", ControlValueUnit::Unit::Grams)
        .value("Volts", ControlValueUnit::Unit::Volts)
        .value("Dbv", ControlValueUnit::Unit::Dbv)
        .value("Dbu", ControlValueUnit::Unit::Dbu)
        .value("Amps", ControlValueUnit::Unit::Amps)
        .value("Watts", ControlValueUnit::Unit::Watts)
        .value("Dbm", ControlValueUnit::Unit::Dbm)
        .value("Dbw", ControlValueUnit::Unit::Dbw)
        .value("Pascals", ControlValueUnit::Unit::Pascals)
        .value("Bits", ControlValueUnit::Unit::Bits)
        .value("Bytes", ControlValueUnit::Unit::Bytes)
        .value("KibiBytes", ControlValueUnit::Unit::KibiBytes)
        .value("MebiBytes", ControlValueUnit::Unit::MebiBytes)
        .value("GibiBytes", ControlValueUnit::Unit::GibiBytes)
        .value("TebiBytes", ControlValueUnit::Unit::TebiBytes)
        .value("BitsPerSec", ControlValueUnit::Unit::BitsPerSec)
        .value("BytesPerSec", ControlValueUnit::Unit::BytesPerSec)
        .value("KibiBytesPerSec", ControlValueUnit::Unit::KibiBytesPerSec)
        .value("MebiBytesPerSec", ControlValueUnit::Unit::MebiBytesPerSec)
        .value("GibiBytesPerSec", ControlValueUnit::Unit::GibiBytesPerSec)
        .value("TebiBytesPerSec", ControlValueUnit::Unit::TebiBytesPerSec)
        .value("Candelas", ControlValueUnit::Unit::Candelas)
        .value("Joules", ControlValueUnit::Unit::Joules)
        .value("Radians", ControlValueUnit::Unit::Radians)
        .value("Newtons", ControlValueUnit::Unit::Newtons)
        .value("Ohms", ControlValueUnit::Unit::Ohms)
        .value("MetresPerSec", ControlValueUnit::Unit::MetresPerSec)
        .value("RadiansPerSec", ControlValueUnit::Unit::RadiansPerSec)
        .value("MetresPerSecSquared", ControlValueUnit::Unit::MetresPerSecSquared)
        .value("RadiansPerSecSquared", ControlValueUnit::Unit::RadiansPerSecSquared)
        .value("Teslas", ControlValueUnit::Unit::Teslas)
        .value("Webers", ControlValueUnit::Unit::Webers)
        .value("AmpsPerMetre", ControlValueUnit::Unit::AmpsPerMetre)
        .value("MetresSquared", ControlValueUnit::Unit::MetresSquared)
        .value("MetresCubed", ControlValueUnit::Unit::MetresCubed)
        .value("Litres", ControlValueUnit::Unit::Litres)
        .value("Db", ControlValueUnit::Unit::Db)
        .value("DbPeak", ControlValueUnit::Unit::DbPeak)
        .value("DbRms", ControlValueUnit::Unit::DbRms)
        .value("Dbfs", ControlValueUnit::Unit::Dbfs)
        .value("DbfsPeak", ControlValueUnit::Unit::DbfsPeak)
        .value("DbfsRms", ControlValueUnit::Unit::DbfsRms)
        .value("Dbtp", ControlValueUnit::Unit::Dbtp)
        .value("DbSplA", ControlValueUnit::Unit::DbSplA)
        .value("DbZ", ControlValueUnit::Unit::DbZ)
        .value("DbSplC", ControlValueUnit::Unit::DbSplC)
        .value("DbSpl", ControlValueUnit::Unit::DbSpl)
        .value("Lu", ControlValueUnit::Unit::Lu)
        .value("Lufs", ControlValueUnit::Unit::Lufs)
        .value("DbA", ControlValueUnit::Unit::DbA)
        .def("asString", [](ControlValueUnit::Unit self) { return controlValueUnitToString(self); });

    cls.def(py::init<>())
        .def(py::init<ControlValueUnit::value_type>(), py::arg("value"))
        .def(py::init<std::int8_t, ControlValueUnit::Unit>(), py::arg("multiplier"), py::arg("unit"))

        .def("setValue", &ControlValueUnit::setValue)
        .def("getValue", &ControlValueUnit::getValue)
        .def("getMultiplier", &ControlValueUnit::getMultiplier)
        .def("getUnit", &ControlValueUnit::getUnit)
        .def("setMultiplierUnit", &ControlValueUnit::setMultiplierUnit)
        .def("getMultiplierUnit", &ControlValueUnit::getMultiplierUnit)

        .def("__eq__", [](const ControlValueUnit& self, const ControlValueUnit& other) { return self == other; })
        .def("__ne__", [](const ControlValueUnit& self, const ControlValueUnit& other) { return self != other; })
        .def("__lt__", [](const ControlValueUnit& self, const ControlValueUnit& other) { return self < other; })
        .def("__int__", [](const ControlValueUnit& u) { return static_cast<ControlValueUnit::value_type>(u); })

        .def("__repr__", [](const ControlValueUnit& u) {
            std::ostringstream oss;
            auto [mult, unit] = u.getMultiplierUnit();
            oss << "ControlValueUnit(multiplier=" << static_cast<int>(mult) << ", unit=" << static_cast<std::uint16_t>(unit) << ")";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindControlValueType(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    auto cls = py::class_<ControlValueType>(m, "ControlValueType");

    py::enum_<ControlValueType::Type>(cls, "TypeDefs")
        .value("ControlLinearInt8", ControlValueType::Type::ControlLinearInt8)
        .value("ControlLinearUInt8", ControlValueType::Type::ControlLinearUInt8)
        .value("ControlLinearInt16", ControlValueType::Type::ControlLinearInt16)
        .value("ControlLinearUInt16", ControlValueType::Type::ControlLinearUInt16)
        .value("ControlLinearInt32", ControlValueType::Type::ControlLinearInt32)
        .value("ControlLinearUInt32", ControlValueType::Type::ControlLinearUInt32)
        .value("ControlLinearInt64", ControlValueType::Type::ControlLinearInt64)
        .value("ControlLinearUInt64", ControlValueType::Type::ControlLinearUInt64)
        .value("ControlLinearFloat", ControlValueType::Type::ControlLinearFloat)
        .value("ControlLinearDouble", ControlValueType::Type::ControlLinearDouble)
        .value("ControlSelectorInt8", ControlValueType::Type::ControlSelectorInt8)
        .value("ControlSelectorUInt8", ControlValueType::Type::ControlSelectorUInt8)
        .value("ControlSelectorInt16", ControlValueType::Type::ControlSelectorInt16)
        .value("ControlSelectorUInt16", ControlValueType::Type::ControlSelectorUInt16)
        .value("ControlSelectorInt32", ControlValueType::Type::ControlSelectorInt32)
        .value("ControlSelectorUInt32", ControlValueType::Type::ControlSelectorUInt32)
        .value("ControlSelectorInt64", ControlValueType::Type::ControlSelectorInt64)
        .value("ControlSelectorUInt64", ControlValueType::Type::ControlSelectorUInt64)
        .value("ControlSelectorFloat", ControlValueType::Type::ControlSelectorFloat)
        .value("ControlSelectorDouble", ControlValueType::Type::ControlSelectorDouble)
        .value("ControlSelectorString", ControlValueType::Type::ControlSelectorString)
        .value("ControlArrayInt8", ControlValueType::Type::ControlArrayInt8)
        .value("ControlArrayUInt8", ControlValueType::Type::ControlArrayUInt8)
        .value("ControlArrayInt16", ControlValueType::Type::ControlArrayInt16)
        .value("ControlArrayUInt16", ControlValueType::Type::ControlArrayUInt16)
        .value("ControlArrayInt32", ControlValueType::Type::ControlArrayInt32)
        .value("ControlArrayUInt32", ControlValueType::Type::ControlArrayUInt32)
        .value("ControlArrayInt64", ControlValueType::Type::ControlArrayInt64)
        .value("ControlArrayUInt64", ControlValueType::Type::ControlArrayUInt64)
        .value("ControlArrayFloat", ControlValueType::Type::ControlArrayFloat)
        .value("ControlArrayDouble", ControlValueType::Type::ControlArrayDouble)
        .value("ControlUtf8", ControlValueType::Type::ControlUtf8)
        .value("ControlBodePlot", ControlValueType::Type::ControlBodePlot)
        .value("ControlSmpteTime", ControlValueType::Type::ControlSmpteTime)
        .value("ControlSampleRate", ControlValueType::Type::ControlSampleRate)
        .value("ControlGptpTime", ControlValueType::Type::ControlGptpTime)
        .value("ControlVendor", ControlValueType::Type::ControlVendor)
        .value("Expansion", ControlValueType::Type::Expansion)
        .def("asString", [](ControlValueType::Type self) { return controlValueTypeToString(self); });

    cls.def(py::init<>())
        .def(py::init<ControlValueType::value_type>(), py::arg("value"))
        .def(py::init<bool, bool, ControlValueType::Type>(), py::arg("isReadOnly"), py::arg("isUnknown"), py::arg("type"))

        .def("setValue", &ControlValueType::setValue)
        .def("getValue", &ControlValueType::getValue)
        .def_property_readonly("isReadOnly", &ControlValueType::isReadOnly)
        .def_property_readonly("isUnknown", &ControlValueType::isUnknown)
        .def("getType", &ControlValueType::getType)
        .def("setReadOnlyUnknownType", &ControlValueType::setReadOnlyUnknownType)

        .def("__eq__", [](const ControlValueType& self, const ControlValueType& other) { return self == other; })
        .def("__ne__", [](const ControlValueType& self, const ControlValueType& other) { return self != other; })
        .def("__lt__", [](const ControlValueType& self, const ControlValueType& other) { return self < other; })
        .def("__int__", [](const ControlValueType& v) { return static_cast<ControlValueType::value_type>(v); })

        .def("__repr__", [](const ControlValueType& v) {
            std::ostringstream oss;
            oss << "ControlValueType(readOnly=" << v.isReadOnly() << ", unknown=" << v.isUnknown() << ", type=" << controlValueTypeToString(v.getType()) << ")";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindBaseControlValues(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<ControlValues> cls(m, "ControlValues");

    cls.def(py::init<>())
        .def("getType", &ControlValues::getType)
        .def("areDynamicValues", &ControlValues::areDynamicValues)
        .def("countMustBeIdentical", &ControlValues::countMustBeIdentical)
        .def_property_readonly("size", &ControlValues::size)
        .def_property_readonly("empty", &ControlValues::empty)
        .def_property_readonly("isValid", &ControlValues::isValid)
        .def("__repr__", [](const ControlValues& c) {
            std::ostringstream oss;
            oss << "ControlValues(valid=" << c.isValid() << ", type=" << static_cast<int>(c.getType()) << ", size=" << c.size() << ")";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamIdentification(py::module_& m)
{
    using namespace la::avdecc;

    py::class_<entity::model::StreamIdentification>(m, "StreamIdentification")
        .def(py::init<>())
        .def_readwrite("entityID", &entity::model::StreamIdentification::entityID)
        .def_readwrite("streamIndex", &entity::model::StreamIdentification::streamIndex)

        .def("__eq__", [](const entity::model::StreamIdentification& self, const entity::model::StreamIdentification& other) { return self == other; })
        .def("__ne__", [](const entity::model::StreamIdentification& self, const entity::model::StreamIdentification& other) { return self != other; })
        .def("__lt__", [](const entity::model::StreamIdentification& self, const entity::model::StreamIdentification& other) { return self < other; })

        .def("__repr__", [](const entity::model::StreamIdentification& id) {
            std::ostringstream oss;
            oss << "StreamIdentification(entityID=" << id.entityID.getValue() << ", streamIndex=" << id.streamIndex << ")";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMilanVersion(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<MilanVersion>(m, "MilanVersion")
        .def(py::init<>())
        .def(py::init<MilanVersion::value_type>(), py::arg("value"))
        .def(py::init<MilanVersion::digit_type, MilanVersion::digit_type, MilanVersion::digit_type, MilanVersion::digit_type>(), py::arg("majorVersion"),
             py::arg("minorVersion"), py::arg("patchVersion") = 0, py::arg("buildVersion") = 0)
        .def(py::init<const std::string&>(), py::arg("version"))

        .def("setValue", &MilanVersion::setValue)
        .def("getValue", &MilanVersion::getValue)
        .def("getMajorVersion", &MilanVersion::getMajorVersion)
        .def("getMinorVersion", &MilanVersion::getMinorVersion)
        .def("getPatchVersion", &MilanVersion::getPatchVersion)
        .def("getBuildVersion", &MilanVersion::getBuildVersion)

        .def("to_string", &MilanVersion::to_string, py::arg("digits") = 4)

        .def("__eq__", [](const MilanVersion& self, const MilanVersion& other) { return self == other; })
        .def("__ne__", [](const MilanVersion& self, const MilanVersion& other) { return self != other; })
        .def("__lt__", [](const MilanVersion& self, const MilanVersion& other) { return self < other; })
        .def("__le__", [](const MilanVersion& self, const MilanVersion& other) { return self <= other; })
        .def("__gt__", [](const MilanVersion& self, const MilanVersion& other) { return self > other; })
        .def("__ge__", [](const MilanVersion& self, const MilanVersion& other) { return self >= other; })

        .def("__int__", [](const MilanVersion& v) { return v.getValue(); })
        .def("__str__", [](const MilanVersion& v) { return v.to_string(); })
        .def("__repr__", [](const MilanVersion& v) {
            std::ostringstream oss;
            oss << "MilanVersion(" << v.to_string() << ")";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindProbingStatus(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<ProbingStatus>(m, "ProbingStatus")
        .value("Disabled", ProbingStatus::Disabled, "The sink is not probing because it is not bound.")
        .value("Passive", ProbingStatus::Passive, "The sink is probing passively.")
        .value("Active", ProbingStatus::Active, "The sink is probing actively.")
        .value("Completed", ProbingStatus::Completed, "The sink is not probing because it is settled.");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMsrpFailureCode(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<MsrpFailureCode>(m, "MsrpFailureCode")
        .value("NoFailure", MsrpFailureCode::NoFailure)
        .value("InsufficientBandwidth", MsrpFailureCode::InsufficientBandwidth)
        .value("InsufficientResources", MsrpFailureCode::InsufficientResources)
        .value("InsufficientTrafficClassBandwidth", MsrpFailureCode::InsufficientTrafficClassBandwidth)
        .value("StreamIDInUse", MsrpFailureCode::StreamIDInUse)
        .value("StreamDestinationAddressInUse", MsrpFailureCode::StreamDestinationAddressInUse)
        .value("StreamPreemptedByHigherRank", MsrpFailureCode::StreamPreemptedByHigherRank)
        .value("LatencyHasChanged", MsrpFailureCode::LatencyHasChanged)
        .value("EgressPortNotAVBCapable", MsrpFailureCode::EgressPortNotAVBCapable)
        .value("UseDifferentDestinationAddress", MsrpFailureCode::UseDifferentDestinationAddress)
        .value("OutOfMSRPResources", MsrpFailureCode::OutOfMSRPResources)
        .value("OutOfMMRPResources", MsrpFailureCode::OutOfMMRPResources)
        .value("CannotStoreDestinationAddress", MsrpFailureCode::CannotStoreDestinationAddress)
        .value("PriorityIsNotAnSRClass", MsrpFailureCode::PriorityIsNotAnSRClass)
        .value("MaxFrameSizeTooLarge", MsrpFailureCode::MaxFrameSizeTooLarge)
        .value("MaxFanInPortsLimitReached", MsrpFailureCode::MaxFanInPortsLimitReached)
        .value("FirstValueChangedForStreamID", MsrpFailureCode::FirstValueChangedForStreamID)
        .value("VlanBlockedOnEgress", MsrpFailureCode::VlanBlockedOnEgress)
        .value("VlanTaggingDisabledOnEgress", MsrpFailureCode::VlanTaggingDisabledOnEgress)
        .value("SrClassPriorityMismatch", MsrpFailureCode::SrClassPriorityMismatch)
        .def("asString", [](MsrpFailureCode self) { return msrpFailureCodeToString(self); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindDefaultMediaClockReferencePriority(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::enum_<DefaultMediaClockReferencePriority>(m, "DefaultMediaClockReferencePriority")
        .value("Highest", DefaultMediaClockReferencePriority::Highest, "Highest priority")
        .value("DedicatedGenerators", DefaultMediaClockReferencePriority::DedicatedGenerators, "Dedicated media clock reference generators")
        .value("MatrixMixingDevices", DefaultMediaClockReferencePriority::MatrixMixingDevices,
               "Matrix mixing devices, signal routers, network switches with central audio processing capability")
        .value("MixingConsoles", DefaultMediaClockReferencePriority::MixingConsoles, "Mixing consoles")
        .value("Stageboxes", DefaultMediaClockReferencePriority::Stageboxes, "Stageboxes, audio interfaces")
        .value("Processors", DefaultMediaClockReferencePriority::Processors, "Loudspeaker processors")
        .value("Amplifiers", DefaultMediaClockReferencePriority::Amplifiers, "Amplifiers, powered loudspeakers, in-ear transmitters")
        .value("RecordingDevices", DefaultMediaClockReferencePriority::RecordingDevices, "Recording devices")
        .value("Default", DefaultMediaClockReferencePriority::Default, "Default (if the device provides no data, this is taken as its priority)")
        .value("EffectProcessingDevices", DefaultMediaClockReferencePriority::EffectProcessingDevices, "Effect processing devices")
        .value("WirelessReceivers", DefaultMediaClockReferencePriority::WirelessReceivers, "Wireless receivers")
        .value("Microphones", DefaultMediaClockReferencePriority::Microphones, "Microphones")
        .value("Instruments", DefaultMediaClockReferencePriority::Instruments, "Instruments")
        .value("Lowest", DefaultMediaClockReferencePriority::Lowest, "Lowest priority")
        .def("asString", [](DefaultMediaClockReferencePriority self) { return defaultMediaClockReferencePriorityToString(self); });
}
