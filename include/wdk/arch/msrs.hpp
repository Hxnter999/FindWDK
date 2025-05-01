#ifndef WDK_ARCH_MSRS_HPP
#define WDK_ARCH_MSRS_HPP

namespace arch {
    template<typename T>
    T load_msr() {
        return intrin::rdmsr(T::number);
    }

    struct efer : win::aliasable_bitfield<efer, std::uint64_t> {
        using win::aliasable_bitfield<efer, std::uint64_t>::aliasable_bitfield;
        static constexpr std::uint32_t number = 0xC000'0080;

        std::uint64_t syscall_extensions: 1;
        std::uint64_t : 7;
        std::uint64_t long_mode: 1;
        std::uint64_t : 1;
        std::uint64_t long_mode_active: 1;
        std::uint64_t no_execute: 1;
        std::uint64_t svm: 1;
        std::uint64_t long_mode_segment_limit: 1;
        std::uint64_t fast_fxsave_fxrstor: 1;
        std::uint64_t translation_cache_extension: 1;
        std::uint64_t execute_only_pte: 1; // this is xotext, allows any given pte to be marked as execute only
        std::uint64_t mcommit: 1;
        std::uint64_t interruptible_wbinvd_wbnoinvd: 1;
        std::uint64_t : 1;
        std::uint64_t upper_address_ignore: 1;
        std::uint64_t auto_ibrs: 1;
        std::uint64_t : 42;
    };

    // virtual machine host save physical address as per the manual
    struct vmhs_pa : win::aliasable_bitfield<vmhs_pa, std::uint64_t> {
        using win::aliasable_bitfield<vmhs_pa, std::uint64_t>::aliasable_bitfield;
        static constexpr uint32_t number = 0xC001'0117;

        std::uint64_t value{};
    };
} // namespace arch

#endif // WDK_ARCH_MSRS_HPP
