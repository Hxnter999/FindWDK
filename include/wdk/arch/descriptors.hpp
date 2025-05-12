#ifndef WDK_ARCH_DESCRIPTORS_HPP
#define WDK_ARCH_DESCRIPTORS_HPP
#include <iterator>

namespace arch {
    template<typename T>
    struct descriptor_table_first {
        std::uint16_t limit;
        T *base;

        static constexpr std::size_t descriptor_size = sizeof(T); // long mode focused

        struct iterator {
            using iterator_category = std::forward_iterator_tag;
            using value_type = T ;
            using difference_type = std::ptrdiff_t;
            using pointer = T *;
            using reference = T &;

            T *current;
            std::size_t index = 0;

            iterator(T *base, std::size_t idx)
                : current(base + idx), index(idx) {
            }

            T *operator*() const {
                return current;
            }

            iterator &operator++() {
                ++index;
                ++current;
                return *this;
            }

            iterator operator++(int) {
                iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const iterator &other) const {
                return current == other.current;
            }
        };

        std::size_t size() const {
            return (limit + 1) / descriptor_size;
        }

        iterator begin() const {
            return iterator(base, 0);
        }

        iterator end() const {
            return iterator(base, size());
        }
    } __attribute__((packed));

    static_assert(sizeof(descriptor_table_first<address>) == 10,
                  "arch::descriptor_table_first size is incorrect");
    //using global_descriptor_table = descriptor_table_first</*segment descriptors*/>
    using global_descriptor_table = descriptor_table_first<address>;
    using interrupt_descriptor_table = descriptor_table_first<struct interrupt_descriptor>;

    struct interrupt_descriptor {
        std::uint16_t offset_low;
        std::uint16_t selector;
        std::uint8_t interrupt_stack_table_index: 3;
        std::uint8_t reserved1: 5;
        std::uint8_t type: 4;
        std::uint8_t must_be_zero: 1;
        std::uint8_t descriptor_privilege_level: 2;
        std::uint16_t offset_mid;
        std::uint32_t offset_high;
        std::uint32_t reserved2: 32;

        address get_handler() const {
            return static_cast<address>(
                (static_cast<std::uint64_t>(offset_high) << 32) |
                (static_cast<std::uint64_t>(offset_mid) << 16) |
                offset_low
            );
        }

        void set_handler(const address handler) {
            const std::uint64_t addr = static_cast<std::uint64_t>(handler);
            offset_low = addr & 0xFFFF;
            offset_mid = (addr >> 16) & 0xFFFF;
            offset_high = (addr >> 32) & 0xFFFFFFFF;
        }
    } __attribute__((packed));

    static_assert(sizeof(interrupt_descriptor) == 16, "arch::interrupt_descriptor size is incorrect");
} // namespace arch

#endif // WDK_ARCH_DESCRIPTORS_HPP
