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

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Globals --------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

extern std::optional<py::class_<la::avdecc::UniqueIdentifier>> UniqueIdentifierBinding{std::nullopt};

/*-------------------------------------------------------------------------------------------------------------------*/
/*-- Declarations ---------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
void bindUniqueIdentifier(py::module_& m);
void bindEntityCapability(py::module_& m);
void bindTalkerCapability(py::module_& m);
void bindListenerCapability(py::module_& m);
void bindControllerCapability(py::module_& m);
void bindConnectionFlag(py::module_& m);
void bindStreamFlag(py::module_& m);
void bindJackFlag(py::module_& m);
void bindAvbInterfaceFlag(py::module_& m);
void bindClockSourceFlag(py::module_& m);
void bindPortFlag(py::module_& m);
void bindPtpInstanceFlag(py::module_& m);
void bindPtpPortFlag(py::module_& m);
void bindStreamInfoFlag(py::module_& m);
void bindStreamInfoFlagEx(py::module_& m);
void bindAvbInfoFlag(py::module_& m);
void bindEntityCounterValidFlag(py::module_& m);
void bindAvbInterfaceCounterValidFlag(py::module_& m);
void bindClockDomainCounterValidFlag(py::module_& m);
void bindStreamInputCounterValidFlag(py::module_& m);
void bindStreamOutputCounterValidFlag(py::module_& m);
void bindStreamOutputCounterValidFlag17221(py::module_& m);
void bindMilanInfoFeaturesFlag(py::module_& m);
void bindMediaClockReferenceInfoFlag(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntity(py::module_& m)
{
    // la\avdecc\internals\uniqueIdentifier.hpp
    bindUniqueIdentifier(m);

    // \la\avdecc\internals\entityEnums.hpp
    bindEntityCapability(m);
    bindTalkerCapability(m);
    bindListenerCapability(m);
    bindControllerCapability(m);
    bindConnectionFlag(m);
    bindStreamFlag(m);
    bindJackFlag(m);
    bindAvbInterfaceFlag(m);
    bindClockSourceFlag(m);
    bindPortFlag(m);
    bindPtpInstanceFlag(m);
    bindPtpPortFlag(m);
    bindStreamInfoFlag(m);
    bindStreamInfoFlagEx(m);
    bindAvbInfoFlag(m);
    bindEntityCounterValidFlag(m);
    bindAvbInterfaceCounterValidFlag(m);
    bindClockDomainCounterValidFlag(m);
    bindStreamInputCounterValidFlag(m);
    bindStreamOutputCounterValidFlag(m);
    bindStreamOutputCounterValidFlag17221(m);
    bindMilanInfoFeaturesFlag(m);
    bindMediaClockReferenceInfoFlag(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindUniqueIdentifier(py::module_& m)
{
    using namespace la::avdecc;

    UniqueIdentifierBinding =
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
                 [](const UniqueIdentifier& self) {
                     std::ostringstream oss;
                     oss << "UniqueIdentifier(0x" << std::hex << self.getValue() << ")";
                     return oss.str();
                 })

            .def("asString", [](const UniqueIdentifier& self) { return entity::model::controlTypeToString(self); })

            .def_static("getNullUniqueIdentifier", &UniqueIdentifier::getNullUniqueIdentifier)
            .def_static("getUninitializedUniqueIdentifier", &UniqueIdentifier::getUninitializedUniqueIdentifier);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityCapability(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<EntityCapability>(m, "EntityCapability", py::arithmetic())
        .value("Unspecified", EntityCapability::None, "No capabilities.")
        .value("EfuMode", EntityCapability::EfuMode, "Entity is in firmware upgrade mode.")
        .value("AddressAccessSupported", EntityCapability::AddressAccessSupported, "Supports ADDRESS_ACCESS commands.")
        .value("GatewayEntity", EntityCapability::GatewayEntity,
               "Serves as a gateway to a device on another media type.")
        .value("AemSupported", EntityCapability::AemSupported, "Supports AEM AECP commands.")
        .value("LegacyAvc", EntityCapability::LegacyAvc, "Supports IEEE 1394 AV/C protocol.")
        .value("AssociationIDSupported", EntityCapability::AssociationIDSupported, "Supports association_id field.")
        .value("AssociationIDValid", EntityCapability::AssociationIDValid,
               "association_id field contains a valid value.")
        .value("VendorUniqueSupported", EntityCapability::VendorUniqueSupported, "Supports AEM VENDOR_UNIQUE commands.")
        .value("ClassASupported", EntityCapability::ClassASupported, "Supports Class A Streams.")
        .value("ClassBSupported", EntityCapability::ClassBSupported, "Supports Class B Streams.")
        .value("GptpSupported", EntityCapability::GptpSupported, "Implements IEEE 802.1AS.")
        .value("AemAuthenticationSupported", EntityCapability::AemAuthenticationSupported,
               "Supports AEM authentication.")
        .value("AemAuthenticationRequired", EntityCapability::AemAuthenticationRequired, "Requires AEM authentication.")
        .value("AemPersistentAcquireSupported", EntityCapability::AemPersistentAcquireSupported,
               "Supports persistent ACQUIRE.")
        .value("AemIdentifyControlIndexValid", EntityCapability::AemIdentifyControlIndexValid,
               "Valid identify_control_index.")
        .value("AemInterfaceIndexValid", EntityCapability::AemInterfaceIndexValid, "Valid interface_index for ADPDU.")
        .value("GeneralControllerIgnore", EntityCapability::GeneralControllerIgnore,
               "Should be ignored by general AVDECC controllers.")
        .value("EntityNotReady", EntityCapability::EntityNotReady, "Entity is not ready.")
        .export_values();

    bindEnumBitfield<EntityCapability>(m, "EntityCapabilities");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindTalkerCapability(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<TalkerCapability>(m, "TalkerCapability", py::arithmetic())
        .value("Unspecified", TalkerCapability::None, "No capabilities.")
        .value("Implemented", TalkerCapability::Implemented, "Implements an AVDECC Talker.")
        .value("OtherSource", TalkerCapability::OtherSource,
               "Has other Stream sources not covered by specific categories.")
        .value("ControlSource", TalkerCapability::ControlSource, "Has Control Stream sources.")
        .value("MediaClockSource", TalkerCapability::MediaClockSource, "Has Media Clock Stream sources.")
        .value("SmpteSource", TalkerCapability::SmpteSource, "Has SMPTE time code Stream sources.")
        .value("MidiSource", TalkerCapability::MidiSource, "Has MIDI Stream sources.")
        .value("AudioSource", TalkerCapability::AudioSource, "Has Audio Stream sources.")
        .value("VideoSource", TalkerCapability::VideoSource,
               "Has Video Stream sources (which can include embedded audio).")
        .export_values();

    bindEnumBitfield<TalkerCapability>(m, "TalkerCapabilities");
}


/*-------------------------------------------------------------------------------------------------------------------*/
void bindListenerCapability(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<ListenerCapability>(m, "ListenerCapability", py::arithmetic())
        .value("Unspecified", ListenerCapability::None, "No capabilities.")
        .value("Implemented", ListenerCapability::Implemented, "Implements an AVDECC Listener.")
        .value("OtherSink", ListenerCapability::OtherSink, "Has other Stream sinks not covered by specific categories.")
        .value("ControlSink", ListenerCapability::ControlSink, "Has Control Stream sinks.")
        .value("MediaClockSink", ListenerCapability::MediaClockSink, "Has Media Clock Stream sinks.")
        .value("SmpteSink", ListenerCapability::SmpteSink, "Has SMPTE time code Stream sinks.")
        .value("MidiSink", ListenerCapability::MidiSink, "Has MIDI Stream sinks.")
        .value("AudioSink", ListenerCapability::AudioSink, "Has Audio Stream sinks.")
        .value("VideoSink", ListenerCapability::VideoSink, "Has Video Stream sinks (which can include embedded audio).")
        .export_values();

    bindEnumBitfield<ListenerCapability>(m, "ListenerCapabilities");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindControllerCapability(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<ControllerCapability>(m, "ControllerCapability", py::arithmetic())
        .value("Unspecified", ControllerCapability::None, "No capabilities.")
        .value("Implemented", ControllerCapability::Implemented, "Implements an AVDECC Controller.")
        .export_values();

    bindEnumBitfield<ControllerCapability>(m, "ControllerCapabilities");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindConnectionFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<ConnectionFlag>(m, "ConnectionFlag", py::arithmetic())
        .value("Unspecified", ConnectionFlag::None, "No flags.")
        .value("ClassB", ConnectionFlag::ClassB, "Stream is Class B instead of default Class A.")
        .value("FastConnect", ConnectionFlag::FastConnect, "Connection is being attempted in fast connect mode.")
        .value("SavedState", ConnectionFlag::SavedState, "Connection has saved state (used in Get State only).")
        .value("StreamingWait", ConnectionFlag::StreamingWait,
               "Talker waits to start streaming until explicitly told to.")
        .value("SupportsEncrypted", ConnectionFlag::SupportsEncrypted, "Stream supports encrypted PDUs.")
        .value("EncryptedPdu", ConnectionFlag::EncryptedPdu, "Stream is using encrypted PDUs.")
        .value("TalkerFailed", ConnectionFlag::TalkerFailed, "Talker failed according to IEEE1722.1-2013.")
        .value("SrpRegistrationFailed", ConnectionFlag::SrpRegistrationFailed,
               "SRP registration failed (IEEE1722.1-2021).")
        .value("ClEntriesValid", ConnectionFlag::ClEntriesValid, "connected_listeners_entries field is valid.")
        .value("NoSrp", ConnectionFlag::NoSrp, "SRP is not used for the stream.")
        .value("Udp", ConnectionFlag::Udp, "Stream is using UDP-based transport instead of AVTPDUs.")
        .export_values();

    bindEnumBitfield<ConnectionFlag>(m, "ConnectionFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<StreamFlag>(m, "StreamFlag", py::arithmetic())
        .value("Unspecified", StreamFlag::None, "No stream flags.")
        .value("ClockSyncSource", StreamFlag::ClockSyncSource, "Stream can be used as a clock synchronization source.")
        .value("ClassA", StreamFlag::ClassA, "Stream supports Class A traffic.")
        .value("ClassB", StreamFlag::ClassB, "Stream supports Class B traffic.")
        .value("SupportsEncrypted", StreamFlag::SupportsEncrypted, "Stream supports encrypted PDUs.")
        .value("PrimaryBackupSupported", StreamFlag::PrimaryBackupSupported,
               "Primary backup talker entity fields are supported.")
        .value("PrimaryBackupValid", StreamFlag::PrimaryBackupValid, "Primary backup talker entity fields are valid.")
        .value("SecondaryBackupSupported", StreamFlag::SecondaryBackupSupported,
               "Secondary backup talker entity fields are supported.")
        .value("SecondaryBackupValid", StreamFlag::SecondaryBackupValid,
               "Secondary backup talker entity fields are valid.")
        .value("TertiaryBackupSupported", StreamFlag::TertiaryBackupSupported,
               "Tertiary backup talker entity fields are supported.")
        .value("TertiaryBackupValid", StreamFlag::TertiaryBackupValid,
               "Tertiary backup talker entity fields are valid.")
        .value("SupportsAvtpUdpV4", StreamFlag::SupportsAvtpUdpV4,
               "Stream supports AVTP over UDP/IPv4 (1722-2016 Annex J).")
        .value("SupportsAvtpUdpV6", StreamFlag::SupportsAvtpUdpV6,
               "Stream supports AVTP over UDP/IPv6 (1722-2016 Annex J).")
        .value("NoSupportAvtpNative", StreamFlag::NoSupportAvtpNative,
               "Stream does not support native AVTPDUs (Ethertype 0x22f0).")
        .value("TimingFieldValid", StreamFlag::TimingFieldValid,
               "Timing field contains a valid TIMING descriptor index.")
        .value("NoMediaClock", StreamFlag::NoMediaClock, "Stream does not use a media clock.")
        .value("SupportsNoSrp", StreamFlag::SupportsNoSrp, "Stream supports streaming without SRP reservation.")
        .export_values();

    bindEnumBitfield<StreamFlag>(m, "StreamFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindJackFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<JackFlag>(m, "JackFlag", py::arithmetic())
        .value("Unspecified", JackFlag::None, "No jack flags.")
        .value("ClockSyncSource", JackFlag::ClockSyncSource, "Jack can be used as a clock synchronization source.")
        .value("Captive", JackFlag::Captive, "Jack connection is hardwired and cannot be disconnected.")
        .export_values();

    bindEnumBitfield<JackFlag>(m, "JackFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAvbInterfaceFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<AvbInterfaceFlag>(m, "AvbInterfaceFlag", py::arithmetic())
        .value("Unspecified", AvbInterfaceFlag::None, "No AVB interface flags.")
        .value("GptpGrandmasterSupported", AvbInterfaceFlag::GptpGrandmasterSupported,
               "Interface supports IEEE 802.1AS-2011 grandmaster functionality.")
        .value("GptpSupported", AvbInterfaceFlag::GptpSupported, "Interface supports IEEE 802.1AS-2011 functionality.")
        .value("SrpSupported", AvbInterfaceFlag::SrpSupported,
               "Interface supports IEEE 802.1Q-2011 Stream Reservation Protocol (SRP).")
        .value("FqtssNotSupported", AvbInterfaceFlag::FqtssNotSupported,
               "Interface does not support IEEE 802.1Q-2018 Clause 34 FQTSS functionality.")
        .value("ScheduledTrafficSupported", AvbInterfaceFlag::ScheduledTrafficSupported,
               "Interface supports IEEE 802.1Q-2018 scheduled traffic enhancements.")
        .value("CanListenToSelf", AvbInterfaceFlag::CanListenToSelf,
               "Listener on interface can listen to talker on same interface.")
        .value("CanListenToOtherSelf", AvbInterfaceFlag::CanListenToOtherSelf,
               "Listener on interface can listen to talker on another interface within same entity.")
        .export_values();

    bindEnumBitfield<AvbInterfaceFlag>(m, "AvbInterfaceFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindClockSourceFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<ClockSourceFlag>(m, "ClockSourceFlag", py::arithmetic())
        .value("Unspecified", ClockSourceFlag::None, "No clock source flags.")
        .value("StreamID", ClockSourceFlag::StreamID, "The INPUT_STREAM Clock Source is identified by the stream_id.")
        .value("LocalID", ClockSourceFlag::LocalID, "The INPUT_STREAM Clock Source is identified by its local ID.")
        .export_values();

    bindEnumBitfield<ClockSourceFlag>(m, "ClockSourceFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindPortFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<PortFlag>(m, "PortFlag", py::arithmetic())
        .value("Unspecified", PortFlag::None, "No port flags.")
        .value("ClockSyncSource", PortFlag::ClockSyncSource,
               "Indicates that the Port can be used as a clock synchronization source.")
        .value(
            "AsyncSampleRateConv", PortFlag::AsyncSampleRateConv,
            "Indicates that the Port has an asynchronous sample rate convertor to convert sample rates between another Clock Domain and the Unit's.")
        .value(
            "SyncSampleRateConv", PortFlag::SyncSampleRateConv,
            "Indicates that the Port has a synchronous sample rate convertor to convert between sample rates in the same Clock Domain.")
        .export_values();

    bindEnumBitfield<PortFlag>(m, "PortFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindPtpInstanceFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<PtpInstanceFlag>(m, "PtpInstanceFlag", py::arithmetic())
        .value("Unspecified", PtpInstanceFlag::None, "No PTP instance flags.")
        .value("CanSetInstanceEnable", PtpInstanceFlag::CanSetInstanceEnable, "Can enable or disable the PTP instance.")
        .value("CanSetPriority1", PtpInstanceFlag::CanSetPriority1, "Can configure Priority1 value.")
        .value("CanSetPriority2", PtpInstanceFlag::CanSetPriority2, "Can configure Priority2 value.")
        .value("CanSetDomainNumber", PtpInstanceFlag::CanSetDomainNumber, "Can configure PTP domain number.")
        .value("CanSetExternalPortConfiguration", PtpInstanceFlag::CanSetExternalPortConfiguration,
               "Can configure external port settings.")
        .value("CanSetSlaveOnly", PtpInstanceFlag::CanSetSlaveOnly, "Can set the slave-only mode.")
        .value("CanEnablePerformance", PtpInstanceFlag::CanEnablePerformance, "Can enable PTP performance monitoring.")
        .value("PerformanceMonitoring", PtpInstanceFlag::PerformanceMonitoring,
               "PTP instance supports performance monitoring.")
        .value("GrandmasterCapable", PtpInstanceFlag::GrandmasterCapable,
               "PTP instance is capable of being a grandmaster.")
        .export_values();

    bindEnumBitfield<PtpInstanceFlag>(m, "PtpInstanceFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindPtpPortFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<PtpPortFlag>(m, "PtpPortFlag", py::arithmetic())
        .value("Unspecified", PtpPortFlag::None, "No PTP port flags.")
        .value("CanSetEnable", PtpPortFlag::CanSetEnable, "Can enable or disable the PTP port.")
        .value("CanSetLinkDelayThreshold", PtpPortFlag::CanSetLinkDelayThreshold, "Can configure link delay threshold.")
        .value("CanSetDelayMechanism", PtpPortFlag::CanSetDelayMechanism, "Can configure the delay mechanism.")
        .value("CanSetDelayAsymmetry", PtpPortFlag::CanSetDelayAsymmetry, "Can configure delay asymmetry.")
        .value("CanSetInitialMessageIntervals", PtpPortFlag::CanSetInitialMessageIntervals,
               "Can configure initial message intervals.")
        .value("CanSetTimeouts", PtpPortFlag::CanSetTimeouts, "Can configure timeout values.")
        .value("CanOverrideAnnounceInterval", PtpPortFlag::CanOverrideAnnounceInterval,
               "Can override announce interval.")
        .value("CanOverrideSyncInterval", PtpPortFlag::CanOverrideSyncInterval, "Can override sync interval.")
        .value("CanOverridePDelayInterval", PtpPortFlag::CanOverridePDelayInterval, "Can override peer delay interval.")
        .value("CanOverrideGptpCapableInterval", PtpPortFlag::CanOverrideGptpCapableInterval,
               "Can override gPTP capable interval.")
        .value("CanOverrideComputeNeighbor", PtpPortFlag::CanOverrideComputeNeighbor,
               "Can override computation of neighbor propagation delay.")
        .value("CanOverrideComputeLinkDelay", PtpPortFlag::CanOverrideComputeLinkDelay,
               "Can override computation of link delay.")
        .value("CanOverrideOnestep", PtpPortFlag::CanOverrideOnestep, "Can override One-Step mode.")
        .value("SupportsRemoteIntervalSignal", PtpPortFlag::SupportsRemoteIntervalSignal,
               "Supports signaling remote intervals.")
        .value("SupportsOnestepTransmit", PtpPortFlag::SupportsOnestepTransmit,
               "Supports transmitting One-Step timestamps.")
        .value("SupportsOnestepReceive", PtpPortFlag::SupportsOnestepReceive, "Supports receiving One-Step timestamps.")
        .value("SupportsUnicastNegotiate", PtpPortFlag::SupportsUnicastNegotiate,
               "Supports unicast negotiation for PTP messages.")
        .export_values();

    bindEnumBitfield<PtpPortFlag>(m, "PtpPortFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamInfoFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<StreamInfoFlag>(m, "StreamInfoFlag", py::arithmetic())
        .value("Unspecified", StreamInfoFlag::None, "No flags.")
        .value("ClassB", StreamInfoFlag::ClassB, "Indicates that the Stream is Class B instead of Class A.")
        .value("FastConnect", StreamInfoFlag::FastConnect,
               "The Stream was connected or is connecting in Fast Connect Mode.")
        .value("SavedState", StreamInfoFlag::SavedState, "The connection has saved ACMP state.")
        .value("StreamingWait", StreamInfoFlag::StreamingWait, "Stream is in STREAMING_WAIT state.")
        .value("SupportsEncrypted", StreamInfoFlag::SupportsEncrypted, "Stream supports encrypted PDUs.")
        .value("EncryptedPdu", StreamInfoFlag::EncryptedPdu, "Stream is currently using encrypted PDUs.")
        .value("TalkerFailed", StreamInfoFlag::TalkerFailed, "SRP Talker Failed attribute registered for the stream.")
        .value("NoSrp", StreamInfoFlag::NoSrp, "SRP is not used for the stream.")
        .value("IpFlagsValid", StreamInfoFlag::IpFlagsValid, "The ip_flags field is valid.")
        .value("IpSrcPortValid", StreamInfoFlag::IpSrcPortValid, "The source_port field is valid.")
        .value("IpDstPortValid", StreamInfoFlag::IpDstPortValid, "The destination_port field is valid.")
        .value("IpSrcAddrValid", StreamInfoFlag::IpSrcAddrValid, "The source_ip_address field is valid.")
        .value("IpDstAddrValid", StreamInfoFlag::IpDstAddrValid, "The destination_ip_address field is valid.")
        .value("NotRegisteringSrp", StreamInfoFlag::NotRegisteringSrp,
               "Indicates that the stream is not registering an SRP attribute.")
        .value("StreamVlanIDValid", StreamInfoFlag::StreamVlanIDValid, "The stream_vlan_id field is valid.")
        .value("Connected", StreamInfoFlag::Connected, "The Stream has been connected with ACMP.")
        .value("MsrpFailureValid", StreamInfoFlag::MsrpFailureValid,
               "msrp_failure_code and msrp_failure_bridge_id fields are valid.")
        .value("StreamDestMacValid", StreamInfoFlag::StreamDestMacValid, "The stream_dest_mac field is valid.")
        .value("MsrpAccLatValid", StreamInfoFlag::MsrpAccLatValid, "The msrp_accumulated_latency field is valid.")
        .value("StreamIDValid", StreamInfoFlag::StreamIDValid, "The stream_id field is valid.")
        .value("StreamFormatValid", StreamInfoFlag::StreamFormatValid,
               "The stream_format field is valid and may be used to change the stream format.")
        .export_values();

    bindEnumBitfield<StreamInfoFlag>(m, "StreamInfoFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamInfoFlagEx(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<StreamInfoFlagEx>(m, "StreamInfoFlagEx", py::arithmetic())
        .value("Unspecified", StreamInfoFlagEx::None, "No flags.")
        .value(
            "Registering", StreamInfoFlagEx::Registering,
            "StreamInput: Registering a matching Talker Advertise or Talker Failed attribute.\n"
            "StreamOutput: Declaring a Talker Advertise or Talker Failed attribute and registering a matching Listener attribute.")
        .export_values();

    bindEnumBitfield<StreamInfoFlagEx>(m, "StreamInfoFlagsEx");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAvbInfoFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<AvbInfoFlag>(m, "AvbInfoFlag", py::arithmetic())
        .value("Unspecified", AvbInfoFlag::None, "No AVB info flags.")
        .value("AsCapable", AvbInfoFlag::AsCapable,
               "The IEEE Std 802.1AS-2011 variable asCapable is set on this interface.")
        .value("GptpEnabled", AvbInfoFlag::GptpEnabled, "Indicates that IEEE 802.1AS (gPTP) functionality is enabled.")
        .value("SrpEnabled", AvbInfoFlag::SrpEnabled, "Indicates that IEEE 802.1Q SRP functionality is enabled.")
        .value("AvtpDown", AvbInfoFlag::AvtpDown, "The interface cannot transmit or receive AVTPDUs.")
        .value("AvtpDownValid", AvbInfoFlag::AvtpDownValid, "Indicates that the value of the AVTP_DOWN bit is valid.")
        .export_values();

    bindEnumBitfield<AvbInfoFlag>(m, "AvbInfoFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntityCounterValidFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<EntityCounterValidFlag>(m, "EntityCounterValidFlag", py::arithmetic())
        .value("Unspecified", EntityCounterValidFlag::None, "No entity-specific counter validity flags.")
        .value("EntitySpecific8", EntityCounterValidFlag::EntitySpecific8, "Entity-specific counter 8 is valid.")
        .value("EntitySpecific7", EntityCounterValidFlag::EntitySpecific7, "Entity-specific counter 7 is valid.")
        .value("EntitySpecific6", EntityCounterValidFlag::EntitySpecific6, "Entity-specific counter 6 is valid.")
        .value("EntitySpecific5", EntityCounterValidFlag::EntitySpecific5, "Entity-specific counter 5 is valid.")
        .value("EntitySpecific4", EntityCounterValidFlag::EntitySpecific4, "Entity-specific counter 4 is valid.")
        .value("EntitySpecific3", EntityCounterValidFlag::EntitySpecific3, "Entity-specific counter 3 is valid.")
        .value("EntitySpecific2", EntityCounterValidFlag::EntitySpecific2, "Entity-specific counter 2 is valid.")
        .value("EntitySpecific1", EntityCounterValidFlag::EntitySpecific1, "Entity-specific counter 1 is valid.")
        .export_values();

    bindEnumBitfield<EntityCounterValidFlag>(m, "EntityCounterValidFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindAvbInterfaceCounterValidFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<AvbInterfaceCounterValidFlag>(m, "AvbInterfaceCounterValidFlag", py::arithmetic())
        .value("Unspecified", AvbInterfaceCounterValidFlag::None, "No AVB interface counter validity flags.")
        .value("LinkUp", AvbInterfaceCounterValidFlag::LinkUp, "Total number of network link up events.")
        .value("LinkDown", AvbInterfaceCounterValidFlag::LinkDown, "Total number of network link down events.")
        .value("FramesTx", AvbInterfaceCounterValidFlag::FramesTx, "Total number of network frames sent.")
        .value("FramesRx", AvbInterfaceCounterValidFlag::FramesRx, "Total number of network frames received.")
        .value("RxCrcError", AvbInterfaceCounterValidFlag::RxCrcError,
               "Total number of network frames received with an incorrect CRC.")
        .value("GptpGmChanged", AvbInterfaceCounterValidFlag::GptpGmChanged, "gPTP grandmaster change count.")
        .value("EntitySpecific8", AvbInterfaceCounterValidFlag::EntitySpecific8, "Entity-specific counter 8 is valid.")
        .value("EntitySpecific7", AvbInterfaceCounterValidFlag::EntitySpecific7, "Entity-specific counter 7 is valid.")
        .value("EntitySpecific6", AvbInterfaceCounterValidFlag::EntitySpecific6, "Entity-specific counter 6 is valid.")
        .value("EntitySpecific5", AvbInterfaceCounterValidFlag::EntitySpecific5, "Entity-specific counter 5 is valid.")
        .value("EntitySpecific4", AvbInterfaceCounterValidFlag::EntitySpecific4, "Entity-specific counter 4 is valid.")
        .value("EntitySpecific3", AvbInterfaceCounterValidFlag::EntitySpecific3, "Entity-specific counter 3 is valid.")
        .value("EntitySpecific2", AvbInterfaceCounterValidFlag::EntitySpecific2, "Entity-specific counter 2 is valid.")
        .value("EntitySpecific1", AvbInterfaceCounterValidFlag::EntitySpecific1, "Entity-specific counter 1 is valid.")
        .export_values();

    bindEnumBitfield<AvbInterfaceCounterValidFlag>(m, "AvbInterfaceCounterValidFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindClockDomainCounterValidFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<ClockDomainCounterValidFlag>(m, "ClockDomainCounterValidFlag", py::arithmetic())
        .value("Unspecified", ClockDomainCounterValidFlag::None, "No clock domain counter validity flags.")
        .value("Locked", ClockDomainCounterValidFlag::Locked, "Increments on a clock locking event.")
        .value("Unlocked", ClockDomainCounterValidFlag::Unlocked, "Increments on a clock unlocking event.")
        .value("EntitySpecific8", ClockDomainCounterValidFlag::EntitySpecific8, "Entity-specific counter 8 is valid.")
        .value("EntitySpecific7", ClockDomainCounterValidFlag::EntitySpecific7, "Entity-specific counter 7 is valid.")
        .value("EntitySpecific6", ClockDomainCounterValidFlag::EntitySpecific6, "Entity-specific counter 6 is valid.")
        .value("EntitySpecific5", ClockDomainCounterValidFlag::EntitySpecific5, "Entity-specific counter 5 is valid.")
        .value("EntitySpecific4", ClockDomainCounterValidFlag::EntitySpecific4, "Entity-specific counter 4 is valid.")
        .value("EntitySpecific3", ClockDomainCounterValidFlag::EntitySpecific3, "Entity-specific counter 3 is valid.")
        .value("EntitySpecific2", ClockDomainCounterValidFlag::EntitySpecific2, "Entity-specific counter 2 is valid.")
        .value("EntitySpecific1", ClockDomainCounterValidFlag::EntitySpecific1, "Entity-specific counter 1 is valid.")
        .export_values();

    bindEnumBitfield<ClockDomainCounterValidFlag>(m, "ClockDomainCounterValidFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamInputCounterValidFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<StreamInputCounterValidFlag>(m, "StreamInputCounterValidFlag", py::arithmetic())
        .value("Unspecified", StreamInputCounterValidFlag::None, "No stream input counters are valid.")
        .value("MediaLocked", StreamInputCounterValidFlag::MediaLocked, "Increments on a Stream media clock locking.")
        .value("MediaUnlocked", StreamInputCounterValidFlag::MediaUnlocked,
               "Increments on a Stream media clock unlocking.")
        .value("StreamReset", StreamInputCounterValidFlag::StreamReset,
               "Increments when stream playback is reset (IEEE1722.1-2013).")
        .value(
            "StreamInterrupted", StreamInputCounterValidFlag::StreamInterrupted,
            "Increments when stream playback is interrupted for reasons other than a controller unbind (IEEE1722.1-2021 / Milan).")
        .value("SeqNumMismatch", StreamInputCounterValidFlag::SeqNumMismatch,
               "Increments on reception of AVTPDU with non-sequential sequence_num field.")
        .value("MediaReset", StreamInputCounterValidFlag::MediaReset,
               "Increments on toggle of the mr bit in the AVTPDU.")
        .value("TimestampUncertain", StreamInputCounterValidFlag::TimestampUncertain,
               "Increments on toggle of the tu bit in the AVTPDU.")
        .value("TimestampValid", StreamInputCounterValidFlag::TimestampValid,
               "Increments on receipt of AVTPDU with tv bit set.")
        .value("TimestampNotValid", StreamInputCounterValidFlag::TimestampNotValid,
               "Increments on receipt of AVTPDU with tv bit cleared.")
        .value("UnsupportedFormat", StreamInputCounterValidFlag::UnsupportedFormat,
               "Increments on receipt of AVTPDU with unsupported media format.")
        .value("LateTimestamp", StreamInputCounterValidFlag::LateTimestamp,
               "Increments on receipt of AVTPDU with timestamp in the past.")
        .value("EarlyTimestamp", StreamInputCounterValidFlag::EarlyTimestamp,
               "Increments on receipt of AVTPDU with timestamp too far in the future.")
        .value("FramesRx", StreamInputCounterValidFlag::FramesRx, "Increments on each AVTPDU received.")
        .value("FramesTx", StreamInputCounterValidFlag::FramesTx, "Increments on each AVTPDU transmitted.")
        .value("EntitySpecific8", StreamInputCounterValidFlag::EntitySpecific8, "Entity-specific counter 8 is valid.")
        .value("EntitySpecific7", StreamInputCounterValidFlag::EntitySpecific7, "Entity-specific counter 7 is valid.")
        .value("EntitySpecific6", StreamInputCounterValidFlag::EntitySpecific6, "Entity-specific counter 6 is valid.")
        .value("EntitySpecific5", StreamInputCounterValidFlag::EntitySpecific5, "Entity-specific counter 5 is valid.")
        .value("EntitySpecific4", StreamInputCounterValidFlag::EntitySpecific4, "Entity-specific counter 4 is valid.")
        .value("EntitySpecific3", StreamInputCounterValidFlag::EntitySpecific3, "Entity-specific counter 3 is valid.")
        .value("EntitySpecific2", StreamInputCounterValidFlag::EntitySpecific2, "Entity-specific counter 2 is valid.")
        .value("EntitySpecific1", StreamInputCounterValidFlag::EntitySpecific1, "Entity-specific counter 1 is valid.")
        .export_values();

    bindEnumBitfield<StreamInputCounterValidFlag>(m, "StreamInputCounterValidFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamOutputCounterValidFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<StreamOutputCounterValidFlag>(m, "StreamOutputCounterValidFlag", py::arithmetic())
        .value("Unspecified", StreamOutputCounterValidFlag::None, "No stream output counters are valid.")
        .value("StreamStart", StreamOutputCounterValidFlag::StreamStart,
               "Incremented each time the Talker starts streaming.")
        .value(
            "StreamStop", StreamOutputCounterValidFlag::StreamStop,
            "Incremented each time the Talker stops streaming.\n"
            "PAAD-AE ensures STREAM_START == STREAM_STOP + 1 (streaming) or STREAM_START == STREAM_STOP (not streaming).")
        .value(
            "MediaReset", StreamOutputCounterValidFlag::MediaReset,
            "Incremented at the end of each observation interval where the 'mr' bit toggled in any transmitted AVTPDU.\n"
            "Observation interval ≤ 1 second.")
        .value(
            "TimestampUncertain", StreamOutputCounterValidFlag::TimestampUncertain,
            "Incremented at the end of each observation interval where the 'tu' bit was set in any transmitted AVTPDU.\n"
            "Observation interval ≤ 1 second.")
        .value("FramesTx", StreamOutputCounterValidFlag::FramesTx,
               "Incremented at the end of each observation interval if at least one AVTPDU was transmitted.\n"
               "Observation interval ≤ 1 second.")
        .export_values();

    bindEnumBitfield<StreamOutputCounterValidFlag>(m, "StreamOutputCounterValidFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamOutputCounterValidFlag17221(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<StreamOutputCounterValidFlag17221>(m, "StreamOutputCounterValidFlag17221", py::arithmetic())
        .value("Unspecified", StreamOutputCounterValidFlag17221::None, "No stream output counters are valid.")
        .value("StreamStart", StreamOutputCounterValidFlag17221::StreamStart, "Incremented when a stream is started.")
        .value("StreamStop", StreamOutputCounterValidFlag17221::StreamStop, "Incremented when a stream is stopped.")
        .value("StreamInterrupted", StreamOutputCounterValidFlag17221::StreamInterrupted,
               "Incremented when Stream playback is interrupted.")
        .value("MediaReset", StreamOutputCounterValidFlag17221::MediaReset,
               "Increments on a toggle of the 'mr' bit in the Stream data AVTPDU.")
        .value("TimestampUncertain", StreamOutputCounterValidFlag17221::TimestampUncertain,
               "Increments on a toggle of the 'tu' bit in the Stream data AVTPDU.")
        .value("TimestampValid", StreamOutputCounterValidFlag17221::TimestampValid,
               "Increments on receipt of a Stream data AVTPDU with the 'tv' bit set.")
        .value("TimestampNotValid", StreamOutputCounterValidFlag17221::TimestampNotValid,
               "Increments on receipt of a Stream data AVTPDU with the 'tv' bit cleared.")
        .value("FramesTx", StreamOutputCounterValidFlag17221::FramesTx,
               "Increments on each Stream data AVTPDU transmitted.")
        .export_values();

    bindEnumBitfield<StreamOutputCounterValidFlag17221>(m, "StreamOutputCounterValidFlags17221");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMilanInfoFeaturesFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<MilanInfoFeaturesFlag>(m, "MilanInfoFeaturesFlag", py::arithmetic())
        .value("Unspecified", MilanInfoFeaturesFlag::None, "No Milan-specific feature flags are set.")
        .value("Redundancy", MilanInfoFeaturesFlag::Redundancy, "The entity supports the Milan redundancy scheme.")
        .value("TalkerDynamicMappingsWhileRunning", MilanInfoFeaturesFlag::TalkerDynamicMappingsWhileRunning,
               "The entity supports changing dynamic mappings of talker streams while streaming.")
        .export_values();

    bindEnumBitfield<MilanInfoFeaturesFlag>(m, "MilanInfoFeaturesFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindMediaClockReferenceInfoFlag(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<MediaClockReferenceInfoFlag>(m, "MediaClockReferenceInfoFlag", py::arithmetic())
        .value("Unspecified", MediaClockReferenceInfoFlag::None, "No media clock reference info flags are set.")
        .value("UserMediaClockReferencePriorityValid",
               MediaClockReferenceInfoFlag::UserMediaClockReferencePriorityValid,
               "The value in the user_media_clock_reference_priority field is valid.")
        .value("MediaClockDomainNameValid", MediaClockReferenceInfoFlag::MediaClockDomainNameValid,
               "The value in the media_clock_domain_name field is valid.")
        .export_values();

    bindEnumBitfield<MediaClockReferenceInfoFlag>(m, "MediaClockReferenceInfoFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/