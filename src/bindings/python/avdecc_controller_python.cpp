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
 * @file avdecc_controller_python.cpp
 * @author Vitalij Mast
 */

#include "avdecc_controller_python.hpp"


#include <la/avdecc/avdecc.hpp>

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void bindDynamicInfoParameter(py::module_& m);
void bindControllerInterface(py::module_& m);
void bindControllerDelegate(py::module_& m);
void bindControllerDefaultedDelegate(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
void bindControllerEntity(py::module_& m)
{
    bindDynamicInfoParameter(m);
    bindControllerInterface(m);
    bindControllerDelegate(m);
    bindControllerDefaultedDelegate(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindDynamicInfoParameter(py::module_& m)
{
    using namespace la::avdecc;
    using namespace la::avdecc::entity;
    using namespace la::avdecc::entity::controller;

    py::class_<DynamicInfoParameter>(m, "DynamicInfoParameter", "Represents a parameter for dynamic info queries.")
        .def_property_readonly(
            "status", [](const DynamicInfoParameter& self) { return self.status; }, "AEM command execution status.")
        .def_property_readonly(
            "commandType", [](const DynamicInfoParameter& self) { return self.commandType; }, "The associated AEM command type.")

        // GetStreamFormat(descriptorType, descriptorIndex)
        .def_static(
            "constructGetStreamFormat",
            [](model::DescriptorType type, int index) {
                DynamicInfoParameter param;
                param.commandType = protocol::AemCommandType::GetStreamFormat;
                param.arguments.emplace_back(type);
                param.arguments.emplace_back(static_cast<model::DescriptorIndex>(index));
                return param;
            },
            py::arg("descriptor_type"), py::arg("descriptor_index"))

        // GetName(configIndex, descriptorType, descriptorIndex, nameIndex)
        .def_static(
            "constructGetName",
            [](int config_index, model::DescriptorType type, int index, std::uint16_t name_index) {
                DynamicInfoParameter param;
                param.commandType = protocol::AemCommandType::GetName;
                param.arguments.emplace_back(static_cast<model::ConfigurationIndex>(config_index));
                param.arguments.emplace_back(type);
                param.arguments.emplace_back(static_cast<model::DescriptorIndex>(index));
                param.arguments.emplace_back(name_index);
                return param;
            },
            py::arg("configuration_index"), py::arg("descriptor_type"), py::arg("descriptor_index"), py::arg("name_index"))

        // GetCounters(descriptorType, descriptorIndex)
        .def_static(
            "constructGetCounters",
            [](model::DescriptorType type, int index) {
                DynamicInfoParameter param;
                param.commandType = protocol::AemCommandType::GetCounters;
                param.arguments.emplace_back(type);
                param.arguments.emplace_back(static_cast<model::DescriptorIndex>(index));
                return param;
            },
            py::arg("descriptor_type"), py::arg("descriptor_index"))

        // GetMaxTransitTime(streamIndex)
        .def_static(
            "constructGetMaxTransitTime",
            [](int stream_index) {
                DynamicInfoParameter param;
                param.commandType = protocol::AemCommandType::GetMaxTransitTime;
                param.arguments.emplace_back(static_cast<model::StreamIndex>(stream_index));
                return param;
            },
            py::arg("stream_index"))

        // GetConfiguration()
        .def_static("constructGetConfiguration",
                    []() {
                        DynamicInfoParameter param;
                        param.commandType = protocol::AemCommandType::GetConfiguration;
                        return param;
                    })

        // GetAssociationID()
        .def_static("constructGetAssociationID",
                    []() {
                        DynamicInfoParameter param;
                        param.commandType = protocol::AemCommandType::GetAssociationID;
                        return param;
                    })

        // GetSamplingRate(descriptorType, descriptorIndex)
        .def_static(
            "constructGetSamplingRate",
            [](model::DescriptorType type, int index) {
                DynamicInfoParameter param;
                param.commandType = protocol::AemCommandType::GetSamplingRate;
                param.arguments.emplace_back(type);
                param.arguments.emplace_back(static_cast<model::DescriptorIndex>(index));
                return param;
            },
            py::arg("descriptor_type"), py::arg("descriptor_index"))

        // GetClockSource(clockDomainIndex)
        .def_static(
            "constructGetClockSource",
            [](int clock_domain_index) {
                DynamicInfoParameter param;
                param.commandType = protocol::AemCommandType::GetClockSource;
                param.arguments.emplace_back(static_cast<model::DescriptorIndex>(clock_domain_index));
                return param;
            },
            py::arg("clock_domain_index"))

        // GetStreamInfo(descriptorType, descriptorIndex)
        .def_static(
            "constructGetStreamInfo",
            [](model::DescriptorType type, int index) {
                DynamicInfoParameter param;
                param.commandType = protocol::AemCommandType::GetStreamInfo;
                param.arguments.emplace_back(type);
                param.arguments.emplace_back(static_cast<model::DescriptorIndex>(index));
                return param;
            },
            py::arg("descriptor_type"), py::arg("descriptor_index"))

        // GetMemoryObjectLength(configIndex, memoryObjectIndex)
        .def_static(
            "constructGetMemoryObjectLength",
            [](int config_index, int memory_object_index) {
                DynamicInfoParameter param;
                param.commandType = protocol::AemCommandType::GetMemoryObjectLength;
                param.arguments.emplace_back(static_cast<model::ConfigurationIndex>(config_index));
                param.arguments.emplace_back(static_cast<model::MemoryObjectIndex>(memory_object_index));
                return param;
            },
            py::arg("configuration_index"), py::arg("memory_object_index"))

        .def("__repr__", [](const DynamicInfoParameter& self) {
            py::object pyCommandType = py::cast(self.commandType);
            py::object pyStatus      = py::cast(self.status);

            std::ostringstream oss;
            oss << "<DynamicInfoParameter commandType=" << py::str(pyCommandType) << ", arguments=<" << self.arguments.size()
                << ">, status=" << py::str(pyStatus) << ">";
            return oss.str();
        });
}

/*-------------------------------------------------------------------------------------------------------------------*/

namespace la::avdecc::entity::controller
{
    class PyInterface : public Interface
    {
    public:
        using Interface::Interface;

        // clang-format off
        void acquireEntity(la::avdecc::UniqueIdentifier const targetEntityID, bool const isPersistent, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, AcquireEntityHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, acquireEntity, targetEntityID, isPersistent, descriptorType, descriptorIndex, handler);
        }

        void releaseEntity(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, ReleaseEntityHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, releaseEntity, targetEntityID, descriptorType, descriptorIndex, handler);
        }

        void lockEntity(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, LockEntityHandler const& handler) const noexcept override      
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, lockEntity, targetEntityID, descriptorType, descriptorIndex, handler);
        }

        void unlockEntity(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, UnlockEntityHandler const& handler) const noexcept override  
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, unlockEntity, targetEntityID, descriptorType, descriptorIndex, handler);
        }

        void queryEntityAvailable(la::avdecc::UniqueIdentifier const targetEntityID, QueryEntityAvailableHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, queryEntityAvailable, targetEntityID, handler);
        }

        void queryControllerAvailable(la::avdecc::UniqueIdentifier const targetEntityID, QueryControllerAvailableHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, queryControllerAvailable, targetEntityID, handler);
        }

        void registerUnsolicitedNotifications(la::avdecc::UniqueIdentifier const targetEntityID, RegisterUnsolicitedNotificationsHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, registerUnsolicitedNotifications, targetEntityID, handler);
        }

        void unregisterUnsolicitedNotifications(la::avdecc::UniqueIdentifier const targetEntityID, UnregisterUnsolicitedNotificationsHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, unregisterUnsolicitedNotifications, targetEntityID, handler);
        }

        void readEntityDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, EntityDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readEntityDescriptor, targetEntityID, handler);
        }

        void readConfigurationDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, ConfigurationDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readConfigurationDescriptor, targetEntityID, configurationIndex, handler);
        }

        void readAudioUnitDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, AudioUnitDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readAudioUnitDescriptor, targetEntityID, configurationIndex, audioUnitIndex, handler);
        }

        void readStreamInputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, StreamInputDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readStreamInputDescriptor, targetEntityID, configurationIndex, streamIndex, handler);
        }

        void readStreamOutputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, StreamOutputDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readStreamOutputDescriptor, targetEntityID, configurationIndex, streamIndex, handler);
        }

        void readJackInputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, JackInputDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readJackInputDescriptor, targetEntityID, configurationIndex, jackIndex, handler);
        }

        void readJackOutputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, JackOutputDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readJackOutputDescriptor, targetEntityID, configurationIndex, jackIndex, handler);
        }

        void readAvbInterfaceDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, AvbInterfaceDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readAvbInterfaceDescriptor, targetEntityID, configurationIndex, avbInterfaceIndex, handler);
        }

        void readClockSourceDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex, ClockSourceDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readClockSourceDescriptor, targetEntityID, configurationIndex, clockSourceIndex, handler);
        }

        void readMemoryObjectDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, MemoryObjectDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readMemoryObjectDescriptor, targetEntityID, configurationIndex, memoryObjectIndex, handler);
        }

        void readLocaleDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::LocaleIndex const localeIndex, LocaleDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readLocaleDescriptor, targetEntityID, configurationIndex, localeIndex, handler);
        }

        void readStringsDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StringsIndex const stringsIndex, StringsDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readStringsDescriptor, targetEntityID, configurationIndex, stringsIndex, handler);
        }

        void readStreamPortInputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, StreamPortInputDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readStreamPortInputDescriptor, targetEntityID, configurationIndex, streamPortIndex, handler);
        }

        void readStreamPortOutputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, StreamPortOutputDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readStreamPortOutputDescriptor, targetEntityID, configurationIndex, streamPortIndex, handler);
        }

        void readExternalPortInputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ExternalPortIndex const externalPortIndex, ExternalPortInputDescriptorHandler const& handler) const noexcept override     
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readExternalPortInputDescriptor, targetEntityID, configurationIndex, externalPortIndex, handler);
        }

        void readExternalPortOutputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ExternalPortIndex const externalPortIndex, ExternalPortOutputDescriptorHandler const& handler) const noexcept override   
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readExternalPortOutputDescriptor, targetEntityID, configurationIndex, externalPortIndex, handler);
        }

        void readInternalPortInputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::InternalPortIndex const internalPortIndex, InternalPortInputDescriptorHandler const& handler) const noexcept override     
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readInternalPortInputDescriptor, targetEntityID, configurationIndex, internalPortIndex, handler);
        }

        void readInternalPortOutputDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::InternalPortIndex const internalPortIndex, InternalPortOutputDescriptorHandler const& handler) const noexcept override   
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readInternalPortOutputDescriptor, targetEntityID, configurationIndex, internalPortIndex, handler);
        }

        void readAudioClusterDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClusterIndex const clusterIndex, AudioClusterDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readAudioClusterDescriptor, targetEntityID, configurationIndex, clusterIndex, handler);
        }

        void readAudioMapDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MapIndex const mapIndex, AudioMapDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readAudioMapDescriptor, targetEntityID, configurationIndex, mapIndex, handler);
        }

        void readControlDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ControlIndex const controlIndex, ControlDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readControlDescriptor, targetEntityID, configurationIndex, controlIndex, handler);
        }

        void readClockDomainDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, ClockDomainDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readClockDomainDescriptor, targetEntityID, configurationIndex, clockDomainIndex, handler);
        }

        void readTimingDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::TimingIndex const timingIndex, TimingDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readTimingDescriptor, targetEntityID, configurationIndex, timingIndex, handler);
        }

        void readPtpInstanceDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpInstanceIndex const ptpInstanceIndex, PtpInstanceDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readPtpInstanceDescriptor, targetEntityID, configurationIndex, ptpInstanceIndex, handler);
        }

        void readPtpPortDescriptor(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpPortIndex const ptpPortIndex, PtpPortDescriptorHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, readPtpPortDescriptor, targetEntityID, configurationIndex, ptpPortIndex, handler);
        }

        void setConfiguration(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, SetConfigurationHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setConfiguration, targetEntityID, configurationIndex, handler);
        }

        void getConfiguration(la::avdecc::UniqueIdentifier const targetEntityID, GetConfigurationHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getConfiguration, targetEntityID, handler);
        }

        void setStreamInputFormat(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamFormat const streamFormat, SetStreamInputFormatHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setStreamInputFormat, targetEntityID, streamIndex, streamFormat, handler);
        }

        void getStreamInputFormat(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, GetStreamInputFormatHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamInputFormat, targetEntityID, streamIndex, handler);
        }

        void setStreamOutputFormat(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamFormat const streamFormat, SetStreamOutputFormatHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setStreamOutputFormat, targetEntityID, streamIndex, streamFormat, handler);
        }

        void getStreamOutputFormat(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, GetStreamOutputFormatHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamOutputFormat, targetEntityID, streamIndex, handler);
        }

        void getStreamPortInputAudioMap(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::MapIndex const mapIndex, GetStreamPortInputAudioMapHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamPortInputAudioMap, targetEntityID, streamPortIndex, mapIndex, handler);
        }

        void getStreamPortOutputAudioMap(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::MapIndex const mapIndex, GetStreamPortOutputAudioMapHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamPortOutputAudioMap, targetEntityID, streamPortIndex, mapIndex, handler);
        }

        void addStreamPortInputAudioMappings(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings, AddStreamPortInputAudioMappingsHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, addStreamPortInputAudioMappings, targetEntityID, streamPortIndex, mappings, handler);
        }

        void addStreamPortOutputAudioMappings(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings, AddStreamPortOutputAudioMappingsHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, addStreamPortOutputAudioMappings, targetEntityID, streamPortIndex, mappings, handler);
        }

        void removeStreamPortInputAudioMappings(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings, RemoveStreamPortInputAudioMappingsHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, removeStreamPortInputAudioMappings, targetEntityID, streamPortIndex, mappings, handler);
        }

        void removeStreamPortOutputAudioMappings(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings, RemoveStreamPortOutputAudioMappingsHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, removeStreamPortOutputAudioMappings, targetEntityID, streamPortIndex, mappings, handler);
        }

        void setStreamInputInfo(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamInfo const& info, SetStreamInputInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setStreamInputInfo, targetEntityID, streamIndex, info, handler);
        }

        void setStreamOutputInfo(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamInfo const& info, SetStreamOutputInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setStreamOutputInfo, targetEntityID, streamIndex, info, handler);
        }

        void getStreamInputInfo(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, GetStreamInputInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamInputInfo, targetEntityID, streamIndex, handler);
        }

        void getStreamOutputInfo(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, GetStreamOutputInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamOutputInfo, targetEntityID, streamIndex, handler);
        }

        void setEntityName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::AvdeccFixedString const& entityName, SetEntityNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setEntityName, targetEntityID, entityName, handler);
        }

        void getEntityName(la::avdecc::UniqueIdentifier const targetEntityID, GetEntityNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getEntityName, targetEntityID, handler);
        }

        void setEntityGroupName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::AvdeccFixedString const& entityGroupName, SetEntityGroupNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setEntityGroupName, targetEntityID, entityGroupName, handler);
        }

        void getEntityGroupName(la::avdecc::UniqueIdentifier const targetEntityID, GetEntityGroupNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getEntityGroupName, targetEntityID, handler);
        }

        void setConfigurationName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvdeccFixedString const& configurationName, SetConfigurationNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setConfigurationName, targetEntityID, configurationIndex, configurationName, handler);
        }

        void getConfigurationName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, GetConfigurationNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getConfigurationName, targetEntityID, configurationIndex, handler);
        }

        void setAudioUnitName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, la::avdecc::entity::model::AvdeccFixedString const& audioUnitName, SetAudioUnitNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setAudioUnitName, targetEntityID, configurationIndex, audioUnitIndex, audioUnitName, handler);
        }

        void getAudioUnitName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, GetAudioUnitNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getAudioUnitName, targetEntityID, configurationIndex, audioUnitIndex, handler);
        }

        void setStreamInputName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::AvdeccFixedString const& streamInputName, SetStreamInputNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setStreamInputName, targetEntityID, configurationIndex, streamIndex, streamInputName, handler);
        }

        void getStreamInputName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, GetStreamInputNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamInputName, targetEntityID, configurationIndex, streamIndex, handler);
        }

        void setStreamOutputName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::AvdeccFixedString const& streamOutputName, SetStreamOutputNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setStreamOutputName, targetEntityID, configurationIndex, streamIndex, streamOutputName, handler);
        }

        void getStreamOutputName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, GetStreamOutputNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamOutputName, targetEntityID, configurationIndex, streamIndex, handler);
        }

        void setJackInputName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, la::avdecc::entity::model::AvdeccFixedString const& jackInputName, SetJackInputNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setJackInputName, targetEntityID, configurationIndex, jackIndex, jackInputName, handler);
        }

        void getJackInputName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, GetJackInputNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getJackInputName, targetEntityID, configurationIndex, jackIndex, handler);
        }

        void setJackOutputName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, la::avdecc::entity::model::AvdeccFixedString const& jackOutputName, SetJackOutputNameHandler const& handler) 
        const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setJackOutputName, targetEntityID, configurationIndex, jackIndex, jackOutputName, handler);
        }

        void getJackOutputName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, GetJackOutputNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getJackOutputName, targetEntityID, configurationIndex, jackIndex, handler);
        }

        void setAvbInterfaceName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AvdeccFixedString const& avbInterfaceName, SetAvbInterfaceNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setAvbInterfaceName, targetEntityID, configurationIndex, avbInterfaceIndex, avbInterfaceName, handler);
        }

        void getAvbInterfaceName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, GetAvbInterfaceNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getAvbInterfaceName, targetEntityID, configurationIndex, avbInterfaceIndex, handler);
        }

        void setClockSourceName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex, la::avdecc::entity::model::AvdeccFixedString const& clockSourceName, SetClockSourceNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setClockSourceName, targetEntityID, configurationIndex, clockSourceIndex, clockSourceName, handler);
        }

        void getClockSourceName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex, GetClockSourceNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getClockSourceName, targetEntityID, configurationIndex, clockSourceIndex, handler);
        }

        void setMemoryObjectName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, la::avdecc::entity::model::AvdeccFixedString const& memoryObjectName, SetMemoryObjectNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setMemoryObjectName, targetEntityID, configurationIndex, memoryObjectIndex, memoryObjectName, handler);
        }

        void getMemoryObjectName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, GetMemoryObjectNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getMemoryObjectName, targetEntityID, configurationIndex, memoryObjectIndex, handler);
        }

        void setAudioClusterName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClusterIndex const audioClusterIndex, la::avdecc::entity::model::AvdeccFixedString const& audioClusterName, SetAudioClusterNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setAudioClusterName, targetEntityID, configurationIndex, audioClusterIndex, audioClusterName, handler);
        }

        void getAudioClusterName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClusterIndex const audioClusterIndex, GetAudioClusterNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getAudioClusterName, targetEntityID, configurationIndex, audioClusterIndex, handler);
        }

        void setControlName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ControlIndex const controlIndex, la::avdecc::entity::model::AvdeccFixedString const& controlName, SetControlNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setControlName, targetEntityID, configurationIndex, controlIndex, controlName, handler);
        }

        void getControlName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ControlIndex const controlIndex, GetControlNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getControlName, targetEntityID, configurationIndex, controlIndex, handler);
        }

        void setClockDomainName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::AvdeccFixedString const& clockDomainName, SetClockDomainNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setClockDomainName, targetEntityID, configurationIndex, clockDomainIndex, clockDomainName, handler);
        }

        void getClockDomainName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, GetClockDomainNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getClockDomainName, targetEntityID, configurationIndex, clockDomainIndex, handler);
        }

        void setTimingName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::TimingIndex const timingIndex, la::avdecc::entity::model::AvdeccFixedString const& timingName, SetTimingNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setTimingName, targetEntityID, configurationIndex, timingIndex, timingName, handler);
        }

        void getTimingName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::TimingIndex const timingIndex, GetTimingNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getTimingName, targetEntityID, configurationIndex, timingIndex, handler);
        }

        void setPtpInstanceName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpInstanceIndex const ptpInstanceIndex, la::avdecc::entity::model::AvdeccFixedString const& ptpInstanceName, SetPtpInstanceNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setPtpInstanceName, targetEntityID, configurationIndex, ptpInstanceIndex, ptpInstanceName, handler);
        }

        void getPtpInstanceName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpInstanceIndex const ptpInstanceIndex, GetPtpInstanceNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getPtpInstanceName, targetEntityID, configurationIndex, ptpInstanceIndex, handler);
        }

        void setPtpPortName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpPortIndex const ptpPortIndex, la::avdecc::entity::model::AvdeccFixedString const& ptpPortName, SetPtpPortNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setPtpPortName, targetEntityID, configurationIndex, ptpPortIndex, ptpPortName, handler);
        }

        void getPtpPortName(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpPortIndex const ptpPortIndex, GetPtpPortNameHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getPtpPortName, targetEntityID, configurationIndex, ptpPortIndex, handler);
        }

        void setAssociation(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::UniqueIdentifier const associationID, SetAssociationHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setAssociation, targetEntityID, associationID, handler);
        }

        void getAssociation(la::avdecc::UniqueIdentifier const targetEntityID, GetAssociationHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getAssociation, targetEntityID, handler);
        }

        void setAudioUnitSamplingRate(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, la::avdecc::entity::model::SamplingRate const samplingRate, SetAudioUnitSamplingRateHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setAudioUnitSamplingRate, targetEntityID, audioUnitIndex, samplingRate, handler);
        }

        void getAudioUnitSamplingRate(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, GetAudioUnitSamplingRateHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getAudioUnitSamplingRate, targetEntityID, audioUnitIndex, handler);
        }

        void setVideoClusterSamplingRate(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClusterIndex const videoClusterIndex, la::avdecc::entity::model::SamplingRate const samplingRate, SetVideoClusterSamplingRateHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setVideoClusterSamplingRate, targetEntityID, videoClusterIndex, samplingRate, handler);
        }

        void getVideoClusterSamplingRate(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClusterIndex const videoClusterIndex, GetVideoClusterSamplingRateHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getVideoClusterSamplingRate, targetEntityID, videoClusterIndex, handler);
        }

        void setSensorClusterSamplingRate(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClusterIndex const sensorClusterIndex, la::avdecc::entity::model::SamplingRate const samplingRate, SetSensorClusterSamplingRateHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setSensorClusterSamplingRate, targetEntityID, sensorClusterIndex, samplingRate, handler);
        }

        void getSensorClusterSamplingRate(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClusterIndex const sensorClusterIndex, GetSensorClusterSamplingRateHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getSensorClusterSamplingRate, targetEntityID, sensorClusterIndex, handler);
        }

        void setClockSource(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex, SetClockSourceHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setClockSource, targetEntityID, clockDomainIndex, clockSourceIndex, handler);
        }

        void getClockSource(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, GetClockSourceHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getClockSource, targetEntityID, clockDomainIndex, handler);
        }

        void setControlValues(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ControlIndex const controlIndex, la::avdecc::entity::model::ControlValues const& controlValues, SetControlValuesHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setControlValues, targetEntityID, controlIndex, controlValues, handler);
        }

        void getControlValues(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ControlIndex const controlIndex, GetControlValuesHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getControlValues, targetEntityID, controlIndex, handler);
        }

        void startStreamInput(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, StartStreamInputHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, startStreamInput, targetEntityID, streamIndex, handler);
        }

        void startStreamOutput(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, StartStreamOutputHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, startStreamOutput, targetEntityID, streamIndex, handler);
        }

        void stopStreamInput(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, StopStreamInputHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, stopStreamInput, targetEntityID, streamIndex, handler);
        }

        void stopStreamOutput(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, StopStreamOutputHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, stopStreamOutput, targetEntityID, streamIndex, handler);
        }

        void getAvbInfo(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, GetAvbInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getAvbInfo, targetEntityID, avbInterfaceIndex, handler);
        }

        void getAsPath(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, GetAsPathHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getAsPath, targetEntityID, avbInterfaceIndex, handler);
        }

        void getEntityCounters(la::avdecc::UniqueIdentifier const targetEntityID, GetEntityCountersHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getEntityCounters, targetEntityID, handler);
        }

        void getAvbInterfaceCounters(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, GetAvbInterfaceCountersHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getAvbInterfaceCounters, targetEntityID, avbInterfaceIndex, handler);
        }

        void getClockDomainCounters(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, GetClockDomainCountersHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getClockDomainCounters, targetEntityID, clockDomainIndex, handler);
        }

        void getStreamInputCounters(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, GetStreamInputCountersHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamInputCounters, targetEntityID, streamIndex, handler);
        }

        void getStreamOutputCounters(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, GetStreamOutputCountersHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getStreamOutputCounters, targetEntityID, streamIndex, handler);
        }

        void reboot(la::avdecc::UniqueIdentifier const targetEntityID, RebootHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, reboot, targetEntityID, handler);
        }

        void rebootToFirmware(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, RebootToFirmwareHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, rebootToFirmware, targetEntityID, memoryObjectIndex, handler);
        }

        void startOperation(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, la::avdecc::entity::model::MemoryObjectOperationType const operationType, la::avdecc::MemoryBuffer const& memoryBuffer, StartOperationHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, startOperation, targetEntityID, descriptorType, descriptorIndex, operationType, memoryBuffer, handler);
        }

        void abortOperation(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, la::avdecc::entity::model::OperationID const operationID, AbortOperationHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, abortOperation, targetEntityID, descriptorType, descriptorIndex, operationID, handler);
        }

        void setMemoryObjectLength(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, std::uint64_t const length, SetMemoryObjectLengthHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setMemoryObjectLength, targetEntityID, configurationIndex, memoryObjectIndex, length, handler);
        }

        void getMemoryObjectLength(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, GetMemoryObjectLengthHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getMemoryObjectLength, targetEntityID, configurationIndex, memoryObjectIndex, handler);
        }

        void getDynamicInfo(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::controller::DynamicInfoParameters const& parameters, GetDynamicInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getDynamicInfo, targetEntityID, parameters, handler);
        }

        void setMaxTransitTime(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, std::chrono::nanoseconds const& maxTransitTime, SetMaxTransitTimeHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setMaxTransitTime, targetEntityID, streamIndex, maxTransitTime, handler);
        }

        void getMaxTransitTime(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::StreamIndex const streamIndex, GetMaxTransitTimeHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getMaxTransitTime, targetEntityID, streamIndex, handler);
        }

        void addressAccess(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::addressAccess::Tlvs const& tlvs, AddressAccessHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, addressAccess, targetEntityID, tlvs, handler);
        }

        void getMilanInfo(la::avdecc::UniqueIdentifier const targetEntityID, GetMilanInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getMilanInfo, targetEntityID, handler);
        }

        void setSystemUniqueID(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::SystemUniqueIdentifier const systemUniqueID, SetSystemUniqueIDHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setSystemUniqueID, targetEntityID, systemUniqueID, handler);
        }

        void getSystemUniqueID(la::avdecc::UniqueIdentifier const targetEntityID, GetSystemUniqueIDHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getSystemUniqueID, targetEntityID, handler);
        }

        void setMediaClockReferenceInfo(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, std::optional<la::avdecc::entity::model::MediaClockReferencePriority>const userPriority, std::optional<la::avdecc::entity::model::AvdeccFixedString>const& domainName, SetMediaClockReferenceInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, setMediaClockReferenceInfo, targetEntityID, clockDomainIndex, userPriority, domainName, handler);
        }

        void getMediaClockReferenceInfo(la::avdecc::UniqueIdentifier const targetEntityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, GetMediaClockReferenceInfoHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getMediaClockReferenceInfo, targetEntityID, clockDomainIndex, handler);
        }

        void connectStream(la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, ConnectStreamHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, connectStream, talkerStream, listenerStream, handler);
        }

        void disconnectStream(la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, DisconnectStreamHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, disconnectStream, talkerStream, listenerStream, handler);
        }

        void disconnectTalkerStream(la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, DisconnectTalkerStreamHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, disconnectTalkerStream, talkerStream, listenerStream, handler);
        }

        void getTalkerStreamState(la::avdecc::entity::model::StreamIdentification const& talkerStream, GetTalkerStreamStateHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getTalkerStreamState, talkerStream, handler);
        }

        void getListenerStreamState(la::avdecc::entity::model::StreamIdentification const& listenerStream, GetListenerStreamStateHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getListenerStreamState, listenerStream, handler);
        }

        void getTalkerStreamConnection(la::avdecc::entity::model::StreamIdentification const& talkerStream, std::uint16_t const connectionIndex, GetTalkerStreamConnectionHandler const& handler) const noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Interface, getTalkerStreamConnection, talkerStream, connectionIndex, handler);
        }
        // clang-format on
    };
} // namespace la::avdecc::entity::controller

/*-------------------------------------------------------------------------------------------------------------------*/
void bindControllerInterface(py::module_& m)
{
    using namespace la::avdecc::entity::controller;

    auto cls = py::class_<Interface, PyInterface>(m, "ControllerInterface").def(py::init<>());

    // TODO: Bind methods for Interface here.
}

/*-------------------------------------------------------------------------------------------------------------------*/
namespace la::avdecc::entity::controller
{
    class PyDelegate : public Delegate
    {
    public:
        using Delegate::Delegate;

        // clang-format off
        void onTransportError(la::avdecc::entity::controller::Interface const* const controller) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onTransportError, controller);
        }

        void onEntityOnline(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::Entity const& entity) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityOnline, controller, entityID, entity);
        }

        void onEntityUpdate(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::Entity const& entity) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityUpdate, controller, entityID, entity);
        }

        void onEntityOffline(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityOffline, controller, entityID);
        }

        void onControllerConnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onControllerConnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onControllerDisconnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onControllerDisconnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onListenerConnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onListenerConnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onListenerDisconnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onListenerDisconnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onGetTalkerStreamStateResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onGetTalkerStreamStateResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onGetListenerStreamStateResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onGetListenerStreamStateResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onDeregisteredFromUnsolicitedNotifications(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onDeregisteredFromUnsolicitedNotifications, controller, entityID);
        }

        void onEntityAcquired(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const owningEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityAcquired, controller, entityID, owningEntity, descriptorType, descriptorIndex);
        }

        void onEntityReleased(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const owningEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityReleased, controller, entityID, owningEntity, descriptorType, descriptorIndex);
        }

        void onEntityLocked(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const lockingEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityLocked, controller, entityID, lockingEntity, descriptorType, descriptorIndex);
        }

        void onEntityUnlocked(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const lockingEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityUnlocked, controller, entityID, lockingEntity, descriptorType, descriptorIndex);
        }

        void onConfigurationChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onConfigurationChanged, controller, entityID, configurationIndex);
        }

        void onStreamInputFormatChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamFormat const streamFormat) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamInputFormatChanged, controller, entityID, streamIndex, streamFormat);
        }

        void onStreamOutputFormatChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamFormat const streamFormat) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamOutputFormatChanged, controller, entityID, streamIndex, streamFormat);
        }

        void onStreamPortInputAudioMappingsChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::MapIndex const numberOfMaps, la::avdecc::entity::model::MapIndex const mapIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamPortInputAudioMappingsChanged, controller, entityID, streamPortIndex, numberOfMaps, mapIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::MapIndex const numberOfMaps, la::avdecc::entity::model::MapIndex const mapIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamPortOutputAudioMappingsChanged, controller, entityID, streamPortIndex, numberOfMaps, mapIndex, mappings);
        }

        void onStreamInputInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamInfo const& info, bool const fromGetStreamInfoResponse) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamInputInfoChanged, controller, entityID, streamIndex, info, fromGetStreamInfoResponse);
        }

        void onStreamOutputInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamInfo const& info, bool const fromGetStreamInfoResponse) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamOutputInfoChanged, controller, entityID, streamIndex, info, fromGetStreamInfoResponse);
        }

        void onEntityNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvdeccFixedString const& entityName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityNameChanged, controller, entityID, entityName);
        }

        void onEntityGroupNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvdeccFixedString const& entityGroupName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityGroupNameChanged, controller, entityID, entityGroupName);
        }

        void onConfigurationNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvdeccFixedString const& configurationName) noexcept override  
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onConfigurationNameChanged, controller, entityID, configurationIndex, configurationName);
        }

        void onAudioUnitNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, la::avdecc::entity::model::AvdeccFixedString const& audioUnitName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAudioUnitNameChanged, controller, entityID, configurationIndex, audioUnitIndex, audioUnitName);
        }

        void onStreamInputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::AvdeccFixedString const& streamName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamInputNameChanged, controller, entityID, configurationIndex, streamIndex, streamName);
        }

        void onStreamOutputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::AvdeccFixedString const& streamName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamOutputNameChanged, controller, entityID, configurationIndex, streamIndex, streamName);
        }

        void onJackInputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, la::avdecc::entity::model::AvdeccFixedString const& jackName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onJackInputNameChanged, controller, entityID, configurationIndex, jackIndex, jackName);
        }

        void onJackOutputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, la::avdecc::entity::model::AvdeccFixedString const& jackName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onJackOutputNameChanged, controller, entityID, configurationIndex, jackIndex, jackName);
        }

        void onAvbInterfaceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AvdeccFixedString const& avbInterfaceName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAvbInterfaceNameChanged, controller, entityID, configurationIndex, avbInterfaceIndex, avbInterfaceName);
        }

        void onClockSourceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex, la::avdecc::entity::model::AvdeccFixedString const& clockSourceName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onClockSourceNameChanged, controller, entityID, configurationIndex, clockSourceIndex, clockSourceName);
        }

        void onMemoryObjectNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, la::avdecc::entity::model::AvdeccFixedString const& memoryObjectName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onMemoryObjectNameChanged, controller, entityID, configurationIndex, memoryObjectIndex, memoryObjectName);
        }

        void onAudioClusterNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClusterIndex const audioClusterIndex, la::avdecc::entity::model::AvdeccFixedString const& audioClusterName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAudioClusterNameChanged, controller, entityID, configurationIndex, audioClusterIndex, audioClusterName);
        }

        void onControlNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ControlIndex const controlIndex, la::avdecc::entity::model::AvdeccFixedString const& controlName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onControlNameChanged, controller, entityID, configurationIndex, controlIndex, controlName);
        }

        void onClockDomainNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::AvdeccFixedString const& clockDomainName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onClockDomainNameChanged, controller, entityID, configurationIndex, clockDomainIndex, clockDomainName);
        }

        void onTimingNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::TimingIndex const timingIndex, la::avdecc::entity::model::AvdeccFixedString const& timingName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onTimingNameChanged, controller, entityID, configurationIndex, timingIndex, timingName);
        }

        void onPtpInstanceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpInstanceIndex const ptpInstanceIndex, la::avdecc::entity::model::AvdeccFixedString const& ptpInstanceName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onPtpInstanceNameChanged, controller, entityID, configurationIndex, ptpInstanceIndex, ptpInstanceName);
        }

        void onPtpPortNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpPortIndex const ptpPortIndex, la::avdecc::entity::model::AvdeccFixedString const& ptpPortName) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onPtpPortNameChanged, controller, entityID, configurationIndex, ptpPortIndex, ptpPortName);
        }

        void onAssociationIDChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const associationID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAssociationIDChanged, controller, entityID, associationID);
        }

        void onAudioUnitSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAudioUnitSamplingRateChanged, controller, entityID, audioUnitIndex, samplingRate);
        }

        void onVideoClusterSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClusterIndex const videoClusterIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onVideoClusterSamplingRateChanged, controller, entityID, videoClusterIndex, samplingRate);
        }

        void onSensorClusterSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClusterIndex const sensorClusterIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onSensorClusterSamplingRateChanged, controller, entityID, sensorClusterIndex, samplingRate);
        }

        void onClockSourceChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onClockSourceChanged, controller, entityID, clockDomainIndex, clockSourceIndex);
        }

        void onControlValuesChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ControlIndex const controlIndex, la::avdecc::MemoryBuffer const& packedControlValues) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onControlValuesChanged, controller, entityID, controlIndex, packedControlValues);
        }

        void onStreamInputStarted(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamInputStarted, controller, entityID, streamIndex);
        }

        void onStreamOutputStarted(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamOutputStarted, controller, entityID, streamIndex);
        }

        void onStreamInputStopped(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamInputStopped, controller, entityID, streamIndex);
        }

        void onStreamOutputStopped(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamOutputStopped, controller, entityID, streamIndex);
        }

        void onAvbInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AvbInfo const& info) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAvbInfoChanged, controller, entityID, avbInterfaceIndex, info);
        }

        void onAsPathChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AsPath const& asPath) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAsPathChanged, controller, entityID, avbInterfaceIndex, asPath);
        }

        void onEntityCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::EntityCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityCountersChanged, controller, entityID, validCounters, counters);
        }

        void onAvbInterfaceCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::AvbInterfaceCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAvbInterfaceCountersChanged, controller, entityID, avbInterfaceIndex, validCounters, counters);
        }

        void onClockDomainCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::ClockDomainCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onClockDomainCountersChanged, controller, entityID, clockDomainIndex, validCounters, counters);
        }

        void onStreamInputCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::StreamInputCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamInputCountersChanged, controller, entityID, streamIndex, validCounters, counters);
        }

        void onStreamOutputCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::StreamOutputCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamOutputCountersChanged, controller, entityID, streamIndex, validCounters, counters);
        }

        void onStreamPortInputAudioMappingsAdded(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamPortInputAudioMappingsAdded, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsAdded(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamPortOutputAudioMappingsAdded, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortInputAudioMappingsRemoved(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamPortInputAudioMappingsRemoved, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsRemoved(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onStreamPortOutputAudioMappingsRemoved, controller, entityID, streamPortIndex, mappings);
        }

        void onMemoryObjectLengthChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, std::uint64_t const length) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onMemoryObjectLengthChanged, controller, entityID, configurationIndex, memoryObjectIndex, length);
        }

        void onOperationStatus(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, la::avdecc::entity::model::OperationID const operationID, std::uint16_t const percentComplete) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onOperationStatus, controller, entityID, descriptorType, descriptorIndex, operationID, percentComplete);
        }

        void onMaxTransitTimeChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, std::chrono::nanoseconds const& maxTransitTime) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onMaxTransitTimeChanged, controller, entityID, streamIndex, maxTransitTime);
        }

        void onSystemUniqueIDChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::SystemUniqueIdentifier const systemUniqueID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onSystemUniqueIDChanged, controller, entityID, systemUniqueID);
        }

        void onMediaClockReferenceInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::MediaClockReferenceInfo const& mcrInfo) noexcept override    
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onMediaClockReferenceInfoChanged, controller, entityID, clockDomainIndex, mcrInfo);
        }

        void onEntityIdentifyNotification(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onEntityIdentifyNotification, controller, entityID);
        }

        void onAecpRetry(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAecpRetry, controller, entityID);
        }

        void onAecpTimeout(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAecpTimeout, controller, entityID);
        }

        void onAecpUnexpectedResponse(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAecpUnexpectedResponse, controller, entityID);
        }

        void onAecpResponseTime(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, std::chrono::milliseconds const& responseTime) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAecpResponseTime, controller, entityID, responseTime);
        }

        void onAemAecpUnsolicitedReceived(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, la::avdecc::protocol::AecpSequenceID const sequenceID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onAemAecpUnsolicitedReceived, controller, entityID, sequenceID);
        }

        void onMvuAecpUnsolicitedReceived(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, la::avdecc::protocol::AecpSequenceID const sequenceID) noexcept override
        {
            PYBIND11_OVERRIDE_PURE(void, Delegate, onMvuAecpUnsolicitedReceived, controller, entityID, sequenceID);
        }
        // clang-format on
    };
} // namespace la::avdecc::entity::controller


/*-------------------------------------------------------------------------------------------------------------------*/
void bindControllerDelegate(py::module_& m)
{
    using namespace la::avdecc::entity::controller;

    auto cls = py::class_<Delegate, PyDelegate>(m, "ControllerDelegate").def(py::init<>());

    // TODO: Bind methods for Delegate here.
}

/*-------------------------------------------------------------------------------------------------------------------*/

namespace la::avdecc::entity::controller
{
    class PyDefaultedDelegate : public DefaultedDelegate
    {
    public:
        using DefaultedDelegate::DefaultedDelegate;

        // clang-format off
        void onTransportError(la::avdecc::entity::controller::Interface const* const controller) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onTransportError, controller);
        }

        void onEntityOnline(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::Entity const& entity) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityOnline, controller, entityID, entity);
        }

        void onEntityUpdate(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::Entity const& entity) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityUpdate, controller, entityID, entity);
        }

        void onEntityOffline(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityOffline, controller, entityID);
        }

        void onControllerConnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onControllerConnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onControllerDisconnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onControllerDisconnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onListenerConnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onListenerConnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onListenerDisconnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onListenerDisconnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onGetTalkerStreamStateResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onGetTalkerStreamStateResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onGetListenerStreamStateResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onGetListenerStreamStateResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onDeregisteredFromUnsolicitedNotifications(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onDeregisteredFromUnsolicitedNotifications, controller, entityID);
        }

        void onEntityAcquired(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const owningEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityAcquired, controller, entityID, owningEntity, descriptorType, descriptorIndex);
        }

        void onEntityReleased(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const owningEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityReleased, controller, entityID, owningEntity, descriptorType, descriptorIndex);
        }

        void onEntityLocked(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const lockingEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityLocked, controller, entityID, lockingEntity, descriptorType, descriptorIndex);
        }

        void onEntityUnlocked(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const lockingEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityUnlocked, controller, entityID, lockingEntity, descriptorType, descriptorIndex);
        }

        void onConfigurationChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onConfigurationChanged, controller, entityID, configurationIndex);
        }

        void onStreamInputFormatChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamFormat const streamFormat) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamInputFormatChanged, controller, entityID, streamIndex, streamFormat);
        }

        void onStreamOutputFormatChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamFormat const streamFormat) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamOutputFormatChanged, controller, entityID, streamIndex, streamFormat);
        }

        void onStreamPortInputAudioMappingsChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::MapIndex const numberOfMaps, la::avdecc::entity::model::MapIndex const mapIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamPortInputAudioMappingsChanged, controller, entityID, streamPortIndex, numberOfMaps, mapIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::MapIndex const numberOfMaps, la::avdecc::entity::model::MapIndex const mapIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamPortOutputAudioMappingsChanged, controller, entityID, streamPortIndex, numberOfMaps, mapIndex, mappings);
        }

        void onStreamInputInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamInfo const& info, bool const fromGetStreamInfoResponse) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamInputInfoChanged, controller, entityID, streamIndex, info, fromGetStreamInfoResponse);
        }

        void onStreamOutputInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamInfo const& info, bool const fromGetStreamInfoResponse) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamOutputInfoChanged, controller, entityID, streamIndex, info, fromGetStreamInfoResponse);
        }

        void onEntityNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvdeccFixedString const& entityName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityNameChanged, controller, entityID, entityName);
        }

        void onEntityGroupNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvdeccFixedString const& entityGroupName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityGroupNameChanged, controller, entityID, entityGroupName);
        }

        void onConfigurationNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvdeccFixedString const& configurationName) noexcept override  
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onConfigurationNameChanged, controller, entityID, configurationIndex, configurationName);
        }

        void onAudioUnitNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, la::avdecc::entity::model::AvdeccFixedString const& audioUnitName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAudioUnitNameChanged, controller, entityID, configurationIndex, audioUnitIndex, audioUnitName);
        }

        void onStreamInputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::AvdeccFixedString const& streamName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamInputNameChanged, controller, entityID, configurationIndex, streamIndex, streamName);
        }

        void onStreamOutputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::AvdeccFixedString const& streamName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamOutputNameChanged, controller, entityID, configurationIndex, streamIndex, streamName);
        }

        void onJackInputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, la::avdecc::entity::model::AvdeccFixedString const& jackName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onJackInputNameChanged, controller, entityID, configurationIndex, jackIndex, jackName);
        }

        void onJackOutputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, la::avdecc::entity::model::AvdeccFixedString const& jackName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onJackOutputNameChanged, controller, entityID, configurationIndex, jackIndex, jackName);
        }

        void onAvbInterfaceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AvdeccFixedString const& avbInterfaceName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAvbInterfaceNameChanged, controller, entityID, configurationIndex, avbInterfaceIndex, avbInterfaceName);
        }

        void onClockSourceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex, la::avdecc::entity::model::AvdeccFixedString const& clockSourceName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onClockSourceNameChanged, controller, entityID, configurationIndex, clockSourceIndex, clockSourceName);
        }

        void onMemoryObjectNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, la::avdecc::entity::model::AvdeccFixedString const& memoryObjectName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onMemoryObjectNameChanged, controller, entityID, configurationIndex, memoryObjectIndex, memoryObjectName);
        }

        void onAudioClusterNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClusterIndex const audioClusterIndex, la::avdecc::entity::model::AvdeccFixedString const& audioClusterName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAudioClusterNameChanged, controller, entityID, configurationIndex, audioClusterIndex, audioClusterName);
        }

        void onControlNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ControlIndex const controlIndex, la::avdecc::entity::model::AvdeccFixedString const& controlName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onControlNameChanged, controller, entityID, configurationIndex, controlIndex, controlName);
        }

        void onClockDomainNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::AvdeccFixedString const& clockDomainName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onClockDomainNameChanged, controller, entityID, configurationIndex, clockDomainIndex, clockDomainName);
        }

        void onTimingNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::TimingIndex const timingIndex, la::avdecc::entity::model::AvdeccFixedString const& timingName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onTimingNameChanged, controller, entityID, configurationIndex, timingIndex, timingName);
        }

        void onPtpInstanceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpInstanceIndex const ptpInstanceIndex, la::avdecc::entity::model::AvdeccFixedString const& ptpInstanceName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onPtpInstanceNameChanged, controller, entityID, configurationIndex, ptpInstanceIndex, ptpInstanceName);
        }

        void onPtpPortNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpPortIndex const ptpPortIndex, la::avdecc::entity::model::AvdeccFixedString const& ptpPortName) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onPtpPortNameChanged, controller, entityID, configurationIndex, ptpPortIndex, ptpPortName);
        }

        void onAssociationIDChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const associationID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAssociationIDChanged, controller, entityID, associationID);
        }

        void onAudioUnitSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAudioUnitSamplingRateChanged, controller, entityID, audioUnitIndex, samplingRate);
        }

        void onVideoClusterSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClusterIndex const videoClusterIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onVideoClusterSamplingRateChanged, controller, entityID, videoClusterIndex, samplingRate);
        }

        void onSensorClusterSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClusterIndex const sensorClusterIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onSensorClusterSamplingRateChanged, controller, entityID, sensorClusterIndex, samplingRate);
        }

        void onClockSourceChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onClockSourceChanged, controller, entityID, clockDomainIndex, clockSourceIndex);
        }

        void onControlValuesChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ControlIndex const controlIndex, la::avdecc::MemoryBuffer const& packedControlValues) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onControlValuesChanged, controller, entityID, controlIndex, packedControlValues);
        }

        void onStreamInputStarted(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamInputStarted, controller, entityID, streamIndex);
        }

        void onStreamOutputStarted(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamOutputStarted, controller, entityID, streamIndex);
        }

        void onStreamInputStopped(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamInputStopped, controller, entityID, streamIndex);
        }

        void onStreamOutputStopped(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamOutputStopped, controller, entityID, streamIndex);
        }

        void onAvbInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AvbInfo const& info) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAvbInfoChanged, controller, entityID, avbInterfaceIndex, info);
        }

        void onAsPathChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AsPath const& asPath) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAsPathChanged, controller, entityID, avbInterfaceIndex, asPath);
        }

        void onEntityCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::EntityCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityCountersChanged, controller, entityID, validCounters, counters);
        }

        void onAvbInterfaceCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::AvbInterfaceCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAvbInterfaceCountersChanged, controller, entityID, avbInterfaceIndex, validCounters, counters);
        }

        void onClockDomainCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::ClockDomainCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onClockDomainCountersChanged, controller, entityID, clockDomainIndex, validCounters, counters);
        }

        void onStreamInputCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::StreamInputCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamInputCountersChanged, controller, entityID, streamIndex, validCounters, counters);
        }

        void onStreamOutputCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::StreamOutputCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamOutputCountersChanged, controller, entityID, streamIndex, validCounters, counters);
        }

        void onStreamPortInputAudioMappingsAdded(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamPortInputAudioMappingsAdded, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsAdded(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamPortOutputAudioMappingsAdded, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortInputAudioMappingsRemoved(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamPortInputAudioMappingsRemoved, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsRemoved(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onStreamPortOutputAudioMappingsRemoved, controller, entityID, streamPortIndex, mappings);
        }

        void onMemoryObjectLengthChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, std::uint64_t const length) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onMemoryObjectLengthChanged, controller, entityID, configurationIndex, memoryObjectIndex, length);
        }

        void onOperationStatus(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, la::avdecc::entity::model::OperationID const operationID, std::uint16_t const percentComplete) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onOperationStatus, controller, entityID, descriptorType, descriptorIndex, operationID, percentComplete);
        }

        void onMaxTransitTimeChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, std::chrono::nanoseconds const& maxTransitTime) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onMaxTransitTimeChanged, controller, entityID, streamIndex, maxTransitTime);
        }

        void onSystemUniqueIDChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::SystemUniqueIdentifier const systemUniqueID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onSystemUniqueIDChanged, controller, entityID, systemUniqueID);
        }

        void onMediaClockReferenceInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::MediaClockReferenceInfo const& mcrInfo) noexcept override    
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onMediaClockReferenceInfoChanged, controller, entityID, clockDomainIndex, mcrInfo);
        }

        void onEntityIdentifyNotification(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onEntityIdentifyNotification, controller, entityID);
        }

        void onAecpRetry(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAecpRetry, controller, entityID);
        }

        void onAecpTimeout(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAecpTimeout, controller, entityID);
        }

        void onAecpUnexpectedResponse(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAecpUnexpectedResponse, controller, entityID);
        }

        void onAecpResponseTime(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, std::chrono::milliseconds const& responseTime) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAecpResponseTime, controller, entityID, responseTime);
        }

        void onAemAecpUnsolicitedReceived(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, la::avdecc::protocol::AecpSequenceID const sequenceID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onAemAecpUnsolicitedReceived, controller, entityID, sequenceID);
        }

        void onMvuAecpUnsolicitedReceived(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, la::avdecc::protocol::AecpSequenceID const sequenceID) noexcept override
        {
            PYBIND11_OVERRIDE(void, DefaultedDelegate, onMvuAecpUnsolicitedReceived, controller, entityID, sequenceID);
        }
        // clang-format on
    };
} // namespace la::avdecc::entity::controller

/*-------------------------------------------------------------------------------------------------------------------*/
void bindControllerDefaultedDelegate(py::module_& m)
{
    using namespace la::avdecc::entity::controller;

    auto cls = py::class_<DefaultedDelegate, PyDefaultedDelegate>(m, "ControllerDefaultedDelegate").def(py::init<>());

    // TODO: Bind methods for DefaultedDelegate here.
}

/*-------------------------------------------------------------------------------------------------------------------*/