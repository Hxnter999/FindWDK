#ifndef WDK_ARCH_MSRS_HPP
#define WDK_ARCH_MSRS_HPP

namespace arch {
    template <typename T>
    concept is_msr = requires { T::number; };

    struct efer : win::scalar_convertible<efer, std::uint64_t> {
        using win::scalar_convertible<efer, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC000'0080;

        std::uint64_t syscall_extensions            : 1 {};
        std::uint64_t reserved1                     : 7 {};
        std::uint64_t long_mode                     : 1 {};
        std::uint64_t reserved2                     : 1 {};
        std::uint64_t long_mode_active              : 1 {};
        std::uint64_t no_execute                    : 1 {};
        std::uint64_t svm                           : 1 {};
        std::uint64_t long_mode_segment_limit       : 1 {};
        std::uint64_t fast_fxsave_fxrstor           : 1 {};
        std::uint64_t translation_cache_extension   : 1 {};
        std::uint64_t execute_only_pte              : 1 {}; // this is xotext, allows any given pte to be marked as execute only
        std::uint64_t mcommit                       : 1 {};
        std::uint64_t interruptible_wbinvd_wbnoinvd : 1 {};
        std::uint64_t reserved3                     : 1 {};
        std::uint64_t upper_address_ignore          : 1 {};
        std::uint64_t auto_ibrs                     : 1 {};
        std::uint64_t reserved4                     : 42 {};
    };

    // virtual machine host save physical address as per the manual
    struct vmhs_pa : win::scalar_convertible<vmhs_pa, std::uint64_t> {
        using win::scalar_convertible<vmhs_pa, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC001'0117;

        std::uint64_t value{};
    };

    struct lstar : win::scalar_convertible<lstar, std::uint64_t> {
        using win::scalar_convertible<lstar, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC000'0082;

        std::uint64_t value{};
    };

    // max performance
    struct mperf : win::scalar_convertible<mperf, std::uint64_t> {
        using win::scalar_convertible<mperf, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC000'00E7;

        std::uint64_t value{};
    };

    // actual performance
    struct aperf : win::scalar_convertible<aperf, std::uint64_t> {
        using win::scalar_convertible<aperf, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC000'00E8;

        std::uint64_t value{};
    };

    // instructions retired
    struct irperf : win::scalar_convertible<irperf, std::uint64_t> {
        using win::scalar_convertible<irperf, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC000'00E9;

        std::uint64_t value    : 48 {};
        std::uint64_t reserved : 16 {};
    };

    struct fs_base : win::scalar_convertible<fs_base, std::uint64_t> {
        using win::scalar_convertible<fs_base, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC000'0100;

        std::uint64_t value{};
    };

    struct gs_base : win::scalar_convertible<gs_base, std::uint64_t> {
        using win::scalar_convertible<gs_base, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC000'0101;

        std::uint64_t value{};
    };

    struct kernel_gs_base : win::scalar_convertible<kernel_gs_base, std::uint64_t> {
        using win::scalar_convertible<kernel_gs_base, std::uint64_t>::scalar_convertible;
        static constexpr std::uint32_t number = 0xC000'0102;

        std::uint64_t value{};
    };
} // namespace arch

#endif // WDK_ARCH_MSRS_HPP
