// windows function declarations
#ifndef WDK_WINDOWS_DECLARATIONS_HPP
#define WDK_WINDOWS_DECLARATIONS_HPP
#include "types.hpp"


namespace win {
    extern "C" {
    ntstatus DbgPrint(const char *fmt, ...);

    ntstatus DbgPrintEx(std::uint32_t component_id, std::uint32_t level, const char *fmt, ...);

    std::uint32_t KeQueryActiveProcessorCount(std::uint64_t *active_processors_affinity = nullptr);

    std::uint64_t KeSetSystemAffinityThreadEx(std::uint64_t affinity);

    void KeRevertToUserAffinityThreadEx(std::uint64_t affinity);

    arch::address ExAllocatePoolWithTag(std::uint32_t type, std::size_t size, std::uint32_t tag);

    void ExFreePool(arch::address pool_address);

    arch::address MmGetPhysicalAddress(arch::address virtual_address);

    arch::address MmGetVirtualForPhysical(arch::address physical_address);

    bool MmIsAddressValid(arch::address virtual_address);
    } // extern "C"
} // namespace win
#endif // WDK_WINDOWS_DECLARATIONS_HPP
