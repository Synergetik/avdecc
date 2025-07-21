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
 * @file avdecc_entity_model_python.cpp
 * @author Vitalij Mast
 */

#include "avdecc_entity_python.hpp"

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityDescriptor(py::module_& m);
void bindConfigurationDescriptor(py::module_& m);
void bindAudioUnitDescriptor(py::module_& m);
void bindStreamDescriptor(py::module_& m);
void bindJackDescriptor(py::module_& m);
void bindAvbInterfaceDescriptor(py::module_& m);
void bindClockSourceDescriptor(py::module_& m);
void bindMemoryObjectDescriptor(py::module_& m);
void bindLocaleDescriptor(py::module_& m);
void bindStringsDescriptor(py::module_& m);
void bindStreamPortDescriptor(py::module_& m);
void bindExternalPortDescriptor(py::module_& m);
void bindInternalPortDescriptor(py::module_& m);
void bindAudioClusterDescriptor(py::module_& m);
void bindAudioMapDescriptor(py::module_& m);
void bindControlDescriptor(py::module_& m);
void bindClockDomainDescriptor(py::module_& m);
void bindTimingDescriptor(py::module_& m);
void bindPtpInstanceDescriptor(py::module_& m);
void bindPtpPortDescriptor(py::module_& m);
void bindStreamInfo(py::module_& m);
void bindAvbInfo(py::module_& m);
void bindAsPath(py::module_& m);
void bindMilanInfo(py::module_& m);
void bindMilanDynamicState(py::module_& m);
void bindMediaClockReferenceInfo(py::module_& m);
void bindEntityModelUniqueIdentifierExtensions(py::module_& m);
void bindStreamFormatInfo(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityModel(py::module_& m)
{
    // la/avdecc/internals/entityModel.hpp
    bindEntityDescriptor(m);
    bindConfigurationDescriptor(m);
    bindAudioUnitDescriptor(m);
    bindStreamDescriptor(m);
    bindJackDescriptor(m);
    bindAvbInterfaceDescriptor(m);
    bindClockSourceDescriptor(m);
    bindMemoryObjectDescriptor(m);
    bindLocaleDescriptor(m);
    bindStringsDescriptor(m);
    bindStreamPortDescriptor(m);
    bindExternalPortDescriptor(m);
    bindInternalPortDescriptor(m);
    bindAudioClusterDescriptor(m);
    bindAudioMapDescriptor(m);
    bindControlDescriptor(m);
    bindClockDomainDescriptor(m);
    bindTimingDescriptor(m);
    bindPtpInstanceDescriptor(m);
    bindPtpPortDescriptor(m);
    bindStreamInfo(m);
    bindAvbInfo(m);
    bindAsPath(m);
    bindMilanInfo(m);
    bindMilanDynamicState(m);
    bindMediaClockReferenceInfo(m);
    bindEntityModelUniqueIdentifierExtensions(m);

    // la/avdecc/internals/streamFormatInfo.hpp
    bindStreamFormatInfo(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<EntityDescriptor>(m, "EntityDescriptor")
        .def(py::init<>())
        .def_readwrite("entityID", &EntityDescriptor::entityID)
        .def_readwrite("entityModelID", &EntityDescriptor::entityModelID)
        .def_readwrite("entityCapabilities", &EntityDescriptor::entityCapabilities)
        .def_readwrite("talkerStreamSources", &EntityDescriptor::talkerStreamSources)
        .def_readwrite("talkerCapabilities", &EntityDescriptor::talkerCapabilities)
        .def_readwrite("listenerStreamSinks", &EntityDescriptor::listenerStreamSinks)
        .def_readwrite("listenerCapabilities", &EntityDescriptor::listenerCapabilities)
        .def_readwrite("controllerCapabilities", &EntityDescriptor::controllerCapabilities)
        .def_readwrite("availableIndex", &EntityDescriptor::availableIndex)
        .def_readwrite("associationID", &EntityDescriptor::associationID)
        .def_readwrite("entityName", &EntityDescriptor::entityName)
        .def_readwrite("vendorNameString", &EntityDescriptor::vendorNameString)
        .def_readwrite("modelNameString", &EntityDescriptor::modelNameString)
        .def_readwrite("firmwareVersion", &EntityDescriptor::firmwareVersion)
        .def_readwrite("groupName", &EntityDescriptor::groupName)
        .def_readwrite("serialNumber", &EntityDescriptor::serialNumber)
        .def_readwrite("configurationsCount", &EntityDescriptor::configurationsCount)
        .def_readwrite("currentConfiguration", &EntityDescriptor::currentConfiguration)
        .def("__repr__", [](const EntityDescriptor& self) {
            std::ostringstream oss;
            oss << "<EntityDescriptor "
                << "entityID=" << self.entityID << ", entityName='" << self.entityName << "', firmwareVersion='" << self.firmwareVersion << "', serialNumber='"
                << self.serialNumber << "'>";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindConfigurationDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<ConfigurationDescriptor>(m, "ConfigurationDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &ConfigurationDescriptor::objectName)
        .def_readwrite("localizedDescription", &ConfigurationDescriptor::localizedDescription)
        .def_readwrite("descriptorCounts", &ConfigurationDescriptor::descriptorCounts)
        .def("__repr__", [](const ConfigurationDescriptor& self) {
            std::ostringstream oss;
            oss << "<ConfigurationDescriptor "
                << "objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAudioUnitDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<AudioUnitDescriptor>(m, "AudioUnitDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &AudioUnitDescriptor::objectName)
        .def_readwrite("localizedDescription", &AudioUnitDescriptor::localizedDescription)
        .def_readwrite("clockDomainIndex", &AudioUnitDescriptor::clockDomainIndex)
        .def_readwrite("numberOfStreamInputPorts", &AudioUnitDescriptor::numberOfStreamInputPorts)
        .def_readwrite("baseStreamInputPort", &AudioUnitDescriptor::baseStreamInputPort)
        .def_readwrite("numberOfStreamOutputPorts", &AudioUnitDescriptor::numberOfStreamOutputPorts)
        .def_readwrite("baseStreamOutputPort", &AudioUnitDescriptor::baseStreamOutputPort)
        .def_readwrite("numberOfExternalInputPorts", &AudioUnitDescriptor::numberOfExternalInputPorts)
        .def_readwrite("baseExternalInputPort", &AudioUnitDescriptor::baseExternalInputPort)
        .def_readwrite("numberOfExternalOutputPorts", &AudioUnitDescriptor::numberOfExternalOutputPorts)
        .def_readwrite("baseExternalOutputPort", &AudioUnitDescriptor::baseExternalOutputPort)
        .def_readwrite("numberOfInternalInputPorts", &AudioUnitDescriptor::numberOfInternalInputPorts)
        .def_readwrite("baseInternalInputPort", &AudioUnitDescriptor::baseInternalInputPort)
        .def_readwrite("numberOfInternalOutputPorts", &AudioUnitDescriptor::numberOfInternalOutputPorts)
        .def_readwrite("baseInternalOutputPort", &AudioUnitDescriptor::baseInternalOutputPort)
        .def_readwrite("numberOfControls", &AudioUnitDescriptor::numberOfControls)
        .def_readwrite("baseControl", &AudioUnitDescriptor::baseControl)
        .def_readwrite("numberOfSignalSelectors", &AudioUnitDescriptor::numberOfSignalSelectors)
        .def_readwrite("baseSignalSelector", &AudioUnitDescriptor::baseSignalSelector)
        .def_readwrite("numberOfMixers", &AudioUnitDescriptor::numberOfMixers)
        .def_readwrite("baseMixer", &AudioUnitDescriptor::baseMixer)
        .def_readwrite("numberOfMatrices", &AudioUnitDescriptor::numberOfMatrices)
        .def_readwrite("baseMatrix", &AudioUnitDescriptor::baseMatrix)
        .def_readwrite("numberOfSplitters", &AudioUnitDescriptor::numberOfSplitters)
        .def_readwrite("baseSplitter", &AudioUnitDescriptor::baseSplitter)
        .def_readwrite("numberOfCombiners", &AudioUnitDescriptor::numberOfCombiners)
        .def_readwrite("baseCombiner", &AudioUnitDescriptor::baseCombiner)
        .def_readwrite("numberOfDemultiplexers", &AudioUnitDescriptor::numberOfDemultiplexers)
        .def_readwrite("baseDemultiplexer", &AudioUnitDescriptor::baseDemultiplexer)
        .def_readwrite("numberOfMultiplexers", &AudioUnitDescriptor::numberOfMultiplexers)
        .def_readwrite("baseMultiplexer", &AudioUnitDescriptor::baseMultiplexer)
        .def_readwrite("numberOfTranscoders", &AudioUnitDescriptor::numberOfTranscoders)
        .def_readwrite("baseTranscoder", &AudioUnitDescriptor::baseTranscoder)
        .def_readwrite("numberOfControlBlocks", &AudioUnitDescriptor::numberOfControlBlocks)
        .def_readwrite("baseControlBlock", &AudioUnitDescriptor::baseControlBlock)
        .def_readwrite("currentSamplingRate", &AudioUnitDescriptor::currentSamplingRate)
        .def_readwrite("samplingRates", &AudioUnitDescriptor::samplingRates)
        .def("__repr__", [](const AudioUnitDescriptor& self) {
            std::ostringstream oss;
            oss << "<AudioUnitDescriptor "
                << "objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<StreamDescriptor>(m, "StreamDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &StreamDescriptor::objectName)
        .def_readwrite("localizedDescription", &StreamDescriptor::localizedDescription)
        .def_readwrite("clockDomainIndex", &StreamDescriptor::clockDomainIndex)
        .def_readwrite("streamFlags", &StreamDescriptor::streamFlags)
        .def_readwrite("currentFormat", &StreamDescriptor::currentFormat)
        .def_readwrite("backupTalkerEntityID_0", &StreamDescriptor::backupTalkerEntityID_0)
        .def_readwrite("backupTalkerUniqueID_0", &StreamDescriptor::backupTalkerUniqueID_0)
        .def_readwrite("backupTalkerEntityID_1", &StreamDescriptor::backupTalkerEntityID_1)
        .def_readwrite("backupTalkerUniqueID_1", &StreamDescriptor::backupTalkerUniqueID_1)
        .def_readwrite("backupTalkerEntityID_2", &StreamDescriptor::backupTalkerEntityID_2)
        .def_readwrite("backupTalkerUniqueID_2", &StreamDescriptor::backupTalkerUniqueID_2)
        .def_readwrite("backedupTalkerEntityID", &StreamDescriptor::backedupTalkerEntityID)
        .def_readwrite("backedupTalkerUnique", &StreamDescriptor::backedupTalkerUnique)
        .def_readwrite("avbInterfaceIndex", &StreamDescriptor::avbInterfaceIndex)
        .def_readwrite("bufferLength", &StreamDescriptor::bufferLength)
        .def_readwrite("formats", &StreamDescriptor::formats)
#ifdef ENABLE_AVDECC_FEATURE_REDUNDANCY
        .def_readwrite("redundantStreams", &StreamDescriptor::redundantStreams)
#endif
        .def("__repr__", [](const StreamDescriptor& self) {
            std::ostringstream oss;
            oss << "<StreamDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindJackDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<JackDescriptor>(m, "JackDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &JackDescriptor::objectName)
        .def_readwrite("localizedDescription", &JackDescriptor::localizedDescription)
        .def_readwrite("jackFlags", &JackDescriptor::jackFlags)
        .def_readwrite("jackType", &JackDescriptor::jackType)
        .def_readwrite("numberOfControls", &JackDescriptor::numberOfControls)
        .def_readwrite("baseControl", &JackDescriptor::baseControl)
        .def("__repr__", [](const JackDescriptor& self) {
            std::ostringstream oss;
            oss << "<JackDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAvbInterfaceDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<AvbInterfaceDescriptor>(m, "AvbInterfaceDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &AvbInterfaceDescriptor::objectName)
        .def_readwrite("localizedDescription", &AvbInterfaceDescriptor::localizedDescription)
        .def_readwrite("macAddress", &AvbInterfaceDescriptor::macAddress)
        .def_readwrite("interfaceFlags", &AvbInterfaceDescriptor::interfaceFlags)
        .def_readwrite("clockIdentity", &AvbInterfaceDescriptor::clockIdentity)
        .def_readwrite("priority1", &AvbInterfaceDescriptor::priority1)
        .def_readwrite("clockClass", &AvbInterfaceDescriptor::clockClass)
        .def_readwrite("offsetScaledLogVariance", &AvbInterfaceDescriptor::offsetScaledLogVariance)
        .def_readwrite("clockAccuracy", &AvbInterfaceDescriptor::clockAccuracy)
        .def_readwrite("priority2", &AvbInterfaceDescriptor::priority2)
        .def_readwrite("domainNumber", &AvbInterfaceDescriptor::domainNumber)
        .def_readwrite("logSyncInterval", &AvbInterfaceDescriptor::logSyncInterval)
        .def_readwrite("logAnnounceInterval", &AvbInterfaceDescriptor::logAnnounceInterval)
        .def_readwrite("logPDelayInterval", &AvbInterfaceDescriptor::logPDelayInterval)
        .def_readwrite("portNumber", &AvbInterfaceDescriptor::portNumber)
        .def("__repr__", [](const AvbInterfaceDescriptor& self) {
            std::ostringstream oss;
            oss << "<AvbInterfaceDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindClockSourceDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<ClockSourceDescriptor>(m, "ClockSourceDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &ClockSourceDescriptor::objectName)
        .def_readwrite("localizedDescription", &ClockSourceDescriptor::localizedDescription)
        .def_readwrite("clockSourceFlags", &ClockSourceDescriptor::clockSourceFlags)
        .def_readwrite("clockSourceType", &ClockSourceDescriptor::clockSourceType)
        .def_readwrite("clockSourceIdentifier", &ClockSourceDescriptor::clockSourceIdentifier)
        .def_readwrite("clockSourceLocationType", &ClockSourceDescriptor::clockSourceLocationType)
        .def_readwrite("clockSourceLocationIndex", &ClockSourceDescriptor::clockSourceLocationIndex)
        .def("__repr__", [](const ClockSourceDescriptor& self) {
            std::ostringstream oss;
            oss << "<ClockSourceDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMemoryObjectDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<MemoryObjectDescriptor>(m, "MemoryObjectDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &MemoryObjectDescriptor::objectName)
        .def_readwrite("localizedDescription", &MemoryObjectDescriptor::localizedDescription)
        .def_readwrite("memoryObjectType", &MemoryObjectDescriptor::memoryObjectType)
        .def_readwrite("targetDescriptorType", &MemoryObjectDescriptor::targetDescriptorType)
        .def_readwrite("targetDescriptorIndex", &MemoryObjectDescriptor::targetDescriptorIndex)
        .def_readwrite("startAddress", &MemoryObjectDescriptor::startAddress)
        .def_readwrite("maximumLength", &MemoryObjectDescriptor::maximumLength)
        .def_readwrite("length", &MemoryObjectDescriptor::length)
        .def("__repr__", [](const MemoryObjectDescriptor& self) {
            std::ostringstream oss;
            oss << "<MemoryObjectDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindLocaleDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<LocaleDescriptor>(m, "LocaleDescriptor")
        .def(py::init<>())
        .def_readwrite("localeID", &LocaleDescriptor::localeID)
        .def_readwrite("numberOfStringDescriptors", &LocaleDescriptor::numberOfStringDescriptors)
        .def_readwrite("baseStringDescriptorIndex", &LocaleDescriptor::baseStringDescriptorIndex)
        .def("__repr__", [](const LocaleDescriptor& self) {
            std::ostringstream oss;
            oss << "<LocaleDescriptor localeID='" << self.localeID << "'>";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStringsDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<StringsDescriptor>(m, "StringsDescriptor")
        .def(py::init<>())
        .def_readwrite("strings", &StringsDescriptor::strings)
        .def("__len__", [](const StringsDescriptor& self) { return self.strings.size(); })
        .def(
            "__iter__", [](StringsDescriptor& self) { return py::make_iterator(self.strings.begin(), self.strings.end()); },
            py::keep_alive<0, 1>()) // Keep container alive while iterator exists
        .def(
            "__getitem__",
            [](const StringsDescriptor& self, size_t i) -> const AvdeccFixedString& {
                if (i >= self.strings.size())
                    throw py::index_error();
                return self.strings[i];
            },
            py::return_value_policy::reference_internal)
        .def("__repr__", [](const StringsDescriptor&) { return "<StringsDescriptor>"; });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamPortDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<StreamPortDescriptor>(m, "StreamPortDescriptor")
        .def(py::init<>())
        .def_readwrite("clockDomainIndex", &StreamPortDescriptor::clockDomainIndex)
        .def_readwrite("portFlags", &StreamPortDescriptor::portFlags)
        .def_readwrite("numberOfControls", &StreamPortDescriptor::numberOfControls)
        .def_readwrite("baseControl", &StreamPortDescriptor::baseControl)
        .def_readwrite("numberOfClusters", &StreamPortDescriptor::numberOfClusters)
        .def_readwrite("baseCluster", &StreamPortDescriptor::baseCluster)
        .def_readwrite("numberOfMaps", &StreamPortDescriptor::numberOfMaps)
        .def_readwrite("baseMap", &StreamPortDescriptor::baseMap)
        .def("__repr__", [](const StreamPortDescriptor& self) {
            std::ostringstream oss;
            oss << "<StreamPortDescriptor clockDomainIndex=" << self.clockDomainIndex << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindExternalPortDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<ExternalPortDescriptor>(m, "ExternalPortDescriptor")
        .def(py::init<>())
        .def_readwrite("clockDomainIndex", &ExternalPortDescriptor::clockDomainIndex)
        .def_readwrite("portFlags", &ExternalPortDescriptor::portFlags)
        .def_readwrite("numberOfControls", &ExternalPortDescriptor::numberOfControls)
        .def_readwrite("baseControl", &ExternalPortDescriptor::baseControl)
        .def_readwrite("signalType", &ExternalPortDescriptor::signalType)
        .def_readwrite("signalIndex", &ExternalPortDescriptor::signalIndex)
        .def_readwrite("signalOutput", &ExternalPortDescriptor::signalOutput)
        .def_readwrite("blockLatency", &ExternalPortDescriptor::blockLatency)
        .def_readwrite("jackIndex", &ExternalPortDescriptor::jackIndex)
        .def("__repr__", [](const ExternalPortDescriptor& self) {
            std::ostringstream oss;
            oss << "<ExternalPortDescriptor clockDomainIndex=" << self.clockDomainIndex << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindInternalPortDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<InternalPortDescriptor>(m, "InternalPortDescriptor")
        .def(py::init<>())
        .def_readwrite("clockDomainIndex", &InternalPortDescriptor::clockDomainIndex)
        .def_readwrite("portFlags", &InternalPortDescriptor::portFlags)
        .def_readwrite("numberOfControls", &InternalPortDescriptor::numberOfControls)
        .def_readwrite("baseControl", &InternalPortDescriptor::baseControl)
        .def_readwrite("signalType", &InternalPortDescriptor::signalType)
        .def_readwrite("signalIndex", &InternalPortDescriptor::signalIndex)
        .def_readwrite("signalOutput", &InternalPortDescriptor::signalOutput)
        .def_readwrite("blockLatency", &InternalPortDescriptor::blockLatency)
        .def_readwrite("internalIndex", &InternalPortDescriptor::internalIndex)
        .def("__repr__", [](const InternalPortDescriptor& self) {
            std::ostringstream oss;
            oss << "<InternalPortDescriptor clockDomainIndex=" << self.clockDomainIndex << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAudioClusterDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<AudioClusterDescriptor>(m, "AudioClusterDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &AudioClusterDescriptor::objectName)
        .def_readwrite("localizedDescription", &AudioClusterDescriptor::localizedDescription)
        .def_readwrite("signalType", &AudioClusterDescriptor::signalType)
        .def_readwrite("signalIndex", &AudioClusterDescriptor::signalIndex)
        .def_readwrite("signalOutput", &AudioClusterDescriptor::signalOutput)
        .def_readwrite("pathLatency", &AudioClusterDescriptor::pathLatency)
        .def_readwrite("blockLatency", &AudioClusterDescriptor::blockLatency)
        .def_readwrite("channelCount", &AudioClusterDescriptor::channelCount)
        .def_readwrite("format", &AudioClusterDescriptor::format)
        .def("__repr__", [](const AudioClusterDescriptor& self) {
            std::ostringstream oss;
            oss << "<AudioClusterDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAudioMapDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<AudioMapDescriptor>(m, "AudioMapDescriptor")
        .def(py::init<>())
        .def_readwrite("mappings", &AudioMapDescriptor::mappings)
        .def("__len__", [](const AudioMapDescriptor& self) { return self.mappings.size(); })
        .def(
            "__iter__", [](AudioMapDescriptor& self) { return py::make_iterator(self.mappings.begin(), self.mappings.end()); }, py::keep_alive<0, 1>())
        .def(
            "__getitem__",
            [](const AudioMapDescriptor& self, size_t i) -> const AudioMappings::value_type& {
                if (i >= self.mappings.size())
                    throw py::index_error();
                return self.mappings[i];
            },
            py::return_value_policy::reference_internal)
        .def("__repr__", [](const AudioMapDescriptor&) { return std::string("<AudioMapDescriptor>"); });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindControlDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<ControlDescriptor>(m, "ControlDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &ControlDescriptor::objectName)
        .def_readwrite("localizedDescription", &ControlDescriptor::localizedDescription)
        .def_readwrite("blockLatency", &ControlDescriptor::blockLatency)
        .def_readwrite("controlLatency", &ControlDescriptor::controlLatency)
        .def_readwrite("controlDomain", &ControlDescriptor::controlDomain)
        .def_readwrite("controlType", &ControlDescriptor::controlType)
        .def_readwrite("resetTime", &ControlDescriptor::resetTime)
        .def_readwrite("signalType", &ControlDescriptor::signalType)
        .def_readwrite("signalIndex", &ControlDescriptor::signalIndex)
        .def_readwrite("signalOutput", &ControlDescriptor::signalOutput)
        .def_readwrite("controlValueType", &ControlDescriptor::controlValueType)
        .def_readwrite("numberOfValues", &ControlDescriptor::numberOfValues)
        .def_readwrite("valuesStatic", &ControlDescriptor::valuesStatic)
        .def_readwrite("valuesDynamic", &ControlDescriptor::valuesDynamic)
        .def("__repr__", [](const ControlDescriptor& self) {
            std::ostringstream oss;
            oss << "<ControlDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindClockDomainDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<ClockDomainDescriptor>(m, "ClockDomainDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &ClockDomainDescriptor::objectName)
        .def_readwrite("localizedDescription", &ClockDomainDescriptor::localizedDescription)
        .def_readwrite("clockSourceIndex", &ClockDomainDescriptor::clockSourceIndex)
        .def_readwrite("clockSources", &ClockDomainDescriptor::clockSources)
        .def("__repr__", [](const ClockDomainDescriptor& self) {
            std::ostringstream oss;
            oss << "<ClockDomainDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindTimingDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<TimingDescriptor>(m, "TimingDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &TimingDescriptor::objectName)
        .def_readwrite("localizedDescription", &TimingDescriptor::localizedDescription)
        .def_readwrite("algorithm", &TimingDescriptor::algorithm)
        .def_readwrite("ptpInstances", &TimingDescriptor::ptpInstances)
        .def("__repr__", [](const TimingDescriptor& self) {
            std::ostringstream oss;
            oss << "<TimingDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindPtpInstanceDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<PtpInstanceDescriptor>(m, "PtpInstanceDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &PtpInstanceDescriptor::objectName)
        .def_readwrite("localizedDescription", &PtpInstanceDescriptor::localizedDescription)
        .def_readwrite("clockIdentity", &PtpInstanceDescriptor::clockIdentity)
        .def_readwrite("flags", &PtpInstanceDescriptor::flags)
        .def_readwrite("numberOfControls", &PtpInstanceDescriptor::numberOfControls)
        .def_readwrite("baseControl", &PtpInstanceDescriptor::baseControl)
        .def_readwrite("numberOfPtpPorts", &PtpInstanceDescriptor::numberOfPtpPorts)
        .def_readwrite("basePtpPort", &PtpInstanceDescriptor::basePtpPort)
        .def("__repr__", [](const PtpInstanceDescriptor& self) {
            std::ostringstream oss;
            oss << "<PtpInstanceDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindPtpPortDescriptor(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<PtpPortDescriptor>(m, "PtpPortDescriptor")
        .def(py::init<>())
        .def_readwrite("objectName", &PtpPortDescriptor::objectName)
        .def_readwrite("localizedDescription", &PtpPortDescriptor::localizedDescription)
        .def_readwrite("portNumber", &PtpPortDescriptor::portNumber)
        .def_readwrite("portType", &PtpPortDescriptor::portType)
        .def_readwrite("flags", &PtpPortDescriptor::flags)
        .def_readwrite("avbInterfaceIndex", &PtpPortDescriptor::avbInterfaceIndex)
        .def_readwrite("profileIdentifier", &PtpPortDescriptor::profileIdentifier)
        .def("__repr__", [](const PtpPortDescriptor& self) {
            std::ostringstream oss;
            oss << "<PtpPortDescriptor objectName='" << self.objectName << "', localizedDescription=" << self.localizedDescription << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamInfo(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<StreamInfo>(m, "StreamInfo")
        .def(py::init<>())
        .def_readwrite("streamInfoFlags", &StreamInfo::streamInfoFlags)
        .def_readwrite("streamFormat", &StreamInfo::streamFormat)
        .def_readwrite("streamID", &StreamInfo::streamID)
        .def_readwrite("msrpAccumulatedLatency", &StreamInfo::msrpAccumulatedLatency)
        .def_readwrite("streamDestMac", &StreamInfo::streamDestMac)
        .def_readwrite("msrpFailureCode", &StreamInfo::msrpFailureCode)
        .def_readwrite("msrpFailureBridgeID", &StreamInfo::msrpFailureBridgeID)
        .def_readwrite("streamVlanID", &StreamInfo::streamVlanID)
        .def_readwrite("streamInfoFlagsEx", &StreamInfo::streamInfoFlagsEx)
        .def_readwrite("probingStatus", &StreamInfo::probingStatus)
        .def_readwrite("acmpStatus", &StreamInfo::acmpStatus)
        .def("__eq__", [](const StreamInfo& self, const StreamInfo& other) { return self == other; })
        .def("__ne__", [](const StreamInfo& self, const StreamInfo& other) { return self != other; })
        .def("__repr__", [](const StreamInfo& self) {
            std::ostringstream oss;
            oss << "<StreamInfo streamID=" << self.streamID << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAvbInfo(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<AvbInfo>(m, "AvbInfo")
        .def(py::init<>())
        .def_readwrite("gptpGrandmasterID", &AvbInfo::gptpGrandmasterID)
        .def_readwrite("propagationDelay", &AvbInfo::propagationDelay)
        .def_readwrite("gptpDomainNumber", &AvbInfo::gptpDomainNumber)
        .def_readwrite("flags", &AvbInfo::flags)
        .def_readwrite("mappings", &AvbInfo::mappings)
        .def("__eq__", [](const AvbInfo& self, const AvbInfo& other) { return self == other; })
        .def("__ne__", [](const AvbInfo& self, const AvbInfo& other) { return self != other; })
        .def("__repr__", [](const AvbInfo& self) {
            std::ostringstream oss;
            oss << "<AvbInfo gptpGrandmasterID=" << self.gptpGrandmasterID << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAsPath(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<AsPath>(m, "AsPath")
        .def(py::init<>())
        .def_readwrite("sequence", &AsPath::sequence)
        .def("__eq__", [](const AsPath& self, const AsPath& other) { return self == other; })
        .def("__ne__", [](const AsPath& self, const AsPath& other) { return self != other; })
        .def("__len__", [](const AsPath& self) { return self.sequence.size(); })
        .def("__getitem__",
             [](const AsPath& self, size_t idx) {
                 if (idx >= self.sequence.size())
                     throw py::index_error();
                 return self.sequence[idx];
             })
        .def(
            "__iter__", [](AsPath& self) { return py::make_iterator(self.sequence.begin(), self.sequence.end()); }, py::keep_alive<0, 1>())
        .def("__repr__", [](const AsPath& self) {
            std::ostringstream oss;
            oss << "<AsPath [";
            for (size_t i = 0; i < self.sequence.size(); ++i)
            {
                if (i > 0)
                    oss << ", ";
                oss << "0x" << std::hex << std::setw(16) << std::setfill('0') << self.sequence[i].getValue();
            }
            oss << "]>";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMilanInfo(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<MilanInfo>(m, "MilanInfo")
        .def(py::init<>())
        .def_readwrite("protocolVersion", &MilanInfo::protocolVersion)
        .def_readwrite("featuresFlags", &MilanInfo::featuresFlags)
        .def_readwrite("certificationVersion", &MilanInfo::certificationVersion)
        .def("__eq__", [](const MilanInfo& self, const MilanInfo& other) { return self == other; })
        .def("__ne__", [](const MilanInfo& self, const MilanInfo& other) { return self != other; })
        .def("__repr__", [](const MilanInfo& self) {
            std::ostringstream oss;
            oss << "<MilanInfo>";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMilanDynamicState(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<MilanDynamicState>(m, "MilanDynamicState")
        .def(py::init<>())
        .def_readwrite("systemUniqueID", &MilanDynamicState::systemUniqueID)
        .def("__eq__", [](const MilanDynamicState& self, const MilanDynamicState& other) { return self == other; })
        .def("__ne__", [](const MilanDynamicState& self, const MilanDynamicState& other) { return self != other; })
        .def("__repr__", [](const MilanDynamicState& self) {
            std::ostringstream oss;
            oss << "<MilanDynamicState systemUniqueID=";
            if (self.systemUniqueID)
            {
                oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << *self.systemUniqueID;
            }
            else
            {
                oss << "None";
            }
            oss << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMediaClockReferenceInfo(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    py::class_<MediaClockReferenceInfo>(m, "MediaClockReferenceInfo")
        .def(py::init<>())
        .def_readwrite("userMediaClockPriority", &MediaClockReferenceInfo::userMediaClockPriority)
        .def_readwrite("mediaClockDomainName", &MediaClockReferenceInfo::mediaClockDomainName)
        .def("__repr__", [](const MediaClockReferenceInfo& self) {
            std::ostringstream oss;
            oss << "<MediaClockReferenceInfo userMediaClockPriority=" << (self.userMediaClockPriority ? std::to_string(*self.userMediaClockPriority) : "None")
                << ", mediaClockDomainName=" << (self.mediaClockDomainName ? ("'" + std::string(*self.mediaClockDomainName) + "'") : "None") << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityModelUniqueIdentifierExtensions(py::module_& m)
{
    using namespace la::avdecc;
    using namespace la::avdecc::entity::model;
    assert(UniqueIdentifierBinding.has_value());

    UniqueIdentifierBinding->def_static(
        "makeEntityModelID",
        [](std::uint32_t vendorID, std::uint8_t deviceID, std::uint32_t modelID) { return makeEntityModelID(vendorID, deviceID, modelID); },
        "Construct a UniqueIdentifier from vendorID, deviceID, and modelID. "
        "This helper builds an EntityModelID for use in ADP messages and descriptors.",
        py::arg("vendorID"), "24-bit vendor OUI (8 MSBs are ignored)", py::arg("deviceID"), "8-bit device ID (vendor-specific)", py::arg("modelID"),
        "32-bit model ID (vendor-specific)");

    UniqueIdentifierBinding->def(
        "splitEntityModelID", [](const UniqueIdentifier& self) { return splitEntityModelID(self); },
        "Split this UniqueIdentifier into vendorID, deviceID, and modelID components.\n\n"
        "Helper to extract the OUI-24 vendorID, deviceID, and modelID from an EntityModelID-encoded identifier.\n"
        "Note: Only valid if the identifier was constructed using makeEntityModelID().",
        py::return_value_policy::copy);
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- StreamFormatInfo bindings ------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

class PyStreamFormatInfo : public la::avdecc::entity::model::StreamFormatInfo
{
public:
    using StreamFormat = la::avdecc::entity::model::StreamFormat;
    using SamplingRate = la::avdecc::entity::model::SamplingRate;

    PyStreamFormatInfo(StreamFormat const& streamFormat)
        : _ref(StreamFormatInfo::create(streamFormat))
    {}

    StreamFormat getStreamFormat() const noexcept override
    {
        return _ref->getStreamFormat();
    }

    StreamFormat getAdaptedStreamFormat(std::uint16_t const channelsCount) const noexcept override
    {
        return _ref->getAdaptedStreamFormat(channelsCount);
    }

    Type getType() const noexcept override
    {
        return (Type)_ref->getType();
    }

    std::uint16_t getChannelsCount() const noexcept override
    {
        return _ref->getChannelsCount();
    }

    bool isUpToChannelsCount() const noexcept override
    {
        return _ref->isUpToChannelsCount();
    }

    SamplingRate getSamplingRate() const noexcept override
    {
        return _ref->getSamplingRate();
    }

    SampleFormat getSampleFormat() const noexcept override
    {
        return (SampleFormat)_ref->getSampleFormat();
    }

    bool useSynchronousClock() const noexcept override
    {
        return _ref->useSynchronousClock();
    }

    std::uint16_t getSampleSize() const noexcept override
    {
        return _ref->getSampleSize();
    }

    std::uint16_t getSampleBitDepth() const noexcept override
    {
        return _ref->getSampleBitDepth();
    }

private:
    StreamFormatInfo::UniquePointer _ref;

    void destroy() noexcept override {};
};

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamFormatInfo(py::module_& m)
{
    using namespace la::avdecc::entity::model;

    auto streamFormatInfo = py::class_<PyStreamFormatInfo>(m, "StreamFormatInfo");

    py::enum_<PyStreamFormatInfo::Type>(streamFormatInfo, "StreamFormatType")
        .value("Unspecified", PyStreamFormatInfo::Type::None)
        .value("IEC_61883_6", PyStreamFormatInfo::Type::IEC_61883_6)
        .value("AAF", PyStreamFormatInfo::Type::AAF)
        .value("ClockReference", PyStreamFormatInfo::Type::ClockReference)
        .value("Unsupported", PyStreamFormatInfo::Type::Unsupported);

    py::enum_<PyStreamFormatInfo::SampleFormat>(streamFormatInfo, "SampleFormat")
        .value("Int8", PyStreamFormatInfo::SampleFormat::Int8)
        .value("Int16", PyStreamFormatInfo::SampleFormat::Int16)
        .value("Int24", PyStreamFormatInfo::SampleFormat::Int24)
        .value("Int32", PyStreamFormatInfo::SampleFormat::Int32)
        .value("Int64", PyStreamFormatInfo::SampleFormat::Int64)
        .value("FixedPoint32", PyStreamFormatInfo::SampleFormat::FixedPoint32)
        .value("FloatingPoint32", PyStreamFormatInfo::SampleFormat::FloatingPoint32)
        .value("Unknown", PyStreamFormatInfo::SampleFormat::Unknown);

    streamFormatInfo.def("getStreamFormat", &PyStreamFormatInfo::getStreamFormat)
        .def(py::init<PyStreamFormatInfo::StreamFormat>(), py::arg("streamFormat"),
             "Create a StreamFormatInfo instance from a StreamFormat object.")
        .def_property_readonly("getAdaptedStreamFormat", &PyStreamFormatInfo::getAdaptedStreamFormat)
        .def_property_readonly("type", &PyStreamFormatInfo::getType)
        .def_property_readonly("channelsCount", &PyStreamFormatInfo::getChannelsCount)
        .def_property_readonly("isUpToChannelsCount", &PyStreamFormatInfo::isUpToChannelsCount)
        .def_property_readonly("samplingRate", &PyStreamFormatInfo::getSamplingRate)
        .def_property_readonly("sampleFormat", &PyStreamFormatInfo::getSampleFormat)
        .def_property_readonly("useSynchronousClock", &PyStreamFormatInfo::useSynchronousClock)
        .def_property_readonly("sampleSize", &PyStreamFormatInfo::getSampleSize)
        .def_property_readonly("sampleBitDepth", &PyStreamFormatInfo::getSampleBitDepth)
        .def("__repr__", [](const PyStreamFormatInfo& self) {
            std::ostringstream oss;
            oss << "<StreamFormatInfo "
                << "type=" << py::repr(py::cast(self.getType())) << ", "
                << "sampleFormat=" << py::repr(py::cast(self.getSampleFormat())) << ", "
                << "samplingRate=" << py::repr(py::cast(self.getSamplingRate())) << ", "
                << "channelsCount=" << self.getChannelsCount() << ", "
                << "sampleSize=" << self.getSampleSize() << ">";
            return oss.str();
        });
}