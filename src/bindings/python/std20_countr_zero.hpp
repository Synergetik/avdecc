#include <cstdint>
#include <limits>
#include <type_traits>

namespace std20
{
    template <typename T>
    constexpr int countr_zero(T x) noexcept
    {
        static_assert(std::is_unsigned<T>::value, "countr_zero requires unsigned type");

        if (x == 0)
            return std::numeric_limits<T>::digits;

#if defined(_MSC_VER)
        unsigned long index;
        if constexpr (sizeof(T) <= sizeof(unsigned long))
        {
            if (_BitScanForward(&index, static_cast<unsigned long>(x)))
                return static_cast<int>(index);
        }
#if defined(_WIN64)
        else if constexpr (sizeof(T) <= sizeof(unsigned __int64))
        {
            if (_BitScanForward64(&index, static_cast<unsigned __int64>(x)))
                return static_cast<int>(index);
        }
#endif
        return std::numeric_limits<T>::digits;
#elif defined(__GNUC__) || defined(__clang__)
        if constexpr (sizeof(T) <= sizeof(unsigned int))
        {
            return x ? __builtin_ctz(static_cast<unsigned int>(x)) : std::numeric_limits<T>::digits;
        }
        else if constexpr (sizeof(T) <= sizeof(unsigned long))
        {
            return x ? __builtin_ctzl(static_cast<unsigned long>(x)) : std::numeric_limits<T>::digits;
        }
        else if constexpr (sizeof(T) <= sizeof(unsigned long long))
        {
            return x ? __builtin_ctzll(static_cast<unsigned long long>(x)) : std::numeric_limits<T>::digits;
        }
        return std::numeric_limits<T>::digits;
#else
        // Pure fallback: count manually (slower)
        int count = 0;
        while ((x & 1u) == 0 && count < std::numeric_limits<T>::digits)
        {
            x >>= 1;
            ++count;
        }
        return count;
#endif
    }
} // namespace std20