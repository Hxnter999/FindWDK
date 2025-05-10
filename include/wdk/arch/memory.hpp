#ifndef WDK_ARCH_PAGING_HPP
#define WDK_ARCH_PAGING_HPP

namespace arch {
    template<typename T>
    concept is_address =
            std::is_trivially_copyable_v<T> &&
            sizeof(T) == sizeof(uint64_t) && (std::is_pointer_v<T> || std::is_integral_v<T> || std::is_convertible_v<T,
                                                  void *>);

    struct address {
        std::uint64_t offset: 12;
        std::uint64_t p1_index: 9;
        std::uint64_t p2_index: 9;
        std::uint64_t p3_index: 9;
        std::uint64_t p4_index: 9;
        std::uint64_t sign: 16;

        constexpr address() = default;

        template<is_address T>
        constexpr address(T src) {
            *this = std::bit_cast<address>(src);
        }

        template<is_address T>
        constexpr address &operator=(T src) {
            *this = std::bit_cast<address>(src);
            return *this;
        }

        constexpr operator void *() const { return std::bit_cast<void *>(*this); }

        template<is_address T>
        explicit constexpr operator T() const { return std::bit_cast<T>(*this); }

        explicit constexpr operator bool() const { return static_cast<bool>(std::bit_cast<std::uint64_t>(*this)); }

        constexpr address operator*() const {
            return *static_cast<void **>(*this);
        }

        constexpr address operator+(const std::size_t size) const {
            return static_cast<std::uint64_t>(*this) + size;
        }

        constexpr address &operator+=(const std::size_t size) {
            return *this = *this + size;
        }

        constexpr address &operator++() {
            *this += 1;
            return *this;
        }

        constexpr address operator++(int) {
            const address temp = *this;
            ++(*this);
            return temp;
        }

        constexpr address operator-(const std::size_t size) const {
            return static_cast<std::uint64_t>(*this) - size;
        }

        constexpr address &operator-=(const std::size_t size) {
            return *this = *this - size;
        }

        constexpr address &operator--() {
            *this -= 1;
            return *this;
        }

        constexpr address operator--(int) {
            const address temp = *this;
            --(*this);
            return temp;
        }

        constexpr bool operator==(const address &other) const = default;

        constexpr bool operator!=(const address &other) const = default;

        constexpr auto operator<=>(const address &other) const = default;

        constexpr address operator<<(const std::size_t shift) const {
            return static_cast<std::uint64_t>(*this) << shift;
        }

        constexpr address &operator<<=(const std::size_t shift) {
            return *this = *this << shift;
        }

        constexpr address operator>>(const std::size_t shift) const {
            return static_cast<std::uint64_t>(*this) >> shift;
        }

        constexpr address &operator>>=(const std::size_t shift) {
            return *this = *this >> shift;
        }
    } __attribute__((packed));

    static_assert(sizeof(address) == sizeof(std::uint64_t), "arch::address size is incorrect");

    struct page_entry_4kb : win::scalar_convertible<page_entry_4kb, std::uint64_t> {
        using win::scalar_convertible<page_entry_4kb, std::uint64_t>::scalar_convertible;

        std::uint64_t present: 1;
        std::uint64_t write: 1;
        std::uint64_t user: 1;
        std::uint64_t write_through: 1;
        std::uint64_t cache_disable: 1;
        std::uint64_t accessed: 1;
        std::uint64_t dirty: 1;
        std::uint64_t page_attribute_table: 1;
        std::uint64_t global: 1;
        std::uint64_t ignored1: 3;
        std::uint64_t page_frame_number: 40;
        std::uint64_t ignored2: 7;
        std::uint64_t memory_protection_key: 4;
        std::uint64_t execute_disable: 1;
    } __attribute__((packed));

    static_assert(sizeof(page_entry_4kb) == sizeof(std::uint64_t), "arch::page_entry_4kb size is incorrect");

    struct page_entry_2mb : win::scalar_convertible<page_entry_2mb, std::uint64_t> {
        using win::scalar_convertible<page_entry_2mb, std::uint64_t>::scalar_convertible;

        std::uint64_t present: 1;
        std::uint64_t write: 1;
        std::uint64_t user: 1;
        std::uint64_t write_through: 1;
        std::uint64_t cache_disable: 1;
        std::uint64_t accessed: 1;
        std::uint64_t dirty: 1;
        std::uint64_t page_size: 1; // enabled for non 4kb entries
        std::uint64_t global: 1;
        std::uint64_t ignored1: 3;
        std::uint64_t page_attribute_table: 1;
        std::uint64_t must_be_zero: 8;
        std::uint64_t page_frame_number: 31;
        std::uint64_t ignored2: 7;
        std::uint64_t memory_protection_key: 4;
        std::uint64_t execute_disable: 1;
    } __attribute__((packed));

    static_assert(sizeof(page_entry_2mb) == sizeof(std::uint64_t), "arch::page_entry_2mb size is incorrect");

    struct page_entry_1gb : win::scalar_convertible<page_entry_1gb, std::uint64_t> {
        using win::scalar_convertible<page_entry_1gb, std::uint64_t>::scalar_convertible;

        std::uint64_t present: 1;
        std::uint64_t write: 1;
        std::uint64_t user: 1;
        std::uint64_t write_through: 1;
        std::uint64_t cache_disable: 1;
        std::uint64_t accessed: 1;
        std::uint64_t dirty: 1;
        std::uint64_t page_size: 1; // enabled for non 4kb entries
        std::uint64_t global: 1;
        std::uint64_t ignored1: 3;
        std::uint64_t page_attribute_table: 1;
        std::uint64_t must_be_zero: 17;
        std::uint64_t page_frame_number: 22;
        std::uint64_t ignored2: 7;
        std::uint64_t memory_protection_key: 4;
        std::uint64_t execute_disable: 1;
    } __attribute__((packed));

    static_assert(sizeof(page_entry_1gb) == sizeof(std::uint64_t), "arch::page_entry_1gb size is incorrect");

    using pml4e = page_entry_4kb;
    using pdpte = page_entry_4kb;
    using pde = page_entry_4kb;
    using pte = page_entry_4kb;

    using pdpte_1gb = page_entry_1gb;
    using pde_2mb = page_entry_2mb;
} // namespace arch

#endif // WDK_ARCH_PAGING_HPP
