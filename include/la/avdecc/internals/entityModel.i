////////////////////////////////////////
// AVDECC ENTITY MODEL SWIG file
////////////////////////////////////////

%module(directors="1", threads="1") avdeccEntityModel
%feature("nothreadallow");

%include <stdint.i>
%include <std_string.i>
%include <std_pair.i>
%include <std_vector.i>
%include <std_array.i>
%include <std_set.i>
%include "la/avdecc/internals/std_unordered_map.i" // From https://github.com/microsoft/CNTK/blob/master/bindings/csharp/Swig/std_unordered_map.i and https://github.com/swig/swig/pull/2480
%include "la/avdecc/internals/optional.i"
%include "la/avdecc/internals/swig_facility.i"

// Generated wrapper file needs to include our header file
%{
		#include <la/avdecc/internals/entityModel.hpp>
		#include <la/avdecc/internals/entityAddressAccessTypes.hpp>
		#include <la/avdecc/internals/streamFormatInfoPublic.hpp>
		#include <la/avdecc/internals/entityModelControlValues.hpp>
%}

// C# Specifics
#if defined(SWIGCSHARP)
// Optimize code generation by enabling RVO
%typemap(out, optimal="1") SWIGTYPE
%{
    $result = new $1_ltype(($1_ltype const&)$1);
%}
// Marshal all std::string as UTF8Str
%typemap(imtype, outattributes="[return: System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.LPUTF8Str)]", inattributes="[System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.LPUTF8Str)] ") std::string, std::string const& "string"
// Better debug display
%typemap(csattributes) la::avdecc::entity::model::AvdeccFixedString "[System.Diagnostics.DebuggerDisplay(\"{toString()}\")]"
#endif

// Force define AVDECC C/C++ API Macros to nothing
#define LA_AVDECC_API
#define LA_AVDECC_CALL_CONVENTION

// Other defines
#define ENABLE_AVDECC_FEATURE_REDUNDANCY 1

////////////////////////////////////////
// Utils
////////////////////////////////////////
%include "la/avdecc/utils.i"


////////////////////////////////////////
// UniqueIdentifier
////////////////////////////////////////
%nspaceapp(la::avdecc::UniqueIdentifier);
%ignore la::avdecc::UniqueIdentifier::operator value_type() const noexcept; // Ignore, don't need it (already have getValue() method)
%ignore la::avdecc::UniqueIdentifier::operator bool() const noexcept; // Ignore, don't need it (already have isValid() method)
#if defined(SWIGCSHARP)
%rename("isEqual") operator==(UniqueIdentifier const& lhs, UniqueIdentifier const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
%rename("isDifferent") operator!=(UniqueIdentifier const& lhs, UniqueIdentifier const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
%rename("isLess") operator<(UniqueIdentifier const& lhs, UniqueIdentifier const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
#elif defined(SWIGPYTHON)
%rename("__eq__") la::avdecc::UniqueIdentifier::operator==(UniqueIdentifier const& lhs, UniqueIdentifier const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
%rename("__ne__") la::avdecc::UniqueIdentifier::operator!=(UniqueIdentifier const& lhs, UniqueIdentifier const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
%rename("__lt__") la::avdecc::UniqueIdentifier::operator<(UniqueIdentifier const& lhs, UniqueIdentifier const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
#endif
%ignore la::avdecc::UniqueIdentifier::hash::operator(); // Ignore hash functor
%ignore la::avdecc::UniqueIdentifier::UniqueIdentifier(UniqueIdentifier&&); // Ignore move constructor
%ignore la::avdecc::UniqueIdentifier::operator=; // Ignore copy operator
// Extend the class
%extend la::avdecc::UniqueIdentifier
{
#if defined(SWIGCSHARP)
	// Provide a more native Equals() method
	bool Equals(la::avdecc::UniqueIdentifier const& other) const noexcept
	{
		return *$self == other;
	}
#endif
}

#if defined(SWIGPYTHON)
%typemap(out) la::avdecc::UniqueIdentifier (la::avdecc::UniqueIdentifier* inter = 0) %{
	inter = new la::avdecc::UniqueIdentifier($1);
	$result = SWIG_NewPointerObj(SWIG_as_voidptr(inter), $descriptor(la::avdecc::UniqueIdentifier*), SWIG_POINTER_OWN |  0 );
%}
#endif

SWIG_PY_REPR(la::avdecc::UniqueIdentifier, {
			if ($self->isValid())
			{
				oss << fmt::format("{:08X}", $self->getValue());
			} else
			{
				oss << "invalid";
			}
});

%rename("%s") la::avdecc::UniqueIdentifier::~UniqueIdentifier;


// Include c++ declaration file
%include "la/avdecc/internals/uniqueIdentifier.hpp"


////////////////////////////////////////
// Entity Model Types
////////////////////////////////////////
// Define some macros
%define DEFINE_AEM_TYPES_ENUM_CLASS(name, type)
	%nspaceapp(la::avdecc::entity::model::name);
#if defined(SWIGCSHARP)
	%typemap(csbase) la::avdecc::entity::model::name type
	%rename("isEqual") la::avdecc::entity::model::operator==(name const, name const); // Not put in a namespace https://github.com/swig/swig/issues/2459
#elif defined(SWIGPYTHON)
	%rename("__eq__") la::avdecc::entity::model::operator==(name const, name const); // Not put in a namespace https://github.com/swig/swig/issues/2459
#endif
	%rename("$ignore") la::avdecc::entity::model::operator==(name const, std::underlying_type_t<name> const);
%enddef
%define DEFINE_AEM_TYPES_STRUCT(name)
	%nspaceapp(la::avdecc::entity::model::name);
	%rename("%s") la::avdecc::entity::model::name; // Unignore class
#if defined(SWIGCSHARP)
	%rename("isEqual") operator==(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	%rename("isDifferent") operator!=(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
#elif defined(SWIGPYTHON)
	%rename("__eq__") la::avdecc::entity::model::##name::operator==(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	%rename("__ne__") la::avdecc::entity::model::##name::operator!=(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	
	%typemap(out) la::avdecc::entity::model::name (la::avdecc::entity::model::name* inter = 0) %{
		inter = new la::avdecc::entity::model::name($1);
		$result = SWIG_NewPointerObj(SWIG_as_voidptr(inter), $descriptor(la::avdecc::entity::model::name*), SWIG_POINTER_OWN |  0 );
	%}
#endif
	// Extend the class
	%extend la::avdecc::entity::model::name
	{
#if defined(SWIGCSHARP)
		// Provide a more native Equals() method
		bool Equals(la::avdecc::entity::model::name const& other) const noexcept
		{
			return *$self == other;
		}
#endif
	}
%enddef
%define DEFINE_AEM_TYPES_CLASS_BASE(name)
	%nspaceapp(la::avdecc::entity::model::name);
	%rename("%s") la::avdecc::entity::model::name; // Unignore class
	%ignore la::avdecc::entity::model::name::name(name&&); // Ignore move constructor
	%ignore la::avdecc::entity::model::name::operator=; // Ignore copy operator
%enddef
%define DEFINE_AEM_TYPES_CLASS(name)
	DEFINE_AEM_TYPES_CLASS_BASE(name)
	%ignore la::avdecc::entity::model::name::operator value_type() const noexcept;
	%ignore la::avdecc::entity::model::name::operator bool() const noexcept;
#if defined(SWIGCSHARP)
	%rename("isEqual") operator==(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	%rename("isDifferent") operator!=(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	%rename("isLess") operator<(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
#elif defined(SWIGPYTHON)
	%rename("__eq__") la::avdecc::entity::model::##name::operator==(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	%rename("__ne__") la::avdecc::entity::model::##name::operator!=(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	%rename("__lt__") la::avdecc::entity::model::##name::operator<(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
#endif
	// Extend the class
	%extend la::avdecc::entity::model::name
	{
#if defined(SWIGCSHARP)
		// Provide a more native Equals() method
		bool Equals(la::avdecc::entity::model::name const& other) const noexcept
		{
			return *$self == other;
		}
#endif
	}
%enddef

// Bind enums
DEFINE_AEM_TYPES_ENUM_CLASS(AudioClusterFormat, "byte")
DEFINE_AEM_TYPES_ENUM_CLASS(ClockSourceType, "ushort")
DEFINE_AEM_TYPES_ENUM_CLASS(DescriptorType, "ushort")
%rename("isValid") la::avdecc::entity::model::operator!(DescriptorType const); // Not put in a namespace https://github.com/swig/swig/issues/2459
DEFINE_AEM_TYPES_ENUM_CLASS(JackType, "ushort")
DEFINE_AEM_TYPES_ENUM_CLASS(MemoryObjectOperationType, "ushort")
DEFINE_AEM_TYPES_ENUM_CLASS(MemoryObjectType, "ushort")
DEFINE_AEM_TYPES_ENUM_CLASS(TimingAlgorithm, "ushort")
DEFINE_AEM_TYPES_ENUM_CLASS(PtpPortType, "ushort")
DEFINE_AEM_TYPES_ENUM_CLASS(StandardControlType, "ulong")
DEFINE_AEM_TYPES_ENUM_CLASS(ProbingStatus, "byte")
DEFINE_AEM_TYPES_ENUM_CLASS(MsrpFailureCode, "byte")

// Bind structs and classes
%rename($ignore, %$isclass) ""; // Ignore all structs/classes, manually re-enable

DEFINE_AEM_TYPES_STRUCT(AudioMapping);
DEFINE_AEM_TYPES_STRUCT(MsrpMapping);
DEFINE_AEM_TYPES_STRUCT(StreamIdentification);
%rename("isLess") la::avdecc::entity::model::operator<(StreamIdentification const&, StreamIdentification const&); // Not put in a namespace https://github.com/swig/swig/issues/2459

DEFINE_AEM_TYPES_CLASS_BASE(AvdeccFixedString);
%ignore la::avdecc::entity::model::AvdeccFixedString::data(); // RIGHT NOW IGNORE IT AS WE NEED TO FIND A WAY TO MARSHALL THE RETURNED POINTER
%ignore la::avdecc::entity::model::AvdeccFixedString::data() const; // RIGHT NOW IGNORE IT AS WE NEED TO FIND A WAY TO MARSHALL THE RETURNED POINTER
%ignore la::avdecc::entity::model::AvdeccFixedString::AvdeccFixedString(void const* const ptr, size_t const size) noexcept; // RIGHT NOW IGNORE IT AS WE NEED TO FIND A WAY TO MARSHALL THE RETURNED POINTER
%ignore la::avdecc::entity::model::AvdeccFixedString::assign(void const* const ptr, size_t const size) noexcept; // RIGHT NOW IGNORE IT AS WE NEED TO FIND A WAY TO MARSHALL THE RETURNED POINTER
#if defined(SWIGCSHARP)
%rename("isEqual") la::avdecc::entity::model::AvdeccFixedString::operator==;
%rename("isDifferent") la::avdecc::entity::model::AvdeccFixedString::operator!=;
%rename("toString") la::avdecc::entity::model::AvdeccFixedString::operator std::string;
#elif defined(SWIGPYTHON)
%rename("__eq__") la::avdecc::entity::model::AvdeccFixedString::operator==;
%rename("__ne__") la::avdecc::entity::model::AvdeccFixedString::operator!=;
%rename("__str__") la::avdecc::entity::model::AvdeccFixedString::operator std::string;
#endif
%ignore la::avdecc::entity::model::AvdeccFixedString::operator[](size_t const pos);
%ignore la::avdecc::entity::model::AvdeccFixedString::operator[](size_t const pos) const;
%ignore operator<<(std::ostream&, la::avdecc::entity::model::AvdeccFixedString const&);
// Extend the class
%extend la::avdecc::entity::model::AvdeccFixedString
{
#if defined(SWIGCSHARP)
	// Provide a more native ToString() method
	std::string ToString() const noexcept
	{
		return static_cast<std::string>(*$self);
	}
	// Provide a more native Equals() method
	bool Equals(la::avdecc::entity::model::AvdeccFixedString const& other) const noexcept
	{
		return *$self == other;
	}
#endif
}
SWIG_PY_REPR(la::avdecc::entity::model::AvdeccFixedString, {
			if (!$self->empty())
			{
				oss << fmt::format("'{}'", $self->str());
			} else
			{
				oss << "empty";
			}
});

DEFINE_AEM_TYPES_CLASS(SamplingRate);
DEFINE_AEM_TYPES_CLASS(StreamFormat);
DEFINE_AEM_TYPES_CLASS(LocalizedStringReference);
SWIG_PY_REPR(la::avdecc::entity::model::LocalizedStringReference, {
			if ($self->isValid())
			{
				auto offsetIndex = $self->getOffsetIndex();
				oss << fmt::format("@{},{}", offsetIndex.first, offsetIndex.second);
			} else
			{
				oss << "invalid";
			}
});

DEFINE_AEM_TYPES_CLASS(ControlValueUnit);
%typemap(csbase) la::avdecc::entity::model::ControlValueUnit::Unit "byte"
DEFINE_AEM_TYPES_CLASS(ControlValueType);
%typemap(csbase) la::avdecc::entity::model::ControlValueType::Type "ushort"
DEFINE_AEM_TYPES_CLASS_BASE(ControlValues);
%ignore la::avdecc::entity::model::ControlValues::operator bool() const noexcept;

// Include c++ declaration file
%include "la/avdecc/internals/entityModelTypes.hpp"
%rename("%s", %$isclass) ""; // Undo the ignore all structs/classes

// Define templates
%template(MultiplierUnit) std::pair<std::int8_t, la::avdecc::entity::model::ControlValueUnit::Unit>;
%template(PullBaseFrequency) std::pair<std::uint8_t, std::uint32_t>;
%template(OffsetIndex) std::pair<std::uint16_t, std::uint8_t>;
%template(AudioMappingVector) std::vector<la::avdecc::entity::model::AudioMapping>;
%template(MsrpMappingVector) std::vector<la::avdecc::entity::model::MsrpMapping>;
%template(UniqueIdentifierVector) std::vector<la::avdecc::UniqueIdentifier>;
%template(DescriptorCounterArray) std::array<la::avdecc::entity::model::DescriptorCounter, 32>;

#if defined(SWIGPYTHON)
// Custom python map for DescriptorCounterArray
%typemap(directorin) std::array< unsigned int,32 > const& (PyObject* inter = 0, Py_ssize_t index = 0) %{
	inter = PyTuple_New($1.size());
    for (const auto& n : $1) {
        auto val = SWIG_From_unsigned_SS_int(n);
        PyTuple_SetItem(inter, index++, val);
    }
	$input = inter;
  %}
#endif

#if defined(SWIGPYTHON)
// Custom python map for std::vector<la::avdecc::entity::model::ClockSourceIndex>
%typemap(out) std::vector<la::avdecc::entity::model::ClockSourceIndex>* %{
    $result = PyList_New(NULL);
    for (auto n : *$1) {
        auto val = SWIG_From_unsigned_SS_int(n);
        PyList_Append($result, val);
    }
  %}
#endif

#if defined(SWIGPYTHON)
	// Extend the class
	%extend la::avdecc::entity::model::ControlValues
	{
		// Provide a native constructor from bytearray
		ControlValues(std::span<uint8_t const> const& data, ControlValueType::Type const valueType, std::uint16_t const numberOfValues) {
			auto buffer = la::avdecc::MemoryBuffer(data.data(), data.size());
			auto values = la::avdecc::entity::model::unpackDynamicControlValues(buffer, valueType, numberOfValues);

			return values.has_value() ? new la::avdecc::entity::model::ControlValues { values.value() } : new la::avdecc::entity::model::ControlValues {};
    	}
	}
#endif

////////////////////////////////////////
// Entity Enums
////////////////////////////////////////

%typemap(constcode) int %{SWIG_Python_SetConstant(d, "$symname",PyLong_FromLongLong(static_cast< long long >($1)));%}

// Bind enums
DEFINE_ENUM_CLASS(la::avdecc::entity, EntityCapability, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, TalkerCapability, "ushort")
DEFINE_ENUM_CLASS(la::avdecc::entity, ListenerCapability, "ushort")
DEFINE_ENUM_CLASS(la::avdecc::entity, ControllerCapability, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, ConnectionFlag, "ushort")
DEFINE_ENUM_CLASS(la::avdecc::entity, StreamFlag, "ushort")
DEFINE_ENUM_CLASS(la::avdecc::entity, JackFlag, "ushort")
DEFINE_ENUM_CLASS(la::avdecc::entity, AvbInterfaceFlag, "ushort")
DEFINE_ENUM_CLASS(la::avdecc::entity, ClockSourceFlag, "ushort")
DEFINE_ENUM_CLASS(la::avdecc::entity, PortFlag, "ushort")
DEFINE_ENUM_CLASS(la::avdecc::entity, PtpInstanceFlag, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, PtpPortFlag, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, StreamInfoFlag, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, StreamInfoFlagEx, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, AvbInfoFlag, "byte")
DEFINE_ENUM_CLASS(la::avdecc::entity, EntityCounterValidFlag, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, AvbInterfaceCounterValidFlag, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, ClockDomainCounterValidFlag, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, StreamInputCounterValidFlag, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, StreamOutputCounterValidFlag, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, StreamOutputCounterValidFlag17221, "uint")
DEFINE_ENUM_CLASS(la::avdecc::entity, MilanInfoFeaturesFlag, "uint")

// Bind structs and classes
%rename($ignore, %$isclass) ""; // Ignore all structs/classes, manually re-enable

// Include c++ declaration file
%include "la/avdecc/internals/entityEnums.hpp"
%rename("%s", %$isclass) ""; // Undo the ignore all structs/classes

// Define templates
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, EntityCapabilities, EntityCapability, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, TalkerCapabilities, TalkerCapability, std::uint16_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, ListenerCapabilities, ListenerCapability, std::uint16_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, ControllerCapabilities, ControllerCapability, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, ConnectionFlags, ConnectionFlag, std::uint16_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, StreamFlags, StreamFlag, std::uint16_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, JackFlags, JackFlag, std::uint16_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, AvbInterfaceFlags, AvbInterfaceFlag, std::uint16_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, ClockSourceFlags, ClockSourceFlag, std::uint16_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, PortFlags, PortFlag, std::uint16_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, PtpInstanceFlags, PtpInstanceFlag, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, PtpPortFlags, PtpPortFlag, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, StreamInfoFlags, StreamInfoFlag, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, StreamInfoFlagsEx, StreamInfoFlagEx, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, AvbInfoFlags, AvbInfoFlag, std::uint8_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, EntityCounterValidFlags, EntityCounterValidFlag, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, AvbInterfaceCounterValidFlags, AvbInterfaceCounterValidFlag, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, ClockDomainCounterValidFlags, ClockDomainCounterValidFlag, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, StreamInputCounterValidFlags, StreamInputCounterValidFlag, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, StreamOutputCounterValidFlags, StreamOutputCounterValidFlag, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, StreamOutputCounterValidFlags17221, StreamOutputCounterValidFlag17221, std::uint32_t)
DEFINE_ENUM_BITFIELD_CLASS(la::avdecc::entity, MilanInfoFeaturesFlags, MilanInfoFeaturesFlag, std::uint32_t)


////////////////////////////////////////
// Protocol Defines
////////////////////////////////////////
%define DEFINE_BASE_PROTOCOL_CLASS(name)
	%nspaceapp(la::avdecc::protocol::name);
	%rename("%s") la::avdecc::protocol::name; // Unignore class
	%ignore la::avdecc::protocol::name::name(); // Ignore default constructor
	%rename("toString") la::avdecc::protocol::name::operator std::string() const noexcept;
#if defined(SWIGCSHARP)
	// Better debug display
	%typemap(csattributes) la::avdecc::protocol::name "[System.Diagnostics.DebuggerDisplay(\"{toString()}\")]"
#endif
	// Extend the class
	%extend la::avdecc::protocol::name
	{
#if defined(SWIGCSHARP)
		// Provide a more native ToString() method
		std::string ToString() const noexcept
		{
			return static_cast<std::string>(*$self);
		}
#endif
	}
#if defined(SWIGPYTHON)
%typemap(out) la::avdecc::protocol::name (la::avdecc::protocol::name* inter = 0) %{
	inter = new la::avdecc::protocol::name($1);
	$result = SWIG_NewPointerObj(SWIG_as_voidptr(inter), $descriptor(la::avdecc::protocol::name*), SWIG_POINTER_OWN |  0 );
%}
#endif
%enddef
%define DEFINE_TYPED_PROTOCOL_CLASS(name, typedName, underlyingType)
	DEFINE_BASE_PROTOCOL_CLASS(name)
	// Define the parent TypedDefine class (this template must be declare before including the protocolDefines.hpp file, TypedDefine has already been declared anyway)
	%template(typedName) la::avdecc::utils::TypedDefine<la::avdecc::protocol::name, underlyingType>;
%enddef

// Bind structs and classes
%rename($ignore, %$isclass) ""; // Ignore all structs/classes, manually re-enable

// TODO: Would be easier to map these types to the underlying integer type (but how to do it?)
DEFINE_TYPED_PROTOCOL_CLASS(AdpMessageType, AdpMessageTypedDefine, std::uint8_t)
DEFINE_TYPED_PROTOCOL_CLASS(AecpMessageType, AecpMessageTypedDefine, std::uint8_t)
DEFINE_TYPED_PROTOCOL_CLASS(AecpStatus, AecpStatusTypedDefine, std::uint8_t)
DEFINE_BASE_PROTOCOL_CLASS(AemAecpStatus)
%ignore la::avdecc::protocol::AemAecpStatus::AemAecpStatus(AecpStatus const status) noexcept; // Ignore constructor
DEFINE_TYPED_PROTOCOL_CLASS(AemCommandType, AemCommandTypedDefine, std::uint16_t)
DEFINE_TYPED_PROTOCOL_CLASS(AemAcquireEntityFlags, AemAcquireEntityFlagsTypedDefine, std::uint32_t)
DEFINE_TYPED_PROTOCOL_CLASS(AemLockEntityFlags, AemLockEntityFlagsTypedDefine, std::uint32_t)
DEFINE_TYPED_PROTOCOL_CLASS(AaMode, AaModeTypedDefine, std::uint8_t)
DEFINE_BASE_PROTOCOL_CLASS(AaAecpStatus)
DEFINE_BASE_PROTOCOL_CLASS(MvuAecpStatus)
DEFINE_TYPED_PROTOCOL_CLASS(MvuCommandType, MvuCommandTypedDefine, std::uint16_t)
DEFINE_TYPED_PROTOCOL_CLASS(AcmpMessageType, AcmpMessageTypedDefine, std::uint8_t)
DEFINE_TYPED_PROTOCOL_CLASS(AcmpStatus, AcmpStatusTypedDefine, std::uint8_t)

// Include c++ declaration file
%include "la/avdecc/internals/protocolDefines.hpp"
%rename("%s", %$isclass) ""; // Undo the ignore all structs/classes


////////////////////////////////////////
// Entity Model
////////////////////////////////////////
// We need to import NetworkInterfaces
%import "la/networkInterfaceHelper/networkInterfaceHelper.i"

// Define some macros
%define DEFINE_AEM_DESCRIPTOR(name)
	%nspaceapp(la::avdecc::entity::model::name);
	%rename("%s") la::avdecc::entity::model::name; // Unignore class
%enddef
%define DEFINE_AEM_STRUCT(name)
	%nspaceapp(la::avdecc::entity::model::name);
	%rename("%s") la::avdecc::entity::model::name; // Unignore class
#if defined(SWIGCSHARP)
	%rename("isEqual") operator==(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	%rename("isDifferent") operator!=(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
#elif defined(SWIGPYTHON)
	%rename(#name "_isEqual") operator==(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459
	%rename(#name "_isDifferent") operator!=(name const& lhs, name const& rhs) noexcept; // Not put in a namespace https://github.com/swig/swig/issues/2459

	%typemap(out) la::avdecc::entity::model::name (la::avdecc::entity::model::name* inter = 0) %{
		inter = new la::avdecc::entity::model::name($1);
		$result = SWIG_NewPointerObj(SWIG_as_voidptr(inter), $descriptor(la::avdecc::entity::model::name*), SWIG_POINTER_OWN |  0 );
	%}
#endif
	// Extend the class
	%extend la::avdecc::entity::model::name
	{
		// Add default constructor
		name()
		{
			return new la::avdecc::entity::model::name();
		}
		// Add a copy-constructor
		name(la::avdecc::entity::model::name const& other)
		{
			return new la::avdecc::entity::model::name(other);
		}		
#if defined(SWIGCSHARP)
		// Provide a more native Equals() method
		bool Equals(la::avdecc::entity::model::name const& other) const noexcept
		{
			return *$self == other;
		}
#endif
	}
%enddef

// Define optionals
DEFINE_OPTIONAL_SIMPLE(OptProbingStatus, la::avdecc::entity::model::ProbingStatus, la.avdecc.entity.model.ProbingStatus.Disabled)
DEFINE_OPTIONAL_CLASS(la::avdecc::entity, StreamInfoFlagsEx, OptStreamInfoFlagsEx)
DEFINE_OPTIONAL_CLASS(la::avdecc::protocol, AcmpStatus, OptAcmpStatus)

// Bind structs and classes
%rename($ignore, %$isclass) ""; // Ignore all structs/classes, manually re-enable

DEFINE_AEM_DESCRIPTOR(EntityDescriptor);
DEFINE_AEM_DESCRIPTOR(ConfigurationDescriptor);
DEFINE_AEM_DESCRIPTOR(AudioUnitDescriptor);
DEFINE_AEM_DESCRIPTOR(StreamDescriptor);
DEFINE_AEM_DESCRIPTOR(JackDescriptor);
DEFINE_AEM_DESCRIPTOR(AvbInterfaceDescriptor);
DEFINE_AEM_DESCRIPTOR(ClockSourceDescriptor);
DEFINE_AEM_DESCRIPTOR(MemoryObjectDescriptor);
DEFINE_AEM_DESCRIPTOR(LocaleDescriptor);
DEFINE_AEM_DESCRIPTOR(StringsDescriptor);
DEFINE_AEM_DESCRIPTOR(StreamPortDescriptor);
DEFINE_AEM_DESCRIPTOR(ExternalPortDescriptor);
DEFINE_AEM_DESCRIPTOR(InternalPortDescriptor);
DEFINE_AEM_DESCRIPTOR(AudioClusterDescriptor);
DEFINE_AEM_DESCRIPTOR(AudioMapDescriptor);
DEFINE_AEM_DESCRIPTOR(ControlDescriptor);
DEFINE_AEM_DESCRIPTOR(ClockDomainDescriptor);
DEFINE_AEM_DESCRIPTOR(TimingDescriptor);
DEFINE_AEM_DESCRIPTOR(PtpInstanceDescriptor);
DEFINE_AEM_DESCRIPTOR(PtpPortDescriptor);
DEFINE_AEM_STRUCT(StreamInfo);
DEFINE_AEM_STRUCT(AvbInfo);
DEFINE_AEM_STRUCT(AsPath);
DEFINE_AEM_STRUCT(MilanInfo);

// Some ignores
%ignore la::avdecc::entity::model::makeEntityModelID; // Ignore, not needed
%ignore la::avdecc::entity::model::splitEntityModelID; // Ignore, not needed


#if defined(SWIGPYTHON)
// Custom python map for RedundantStreamIndexSet
%typemap(out) std::set<la::avdecc::entity::model::StreamIndex>* %{
    $result = PySet_New(NULL);
    for (auto n : *$1) {
        auto val = SWIG_From_unsigned_SS_int(n);
        PySet_Add($result, val);
    }
  %}
#endif

// Include c++ declaration file
%include "la/avdecc/internals/entityModel.hpp"
%rename("%s", %$isclass) ""; // Undo the ignore all structs/classes

// Define templates
%template(DescriptorCountMap) std::unordered_map<la::avdecc::entity::model::DescriptorType, std::uint16_t, la::avdecc::utils::EnumClassHash>;
%template(StringArray) std::array<la::avdecc::entity::model::AvdeccFixedString, 7>;
SWIG_STD_VECTOR_ENHANCED(la::avdecc::entity::model::DescriptorIndex); // Swig is struggling with DescriptorIndex alias (it's a std::uint16_t)
%template(DescriptorVector) std::vector<la::avdecc::entity::model::DescriptorIndex>;
%template(SamplingRateSet) std::set<la::avdecc::entity::model::SamplingRate>;
%template(StreamFormatSet) std::set<la::avdecc::entity::model::StreamFormat>;
%template(RedundantStreamIndexSet) std::set<la::avdecc::entity::model::StreamIndex>;

////////////////////////////////////////
// Tlv Interface
////////////////////////////////////////


#if defined(SWIGPYTHON)
	// Some ignores
	%ignore la::avdecc::entity::addressAccess::Tlv::getMemoryData;      // Ignore, not needed
	%ignore la::avdecc::entity::addressAccess::Tlv::data;    		    // Ignore, not needed

	// Extend the class
	%extend la::avdecc::entity::addressAccess::Tlv
	{
		// Provide a more native data() method
		std::span<uint8_t const> raw() const noexcept
		{
			return {reinterpret_cast<uint8_t const*>($self->data()), $self->size()};
		}

		// Provide a native constructor from bytearray
		Tlv(std::uint64_t const address, std::span<uint8_t const> const& data) {
			return new la::avdecc::entity::addressAccess::Tlv(address, la::avdecc::protocol::AaMode::Write, reinterpret_cast<void const*>(data.data()), data.size());
    	}
	}
#endif

SWIG_PY_REPR(la::avdecc::entity::addressAccess::Tlv, {
			if ($self->isValid())
			{
				oss << fmt::format("address: 0x{:08x}, size: {}", $self->getAddress(), $self->size());
			} else
			{
				oss << "invalid";
			}
});

// Include c++ declaration file
%template(Tlvs) std::vector<la::avdecc::entity::addressAccess::Tlv>;
%include "la/avdecc/internals/entityAddressAccessTypes.hpp"


////////////////////////////////////////
// Stream Format Info Public Interface
////////////////////////////////////////

// Include c++ declaration file
%rename("StreamFormatInfo") la::avdecc::entity::model::StreamFormatInfoPublic;
%include "la/avdecc/internals/streamFormatInfoPublic.hpp"
