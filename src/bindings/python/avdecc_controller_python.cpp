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

/*-------------------------------------------------------------------------------------------------------------------*/
void bindControllerEntity(py::module_& m)
{
    bindDynamicInfoParameter(m);
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
