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

#include <la/avdecc/internals/entity.hpp>

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
void bindBaseEntity(py::module_& m);
void bindLocalEntity(py::module_& m);

/*-------------------------------------------------------------------------------------------------------------------*/
void bindEntity(py::module_& m)
{
    // la\avdecc\internals\uniqueIdentifier.hpp
    bindUniqueIdentifier(m);

    // la\avdecc\internals\entityEnums.hpp
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

    // la/avdecc/internals/entity.hpp
    bindBaseEntity(m);
    bindLocalEntity(m);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindUniqueIdentifier(py::module_& m)
{
    using namespace la::avdecc;

    UniqueIdentifierBinding = py::class_<UniqueIdentifier>(m, "UniqueIdentifier")
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
        .value("GatewayEntity", EntityCapability::GatewayEntity, "Serves as a gateway to a device on another media type.")
        .value("AemSupported", EntityCapability::AemSupported, "Supports AEM AECP commands.")
        .value("LegacyAvc", EntityCapability::LegacyAvc, "Supports IEEE 1394 AV/C protocol.")
        .value("AssociationIDSupported", EntityCapability::AssociationIDSupported, "Supports association_id field.")
        .value("AssociationIDValid", EntityCapability::AssociationIDValid, "association_id field contains a valid value.")
        .value("VendorUniqueSupported", EntityCapability::VendorUniqueSupported, "Supports AEM VENDOR_UNIQUE commands.")
        .value("ClassASupported", EntityCapability::ClassASupported, "Supports Class A Streams.")
        .value("ClassBSupported", EntityCapability::ClassBSupported, "Supports Class B Streams.")
        .value("GptpSupported", EntityCapability::GptpSupported, "Implements IEEE 802.1AS.")
        .value("AemAuthenticationSupported", EntityCapability::AemAuthenticationSupported, "Supports AEM authentication.")
        .value("AemAuthenticationRequired", EntityCapability::AemAuthenticationRequired, "Requires AEM authentication.")
        .value("AemPersistentAcquireSupported", EntityCapability::AemPersistentAcquireSupported, "Supports persistent ACQUIRE.")
        .value("AemIdentifyControlIndexValid", EntityCapability::AemIdentifyControlIndexValid, "Valid identify_control_index.")
        .value("AemInterfaceIndexValid", EntityCapability::AemInterfaceIndexValid, "Valid interface_index for ADPDU.")
        .value("GeneralControllerIgnore", EntityCapability::GeneralControllerIgnore, "Should be ignored by general AVDECC controllers.")
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
        .value("OtherSource", TalkerCapability::OtherSource, "Has other Stream sources not covered by specific categories.")
        .value("ControlSource", TalkerCapability::ControlSource, "Has Control Stream sources.")
        .value("MediaClockSource", TalkerCapability::MediaClockSource, "Has Media Clock Stream sources.")
        .value("SmpteSource", TalkerCapability::SmpteSource, "Has SMPTE time code Stream sources.")
        .value("MidiSource", TalkerCapability::MidiSource, "Has MIDI Stream sources.")
        .value("AudioSource", TalkerCapability::AudioSource, "Has Audio Stream sources.")
        .value("VideoSource", TalkerCapability::VideoSource, "Has Video Stream sources (which can include embedded audio).")
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
        .value("StreamingWait", ConnectionFlag::StreamingWait, "Talker waits to start streaming until explicitly told to.")
        .value("SupportsEncrypted", ConnectionFlag::SupportsEncrypted, "Stream supports encrypted PDUs.")
        .value("EncryptedPdu", ConnectionFlag::EncryptedPdu, "Stream is using encrypted PDUs.")
        .value("TalkerFailed", ConnectionFlag::TalkerFailed, "Talker failed according to IEEE1722.1-2013.")
        .value("SrpRegistrationFailed", ConnectionFlag::SrpRegistrationFailed, "SRP registration failed (IEEE1722.1-2021).")
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
        .value("PrimaryBackupSupported", StreamFlag::PrimaryBackupSupported, "Primary backup talker entity fields are supported.")
        .value("PrimaryBackupValid", StreamFlag::PrimaryBackupValid, "Primary backup talker entity fields are valid.")
        .value("SecondaryBackupSupported", StreamFlag::SecondaryBackupSupported, "Secondary backup talker entity fields are supported.")
        .value("SecondaryBackupValid", StreamFlag::SecondaryBackupValid, "Secondary backup talker entity fields are valid.")
        .value("TertiaryBackupSupported", StreamFlag::TertiaryBackupSupported, "Tertiary backup talker entity fields are supported.")
        .value("TertiaryBackupValid", StreamFlag::TertiaryBackupValid, "Tertiary backup talker entity fields are valid.")
        .value("SupportsAvtpUdpV4", StreamFlag::SupportsAvtpUdpV4, "Stream supports AVTP over UDP/IPv4 (1722-2016 Annex J).")
        .value("SupportsAvtpUdpV6", StreamFlag::SupportsAvtpUdpV6, "Stream supports AVTP over UDP/IPv6 (1722-2016 Annex J).")
        .value("NoSupportAvtpNative", StreamFlag::NoSupportAvtpNative, "Stream does not support native AVTPDUs (Ethertype 0x22f0).")
        .value("TimingFieldValid", StreamFlag::TimingFieldValid, "Timing field contains a valid TIMING descriptor index.")
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
        .value("GptpGrandmasterSupported", AvbInterfaceFlag::GptpGrandmasterSupported, "Interface supports IEEE 802.1AS-2011 grandmaster functionality.")
        .value("GptpSupported", AvbInterfaceFlag::GptpSupported, "Interface supports IEEE 802.1AS-2011 functionality.")
        .value("SrpSupported", AvbInterfaceFlag::SrpSupported, "Interface supports IEEE 802.1Q-2011 Stream Reservation Protocol (SRP).")
        .value("FqtssNotSupported", AvbInterfaceFlag::FqtssNotSupported, "Interface does not support IEEE 802.1Q-2018 Clause 34 FQTSS functionality.")
        .value("ScheduledTrafficSupported", AvbInterfaceFlag::ScheduledTrafficSupported, "Interface supports IEEE 802.1Q-2018 scheduled traffic enhancements.")
        .value("CanListenToSelf", AvbInterfaceFlag::CanListenToSelf, "Listener on interface can listen to talker on same interface.")
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
        .value("ClockSyncSource", PortFlag::ClockSyncSource, "Indicates that the Port can be used as a clock synchronization source.")
        .value("AsyncSampleRateConv", PortFlag::AsyncSampleRateConv,
               "Indicates that the Port has an asynchronous sample rate convertor to convert sample rates between another Clock Domain and the Unit's.")
        .value("SyncSampleRateConv", PortFlag::SyncSampleRateConv,
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
        .value("CanSetExternalPortConfiguration", PtpInstanceFlag::CanSetExternalPortConfiguration, "Can configure external port settings.")
        .value("CanSetSlaveOnly", PtpInstanceFlag::CanSetSlaveOnly, "Can set the slave-only mode.")
        .value("CanEnablePerformance", PtpInstanceFlag::CanEnablePerformance, "Can enable PTP performance monitoring.")
        .value("PerformanceMonitoring", PtpInstanceFlag::PerformanceMonitoring, "PTP instance supports performance monitoring.")
        .value("GrandmasterCapable", PtpInstanceFlag::GrandmasterCapable, "PTP instance is capable of being a grandmaster.")
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
        .value("CanSetInitialMessageIntervals", PtpPortFlag::CanSetInitialMessageIntervals, "Can configure initial message intervals.")
        .value("CanSetTimeouts", PtpPortFlag::CanSetTimeouts, "Can configure timeout values.")
        .value("CanOverrideAnnounceInterval", PtpPortFlag::CanOverrideAnnounceInterval, "Can override announce interval.")
        .value("CanOverrideSyncInterval", PtpPortFlag::CanOverrideSyncInterval, "Can override sync interval.")
        .value("CanOverridePDelayInterval", PtpPortFlag::CanOverridePDelayInterval, "Can override peer delay interval.")
        .value("CanOverrideGptpCapableInterval", PtpPortFlag::CanOverrideGptpCapableInterval, "Can override gPTP capable interval.")
        .value("CanOverrideComputeNeighbor", PtpPortFlag::CanOverrideComputeNeighbor, "Can override computation of neighbor propagation delay.")
        .value("CanOverrideComputeLinkDelay", PtpPortFlag::CanOverrideComputeLinkDelay, "Can override computation of link delay.")
        .value("CanOverrideOnestep", PtpPortFlag::CanOverrideOnestep, "Can override One-Step mode.")
        .value("SupportsRemoteIntervalSignal", PtpPortFlag::SupportsRemoteIntervalSignal, "Supports signaling remote intervals.")
        .value("SupportsOnestepTransmit", PtpPortFlag::SupportsOnestepTransmit, "Supports transmitting One-Step timestamps.")
        .value("SupportsOnestepReceive", PtpPortFlag::SupportsOnestepReceive, "Supports receiving One-Step timestamps.")
        .value("SupportsUnicastNegotiate", PtpPortFlag::SupportsUnicastNegotiate, "Supports unicast negotiation for PTP messages.")
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
        .value("FastConnect", StreamInfoFlag::FastConnect, "The Stream was connected or is connecting in Fast Connect Mode.")
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
        .value("NotRegisteringSrp", StreamInfoFlag::NotRegisteringSrp, "Indicates that the stream is not registering an SRP attribute.")
        .value("StreamVlanIDValid", StreamInfoFlag::StreamVlanIDValid, "The stream_vlan_id field is valid.")
        .value("Connected", StreamInfoFlag::Connected, "The Stream has been connected with ACMP.")
        .value("MsrpFailureValid", StreamInfoFlag::MsrpFailureValid, "msrp_failure_code and msrp_failure_bridge_id fields are valid.")
        .value("StreamDestMacValid", StreamInfoFlag::StreamDestMacValid, "The stream_dest_mac field is valid.")
        .value("MsrpAccLatValid", StreamInfoFlag::MsrpAccLatValid, "The msrp_accumulated_latency field is valid.")
        .value("StreamIDValid", StreamInfoFlag::StreamIDValid, "The stream_id field is valid.")
        .value("StreamFormatValid", StreamInfoFlag::StreamFormatValid, "The stream_format field is valid and may be used to change the stream format.")
        .export_values();

    bindEnumBitfield<StreamInfoFlag>(m, "StreamInfoFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindStreamInfoFlagEx(py::module_& m)
{
    using namespace la::avdecc::entity;

    py::enum_<StreamInfoFlagEx>(m, "StreamInfoFlagEx", py::arithmetic())
        .value("Unspecified", StreamInfoFlagEx::None, "No flags.")
        .value("Registering", StreamInfoFlagEx::Registering,
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
        .value("AsCapable", AvbInfoFlag::AsCapable, "The IEEE Std 802.1AS-2011 variable asCapable is set on this interface.")
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
        .value("RxCrcError", AvbInterfaceCounterValidFlag::RxCrcError, "Total number of network frames received with an incorrect CRC.")
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
        .value("MediaUnlocked", StreamInputCounterValidFlag::MediaUnlocked, "Increments on a Stream media clock unlocking.")
        .value("StreamReset", StreamInputCounterValidFlag::StreamReset, "Increments when stream playback is reset (IEEE1722.1-2013).")
        .value("StreamInterrupted", StreamInputCounterValidFlag::StreamInterrupted,
               "Increments when stream playback is interrupted for reasons other than a controller unbind (IEEE1722.1-2021 / Milan).")
        .value("SeqNumMismatch", StreamInputCounterValidFlag::SeqNumMismatch, "Increments on reception of AVTPDU with non-sequential sequence_num field.")
        .value("MediaReset", StreamInputCounterValidFlag::MediaReset, "Increments on toggle of the mr bit in the AVTPDU.")
        .value("TimestampUncertain", StreamInputCounterValidFlag::TimestampUncertain, "Increments on toggle of the tu bit in the AVTPDU.")
        .value("TimestampValid", StreamInputCounterValidFlag::TimestampValid, "Increments on receipt of AVTPDU with tv bit set.")
        .value("TimestampNotValid", StreamInputCounterValidFlag::TimestampNotValid, "Increments on receipt of AVTPDU with tv bit cleared.")
        .value("UnsupportedFormat", StreamInputCounterValidFlag::UnsupportedFormat, "Increments on receipt of AVTPDU with unsupported media format.")
        .value("LateTimestamp", StreamInputCounterValidFlag::LateTimestamp, "Increments on receipt of AVTPDU with timestamp in the past.")
        .value("EarlyTimestamp", StreamInputCounterValidFlag::EarlyTimestamp, "Increments on receipt of AVTPDU with timestamp too far in the future.")
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
        .value("StreamStart", StreamOutputCounterValidFlag::StreamStart, "Incremented each time the Talker starts streaming.")
        .value("StreamStop", StreamOutputCounterValidFlag::StreamStop,
               "Incremented each time the Talker stops streaming.\n"
               "PAAD-AE ensures STREAM_START == STREAM_STOP + 1 (streaming) or STREAM_START == STREAM_STOP (not streaming).")
        .value("MediaReset", StreamOutputCounterValidFlag::MediaReset,
               "Incremented at the end of each observation interval where the 'mr' bit toggled in any transmitted AVTPDU.\n"
               "Observation interval ≤ 1 second.")
        .value("TimestampUncertain", StreamOutputCounterValidFlag::TimestampUncertain,
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
        .value("StreamInterrupted", StreamOutputCounterValidFlag17221::StreamInterrupted, "Incremented when Stream playback is interrupted.")
        .value("MediaReset", StreamOutputCounterValidFlag17221::MediaReset, "Increments on a toggle of the 'mr' bit in the Stream data AVTPDU.")
        .value("TimestampUncertain", StreamOutputCounterValidFlag17221::TimestampUncertain, "Increments on a toggle of the 'tu' bit in the Stream data AVTPDU.")
        .value("TimestampValid", StreamOutputCounterValidFlag17221::TimestampValid, "Increments on receipt of a Stream data AVTPDU with the 'tv' bit set.")
        .value("TimestampNotValid", StreamOutputCounterValidFlag17221::TimestampNotValid,
               "Increments on receipt of a Stream data AVTPDU with the 'tv' bit cleared.")
        .value("FramesTx", StreamOutputCounterValidFlag17221::FramesTx, "Increments on each Stream data AVTPDU transmitted.")
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
        .value("UserMediaClockReferencePriorityValid", MediaClockReferenceInfoFlag::UserMediaClockReferencePriorityValid,
               "The value in the user_media_clock_reference_priority field is valid.")
        .value("MediaClockDomainNameValid", MediaClockReferenceInfoFlag::MediaClockDomainNameValid, "The value in the media_clock_domain_name field is valid.")
        .export_values();

    bindEnumBitfield<MediaClockReferenceInfoFlag>(m, "MediaClockReferenceInfoFlags");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindBaseEntity(py::module_& m)
{
    using namespace la::avdecc::entity;

    auto cls = py::class_<Entity>(m, "BaseEntity", "Represents an AVDECC Entity with common and interface-specific information.");

    py::class_<Entity::CommonInformation>(cls, "CommonInformation", "Common information shared by an entity across all network interfaces.")
        .def(py::init<>())
        .def_readwrite("entityID", &Entity::CommonInformation::entityID, "The entity's unique identifier.")
        .def_readwrite("entityModelID", &Entity::CommonInformation::entityModelID, "The entity model unique identifier.")
        .def_readwrite("entityCapabilities", &Entity::CommonInformation::entityCapabilities, "The entity's current capabilities (can change over time).")
        .def_readwrite("talkerStreamSources", &Entity::CommonInformation::talkerStreamSources,
                       "The maximum number of streams the entity is capable of sourcing simultaneously.")
        .def_readwrite("talkerCapabilities", &Entity::CommonInformation::talkerCapabilities, "The entity's capabilities as a talker.")
        .def_readwrite("listenerStreamSinks", &Entity::CommonInformation::listenerStreamSinks,
                       "The maximum number of streams the entity is capable of sinking simultaneously.")
        .def_readwrite("listenerCapabilities", &Entity::CommonInformation::listenerCapabilities, "The entity's capabilities as a listener.")
        .def_readwrite("controllerCapabilities", &Entity::CommonInformation::controllerCapabilities, "The entity's capabilities as a controller.")
        .def_readwrite("identifyControlIndex", &Entity::CommonInformation::identifyControlIndex,
                       "The ControlIndex for the primary IDENTIFY control, if set. Only valid if EntityCapabilities::AemIdentifyControlIndexValid is defined.")
        .def_readwrite("associationID", &Entity::CommonInformation::associationID,
                       "he unique identifier of the associated entity, if set. Only valid if EntityCapabilities::AssociationIDValid is defined.")
        .def(
            "__repr__",
            [](const Entity::CommonInformation& info) {
                std::ostringstream oss;
                oss << "<BaseEntity.CommonInformation>";
                return oss.str();
            },
            "Returns a string representation of the common entity information.");

    py::class_<Entity::InterfaceInformation>(cls, "InterfaceInformation")
        .def(py::init<>())
        .def_readwrite("macAddress", &Entity::InterfaceInformation::macAddress, "The mac address this interface is attached to.")
        .def_readwrite("validTime", &Entity::InterfaceInformation::validTime,
                       "The number of 2-seconds periods the entity's announcement is valid on this interface.")
        .def_readwrite("availableIndex", &Entity::InterfaceInformation::availableIndex, "The current available index for the entity on this interface.")
        .def_readwrite("gptpGrandmasterID", &Entity::InterfaceInformation::gptpGrandmasterID,
                       "The current gPTP grandmaster unique identifier on this interface. Only valid if EntityCapabilities::GptpSupported is defined.")
        .def_readwrite("gptpDomainNumber", &Entity::InterfaceInformation::gptpDomainNumber,
                       "The current gPTP domain number on this interface. Only valid if EntityCapabilities::GptpSupported is defined.")
        .def(
            "__repr__",
            [](const Entity::InterfaceInformation& info) {
                std::ostringstream oss;
                oss << "<BaseEntity.InterfaceInformation>";
                return oss.str();
            },
            "Returns a string representation of the entity interface information.");

    cls.def_property_readonly_static("GlobalAvbInterfaceIndex", [](const py::object&) { return Entity::GlobalAvbInterfaceIndex; });

    cls.def(py::init<Entity::CommonInformation const&, Entity::InterfacesInformation const&>(), py::arg("commonInformation"), py::arg("interfacesInformation"),
            "Constructs an Entity from common and interface information.\n\n"
            ":param commonInformation: Common information shared by all interfaces.\n"
            ":param interfacesInformation: Map of interface index to interface-specific information.")
        // Getters
        .def("getCommonInformation", py::overload_cast<>(&Entity::getCommonInformation), py::return_value_policy::reference_internal,
             "Returns a reference to the modifiable CommonInformation.")
        .def("getInterfacesInformation", py::overload_cast<>(&Entity::getInterfacesInformation), py::return_value_policy::reference_internal,
             "Returns a reference to the modifiable InterfacesInformation map.")
        .def("getInterfaceInformation", py::overload_cast<model::AvbInterfaceIndex const>(&Entity::getInterfaceInformation), py::arg("interfaceIndex"),
             py::return_value_policy::reference_internal,
             "Returns a modifiable reference to InterfaceInformation for the given interface index.\n"
             ":raises Exception: if the interface index is invalid.")
        .def("hasInterfaceIndex", &Entity::hasInterfaceIndex, py::arg("interfaceIndex"), "Checks whether a given interface index exists in the entity.")
        .def("getEntityID", &Entity::getEntityID, "Returns the entity's unique identifier.")
        .def("getEntityModelID", &Entity::getEntityModelID, "Returns the entity's model identifier.")
        .def("getEntityCapabilities", &Entity::getEntityCapabilities, "Returns the current entity capabilities.")
        .def("getTalkerStreamSources", &Entity::getTalkerStreamSources, "Returns the maximum number of streams the entity can source.")
        .def("getTalkerCapabilities", &Entity::getTalkerCapabilities, "Returns the talker capabilities of the entity.")
        .def("getListenerStreamSinks", &Entity::getListenerStreamSinks, "Returns the maximum number of streams the entity can sink.")
        .def("getListenerCapabilities", &Entity::getListenerCapabilities, "Returns the listener capabilities of the entity.")
        .def("getControllerCapabilities", &Entity::getControllerCapabilities, "Returns the controller capabilities of the entity.")
        .def("getIdentifyControlIndex", &Entity::getIdentifyControlIndex, "Returns the optional identify control index if valid.")
        .def("getAssociationID", &Entity::getAssociationID, "Returns the optional association ID of the entity.")
        .def("getMacAddress", &Entity::getMacAddress, py::arg("interfaceIndex"),
             "Returns the MAC address associated with the given interface index. Returns an invalid MAC if not found.")
        .def("getAnyMacAddress", &Entity::getAnyMacAddress, "Returns any available MAC address from the entity.")

        // Setters
        .def("removeInterfaceInformation", &Entity::removeInterfaceInformation, py::arg("interfaceIndex"),
             "Removes the InterfaceInformation for the specified interface index.")
        .def("setEntityCapabilities", &Entity::setEntityCapabilities, py::arg("entityCapabilities"), "Sets the entity's capabilities.")
        .def("setAssociationID", &Entity::setAssociationID, py::arg("associationID"), "Sets the optional association ID of the entity.")
        .def("setValidTime", &Entity::setValidTime, py::arg("validTime"), py::arg("interfaceIndex") = std::nullopt,
             "Sets the valid time in 2-second periods.\n"
             "If interfaceIndex is given, only applies to that interface; otherwise, applies to all.")
        .def("setGptpGrandmasterID", &Entity::setGptpGrandmasterID, py::arg("gptpGrandmasterID"), py::arg("interfaceIndex"),
             "Sets the gPTP grandmaster ID for the given interface.")
        .def("setGptpDomainNumber", &Entity::setGptpDomainNumber, py::arg("gptpDomainNumber"), py::arg("interfaceIndex"),
             "Sets the gPTP domain number for the given interface.")

        // Static
        .def_static("generateEID", &Entity::generateEID, py::arg("macAddress"), py::arg("progID"), py::arg("useDeprecatedAlgorithm"),
                    "Generates an Entity ID (EID) from a MAC address and a program ID.\n"
                    "This method is provided for backward compatibility, use ProtocolInterface::getDynamicEID instead.");
}

/*-------------------------------------------------------------------------------------------------------------------*/
void bindLocalEntity(py::module_& m)
{
    using namespace la::avdecc::entity;

    auto cls = py::class_<LocalEntity, Entity, std::unique_ptr<LocalEntity, py::nodelete>>(m, "LocalEntity",
                                                                                           "Represents a local AVDECC Entity that extends BaseEntity.");

    py::enum_<LocalEntity::AemCommandStatus>(cls, "AemCommandStatus", "Status code returned by all AEM (AECP) command methods.")
        // AVDECC Protocol Error Codes
        .value("Success", LocalEntity::AemCommandStatus::Success, "The AVDECC Entity successfully performed the command and has valid results.")
        .value("NotImplemented", LocalEntity::AemCommandStatus::NotImplemented, "The AVDECC Entity does not support the command type.")
        .value("NoSuchDescriptor", LocalEntity::AemCommandStatus::NoSuchDescriptor, "A descriptor with the specified type and index does not exist.")
        .value("LockedByOther", LocalEntity::AemCommandStatus::LockedByOther, "The AVDECC Entity has been locked by another controller.")
        .value("AcquiredByOther", LocalEntity::AemCommandStatus::AcquiredByOther, "The AVDECC Entity has been acquired by another controller.")
        .value("NotAuthenticated", LocalEntity::AemCommandStatus::NotAuthenticated, "The controller is not authenticated with the entity.")
        .value("AuthenticationDisabled", LocalEntity::AemCommandStatus::AuthenticationDisabled, "Authentication is not enabled on the AVDECC Entity.")
        .value("BadArguments", LocalEntity::AemCommandStatus::BadArguments, "One or more arguments in the command were invalid or unsupported.")
        .value("NoResources", LocalEntity::AemCommandStatus::NoResources, "The entity does not have sufficient resources to complete the command.")
        .value("InProgress", LocalEntity::AemCommandStatus::InProgress, "The command is still being processed; results will follow.")
        .value("EntityMisbehaving", LocalEntity::AemCommandStatus::EntityMisbehaving, "The entity encountered an internal error while processing the command.")
        .value("NotSupported", LocalEntity::AemCommandStatus::NotSupported,
               "The command is valid but not supported for the specified target (e.g. read-only control).")
        .value("StreamIsRunning", LocalEntity::AemCommandStatus::StreamIsRunning, "The stream is active and cannot accept this command while running.")
        // Library-specific error codes
        .value("BaseProtocolViolation", LocalEntity::AemCommandStatus::BaseProtocolViolation, "The entity sent a message that violates the base protocol.")
        .value("PartialImplementation", LocalEntity::AemCommandStatus::PartialImplementation, "This command is only partially implemented by the library.")
        .value("Busy", LocalEntity::AemCommandStatus::Busy, "The library is currently busy; try again later.")
        .value("NetworkError", LocalEntity::AemCommandStatus::NetworkError, "A network error occurred during command transmission.")
        .value("ProtocolError", LocalEntity::AemCommandStatus::ProtocolError, "The message could not be unpacked due to a protocol violation.")
        .value("TimedOut", LocalEntity::AemCommandStatus::TimedOut, "The command did not receive a response and timed out.")
        .value("UnknownEntity", LocalEntity::AemCommandStatus::UnknownEntity, "The target entity has not been detected on the network.")
        .value("InternalError", LocalEntity::AemCommandStatus::InternalError, "An internal library error occurred. Please report this issue.")
        .export_values()
        .def("asString", [](LocalEntity::AemCommandStatus self) { return LocalEntity::statusToString(self); });

    py::enum_<LocalEntity::AaCommandStatus>(cls, "AaCommandStatus", "Status code returned by all AA (AECP) command methods.")
        // AVDECC Protocol Error Codes
        .value("Success", LocalEntity::AaCommandStatus::Success, "The AVDECC Entity successfully performed the command and has valid results.")
        .value("NotImplemented", LocalEntity::AaCommandStatus::NotImplemented, "The AVDECC Entity does not support the command type.")
        .value("AddressTooLow", LocalEntity::AaCommandStatus::AddressTooLow, "The address is below the start of the memory map.")
        .value("AddressTooHigh", LocalEntity::AaCommandStatus::AddressTooHigh, "The address is above the end of the memory map.")
        .value("AddressInvalid", LocalEntity::AaCommandStatus::AddressInvalid, "The address is within the memory map but lies in an invalid region.")
        .value("TlvInvalid", LocalEntity::AaCommandStatus::TlvInvalid, "One or more TLVs were invalid. No TLVs have been processed.")
        .value("DataInvalid", LocalEntity::AaCommandStatus::DataInvalid, "The data provided for writing is invalid.")
        .value("Unsupported", LocalEntity::AaCommandStatus::Unsupported,
               "The requested action is unsupported, typically due to unknown EXECUTE or unsupported EXECUTE.")
        // Library-specific error codes
        .value("BaseProtocolViolation", LocalEntity::AaCommandStatus::BaseProtocolViolation, "The entity sent a message that violates the base protocol.")
        .value("PartialImplementation", LocalEntity::AaCommandStatus::PartialImplementation,
               "The command is only partially implemented by the library. Please report this.")
        .value("Busy", LocalEntity::AaCommandStatus::Busy, "The library is currently busy; try again later.")
        .value("Aborted", LocalEntity::AaCommandStatus::Aborted, "The request was aborted before completion.")
        .value("NetworkError", LocalEntity::AaCommandStatus::NetworkError, "A network error occurred while transmitting or receiving the command.")
        .value("ProtocolError", LocalEntity::AaCommandStatus::ProtocolError, "Failed to parse the message due to a protocol violation.")
        .value("TimedOut", LocalEntity::AaCommandStatus::TimedOut, "The command did not receive a timely response.")
        .value("UnknownEntity", LocalEntity::AaCommandStatus::UnknownEntity, "The entity has not been detected on the network.")
        .value("InternalError", LocalEntity::AaCommandStatus::InternalError, "An internal library error occurred. Please report this.")
        .export_values()
        .def("asString", [](LocalEntity::AaCommandStatus self) { return LocalEntity::statusToString(self); });

    py::enum_<LocalEntity::MvuCommandStatus>(m, "MvuCommandStatus", "Status code returned by all MVU (Milan Vendor Unique AECP) command methods.")
        // Milan Vendor Unique Protocol Error Codes
        .value("Success", LocalEntity::MvuCommandStatus::Success, "The command completed successfully with valid results.")
        .value("NotImplemented", LocalEntity::MvuCommandStatus::NotImplemented, "The command type is not implemented by the entity.")
        // Library-specific error codes
        .value("BaseProtocolViolation", LocalEntity::MvuCommandStatus::BaseProtocolViolation, "The entity sent a message that violates the base protocol.")
        .value("PartialImplementation", LocalEntity::MvuCommandStatus::PartialImplementation,
               "This command is only partially implemented by the library. Please report this.")
        .value("Busy", LocalEntity::MvuCommandStatus::Busy, "The library is busy. Try again later.")
        .value("NetworkError", LocalEntity::MvuCommandStatus::NetworkError, "A network error occurred during command transmission.")
        .value("ProtocolError", LocalEntity::MvuCommandStatus::ProtocolError, "Failed to parse the message due to a protocol violation.")
        .value("TimedOut", LocalEntity::MvuCommandStatus::TimedOut, "The command did not receive a response within the timeout period.")
        .value("UnknownEntity", LocalEntity::MvuCommandStatus::UnknownEntity, "The target entity is unknown or not currently detected on the network.")
        .value("InternalError", LocalEntity::MvuCommandStatus::InternalError, "An internal library error occurred. Please report this issue.")
        .export_values()
        .def("asString", [](LocalEntity::MvuCommandStatus self) { return LocalEntity::statusToString(self); });

    py::enum_<LocalEntity::ControlStatus>(cls, "ControlStatus", "Status code returned by all ACMP (AVDECC Connection Management Protocol) control methods.")
        // AVDECC Protocol Error Codes
        .value("Success", LocalEntity::ControlStatus::Success, "The command was successful and returned valid results.")
        .value("ListenerUnknownID", LocalEntity::ControlStatus::ListenerUnknownID, "The Listener does not have the specified unique identifier.")
        .value("TalkerUnknownID", LocalEntity::ControlStatus::TalkerUnknownID, "The Talker does not have the specified unique identifier.")
        .value("TalkerDestMacFail", LocalEntity::ControlStatus::TalkerDestMacFail, "The Talker could not allocate a destination MAC for the Stream.")
        .value("TalkerNoStreamIndex", LocalEntity::ControlStatus::TalkerNoStreamIndex, "The Talker has no available Stream index.")
        .value("TalkerNoBandwidth", LocalEntity::ControlStatus::TalkerNoBandwidth, "The Talker could not allocate bandwidth for the Stream.")
        .value("TalkerExclusive", LocalEntity::ControlStatus::TalkerExclusive, "The Talker already has an established Stream and supports only one Listener.")
        .value("ListenerTalkerTimeout", LocalEntity::ControlStatus::ListenerTalkerTimeout, "The Listener timed out after all retries to contact the Talker.")
        .value("ListenerExclusive", LocalEntity::ControlStatus::ListenerExclusive, "The Listener already has an established connection.")
        .value("StateUnavailable", LocalEntity::ControlStatus::StateUnavailable, "Could not retrieve the state from the AVDECC Entity.")
        .value("NotConnected", LocalEntity::ControlStatus::NotConnected,
               "Attempting to disconnect while not connected or not connected to the specified Talker.")
        .value("NoSuchConnection", LocalEntity::ControlStatus::NoSuchConnection, "No connection exists for the specified Talker.")
        .value("CouldNotSendMessage", LocalEntity::ControlStatus::CouldNotSendMessage, "The Listener failed to send the message to the Talker.")
        .value("TalkerMisbehaving", LocalEntity::ControlStatus::TalkerMisbehaving, "Talker failed due to an internal error.")
        .value("ListenerMisbehaving", LocalEntity::ControlStatus::ListenerMisbehaving, "Listener failed due to an internal error.")
        .value("ControllerNotAuthorized", LocalEntity::ControlStatus::ControllerNotAuthorized, "The Controller is not authorized to modify stream connections.")
        .value("IncompatibleRequest", LocalEntity::ControlStatus::IncompatibleRequest,
               "Listener is trying to connect to a Talker with incompatible traffic class or parameters.")
        .value("NotSupported", LocalEntity::ControlStatus::NotSupported, "The command is not supported.")
        // Library Error Codes
        .value("BaseProtocolViolation", LocalEntity::ControlStatus::BaseProtocolViolation, "The entity sent a message that violates the base protocol.")
        .value("NetworkError", LocalEntity::ControlStatus::NetworkError, "A network error occurred.")
        .value("ProtocolError", LocalEntity::ControlStatus::ProtocolError, "A protocol parsing or validation error occurred.")
        .value("TimedOut", LocalEntity::ControlStatus::TimedOut, "The command timed out with no response.")
        .value("UnknownEntity", LocalEntity::ControlStatus::UnknownEntity, "The specified entity is unknown or not present on the network.")
        .value("InternalError", LocalEntity::ControlStatus::InternalError, "An internal library error occurred. Please report this.")
        .export_values()
        .def("asString", [](LocalEntity::ControlStatus self) { return LocalEntity::statusToString(self); });

    py::enum_<LocalEntity::AdvertiseFlag>(cls, "AdvertiseFlag", py::arithmetic(), "EntityAdvertise dirty flags indicating which fields have changed.")
        .value("None", LocalEntity::AdvertiseFlag::None, "No changes have occurred.")
        .value("EntityCapabilities", LocalEntity::AdvertiseFlag::EntityCapabilities, "The EntityCapabilities field has changed.")
        .value("AssociationID", LocalEntity::AdvertiseFlag::AssociationID, "The AssociationID field has changed.")
        .value("ValidTime", LocalEntity::AdvertiseFlag::ValidTime, "The ValidTime field has changed.")
        .value("GptpGrandmasterID", LocalEntity::AdvertiseFlag::GptpGrandmasterID, "The gPTP GrandmasterID field has changed.")
        .value("GptpDomainNumber", LocalEntity::AdvertiseFlag::GptpDomainNumber, "The gPTP DomainNumber field has changed.")
        .export_values();
    bindEnumBitfield<LocalEntity::AdvertiseFlag>(cls, "AdvertiseFlags");

    cls.def("enableEntityAdvertising", &LocalEntity::enableEntityAdvertising, py::arg("availableDuration"), py::arg("interfaceIndex") = std::nullopt,
            "Enables entity advertising with a duration between 2–62 seconds on the specified interface index or all interfaces. "
            "Returns false if parameters are invalid.")
        .def("disableEntityAdvertising", &LocalEntity::disableEntityAdvertising, py::arg("interfaceIndex") = std::nullopt,
             "Disables entity advertising on the specified interface index or all interfaces.")
        .def("discoverRemoteEntities", &LocalEntity::discoverRemoteEntities, "Requests discovery of all remote entities. Returns true if successful.")
        .def("discoverRemoteEntity", &LocalEntity::discoverRemoteEntity, py::arg("entityID"),
             "Requests discovery of a specific remote entity by its unique identifier. Returns true if successful.")
        .def("forgetRemoteEntity", &LocalEntity::forgetRemoteEntity, py::arg("entityID"),
             "Removes knowledge of a previously discovered remote entity. Returns true if successful.")
        .def(
            "setAutomaticDiscoveryDelay",
            [](LocalEntity& self, std::uint64_t delay_ms) { self.setAutomaticDiscoveryDelay(std::chrono::milliseconds{delay_ms}); }, py::arg("delay_ms"),
            "Sets the delay between automatic discovery cycles. 0 disables auto-discovery.")
        .def("lock", &LocalEntity::lock, "Locks the entity for thread-safe access. Part of BasicLockable.")
        .def("unlock", &LocalEntity::unlock, "Unlocks the entity. Part of BasicLockable.")
        .def("isSelfLocked", &LocalEntity::isSelfLocked, "Returns true if the calling thread already holds the entity lock.");
}