#ifndef WDK_INTRINSICS_HPP
#define WDK_INTRINSICS_HPP
#include "../utils.hpp"
#include "amd.hpp"
#include "intel.hpp"

namespace intrin
{
    ALWAYS_INLINE void halt() {
        asm volatile(
            "hlt"
        );
    }

    ALWAYS_INLINE void cli() {
        asm volatile(
            "cli"
        );
    }

    ALWAYS_INLINE void sti() {
        asm volatile(
            "sti"
        );
    }

    ALWAYS_INLINE void nop() {
        asm volatile(
            "nop"
        );
    }

    ALWAYS_INLINE void pause() {
        asm volatile(
            "pause"
        );
    }

    ALWAYS_INLINE void int3() {
        asm volatile(
            "int3"
        );
    }

    ALWAYS_INLINE void iret() {
        asm volatile(
            "iret"
        );
    }

    ALWAYS_INLINE std::uint64_t rdmsr(const std::uint32_t msr) {
        std::uint32_t low, high;
        asm volatile(
            "rdmsr"
            : "=a"(low), "=d"(high)
            : "c"(msr)
        );
        return (static_cast<std::uint64_t>(high) << 32) | low;
    }

    ALWAYS_INLINE void wrmsr(const std::uint32_t msr, const std::uint64_t value) {
        std::uint32_t low = static_cast<std::uint32_t>(value);
        std::uint32_t high = static_cast<std::uint32_t>(value >> 32);
    
        asm volatile (
            "wrmsr"
            :: "c"(msr), "a"(low), "d"(high)
            : "memory"
        );
    }

    ALWAYS_INLINE void invlpg(const void* address) {
        asm volatile(
            "invlpg (%0)"
            :: "r"(address)
            : "memory"
        );
    }

    ALWAYS_INLINE void lfence() {
        asm volatile(
            "lfence"
            ::: "memory"
        );
    }

    ALWAYS_INLINE void sfence() {
        asm volatile(
            "sfence"
            ::: "memory"
        );
    }

    ALWAYS_INLINE void mfence() {
        asm volatile(
            "mfence"
            ::: "memory"
        );
    }

    ALWAYS_INLINE std::uint64_t rdtsc() {
        std::uint32_t low, high;
        asm volatile(
            "rdtsc"
            : "=a"(low), "=d"(high)
        );
        return (static_cast<std::uint64_t>(high) << 32) | low;
    }


} // namespace intrin
#endif // WDK_INTRINSICS_HPP