////////////////////////////////////////
// SWIG FACILITY AND HELPER DEFINITION file
///////////////////////////////////////

%{
#include <span>

#include <string_view>
#include <typeinfo>
#include <sstream>
#include <fmt/format.h>

namespace facility
{
    template <class T>
    constexpr std::string_view type_name(T const* self)
    {
        return typeid(*self).name();
    }

    template <class T>
    constexpr std::string_view class_name(T const* self)
    {
        using namespace std::literals;
        constexpr auto klass = "class "sv;

        // strip prefix if any
        auto name = type_name(self);
        name.remove_prefix(klass.size());

        // strip namespace if any
        auto pos = name.rfind("::");
        auto nsp = (pos == std::string::npos) ? 0 : pos + 2;

        return name.substr(nsp);
    }
} // namespace syn
%}

#if defined(SWIGPYTHON)
	%typemap(in) std::span<uint8_t const> const& {
		char *data = 0;
		Py_ssize_t size = 0;
		int res$argnum;

		res$argnum = PyBytes_AsStringAndSize($input, &data, &size);
		if (!SWIG_IsOK(res$argnum)) {
		%argument_fail(res$argnum, $1_type, $symname, $argnum);
		}

		$1 = new $*1_ltype  { reinterpret_cast<uint8_t const*>(data), static_cast<size_t>(size) };
	}
	%typemap(freearg) std::span<uint8_t const> const& {
		delete $1;
	}

	%typemap(typecheck) std::span<uint8_t const> const& {
		$1 = PyBytes_Check($input);
	}

	%typemap(out) std::span<uint8_t const> {
		$result = PyBytes_FromStringAndSize(reinterpret_cast<const char*>($1.data()), $1.size());
	}
#endif

%define SWIG_PY_REPR(Class, Body)
#if defined(SWIGPYTHON)
%extend Class {
    std::string __repr__() {
        std::ostringstream oss;

        oss << "<" << facility::class_name($self) << "; ";

        Body

        oss << ">";

        return oss.str();
    }
}
#endif
%enddef