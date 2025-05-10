#ifndef WDK_ARCH_CONTROL_REGS_HPP
#define WDK_ARCH_CONTROL_REGS_HPP

namespace arch {
    struct cr2 : win::scalar_convertible<cr2, std::uint64_t> {
        using win::scalar_convertible<cr2, std::uint64_t>::scalar_convertible;

        std::uint64_t page_fault_linear_address;
    } __attribute__((packed));

    static_assert(sizeof(cr2) == sizeof(std::uint64_t), "arch::cr2 size is incorrect");

    struct cr3 : win::scalar_convertible<cr3, std::uint64_t> {
        using win::scalar_convertible<cr3, std::uint64_t>::scalar_convertible;

        std::uint64_t reserved1: 3;
        std::uint64_t write_through: 1;
        std::uint64_t cache_disable: 1;
        std::uint64_t reserved2: 7;
        std::uint64_t pml4_frame_number: 40;
        std::uint64_t reserved3: 12;
    } __attribute__((packed));

    static_assert(sizeof(cr3) == sizeof(std::uint64_t), "arch::cr3 size is incorrect");

    struct cr4 : win::scalar_convertible<cr4, std::uint64_t> {
        using win::scalar_convertible<cr4, std::uint64_t>::scalar_convertible;

        std::uint64_t virtual_8086_mode: 1;
        std::uint64_t protected_mode_virtual_interrupts: 1;
        std::uint64_t time_stamp_disable: 1;
        std::uint64_t debugging_extensions: 1;
        std::uint64_t page_size_extensions: 1;
        std::uint64_t physical_address_extensions: 1;
        std::uint64_t machine_check: 1;
        std::uint64_t page_global: 1;
        std::uint64_t performance_monitoring_counter: 1;
        std::uint64_t os_fxsave_fxrstor: 1;
        std::uint64_t os_unmasked_exception: 1;
        std::uint64_t usermode_instruction_prevention: 1;
        std::uint64_t linear_address_57bits: 1;
        std::uint64_t reserved1: 3;
        std::uint64_t fs_gs_base: 1;
        std::uint64_t process_context_identifier: 1;
        std::uint64_t xsave_extended_state: 1;
        std::uint64_t reserved2: 1;
        std::uint64_t supervisor_execution_prevention: 1;
        std::uint64_t supervisor_access_prevention: 1;
        std::uint64_t protection_key: 1;
        std::uint64_t control_flow_enforcement: 1;
        std::uint64_t reserved3: 40;
    } __attribute__((packed));

    static_assert(sizeof(cr4) == sizeof(std::uint64_t), "arch::cr4 size is incorrect");

    struct cr8 : win::scalar_convertible<cr8, std::uint64_t> {
        using win::scalar_convertible<cr8, std::uint64_t>::scalar_convertible;

        std::uint64_t task_priority: 4;
        std::uint64_t reserved: 60;
    } __attribute__((packed));

    static_assert(sizeof(cr8) == sizeof(std::uint64_t), "arch::cr8 size is incorrect");
} // namespace arch

#endif // WDK_ARCH_CONTROL_REGS_HPP
