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
#include "avdecc_utils_python.hpp"

#include "config.hpp"
#include <la/avdecc/avdecc.hpp>

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void bindCompileOptions(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Module entry definition ----------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
PYBIND11_MODULE(la_avdecc, m)
{
    using namespace la::avdecc;

    m.doc() = "Python bindings for la::avdecc";

    m.def(
        "getLibraryVersion", []() -> std::string { return internals::versionString; },
        "Gets the library version string.");
    m.def(
        "getLibraryName", []() -> std::string { return internals::applicationLongName; },
        "Gets the full name of the library.");
    m.def(
        "getLibraryCopyright", []() -> std::string { return internals::readableCopyright; },
        "Gets the copyright string of the library.");
    m.def("getInterfaceVersion", &getInterfaceVersion, "Gets the interface version of the library.");

    bindCompileOptions(m);
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