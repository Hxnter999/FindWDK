#ifndef WDK_WINDOWS_DECLARATIONS_HPP
#define WDK_WINDOWS_DECLARATIONS_HPP
#include "types.hpp"

namespace win { 
    BEGIN_EXTERN_C
    
    ntstatus DbgPrint(const char* fmt, ...);
    ntstatus DbgPrintEx(std::uint32_t component_id, std::uint32_t level, const char* fmt, ...);
    std::uint32_t KeQueryActiveProcessorCount(std::uint64_t* ActiveProcessors = nullptr);
    END_EXTERN_C 
} // namespace win
#endif // WDK_WINDOWS_DECLARATIONS_HPP