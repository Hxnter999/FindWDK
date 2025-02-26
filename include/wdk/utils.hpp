#ifndef WDK_UTILS_HPP
#define WDK_UTILS_HPP
#include <cstdint>
#include <utility>
#include <type_traits>

#define ALWAYS_INLINE __attribute__((always_inline)) inline

#define BEGIN_INTEL_SYNTAX ".intel_syntax noprefix\n\t"
#define END_INTEL_SYNTAX ".att_syntax\n\t"

#define BEGIN_EXTERN_C extern "C" {
#define END_EXTERN_C }

#endif // WDK_UTILS_HPP