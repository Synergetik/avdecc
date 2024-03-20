////////////////////////////////////////
// SWIG FACILITY AND HELPER DEFINITION file
///////////////////////////////////////

%{
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