#ifndef WDK_WINDOWS_HPP
#define WDK_WINDOWS_HPP
#include "declarations.hpp"

namespace win {
    template <typename ...Ts>
    ALWAYS_INLINE ntstatus dbg_print(const char* fmt, Ts&&... args) {
        return DbgPrint(fmt, std::forward<Ts>(args)...);
    }

    template <typename ...Ts>
    ALWAYS_INLINE ntstatus dbg_printex(const char* fmt, Ts&&... args) { 
        return DbgPrintEx(0, 0, fmt, std::forward<Ts>(args)...);
    }
    
} // namespace win
#endif // WDK_WINDOWS_HPP