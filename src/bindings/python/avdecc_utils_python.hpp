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

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Special lbirary binding helpers --------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
template <typename EnumType>
void bindEnumBitfield(py::handle scope, const std::string& py_class_name)
{
    using namespace la::avdecc::utils;
    using Bitfield = EnumBitfield<EnumType>;

    py::class_<Bitfield> cls(scope, py_class_name.c_str());

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
            oss << "<" << py_class_name << " " << self.value() << ">";
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

/*-------------------------------------------------------------------------------------------------------------------*/
template <typename Derived, typename DataType>
py::class_<la::avdecc::utils::TypedDefine<Derived, DataType>> bindTypedDefine(py::module_&       m,
                                                                              const std::string& py_class_name)
{
    using namespace la::avdecc::utils;
    using derived_type = Derived;
    using value_type   = DataType;
    using EnumWrapper  = TypedDefine<derived_type, value_type>;

    py::class_<EnumWrapper>(m, ("_" + py_class_name + "Base").c_str());

    auto cls =
        py::class_<Derived, EnumWrapper>(m, py_class_name.c_str())
            .def(py::init<value_type>())
            .def_property("value", &EnumWrapper::getValue, &EnumWrapper::setValue)
            .def("__eq__", &EnumWrapper::operator==)
            .def("__ne__", &EnumWrapper::operator!=)
            .def("__int__", [](const EnumWrapper& self) { return static_cast<value_type>(self); })
            .def("__and__", [](const EnumWrapper& lhs, const EnumWrapper& rhs) -> EnumWrapper { return lhs & rhs; })
            .def("__or__", [](const EnumWrapper& lhs, const EnumWrapper& rhs) -> EnumWrapper { return lhs | rhs; })
            .def("__str__",
                 [](const EnumWrapper& self) {
                     const derived_type& derived = static_cast<const derived_type&>(self);
                     return static_cast<std::string>(derived);
                 })
            .def("__repr__", [=](py::object self) {
                // Attempt to find the name of the enum value from within the python class
                const auto  cls   = self.get_type();
                const auto  value = self.attr("value");
                std::string name  = "Undefined";

                const auto dir = py::module_::import("builtins").attr("dir")(cls);
                for (const py::handle& item : dir)
                {
                    const std::string key = py::str(item);

                    try
                    {
                        const py::object attr_val = cls.attr(key.c_str());

                        if (!py::isinstance(attr_val, cls))
                            continue;

                        if (attr_val.equal(self))
                        {
                            name = key;
                            break;
                        }
                    } catch (...)
                    {}
                }

                // Format the string representation
                std::ostringstream oss;
                oss << "<" << py_class_name.c_str() << "." << name << ": "
                    << static_cast<std::uint64_t>(py::int_(value).cast<value_type>()) << ">";
                return oss.str();
            });

    return cls;
}
