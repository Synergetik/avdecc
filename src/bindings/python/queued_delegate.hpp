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
 * @file queued_delegate.hpp
 * @author Vitalij Mast
 */

#include "job_queue.hpp"

#include <la/avdecc/avdecc.hpp>

namespace la::avdecc::entity::controller
{
    class QueuedDelegate final : public DefaultedDelegate
    {
    public:
        using DefaultedDelegate::DefaultedDelegate;

        QueuedDelegate(Delegate* const delegate) noexcept
            : DefaultedDelegate()
            , delegate_(delegate)
        {}

        // clang-format off
        void onTransportError(la::avdecc::entity::controller::Interface const* const controller) noexcept override
        {
            enqueue(&Delegate::onTransportError, controller);
        }

        void onEntityOnline(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::Entity const& entity) noexcept override
        {
            enqueue(&Delegate::onEntityOnline, controller, entityID, entity);
        }

        void onEntityUpdate(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::Entity const& entity) noexcept override
        {
            enqueue(&Delegate::onEntityUpdate, controller, entityID, entity);
        }

        void onEntityOffline(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            enqueue(&Delegate::onEntityOffline, controller, entityID);
        }

        void onControllerConnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            enqueue(&Delegate::onControllerConnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onControllerDisconnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            enqueue(&Delegate::onControllerDisconnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onListenerConnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            enqueue(&Delegate::onListenerConnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onListenerDisconnectResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            enqueue(&Delegate::onListenerDisconnectResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onGetTalkerStreamStateResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            enqueue(&Delegate::onGetTalkerStreamStateResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onGetListenerStreamStateResponseSniffed(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::entity::model::StreamIdentification const& talkerStream, la::avdecc::entity::model::StreamIdentification const& listenerStream, std::uint16_t const connectionCount, la::avdecc::entity::ConnectionFlags const flags, la::avdecc::entity::LocalEntity::ControlStatus const status) noexcept override
        {
            enqueue(&Delegate::onGetListenerStreamStateResponseSniffed, controller, talkerStream, listenerStream, connectionCount, flags, status);
        }

        void onDeregisteredFromUnsolicitedNotifications(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            enqueue(&Delegate::onDeregisteredFromUnsolicitedNotifications, controller, entityID);
        }

        void onEntityAcquired(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const owningEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            enqueue(&Delegate::onEntityAcquired, controller, entityID, owningEntity, descriptorType, descriptorIndex);
        }

        void onEntityReleased(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const owningEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            enqueue(&Delegate::onEntityReleased, controller, entityID, owningEntity, descriptorType, descriptorIndex);
        }

        void onEntityLocked(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const lockingEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            enqueue(&Delegate::onEntityLocked, controller, entityID, lockingEntity, descriptorType, descriptorIndex);
        }

        void onEntityUnlocked(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const lockingEntity, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex) noexcept override
        {
            enqueue(&Delegate::onEntityUnlocked, controller, entityID, lockingEntity, descriptorType, descriptorIndex);
        }

        void onConfigurationChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex) noexcept override
        {
            enqueue(&Delegate::onConfigurationChanged, controller, entityID, configurationIndex);
        }

        void onStreamInputFormatChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamFormat const streamFormat) noexcept override
        {
            enqueue(&Delegate::onStreamInputFormatChanged, controller, entityID, streamIndex, streamFormat);
        }

        void onStreamOutputFormatChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamFormat const streamFormat) noexcept override
        {
            enqueue(&Delegate::onStreamOutputFormatChanged, controller, entityID, streamIndex, streamFormat);
        }

        void onStreamPortInputAudioMappingsChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::MapIndex const numberOfMaps, la::avdecc::entity::model::MapIndex const mapIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            enqueue(&Delegate::onStreamPortInputAudioMappingsChanged, controller, entityID, streamPortIndex, numberOfMaps, mapIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::MapIndex const numberOfMaps, la::avdecc::entity::model::MapIndex const mapIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            enqueue(&Delegate::onStreamPortOutputAudioMappingsChanged, controller, entityID, streamPortIndex, numberOfMaps, mapIndex, mappings);
        }

        void onStreamInputInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamInfo const& info, bool const fromGetStreamInfoResponse) noexcept override
        {
            enqueue(&Delegate::onStreamInputInfoChanged, controller, entityID, streamIndex, info, fromGetStreamInfoResponse);
        }

        void onStreamOutputInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::StreamInfo const& info, bool const fromGetStreamInfoResponse) noexcept override
        {
            enqueue(&Delegate::onStreamOutputInfoChanged, controller, entityID, streamIndex, info, fromGetStreamInfoResponse);
        }

        void onEntityNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvdeccFixedString const& entityName) noexcept override
        {
            enqueue(&Delegate::onEntityNameChanged, controller, entityID, entityName);
        }

        void onEntityGroupNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvdeccFixedString const& entityGroupName) noexcept override
        {
            enqueue(&Delegate::onEntityGroupNameChanged, controller, entityID, entityGroupName);
        }

        void onConfigurationNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvdeccFixedString const& configurationName) noexcept override  
        {
            enqueue(&Delegate::onConfigurationNameChanged, controller, entityID, configurationIndex, configurationName);
        }

        void onAudioUnitNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, la::avdecc::entity::model::AvdeccFixedString const& audioUnitName) noexcept override
        {
            enqueue(&Delegate::onAudioUnitNameChanged, controller, entityID, configurationIndex, audioUnitIndex, audioUnitName);
        }

        void onStreamInputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::AvdeccFixedString const& streamName) noexcept override
        {
            enqueue(&Delegate::onStreamInputNameChanged, controller, entityID, configurationIndex, streamIndex, streamName);
        }

        void onStreamOutputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::model::AvdeccFixedString const& streamName) noexcept override
        {
            enqueue(&Delegate::onStreamOutputNameChanged, controller, entityID, configurationIndex, streamIndex, streamName);
        }

        void onJackInputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, la::avdecc::entity::model::AvdeccFixedString const& jackName) noexcept override
        {
            enqueue(&Delegate::onJackInputNameChanged, controller, entityID, configurationIndex, jackIndex, jackName);
        }

        void onJackOutputNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::JackIndex const jackIndex, la::avdecc::entity::model::AvdeccFixedString const& jackName) noexcept override
        {
            enqueue(&Delegate::onJackOutputNameChanged, controller, entityID, configurationIndex, jackIndex, jackName);
        }

        void onAvbInterfaceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AvdeccFixedString const& avbInterfaceName) noexcept override
        {
            enqueue(&Delegate::onAvbInterfaceNameChanged, controller, entityID, configurationIndex, avbInterfaceIndex, avbInterfaceName);
        }

        void onClockSourceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex, la::avdecc::entity::model::AvdeccFixedString const& clockSourceName) noexcept override
        {
            enqueue(&Delegate::onClockSourceNameChanged, controller, entityID, configurationIndex, clockSourceIndex, clockSourceName);
        }

        void onMemoryObjectNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, la::avdecc::entity::model::AvdeccFixedString const& memoryObjectName) noexcept override
        {
            enqueue(&Delegate::onMemoryObjectNameChanged, controller, entityID, configurationIndex, memoryObjectIndex, memoryObjectName);
        }

        void onAudioClusterNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClusterIndex const audioClusterIndex, la::avdecc::entity::model::AvdeccFixedString const& audioClusterName) noexcept override
        {
            enqueue(&Delegate::onAudioClusterNameChanged, controller, entityID, configurationIndex, audioClusterIndex, audioClusterName);
        }

        void onControlNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ControlIndex const controlIndex, la::avdecc::entity::model::AvdeccFixedString const& controlName) noexcept override
        {
            enqueue(&Delegate::onControlNameChanged, controller, entityID, configurationIndex, controlIndex, controlName);
        }

        void onClockDomainNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::AvdeccFixedString const& clockDomainName) noexcept override
        {
            enqueue(&Delegate::onClockDomainNameChanged, controller, entityID, configurationIndex, clockDomainIndex, clockDomainName);
        }

        void onTimingNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::TimingIndex const timingIndex, la::avdecc::entity::model::AvdeccFixedString const& timingName) noexcept override
        {
            enqueue(&Delegate::onTimingNameChanged, controller, entityID, configurationIndex, timingIndex, timingName);
        }

        void onPtpInstanceNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpInstanceIndex const ptpInstanceIndex, la::avdecc::entity::model::AvdeccFixedString const& ptpInstanceName) noexcept override
        {
            enqueue(&Delegate::onPtpInstanceNameChanged, controller, entityID, configurationIndex, ptpInstanceIndex, ptpInstanceName);
        }

        void onPtpPortNameChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::PtpPortIndex const ptpPortIndex, la::avdecc::entity::model::AvdeccFixedString const& ptpPortName) noexcept override
        {
            enqueue(&Delegate::onPtpPortNameChanged, controller, entityID, configurationIndex, ptpPortIndex, ptpPortName);
        }

        void onAssociationIDChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::UniqueIdentifier const associationID) noexcept override
        {
            enqueue(&Delegate::onAssociationIDChanged, controller, entityID, associationID);
        }

        void onAudioUnitSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AudioUnitIndex const audioUnitIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            enqueue(&Delegate::onAudioUnitSamplingRateChanged, controller, entityID, audioUnitIndex, samplingRate);
        }

        void onVideoClusterSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClusterIndex const videoClusterIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            enqueue(&Delegate::onVideoClusterSamplingRateChanged, controller, entityID, videoClusterIndex, samplingRate);
        }

        void onSensorClusterSamplingRateChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClusterIndex const sensorClusterIndex, la::avdecc::entity::model::SamplingRate const samplingRate) noexcept override
        {
            enqueue(&Delegate::onSensorClusterSamplingRateChanged, controller, entityID, sensorClusterIndex, samplingRate);
        }

        void onClockSourceChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::ClockSourceIndex const clockSourceIndex) noexcept override
        {
            enqueue(&Delegate::onClockSourceChanged, controller, entityID, clockDomainIndex, clockSourceIndex);
        }

        void onControlValuesChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ControlIndex const controlIndex, la::avdecc::MemoryBuffer const& packedControlValues) noexcept override
        {
            enqueue(&Delegate::onControlValuesChanged, controller, entityID, controlIndex, packedControlValues);
        }

        void onStreamInputStarted(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            enqueue(&Delegate::onStreamInputStarted, controller, entityID, streamIndex);
        }

        void onStreamOutputStarted(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            enqueue(&Delegate::onStreamOutputStarted, controller, entityID, streamIndex);
        }

        void onStreamInputStopped(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            enqueue(&Delegate::onStreamInputStopped, controller, entityID, streamIndex);
        }

        void onStreamOutputStopped(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex) noexcept override
        {
            enqueue(&Delegate::onStreamOutputStopped, controller, entityID, streamIndex);
        }

        void onAvbInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AvbInfo const& info) noexcept override
        {
            enqueue(&Delegate::onAvbInfoChanged, controller, entityID, avbInterfaceIndex, info);
        }

        void onAsPathChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::model::AsPath const& asPath) noexcept override
        {
            enqueue(&Delegate::onAsPathChanged, controller, entityID, avbInterfaceIndex, asPath);
        }

        void onEntityCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::EntityCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            enqueue(&Delegate::onEntityCountersChanged, controller, entityID, validCounters, counters);
        }

        void onAvbInterfaceCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::AvbInterfaceIndex const avbInterfaceIndex, la::avdecc::entity::AvbInterfaceCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            enqueue(&Delegate::onAvbInterfaceCountersChanged, controller, entityID, avbInterfaceIndex, validCounters, counters);
        }

        void onClockDomainCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::ClockDomainCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            enqueue(&Delegate::onClockDomainCountersChanged, controller, entityID, clockDomainIndex, validCounters, counters);
        }

        void onStreamInputCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::StreamInputCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            enqueue(&Delegate::onStreamInputCountersChanged, controller, entityID, streamIndex, validCounters, counters);
        }

        void onStreamOutputCountersChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, la::avdecc::entity::StreamOutputCounterValidFlags const validCounters, la::avdecc::entity::model::DescriptorCounters const& counters) noexcept override
        {
            enqueue(&Delegate::onStreamOutputCountersChanged, controller, entityID, streamIndex, validCounters, counters);
        }

        void onStreamPortInputAudioMappingsAdded(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            enqueue(&Delegate::onStreamPortInputAudioMappingsAdded, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsAdded(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            enqueue(&Delegate::onStreamPortOutputAudioMappingsAdded, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortInputAudioMappingsRemoved(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            enqueue(&Delegate::onStreamPortInputAudioMappingsRemoved, controller, entityID, streamPortIndex, mappings);
        }

        void onStreamPortOutputAudioMappingsRemoved(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamPortIndex const streamPortIndex, la::avdecc::entity::model::AudioMappings const& mappings) noexcept override
        {
            enqueue(&Delegate::onStreamPortOutputAudioMappingsRemoved, controller, entityID, streamPortIndex, mappings);
        }

        void onMemoryObjectLengthChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ConfigurationIndex const configurationIndex, la::avdecc::entity::model::MemoryObjectIndex const memoryObjectIndex, std::uint64_t const length) noexcept override
        {
            enqueue(&Delegate::onMemoryObjectLengthChanged, controller, entityID, configurationIndex, memoryObjectIndex, length);
        }

        void onOperationStatus(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::DescriptorType const descriptorType, la::avdecc::entity::model::DescriptorIndex const descriptorIndex, la::avdecc::entity::model::OperationID const operationID, std::uint16_t const percentComplete) noexcept override
        {
            enqueue(&Delegate::onOperationStatus, controller, entityID, descriptorType, descriptorIndex, operationID, percentComplete);
        }

        void onMaxTransitTimeChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::StreamIndex const streamIndex, std::chrono::nanoseconds const& maxTransitTime) noexcept override
        {
            enqueue(&Delegate::onMaxTransitTimeChanged, controller, entityID, streamIndex, maxTransitTime);
        }

        void onSystemUniqueIDChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::SystemUniqueIdentifier const systemUniqueID) noexcept override
        {
            enqueue(&Delegate::onSystemUniqueIDChanged, controller, entityID, systemUniqueID);
        }

        void onMediaClockReferenceInfoChanged(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID, la::avdecc::entity::model::ClockDomainIndex const clockDomainIndex, la::avdecc::entity::model::MediaClockReferenceInfo const& mcrInfo) noexcept override    
        {
            enqueue(&Delegate::onMediaClockReferenceInfoChanged, controller, entityID, clockDomainIndex, mcrInfo);
        }

        void onEntityIdentifyNotification(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const entityID) noexcept override
        {
            enqueue(&Delegate::onEntityIdentifyNotification, controller, entityID);
        }

        void onAecpRetry(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            enqueue(&Delegate::onAecpRetry, controller, entityID);
        }

        void onAecpTimeout(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            enqueue(&Delegate::onAecpTimeout, controller, entityID);
        }

        void onAecpUnexpectedResponse(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID) noexcept override
        {
            enqueue(&Delegate::onAecpUnexpectedResponse, controller, entityID);
        }

        void onAecpResponseTime(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, std::chrono::milliseconds const& responseTime) noexcept override
        {
            enqueue(&Delegate::onAecpResponseTime, controller, entityID, responseTime);
        }

        void onAemAecpUnsolicitedReceived(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, la::avdecc::protocol::AecpSequenceID const sequenceID) noexcept override
        {
            enqueue(&Delegate::onAemAecpUnsolicitedReceived, controller, entityID, sequenceID);
        }

        void onMvuAecpUnsolicitedReceived(la::avdecc::entity::controller::Interface const* const controller, la::avdecc::UniqueIdentifier const& entityID, la::avdecc::protocol::AecpSequenceID const sequenceID) noexcept override
        {
            enqueue(&Delegate::onMvuAecpUnsolicitedReceived, controller, entityID, sequenceID);
        }
        // clang-format on

        void processJobs() noexcept
        {
            job_queue_.process();
        }

        template <class R, class... A>
        std::function<R(A...)> invoke_defered(std::function<R(A...)> h) noexcept
        {
            // Capture 'this' (or a pointer) + move handler.
            return [q = this, h = std::move(h)](A... a) mutable -> R {
                if constexpr (std::is_void_v<R>)
                {
                    q->enqueueFn(h, std::forward<A>(a)...);
                }
                else
                {
                    static_assert(std::is_void_v<R>, "Non-void handlers are not supported");
                }
            };
        }

    private:
        template <class MemFn, class... Args>
        void enqueue(MemFn mf, Args&&... args) noexcept
        {
            // Copies everything (refs become values). Pointers stay pointers.
            using Tuple = std::tuple<std::decay_t<Args>...>;
            Tuple tup(std::forward<Args>(args)...);

            auto target = delegate_;
            job_queue_.enqueue([target, mf, tup = std::move(tup)]() mutable {
                std::apply([&](auto&&... unpacked) { ((*target).*mf)(std::forward<decltype(unpacked)>(unpacked)...); }, tup);
            });
        };

        template <class Fn, class... Args>
        void enqueueFn(Fn&& fn, Args&&... args) noexcept
        {
            using F = std::decay_t<Fn>;
            F f(std::forward<Fn>(fn));

            using Tuple = std::tuple<std::decay_t<Args>...>;
            Tuple tup(std::forward<Args>(args)...);

            job_queue_.enqueue([f = std::move(f), tup = std::move(tup)]() mutable {
                std::apply([&](auto&&... unpacked) { std::invoke(f, std::forward<decltype(unpacked)>(unpacked)...); }, tup);
            });
        }

        JobQueue        job_queue_;
        Delegate* const delegate_;
    };
} // namespace la::avdecc::entity::controller