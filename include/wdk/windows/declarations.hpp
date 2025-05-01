// windows function declarations
#ifndef WDK_WINDOWS_DECLARATIONS_HPP
#define WDK_WINDOWS_DECLARATIONS_HPP
#include "types.hpp"

namespace win {
    BEGIN_EXTERN_C
    ntstatus DbgPrint(const char *fmt, ...);

    ntstatus DbgPrintEx(std::uint32_t component_id, std::uint32_t level, const char *fmt, ...);

    std::uint32_t KeQueryActiveProcessorCount(std::uint64_t *active_processors_affinity = nullptr);

    void *ExAllocatePoolWithTag(std::uint32_t type, std::size_t size, std::uint32_t tag);

    void ExFreePool(void *pool_address);

    std::uint64_t KeSetSystemAffinityThreadEx(std::uint64_t affinity);

    void KeRevertToUserAffinityThreadEx(std::uint64_t affinity);

    std::uint64_t MmGetPhysicalAddress(std::uint64_t virtual_address);

    std::uint64_t MmGetVirtualForPhysical(std::uint64_t physical_address);

    unsigned char MmIsAddressValid(void* virtual_address);


    END_EXTERN_C
} // namespace win
#endif // WDK_WINDOWS_DECLARATIONS_HPP
