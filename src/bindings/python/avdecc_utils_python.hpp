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
 * @file avdecc_utils_python.cpp
 * @author Vitalij Mast
 */

#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <la/avdecc/utils.hpp>

namespace py = pybind11;

template <typename EnumType>
void bindEnumBitfield(py::module_& m, const std::string& py_class_name)
{
    using namespace la::avdecc::utils;
    using Bitfield = EnumBitfield<EnumType>;

    py::class_<Bitfield> cls(m, py_class_name.c_str());

    cls.def(py::init<>())
        .def(py::init<EnumType>())
        .def("set", &Bitfield::set, py::return_value_policy::reference_internal)
        .def("reset", &Bitfield::reset, py::return_value_policy::reference_internal)
        .def("test", &Bitfield::test)
        .def("clear", &Bitfield::clear)
        .def("empty", &Bitfield::empty)
        .def("count", &Bitfield::count)
        .def("value", &Bitfield::value)
        .def("__or__", [](const Bitfield& a, const Bitfield& b) { return a | b; })
        .def("__and__", [](const Bitfield& a, const Bitfield& b) { return a & b; })
        .def("__eq__", &Bitfield::operator==)
        .def("__ne__", &Bitfield::operator!=)
        .def("__repr__", [=](const Bitfield& self) {
            std::ostringstream oss;
            oss << "<" << py_class_name << " "
                << self.value() << ">";
            return oss.str();
        });

    py::class_<typename Bitfield::iterator>(cls, "iterator")
        .def("__iter__", [](typename Bitfield::iterator& it) -> typename Bitfield::iterator& { return it; })
        .def("__next__", [](typename Bitfield::iterator& it) {
            if (it == Bitfield{}.end())
                throw py::stop_iteration();
            EnumType val = *it;
            ++it;
            return val;
        });

    cls.def(
        "__iter__", [](const Bitfield& self) { return py::make_iterator(self.begin(), self.end()); },
        py::keep_alive<0, 1>());
}
