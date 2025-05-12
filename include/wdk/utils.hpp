#ifndef WDK_UTILS_HPP
#define WDK_UTILS_HPP
#include <cstdint>
#include <utility>
#include <type_traits>
#include <concepts>
#include <cstring>

#define ALWAYS_INLINE __attribute__((always_inline)) inline

#define BEGIN_INTEL_SYNTAX ".intel_syntax noprefix;"
#define END_INTEL_SYNTAX ".att_syntax;"

// custom helper types
namespace win {
    // mostly used for bitfields throughout the library, for example MSRs.
    template<typename Derived, typename Alias>
    struct scalar_convertible {
        constexpr scalar_convertible() = default;

        constexpr scalar_convertible(const Alias &v) {
            assign_from(v);
        }

        constexpr Derived &operator=(const Alias &v) {
            return assign_from(v);
        }

        constexpr operator Alias() const {
            return std::bit_cast<Alias>(*static_cast<const Derived *>(this));
        }

    private:
        constexpr Derived &assign_from(const Alias &v) {
            *static_cast<Derived *>(this) = std::bit_cast<Derived>(v);
            return *static_cast<Derived *>(this);
        }
    } __attribute__((packed));
} // namespace win

#endif // WDK_UTILS_HPP
