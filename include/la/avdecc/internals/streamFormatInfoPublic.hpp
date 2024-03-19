#include <la/avdecc/internals/streamFormatInfo.hpp>

namespace la
{
namespace avdecc
{
namespace entity
{
namespace model
{

class StreamFormatInfoPublic
{
public:
	// Types
	enum class Type
	{
		None,
		IEC_61883_6,
		AAF,
		ClockReference,
		Unsupported,
	};
	// Sample format (depth and type)
	enum class SampleFormat
	{
		Int8,
		Int16,
		Int24,
		Int32,
		Int64,
		FixedPoint32,
		FloatingPoint32,
		Unknown,
	};

    StreamFormatInfoPublic(StreamFormat const& streamFormat)
        : _ref(StreamFormatInfo::create(streamFormat))
    {}

    StreamFormat  getStreamFormat() const noexcept      { return _ref->getStreamFormat(); }
	StreamFormat  getAdaptedStreamFormat(std::uint16_t const channelsCount) const noexcept { return _ref->getAdaptedStreamFormat(channelsCount);}
	Type          getType() const noexcept              { return (Type)_ref->getType(); }
	std::uint16_t getChannelsCount() const noexcept     { return _ref->getChannelsCount(); }
	bool          isUpToChannelsCount() const noexcept  { return _ref->isUpToChannelsCount(); }
	SamplingRate  getSamplingRate() const noexcept      { return _ref->getSamplingRate(); }
	SampleFormat  getSampleFormat() const noexcept      { return (SampleFormat)_ref->getSampleFormat(); }
	bool          useSynchronousClock() const noexcept  { return _ref->useSynchronousClock();}
	std::uint16_t getSampleSize() const noexcept        { return _ref->getSampleSize();}
	std::uint16_t getSampleBitDepth() const noexcept    { return _ref->getSampleBitDepth();}

private:
    StreamFormatInfo::UniquePointer _ref;
};

} // namespace model
} // namespace entity
} // namespace avdecc
} // namespace la
