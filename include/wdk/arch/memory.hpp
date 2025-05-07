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
    } __attribute__((packed));

    static_assert(sizeof(address) == sizeof(std::uint64_t), "arch::address size is incorrect");
} // namespace arch

#endif // WDK_ARCH_PAGING_HPP
