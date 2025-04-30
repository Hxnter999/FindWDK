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

#define SCALAR_WRAPPER_MEMBER_FUNCTIONS(struct_name, member_variable) \
    constexpr struct_name() = default; \
    constexpr struct_name(const decltype(member_variable)& rhs) : member_variable(rhs) {} \
    constexpr struct_name& operator=(const decltype(member_variable)& rhs) { \
        member_variable = rhs; \
        return *this; \
    } \
    constexpr operator decltype(member_variable)() const { return member_variable; } \
    constexpr explicit operator bool() const { return static_cast<bool>(member_variable); } \
    constexpr bool operator==(const struct_name& rhs) const { \
        return member_variable == rhs.member_variable; \
    } \
    constexpr bool operator==(const decltype(member_variable)& rhs) const { \
        return member_variable == rhs; \
    }




// custom helper types
namespace win {

} // namespace win

#endif // WDK_UTILS_HPP
