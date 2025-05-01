#ifndef WDK_ARCH_PAGING_HPP
#define WDK_ARCH_PAGING_HPP

namespace arch {
    template<typename T>
    concept is_address = std::is_pointer_v<T> || (std::is_integral_v<T> && sizeof(T) == 8);

    struct address : win::aliasable_bitfield<address, std::uint64_t>,
                     win::aliasable_bitfield<address, void *> {
        using win::aliasable_bitfield<address, std::uint64_t>::aliasable_bitfield;
        using win::aliasable_bitfield<address, void *>::aliasable_bitfield;

        std::uint64_t offset: 12;
        std::uint64_t p1_index: 9;
        std::uint64_t p2_index: 9;
        std::uint64_t p3_index: 9;
        std::uint64_t p4_index: 9;
        std::uint64_t sign: 16;
    };
} // namespace arch


#endif // WDK_ARCH_PAGING_HPP
