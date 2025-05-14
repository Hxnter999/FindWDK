#ifndef WDK_ARCH_PAGING_HPP
#define WDK_ARCH_PAGING_HPP

namespace arch {
    template<typename T>
    concept is_address =
            std::is_trivially_copyable_v<T> &&
            (std::is_pointer_v<T> || std::is_integral_v<T> || std::is_convertible_v<T, void *> || sizeof(T) == sizeof(
                 std::uint64_t));

    struct address {
        std::uint64_t offset: 12;
        std::uint64_t p1_index: 9;
        std::uint64_t p2_index: 9;
        std::uint64_t p3_index: 9;
        std::uint64_t p4_index: 9;
        std::uint64_t sign: 16;

        constexpr address() = default;

        constexpr address(const is_address auto &src) {
            if constexpr (sizeof(src) < sizeof(address) && std::is_integral_v<decltype(src)>) {
                *this = std::bit_cast<address>(static_cast<std::uint64_t>(src));
            } else {
                *this = std::bit_cast<address>(src);
            }
        }

        constexpr address &operator=(const is_address auto &src) {
            if constexpr (sizeof(src) < sizeof(address) && std::is_integral_v<decltype(src)>) {
                *this = std::bit_cast<address>(static_cast<std::uint64_t>(src));
            } else {
                *this = std::bit_cast<address>(src);
            }
            return *this;
        }

        constexpr operator void *() const { return std::bit_cast<void *>(*this); }
        constexpr operator std::uintptr_t() const { return std::bit_cast<std::uintptr_t>(*this); }

        template<is_address T>
        explicit constexpr operator T() const { return std::bit_cast<T>(*this); }

        explicit constexpr operator bool() const { return static_cast<bool>(std::bit_cast<std::uint64_t>(*this)); }

        constexpr address operator*() const {
            return *static_cast<void **>(*this);
        }


        friend constexpr address operator+(const address &lhs, const address &rhs) {
            return static_cast<std::uint64_t>(lhs) + static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator+(const address &lhs, const is_address auto &rhs) {
            return static_cast<std::uint64_t>(lhs) + static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator+(const is_address auto &lhs, const address &rhs) {
            return static_cast<std::uint64_t>(lhs) + static_cast<std::uint64_t>(rhs);
        }


        friend constexpr address operator-(const address &lhs, const address &rhs) {
            return static_cast<std::uint64_t>(lhs) - static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator-(const address &lhs, const is_address auto &rhs) {
            return static_cast<std::uint64_t>(lhs) - static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator-(const is_address auto &lhs, const address &rhs) {
            return static_cast<std::uint64_t>(lhs) - static_cast<std::uint64_t>(rhs);
        }


        friend constexpr address operator<<(const address &lhs, const address &rhs) {
            return static_cast<std::uint64_t>(lhs) << static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator<<(const address &lhs, const is_address auto &rhs) {
            return static_cast<std::uint64_t>(lhs) << static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator<<(const is_address auto &lhs, const address &rhs) {
            return static_cast<std::uint64_t>(lhs) << static_cast<std::uint64_t>(rhs);
        }


        friend constexpr address operator>>(const address &lhs, const address &rhs) {
            return static_cast<std::uint64_t>(lhs) >> static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator>>(const address &lhs, const is_address auto &rhs) {
            return static_cast<std::uint64_t>(lhs) >> static_cast<std::uint64_t>(rhs);
        }

        friend constexpr address operator>>(const is_address auto &lhs, const address &rhs) {
            return static_cast<std::uint64_t>(lhs) >> static_cast<std::uint64_t>(rhs);
        }


        constexpr address &operator+=(const address &delta) {
            return *this = *this + delta;
        }

        constexpr address &operator+=(const is_address auto &delta) {
            return *this = *this + delta;
        }

        constexpr address &operator-=(const address &delta) {
            return *this = *this - delta;
        }

        constexpr address &operator-=(const is_address auto &delta) {
            return *this = *this - delta;
        }

        constexpr address &operator<<=(const address &shift) {
            return *this = *this << shift;
        }

        constexpr address &operator<<=(const is_address auto &shift) {
            return *this = *this << shift;
        }

        constexpr address &operator>>=(const address &shift) {
            return *this = *this >> shift;
        }

        constexpr address &operator>>=(const is_address auto &shift) {
            return *this = *this >> shift;
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

        constexpr bool operator==(const is_address auto &other) const {
            return *this == static_cast<address>(other);
        }

        constexpr bool operator!=(const address &other) const = default;

        constexpr bool operator!=(const is_address auto &other) const {
            return *this != static_cast<address>(other);
        }

        constexpr auto operator<=>(const address &other) const = default;

        constexpr auto operator<=>(const is_address auto &other) const {
            return *this <=> static_cast<address>(other);
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
