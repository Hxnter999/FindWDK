#ifndef WDK_INTEL_INTRINSICS_HPP
#define WDK_INTEL_INTRINSICS_HPP

namespace intrin::intel {
    ALWAYS_INLINE void vmwrite(const std::uint64_t field, const std::uint64_t value) {
        asm volatile(
            "vmwrite %1, %0"
            :
            : "r"(field), "r"(value)
            : "cc"
        );
    }
} // namespace intrin::intel
#endif // WDK_INTEL_INTRINSICS_HPP