#include <wdk/wdk.hpp>

extern "C"
ntstatus DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING) {
    win::print_ex(0, 0, "Processor count: %u\n", win::KeQueryActiveProcessorCount());

    driver_object->DriverUnload = [](PDRIVER_OBJECT) static {
        win::print_ex(0, 0, "DriverUnload\n");
        return ntstatus::success;
    };

    intrin::wrmsr(0xC000'1011, intrin::rdmsr(0xC000'1011));
    //intrin::amd::clgi();
    //intrin::intel::vmread(field);
    intrin::write_cr3(intrin::read_cr3());

    // msr <-> 64 bit integer
    auto efer = intrin::rdmsr<arch::efer>();
    efer = intrin::rdmsr(arch::efer::number);
    intrin::wrmsr(efer);
    intrin::wrmsr(arch::efer::number, static_cast<std::uint64_t>(efer));

    // address <-> 64 bit integer
    // address <-> T* explicitly
    // address <-> void* implicitly
    arch::address entrypoint{nullptr};
    entrypoint = &DriverEntry;
    win::print_ex(0, 0, "Running from: %p\n", entrypoint);

    auto idtr = intrin::sidt();
    for (auto idte: idtr) {
        win::print_ex(0, 0, "%p\n", idte->get_handler());
    }


    return ntstatus::success;
}
