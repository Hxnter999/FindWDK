#ifndef WDK_INTRINSICS_HPP
#define WDK_INTRINSICS_HPP
#include "../utils.hpp"
#include "../arch/arch.hpp"
#include "amd.hpp"
#include "intel.hpp"

namespace intrin {
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

    template<int N>
    ALWAYS_INLINE void int_() {
        asm volatile(
            "int %0"
            :
            : "i"(N)
        );
    }

    ALWAYS_INLINE void int3() {
        return int_<3>();
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
            :
        );
        return (static_cast<std::uint64_t>(high) << 32) | low;
    }

    template<arch::is_msr T>
    ALWAYS_INLINE T rdmsr() {
        return rdmsr(T::number);
    }

    ALWAYS_INLINE void wrmsr(const std::uint32_t msr, const std::uint64_t value) {
        std::uint32_t low = static_cast<std::uint32_t>(value);
        std::uint32_t high = static_cast<std::uint32_t>(value >> 32);

        asm volatile (
            "wrmsr"
            :
            : "c"(msr), "a"(low), "d"(high)
            : "memory"
        );
    }

    template<arch::is_msr T>
    ALWAYS_INLINE void wrmsr(const T &value) {
        return wrmsr(T::number, static_cast<std::uint64_t>(value));
    }

    ALWAYS_INLINE void invlpg(const void *address) {
        asm volatile(
            "invlpg (%0)"
            :
            : "r"(address)
            : "memory"
        );
    }

    ALWAYS_INLINE void lfence() {
        asm volatile(
            "lfence"
            :
            :
            : "memory"
        );
    }

    ALWAYS_INLINE void sfence() {
        asm volatile(
            "sfence"
            :
            :
            : "memory"
        );
    }

    ALWAYS_INLINE void mfence() {
        asm volatile(
            "mfence"
            :
            :
            : "memory"
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

    ALWAYS_INLINE std::uint64_t read_cr0() {
        std::uint64_t value;
        asm volatile(
            "mov %%cr0, %0"
            : "=r"(value)
        );
        return value;
    }

    ALWAYS_INLINE std::uint64_t read_cr2() {
        std::uint64_t value;
        asm volatile(
            "mov %%cr2, %0"
            : "=r"(value)
        );
        return value;
    }

    ALWAYS_INLINE std::uint64_t read_cr3() {
        std::uint64_t value;
        asm volatile(
            "mov %%cr3, %0"
            : "=r"(value)
        );
        return value;
    }

    ALWAYS_INLINE std::uint64_t read_cr4() {
        std::uint64_t value;
        asm volatile(
            "mov %%cr4, %0"
            : "=r"(value)
        );
        return value;
    }

    ALWAYS_INLINE std::uint64_t read_cr8() {
        std::uint64_t value;
        asm volatile(
            "mov %%cr8, %0"
            : "=r"(value)
        );
        return value;
    }

    ALWAYS_INLINE void write_cr0(std::uint64_t value) {
        asm volatile(
            "mov %0, %%cr0"
            :
            : "r"(value)
            : "memory");
    }

    ALWAYS_INLINE void write_cr2(std::uint64_t value) {
        asm volatile(
            "mov %0, %%cr2"
            :
            : "r"(value)
        );
    }

    ALWAYS_INLINE void write_cr3(std::uint64_t value) {
        asm volatile(
            "mov %0, %%cr3"
            :
            : "r"(value)
            : "memory");
    }

    ALWAYS_INLINE void write_cr4(std::uint64_t value) {
        asm volatile(
            "mov %0, %%cr4"
            :
            : "r"(value)
            : "memory");
    }

    ALWAYS_INLINE void write_cr8(std::uint64_t value) {
        asm volatile(
            "mov %0, %%cr8"
            :
            : "r"(value)
            : "memory");
    }

    ALWAYS_INLINE void lidt(const arch::interrupt_descriptor_table &idt) {
        asm volatile(
            "lidt %0"
            :
            : "m"(idt));
    }

    ALWAYS_INLINE arch::interrupt_descriptor_table sidt() {
        arch::interrupt_descriptor_table idt{};
        asm volatile(
            "sidt %0"
            : "=m"(idt)
            :
            : "memory");
        return idt;
    }

    ALWAYS_INLINE void lgdt(const arch::global_descriptor_table &gdt) {
        asm volatile(
            "lgdt %0"
            :
            : "m"(gdt)
        );
    }

    ALWAYS_INLINE arch::global_descriptor_table lgdt() {
        arch::global_descriptor_table gdt{};
        asm volatile(
            "lgdt %0"
            : "=m"(gdt)
            :
            : "memory"
        );
    }
} // namespace intrin
#endif // WDK_INTRINSICS_HPP
