#ifndef WDK_UTILS_HPP
#define WDK_UTILS_HPP
#include <cstdint>
#include <utility>
#include <type_traits>
#include <concepts>
#include <cstring>

#define ALWAYS_INLINE __attribute__((always_inline)) inline

#define BEGIN_INTEL_SYNTAX ".intel_syntax noprefix\n\t"
#define END_INTEL_SYNTAX ".att_syntax\n\t"

#define BEGIN_EXTERN_C extern "C" {
#define END_EXTERN_C }


// custom helper types
namespace win {
    template<typename Derived, typename Alias>
    struct scalar_convertible {
        scalar_convertible() = default;

        scalar_convertible(const Alias &v) {
            assign_from(v);
        }

        Derived &operator=(const Alias &v) {
            return assign_from(v);
        }

        operator Alias() const {
            return std::bit_cast<Alias>(*static_cast<const Derived *>(this));
        }

    private:
        Derived &assign_from(const Alias &v) {
            *static_cast<Derived *>(this) = std::bit_cast<Derived>(v);
            return *static_cast<Derived *>(this);
        }
    };


} // namespace win

#endif // WDK_UTILS_HPP
