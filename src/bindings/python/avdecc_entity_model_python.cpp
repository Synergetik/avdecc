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

#include "avdecc_entity_model_python.hpp"

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void bindUniqueIdentifier(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityModels(py::module_& m)
{
    bindUniqueIdentifier(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindUniqueIdentifier(py::module_& m)
{
    using namespace la::avdecc;
    py::class_<UniqueIdentifier>(m, "UniqueIdentifier")
        .def(py::init<>())
        .def(py::init<UniqueIdentifier::value_type>(), py::arg("value"))

        .def("setValue", &UniqueIdentifier::setValue)
        .def("getValue", &UniqueIdentifier::getValue)
        .def_property_readonly("isGroupIdentifier", &UniqueIdentifier::isGroupIdentifier)
        .def_property_readonly("isLocalIdentifier", &UniqueIdentifier::isLocalIdentifier)
        .def_property_readonly("isValid", &UniqueIdentifier::isValid)

        .def("__eq__", [](const UniqueIdentifier& a, const UniqueIdentifier& b) { return a == b; })
        .def("__ne__", [](const UniqueIdentifier& a, const UniqueIdentifier& b) { return a != b; })
        .def("__lt__", [](const UniqueIdentifier& a, const UniqueIdentifier& b) { return a < b; })
        .def("__int__", &UniqueIdentifier::operator UniqueIdentifier::value_type)
        .def("__repr__",
             [](const UniqueIdentifier& uid) {
                 std::ostringstream oss;
                 oss << "UniqueIdentifier(0x" << std::hex << uid.getValue() << ")";
                 return oss.str();
             })

        .def_static("getNullUniqueIdentifier", &UniqueIdentifier::getNullUniqueIdentifier)
        .def_static("getUninitializedUniqueIdentifier", &UniqueIdentifier::getUninitializedUniqueIdentifier);
}
