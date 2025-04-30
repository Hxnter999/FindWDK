#ifndef WDK_ARCH_MSRS_HPP
#define WDK_ARCH_MSRS_HPP
#include "../utils.hpp"

namespace arch {
    struct efer {
        static constexpr std::uint32_t number = 0xC000'0080;

        union {
            std::uint64_t value{};
            struct {
                std::uint64_t syscall_extensions : 1;
                std::uint64_t reserved1 : 7;
                std::uint64_t long_mode : 1;
                std::uint64_t reserved9 : 1;
                std::uint64_t long_mode_active : 1;
                std::uint64_t no_execute : 1;
                std::uint64_t svm : 1;
                std::uint64_t long_mode_segment_limit : 1;
                std::uint64_t fast_fxsave_fxrstor : 1;
                std::uint64_t translation_cache_extension : 1;
                std::uint64_t execute_only_pte : 1; // this is xotext, allows any given pte to be marked as execute only
                std::uint64_t mcommit : 1;
                std::uint64_t interruptible_wbinvd_wbnoinvd : 1;
                std::uint64_t reserved19 : 1;
                std::uint64_t upper_address_ignore : 1;
                std::uint64_t auto_ibrs : 1;
                std::uint64_t reserved22 : 42;
            };
        };

        SCALAR_WRAPPER_MEMBER_FUNCTIONS(efer, value);
    };

    // virtual machine host save physical address as per the manual
    struct vmhs_pa {
        static constexpr uint32_t number = 0xC001'0117;

        std::uint64_t value{};
        SCALAR_WRAPPER_MEMBER_FUNCTIONS(vmhs_pa, value);
    };
} // namespace arch

#endif // WDK_ARCH_MSRS_HPP