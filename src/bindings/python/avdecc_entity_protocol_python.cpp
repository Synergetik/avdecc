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
 * @file avdecc_entity_python.cpp
 * @author Vitalij Mast
 */

#include "avdecc_entity_python.hpp"
#include "avdecc_utils_python.hpp"

#include <la/avdecc/internals/entityAddressAccessTypes.hpp>

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void bindAdpMessageType(py::module_& m);
void bindAecpMessageType(py::module_& m);
void bindAecpStatus(py::module_& m);
void bindAemAecpStatus(py::module_& m);
void bindAemCommandType(py::module_& m);
void bindAemAcquireEntityFlags(py::module_& m);
void bindAemLockEntityFlags(py::module_& m);
void bindAaMode(py::module_& m);
void bindAaAecpStatus(py::module_& m);
void bindMvuAecpStatus(py::module_& m);
void bindMvuCommandType(py::module_& m);
void bindAcmpMessageType(py::module_& m);
void bindAcmpStatus(py::module_& m);
void bindAddressAccessTlV(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityModelProtocol(py::module_& m)
{
    // la/avdecc/internals/protocolDefines.hpp
    m.attr("EthernetMaxFrameSize")               = py::int_(la::avdecc::protocol::EthernetMaxFrameSize);
    m.attr("AvtpEtherType")                      = py::int_(la::avdecc::protocol::AvtpEtherType);
    m.attr("AvtpMaxPayloadLength")               = py::int_(la::avdecc::protocol::AvtpMaxPayloadLength);
    m.attr("AvtpVersion")                        = py::int_(la::avdecc::protocol::AvtpVersion);
    m.attr("AvtpSubType_Adp")                    = py::int_(la::avdecc::protocol::AvtpSubType_Adp);
    m.attr("AvtpSubType_Aecp")                   = py::int_(la::avdecc::protocol::AvtpSubType_Aecp);
    m.attr("AvtpSubType_Acmp")                   = py::int_(la::avdecc::protocol::AvtpSubType_Acmp);
    m.attr("AvtpSubType_Maap")                   = py::int_(la::avdecc::protocol::AvtpSubType_Maap);
    m.attr("AvtpSubType_Experimental")           = py::int_(la::avdecc::protocol::AvtpSubType_Experimental);
    m.attr("AaAecpMaxSingleTlvMemoryDataLength") = py::int_(la::avdecc::protocol::AaAecpMaxSingleTlvMemoryDataLength);

    bindAdpMessageType(m);
    bindAecpMessageType(m);
    bindAecpStatus(m);
    bindAemAecpStatus(m);
    bindAemCommandType(m);
    bindAemAcquireEntityFlags(m);
    bindAemLockEntityFlags(m);
    bindAaMode(m);
    bindAaAecpStatus(m);
    bindMvuAecpStatus(m);
    bindMvuCommandType(m);
    bindAcmpMessageType(m);
    bindAcmpStatus(m);

    // la/avdecc/internals/entityAddressAccessTypes.hpp
    bindAddressAccessTlV(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAdpMessageType(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AdpMessageType, std::uint8_t>(m, "AdpMessageType")
        .def_property_readonly_static("EntityAvailable",  [](const py::object&) { return AdpMessageType::EntityAvailable; })
        .def_property_readonly_static("EntityDeparting",  [](const py::object&) { return AdpMessageType::EntityDeparting; })
        .def_property_readonly_static("EntityDiscover",   [](const py::object&) { return AdpMessageType::EntityDiscover; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAecpMessageType(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AecpMessageType, std::uint8_t>(m, "AecpMessageType")
        .def_property_readonly_static("AemCommand",             [](const py::object&) { return AecpMessageType::AemCommand; })
        .def_property_readonly_static("AemResponse",            [](const py::object&) { return AecpMessageType::AemResponse; })
        .def_property_readonly_static("AddressAccessCommand",   [](const py::object&) { return AecpMessageType::AddressAccessCommand; })
        .def_property_readonly_static("AddressAccessResponse",  [](const py::object&) { return AecpMessageType::AddressAccessResponse; })
        .def_property_readonly_static("AvcCommand",             [](const py::object&) { return AecpMessageType::AvcCommand; })
        .def_property_readonly_static("AvcResponse",            [](const py::object&) { return AecpMessageType::AvcResponse; })
        .def_property_readonly_static("VendorUniqueCommand",    [](const py::object&) { return AecpMessageType::VendorUniqueCommand; })
        .def_property_readonly_static("VendorUniqueResponse",   [](const py::object&) { return AecpMessageType::VendorUniqueResponse; })
        .def_property_readonly_static("HdcpAemCommand",         [](const py::object&) { return AecpMessageType::HdcpAemCommand; })
        .def_property_readonly_static("HdcpAemResponse",        [](const py::object&) { return AecpMessageType::HdcpAemResponse; })
        .def_property_readonly_static("ExtendedCommand",        [](const py::object&) { return AecpMessageType::ExtendedCommand; })
        .def_property_readonly_static("ExtendedResponse",       [](const py::object&) { return AecpMessageType::ExtendedResponse; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAecpStatus(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AecpStatus, std::uint8_t>(m, "AecpStatus")
        .def_property_readonly_static("Success",         [](const py::object&) { return AecpStatus::Success; })
        .def_property_readonly_static("NotImplemented",  [](const py::object&) { return AecpStatus::NotImplemented; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAemAecpStatus(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    py::class_<AemAecpStatus, AecpStatus>(m, "AemAecpStatus")
         .def_property_readonly_static("NoSuchDescriptor",         [](const py::object&) { return AemAecpStatus::NoSuchDescriptor; })
         .def_property_readonly_static("EntityLocked",             [](const py::object&) { return AemAecpStatus::EntityLocked; })
         .def_property_readonly_static("EntityAcquired",           [](const py::object&) { return AemAecpStatus::EntityAcquired; })
         .def_property_readonly_static("NotAuthenticated",         [](const py::object&) { return AemAecpStatus::NotAuthenticated; })
         .def_property_readonly_static("AuthenticationDisabled",   [](const py::object&) { return AemAecpStatus::AuthenticationDisabled; })
         .def_property_readonly_static("BadArguments",             [](const py::object&) { return AemAecpStatus::BadArguments; })
         .def_property_readonly_static("NoResources",              [](const py::object&) { return AemAecpStatus::NoResources; })
         .def_property_readonly_static("InProgress",               [](const py::object&) { return AemAecpStatus::InProgress; })
         .def_property_readonly_static("EntityMisbehaving",        [](const py::object&) { return AemAecpStatus::EntityMisbehaving; })
         .def_property_readonly_static("NotSupported",             [](const py::object&) { return AemAecpStatus::NotSupported; })
         .def_property_readonly_static("StreamIsRunning",          [](const py::object&) { return AemAecpStatus::StreamIsRunning; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAemCommandType(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AemCommandType, std::uint16_t>(m, "AemCommandType")
        .def_property_readonly_static("AcquireEntity",                     [](const py::object&) { return AemCommandType::AcquireEntity; })
        .def_property_readonly_static("LockEntity",                        [](const py::object&) { return AemCommandType::LockEntity; })
        .def_property_readonly_static("EntityAvailable",                   [](const py::object&) { return AemCommandType::EntityAvailable; })
        .def_property_readonly_static("ControllerAvailable",               [](const py::object&) { return AemCommandType::ControllerAvailable; })
        .def_property_readonly_static("ReadDescriptor",                    [](const py::object&) { return AemCommandType::ReadDescriptor; })
        .def_property_readonly_static("WriteDescriptor",                   [](const py::object&) { return AemCommandType::WriteDescriptor; })
        .def_property_readonly_static("SetConfiguration",                  [](const py::object&) { return AemCommandType::SetConfiguration; })
        .def_property_readonly_static("GetConfiguration",                  [](const py::object&) { return AemCommandType::GetConfiguration; })
        .def_property_readonly_static("SetStreamFormat",                   [](const py::object&) { return AemCommandType::SetStreamFormat; })
        .def_property_readonly_static("GetStreamFormat",                   [](const py::object&) { return AemCommandType::GetStreamFormat; })
        .def_property_readonly_static("SetVideoFormat",                    [](const py::object&) { return AemCommandType::SetVideoFormat; })
        .def_property_readonly_static("GetVideoFormat",                    [](const py::object&) { return AemCommandType::GetVideoFormat; })
        .def_property_readonly_static("SetSensorFormat",                   [](const py::object&) { return AemCommandType::SetSensorFormat; })
        .def_property_readonly_static("GetSensorFormat",                   [](const py::object&) { return AemCommandType::GetSensorFormat; })
        .def_property_readonly_static("SetStreamInfo",                     [](const py::object&) { return AemCommandType::SetStreamInfo; })
        .def_property_readonly_static("GetStreamInfo",                     [](const py::object&) { return AemCommandType::GetStreamInfo; })
        .def_property_readonly_static("SetName",                           [](const py::object&) { return AemCommandType::SetName; })
        .def_property_readonly_static("GetName",                           [](const py::object&) { return AemCommandType::GetName; })
        .def_property_readonly_static("SetAssociationID",                  [](const py::object&) { return AemCommandType::SetAssociationID; })
        .def_property_readonly_static("GetAssociationID",                  [](const py::object&) { return AemCommandType::GetAssociationID; })
        .def_property_readonly_static("SetSamplingRate",                   [](const py::object&) { return AemCommandType::SetSamplingRate; })
        .def_property_readonly_static("GetSamplingRate",                   [](const py::object&) { return AemCommandType::GetSamplingRate; })
        .def_property_readonly_static("SetClockSource",                    [](const py::object&) { return AemCommandType::SetClockSource; })
        .def_property_readonly_static("GetClockSource",                    [](const py::object&) { return AemCommandType::GetClockSource; })
        .def_property_readonly_static("SetControl",                        [](const py::object&) { return AemCommandType::SetControl; })
        .def_property_readonly_static("GetControl",                        [](const py::object&) { return AemCommandType::GetControl; })
        .def_property_readonly_static("IncrementControl",                  [](const py::object&) { return AemCommandType::IncrementControl; })
        .def_property_readonly_static("DecrementControl",                  [](const py::object&) { return AemCommandType::DecrementControl; })
        .def_property_readonly_static("SetSignalSelector",                 [](const py::object&) { return AemCommandType::SetSignalSelector; })
        .def_property_readonly_static("GetSignalSelector",                 [](const py::object&) { return AemCommandType::GetSignalSelector; })
        .def_property_readonly_static("SetMixer",                          [](const py::object&) { return AemCommandType::SetMixer; })
        .def_property_readonly_static("GetMixer",                          [](const py::object&) { return AemCommandType::GetMixer; })
        .def_property_readonly_static("SetMatrix",                         [](const py::object&) { return AemCommandType::SetMatrix; })
        .def_property_readonly_static("GetMatrix",                         [](const py::object&) { return AemCommandType::GetMatrix; })
        .def_property_readonly_static("StartStreaming",                    [](const py::object&) { return AemCommandType::StartStreaming; })
        .def_property_readonly_static("StopStreaming",                     [](const py::object&) { return AemCommandType::StopStreaming; })
        .def_property_readonly_static("RegisterUnsolicitedNotification",   [](const py::object&) { return AemCommandType::RegisterUnsolicitedNotification; })
        .def_property_readonly_static("DeregisterUnsolicitedNotification", [](const py::object&) { return AemCommandType::DeregisterUnsolicitedNotification; })
        .def_property_readonly_static("IdentifyNotification",              [](const py::object&) { return AemCommandType::IdentifyNotification; })
        .def_property_readonly_static("GetAvbInfo",                        [](const py::object&) { return AemCommandType::GetAvbInfo; })
        .def_property_readonly_static("GetAsPath",                         [](const py::object&) { return AemCommandType::GetAsPath; })
        .def_property_readonly_static("GetCounters",                       [](const py::object&) { return AemCommandType::GetCounters; })
        .def_property_readonly_static("Reboot",                            [](const py::object&) { return AemCommandType::Reboot; })
        .def_property_readonly_static("GetAudioMap",                       [](const py::object&) { return AemCommandType::GetAudioMap; })
        .def_property_readonly_static("AddAudioMappings",                  [](const py::object&) { return AemCommandType::AddAudioMappings; })
        .def_property_readonly_static("RemoveAudioMappings",               [](const py::object&) { return AemCommandType::RemoveAudioMappings; })
        .def_property_readonly_static("GetVideoMap",                       [](const py::object&) { return AemCommandType::GetVideoMap; })
        .def_property_readonly_static("AddVideoMappings",                  [](const py::object&) { return AemCommandType::AddVideoMappings; })
        .def_property_readonly_static("RemoveVideoMappings",               [](const py::object&) { return AemCommandType::RemoveVideoMappings; })
        .def_property_readonly_static("GetSensorMap",                      [](const py::object&) { return AemCommandType::GetSensorMap; })
        .def_property_readonly_static("AddSensorMappings",                 [](const py::object&) { return AemCommandType::AddSensorMappings; })
        .def_property_readonly_static("RemoveSensorMappings",              [](const py::object&) { return AemCommandType::RemoveSensorMappings; })
        .def_property_readonly_static("StartOperation",                    [](const py::object&) { return AemCommandType::StartOperation; })
        .def_property_readonly_static("AbortOperation",                    [](const py::object&) { return AemCommandType::AbortOperation; })
        .def_property_readonly_static("OperationStatus",                   [](const py::object&) { return AemCommandType::OperationStatus; })
        .def_property_readonly_static("AuthAddKey",                        [](const py::object&) { return AemCommandType::AuthAddKey; })
        .def_property_readonly_static("AuthDeleteKey",                     [](const py::object&) { return AemCommandType::AuthDeleteKey; })
        .def_property_readonly_static("AuthGetKeyList",                    [](const py::object&) { return AemCommandType::AuthGetKeyList; })
        .def_property_readonly_static("AuthGetKey",                        [](const py::object&) { return AemCommandType::AuthGetKey; })
        .def_property_readonly_static("AuthAddKeyToChain",                 [](const py::object&) { return AemCommandType::AuthAddKeyToChain; })
        .def_property_readonly_static("AuthDeleteKeyFromChain",            [](const py::object&) { return AemCommandType::AuthDeleteKeyFromChain; })
        .def_property_readonly_static("AuthGetKeychainList",               [](const py::object&) { return AemCommandType::AuthGetKeychainList; })
        .def_property_readonly_static("AuthGetIdentity",                   [](const py::object&) { return AemCommandType::AuthGetIdentity; })
        .def_property_readonly_static("AuthAddToken",                      [](const py::object&) { return AemCommandType::AuthAddToken; })
        .def_property_readonly_static("AuthDeleteToken",                   [](const py::object&) { return AemCommandType::AuthDeleteToken; })
        .def_property_readonly_static("Authenticate",                      [](const py::object&) { return AemCommandType::Authenticate; })
        .def_property_readonly_static("Deauthenticate",                    [](const py::object&) { return AemCommandType::Deauthenticate; })
        .def_property_readonly_static("EnableTransportSecurity",           [](const py::object&) { return AemCommandType::EnableTransportSecurity; })
        .def_property_readonly_static("DisableTransportSecurity",          [](const py::object&) { return AemCommandType::DisableTransportSecurity; })
        .def_property_readonly_static("EnableStreamEncryption",            [](const py::object&) { return AemCommandType::EnableStreamEncryption; })
        .def_property_readonly_static("DisableStreamEncryption",           [](const py::object&) { return AemCommandType::DisableStreamEncryption; })
        .def_property_readonly_static("SetMemoryObjectLength",             [](const py::object&) { return AemCommandType::SetMemoryObjectLength; })
        .def_property_readonly_static("GetMemoryObjectLength",             [](const py::object&) { return AemCommandType::GetMemoryObjectLength; })
        .def_property_readonly_static("SetStreamBackup",                   [](const py::object&) { return AemCommandType::SetStreamBackup; })
        .def_property_readonly_static("GetStreamBackup",                   [](const py::object&) { return AemCommandType::GetStreamBackup; })
        .def_property_readonly_static("GetDynamicInfo",                    [](const py::object&) { return AemCommandType::GetDynamicInfo; })
        .def_property_readonly_static("SetMaxTransitTime",                 [](const py::object&) { return AemCommandType::SetMaxTransitTime; })
        .def_property_readonly_static("GetMaxTransitTime",                 [](const py::object&) { return AemCommandType::GetMaxTransitTime; })
        .def_property_readonly_static("Expansion",                         [](const py::object&) { return AemCommandType::Expansion; })
        .def_property_readonly_static("InvalidCommandType",                [](const py::object&) { return AemCommandType::InvalidCommandType; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAemAcquireEntityFlags(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AemAcquireEntityFlags, std::uint32_t>(m, "AemAcquireEntityFlags")
        .def_property_readonly_static("Unspecified", [](const py::object&) { return AemAcquireEntityFlags::None; })
        .def_property_readonly_static("Persistent",  [](const py::object&) { return AemAcquireEntityFlags::Persistent; })
        .def_property_readonly_static("Release",     [](const py::object&) { return AemAcquireEntityFlags::Release; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAemLockEntityFlags(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AemLockEntityFlags, std::uint32_t>(m, "AemLockEntityFlags")
        .def_property_readonly_static("Unspecified", [](const py::object&) { return AemLockEntityFlags::None; })
        .def_property_readonly_static("Unlock",      [](const py::object&) { return AemLockEntityFlags::Unlock; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAaMode(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AaMode, std::uint8_t>(m, "AaMode")
        .def_property_readonly_static("Read",    [](const py::object&) { return AaMode::Read; })
        .def_property_readonly_static("Write",   [](const py::object&) { return AaMode::Write; })
        .def_property_readonly_static("Execute", [](const py::object&) { return AaMode::Execute; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAaAecpStatus(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    py::class_<AaAecpStatus, AecpStatus>(m, "AaAecpStatus")
        .def_property_readonly_static("AddressTooLow",    [](const py::object&) { return AaAecpStatus::AddressTooLow; })
        .def_property_readonly_static("AddressTooHigh",   [](const py::object&) { return AaAecpStatus::AddressTooHigh; })
        .def_property_readonly_static("AddressInvalid",   [](const py::object&) { return AaAecpStatus::AddressInvalid; })
        .def_property_readonly_static("TlvInvalid",       [](const py::object&) { return AaAecpStatus::TlvInvalid; })
        .def_property_readonly_static("DataInvalid",      [](const py::object&) { return AaAecpStatus::DataInvalid; })
        .def_property_readonly_static("Unsupported",      [](const py::object&) { return AaAecpStatus::Unsupported; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMvuAecpStatus(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    py::class_<MvuAecpStatus, AecpStatus>(m, "MvuAecpStatus");
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMvuCommandType(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<MvuCommandType, std::uint16_t>(m, "MvuCommandType")
        .def_property_readonly_static("GetMilanInfo",               [](const py::object&) { return MvuCommandType::GetMilanInfo; })
        .def_property_readonly_static("SetSystemUniqueID",          [](const py::object&) { return MvuCommandType::SetSystemUniqueID; })
        .def_property_readonly_static("GetSystemUniqueID",          [](const py::object&) { return MvuCommandType::GetSystemUniqueID; })
        .def_property_readonly_static("SetMediaClockReferenceInfo", [](const py::object&) { return MvuCommandType::SetMediaClockReferenceInfo; })
        .def_property_readonly_static("GetMediaClockReferenceInfo", [](const py::object&) { return MvuCommandType::GetMediaClockReferenceInfo; })
        .def_property_readonly_static("InvalidCommandType",         [](const py::object&) { return MvuCommandType::InvalidCommandType; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAcmpMessageType(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AcmpMessageType, std::uint8_t>(m, "AcmpMessageType")
        .def_property_readonly_static("ConnectTxCommand",         [](const py::object&) { return AcmpMessageType::ConnectTxCommand; })
        .def_property_readonly_static("ConnectTxResponse",        [](const py::object&) { return AcmpMessageType::ConnectTxResponse; })
        .def_property_readonly_static("DisconnectTxCommand",      [](const py::object&) { return AcmpMessageType::DisconnectTxCommand; })
        .def_property_readonly_static("DisconnectTxResponse",     [](const py::object&) { return AcmpMessageType::DisconnectTxResponse; })
        .def_property_readonly_static("GetTxStateCommand",        [](const py::object&) { return AcmpMessageType::GetTxStateCommand; })
        .def_property_readonly_static("GetTxStateResponse",       [](const py::object&) { return AcmpMessageType::GetTxStateResponse; })
        .def_property_readonly_static("ConnectRxCommand",         [](const py::object&) { return AcmpMessageType::ConnectRxCommand; })
        .def_property_readonly_static("ConnectRxResponse",        [](const py::object&) { return AcmpMessageType::ConnectRxResponse; })
        .def_property_readonly_static("DisconnectRxCommand",      [](const py::object&) { return AcmpMessageType::DisconnectRxCommand; })
        .def_property_readonly_static("DisconnectRxResponse",     [](const py::object&) { return AcmpMessageType::DisconnectRxResponse; })
        .def_property_readonly_static("GetRxStateCommand",        [](const py::object&) { return AcmpMessageType::GetRxStateCommand; })
        .def_property_readonly_static("GetRxStateResponse",       [](const py::object&) { return AcmpMessageType::GetRxStateResponse; })
        .def_property_readonly_static("GetTxConnectionCommand",   [](const py::object&) { return AcmpMessageType::GetTxConnectionCommand; })
        .def_property_readonly_static("GetTxConnectionResponse",  [](const py::object&) { return AcmpMessageType::GetTxConnectionResponse; });
    // clang-format on
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAcmpStatus(py::module_& m)
{
    using namespace la::avdecc::protocol;

    // clang-format off
    bindTypedDefine<AcmpStatus, std::uint8_t>(m, "AcmpStatus")
        .def_property_readonly_static("Success",                 [](const py::object&) { return AcmpStatus::Success; })
        .def_property_readonly_static("ListenerUnknownID",       [](const py::object&) { return AcmpStatus::ListenerUnknownID; })
        .def_property_readonly_static("TalkerUnknownID",         [](const py::object&) { return AcmpStatus::TalkerUnknownID; })
        .def_property_readonly_static("TalkerDestMacFail",       [](const py::object&) { return AcmpStatus::TalkerDestMacFail; })
        .def_property_readonly_static("TalkerNoStreamIndex",     [](const py::object&) { return AcmpStatus::TalkerNoStreamIndex; })
        .def_property_readonly_static("TalkerNoBandwidth",       [](const py::object&) { return AcmpStatus::TalkerNoBandwidth; })
        .def_property_readonly_static("TalkerExclusive",         [](const py::object&) { return AcmpStatus::TalkerExclusive; })
        .def_property_readonly_static("ListenerTalkerTimeout",   [](const py::object&) { return AcmpStatus::ListenerTalkerTimeout; })
        .def_property_readonly_static("ListenerExclusive",       [](const py::object&) { return AcmpStatus::ListenerExclusive; })
        .def_property_readonly_static("StateUnavailable",        [](const py::object&) { return AcmpStatus::StateUnavailable; })
        .def_property_readonly_static("NotConnected",            [](const py::object&) { return AcmpStatus::NotConnected; })
        .def_property_readonly_static("NoSuchConnection",        [](const py::object&) { return AcmpStatus::NoSuchConnection; })
        .def_property_readonly_static("CouldNotSendMessage",     [](const py::object&) { return AcmpStatus::CouldNotSendMessage; })
        .def_property_readonly_static("TalkerMisbehaving",       [](const py::object&) { return AcmpStatus::TalkerMisbehaving; })
        .def_property_readonly_static("ListenerMisbehaving",     [](const py::object&) { return AcmpStatus::ListenerMisbehaving; })
        .def_property_readonly_static("ControllerNotAuthorized", [](const py::object&) { return AcmpStatus::ControllerNotAuthorized; })
        .def_property_readonly_static("IncompatibleRequest",     [](const py::object&) { return AcmpStatus::IncompatibleRequest; })
        .def_property_readonly_static("NotSupported",            [](const py::object&) { return AcmpStatus::NotSupported; });
    // clang-format on
}


/*-------------------------------------------------------------------------------------------------------------------*/
void bindAddressAccessTlV(py::module_& m)
{
    using namespace la::avdecc::entity::addressAccess;
    using namespace la::avdecc::protocol;

    auto cls = py::class_<Tlv>(m, "Tlv", py::is_final());

    cls.def(py::init<>())
        .def(py::init<std::uint64_t const, size_t const>())
        .def(py::init<AaMode const, std::uint64_t const, size_t const>())
        .def(py::init<std::uint64_t const, AaMode const, Tlv::memory_data_type const&>())
        .def(py::init<std::uint64_t const, AaMode const, Tlv::memory_data_type&&>())
        .def(py::init<Tlv>())
        .def(py::init<Tlv const>())
        .def_property_readonly("mode", &Tlv::getMode)
        .def_property_readonly("address", &Tlv::getAddress)
        .def_property(
            "memory_data", [](Tlv& self) -> Tlv::memory_data_type& { return self.getMemoryData(); },
            [](Tlv& self, py::bytes pyData) {
                std::string buffer = static_cast<std::string>(pyData);
                if (buffer.empty())
                {
                    throw std::invalid_argument("Length is 0");
                }
                if (buffer.size() > Tlv::MaxLength)
                {
                    throw std::invalid_argument("Length too big");
                }
                self.getMemoryData() = Tlv::memory_data_type(buffer.begin(), buffer.end()); // setter
            },
            py::return_value_policy::reference_internal)
        .def_property_readonly("size", &Tlv::size)
        .def_property_readonly("isValid", &Tlv::isValid)
        .def("__eq__", &Tlv::operator==)
        .def("__ne__", &Tlv::operator!=)
        .def("__bool__", [](const Tlv& self) { return static_cast<bool>(self); })
        .def("__len__", &Tlv::size)
        .def("__repr__", [](const Tlv& self) {
            std::ostringstream oss;
            oss << "<Tlv mode=" << static_cast<std::string>(self.getMode()) << " address=0x" << std::hex << self.getAddress() << " size=" << std::dec
                << self.size() << " valid=" << (self.isValid() ? "True" : "False") << ">";
            return oss.str();
        });
}
