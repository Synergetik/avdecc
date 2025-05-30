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
 * @file utils.hpp
 * @author Vitalij Mast
 * @brief Pybind helper methods.
 */

#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- pybind helpers -------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
namespace py = pybind11;

// For non-const member functions
template <typename Ret, typename Class, typename... Args>
auto with_released_gil(Ret (Class::*method)(Args...))
{
    return [method](Class* self, Args... args) -> Ret {
        py::gil_scoped_release release;
        return (self->*method)(std::forward<Args>(args)...);
    };
}

// For const member functions
template <typename Ret, typename Class, typename... Args>
auto with_released_gil(Ret (Class::*method)(Args...) const)
{
    return [method](const Class* self, Args... args) -> Ret {
        py::gil_scoped_release release;
        return (self->*method)(std::forward<Args>(args)...);
    };
}
