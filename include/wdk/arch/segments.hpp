#ifndef WDK_ARCH_SEGMENTS_HPP
#define WDK_ARCH_SEGMENTS_HPP

namespace arch {
    enum class table_indicator : bool {
        global,
        local
    };

    struct segment_selector : win::scalar_convertible<segment_selector, std::uint16_t> {
        using win::scalar_convertible<segment_selector, std::uint16_t>::scalar_convertible;

        std::uint16_t requestor_privilege_level: 2;
        table_indicator table: 1;
        std::uint16_t index: 13;
    } __attribute__((packed));

    struct segment_attributes : win::scalar_convertible<segment_selector, std::uint16_t> {
        using win::scalar_convertible<segment_selector, std::uint16_t>::scalar_convertible;

        // TODO: implement attributes bitfield
        std::uint16_t value;
    };
}

#endif //WDK_ARCH_SEGMENTS_HPP
