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

        address() = default;

        template<is_address T>
        address(T src) {
            *this = std::bit_cast<address>(src);
        }

        template<is_address T>
        address &operator=(T src) {
            *this = std::bit_cast<address>(src);
            return *this;
        }

        operator void *() const { return std::bit_cast<void *>(*this); }

        template<is_address T>
        explicit operator T() const { return std::bit_cast<T>(*this); }

        explicit operator bool() const { return static_cast<bool>(std::bit_cast<std::uint64_t>(*this)); }

        address operator*() const {
            return *static_cast<void **>(*this);
        }

        address operator+(const std::size_t size) const {
            return static_cast<std::uint64_t>(*this) + size;
        }

        address &operator+=(const std::size_t size) {
            return *this = *this + size;
        }

        address operator-(const std::size_t size) const {
            return static_cast<std::uint64_t>(*this) - size;
        }

        address &operator-=(const std::size_t size) {
            return *this = *this - size;
        }

        bool operator==(const address &other) const = default;

        bool operator!=(const address &other) const = default;

        auto operator<=>(const address &other) const = default;
    };
} // namespace arch


#endif // WDK_ARCH_PAGING_HPP
