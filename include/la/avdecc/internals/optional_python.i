#include <optional>

// The macro arguments for all these macros are the name of the exported class
// and the C++ type T of std::optional<T> to generate the typemaps for.

// Common part of the macros below, shouldn't be used directly.
%define DEFINE_OPTIONAL_HELPER(OptT, T)

// Do this to use reference typemaps instead of the pointer ones used by
// default for the member variables of this type.
//
// Notice that this must be done before %template below, SWIG must know about
// all features attached to the type before dealing with it.
%naturalvar std::optional< T >;

// Even although we're not going to really use them, we must still name the
// exported template instantiation, otherwise SWIG would give it an
// auto-generated name starting with SWIGTYPE which would be even uglier.
%template(OptT) std::optional< T >;

%enddef


%define DEFINE_OPTIONAL_SIMPLE(OptT, T, defValue)

DEFINE_OPTIONAL_HELPER(OptT, T)

// This typemap is used for function arguments and for setting member fields of
// std::optional<> type.
//
// Also note the hack with shadowing $1 below: it is a bit ridiculous, but it
// seems like we don't have any way to reuse the typemap defined for T without
// defining this nested variable with the same name as the original one, but
// with the right type. I.e. this $1 intentionally hides the real $1, of type
// "std::optional<T>*", so that $typemap() code compiles correctly.
%typemap(in,implicitconv=1) std::optional< T > %{
  if ($input != Py_None)
  {
    $typemap(in, T)
  }
  %}

%typemap(in,implicitconv=1) const std::optional< T >& (std::optional< T > val) %{
  $1 = &val;
  if ($input != Py_None)
  {
    T $1;
    $typemap(in, T)
    val.emplace($1);
  }
  %}

// For dynamic languages, such as Python, there should be a typecheck typemap
// for each in typemap to allow overloaded functions taking this type to work.
%typemap(typecheck, precedence=SWIG_TYPECHECK_POINTER) std::optional< T >, const std::optional< T >& (std::optional< T > tmp_ov) %{
  if ($input == Py_None)
    $1 = true;
  else {
    $typemap(typecheck, T)
  }
  %}

// This typemap is for functions returning objects of this type.
//
// It again needs to use an ugly trick with shadowing, this time of "result",
// to make the code from $typemap() expansion work correctly.
%typemap(out) std::optional< T > %{
  if ( $1.has_value() )
  {
    std::optional< T >& tmp_ov = $1;
    {
      T result = tmp_ov.value();
      $typemap(out, T)
    }
  }
  else
  {
    $result = Py_None;
    Py_INCREF(Py_None);
  }
  %}

// And this one is for members of this type.
//
// It's basically the same as above, but the type of "$1" is different here.
%typemap(out) std::optional< T >& %{
  if ( $1->has_value() )
  {
    std::optional< T >* tmp_ptr = $1;
    {
      T result = tmp_ptr->value();
      $typemap(out, T)
    }
  }
  else
  {
    $result = Py_None;
    Py_INCREF(Py_None);
  }
  %}

%enddef


%define DEFINE_OPTIONAL_CLASS_HELPER(OptT, T)
DEFINE_OPTIONAL_SIMPLE(OptT, T, 0)
%enddef

// This macro should be used for optional classes which are represented by
// either a valid object or a default value in C#.
//
// Its arguments are the scope in which the class is defined (either a
// namespace or, possibly, a class name if this is a nested class) and the
// unqualified name of the class, the name of the exported optional type is
// defined by the third argument.
// Default value must be defined as forth argument, null by default
%define DEFINE_OPTIONAL_CLASS(scope, classname, name)

DEFINE_OPTIONAL_CLASS_HELPER(name, scope::classname)

%enddef