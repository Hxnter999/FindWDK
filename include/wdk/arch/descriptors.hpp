#ifndef WDK_ARCH_DESCRIPTORS_HPP
#define WDK_ARCH_DESCRIPTORS_HPP
#include <iterator>

#include "segments.hpp"

namespace arch {
    struct descriptor_table_first {
        std::uint16_t limit;
        address base;

        static constexpr std::size_t descriptor_size = 16; // long mode focused, sizeof(arch::descriptor)

        struct iterator {
            using iterator_category = std::forward_iterator_tag;
            using value_type = address;
            using difference_type = std::ptrdiff_t;
            using pointer = address *;
            using reference = address &;

            address current;
            std::size_t index = 0;

            iterator(const address base, const std::size_t idx) : current(base + idx * descriptor_size), index(idx) {
            }

            address operator*() const {
                return current;
            }

            iterator &operator++() {
                index++;
                current += descriptor_size;
                return *this;
            }

            iterator operator++(int) {
                const iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const iterator &other) const {
                return index == other.index;
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

    static_assert(sizeof(descriptor_table_first) == (sizeof(address) + sizeof(std::uint16_t)),
                  "arch::descriptor_table_first size is incorrect");
    using global_descriptor_table = descriptor_table_first;
    using interrupt_descriptor_table = descriptor_table_first;

} // namespace arch

#endif // WDK_ARCH_DESCRIPTORS_HPP
