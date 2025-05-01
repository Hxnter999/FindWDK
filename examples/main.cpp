#include <wdk/wdk.hpp>

extern "C"
ntstatus DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING) {
    win::print("Processor count: %u\n", win::KeQueryActiveProcessorCount());

    driver_object->DriverUnload = [](PDRIVER_OBJECT) static {
        win::print("DriverUnload\n");
        return ntstatus::success;
    };

    intrin::wrmsr(0xC000'1011, intrin::rdmsr(0xC000'1011));
    intrin::amd::clgi();
    //intrin::intel::...
    intrin::write_cr3(intrin::read_cr3());

    // msr <-> 64 bit integer
    auto efer = arch::load_msr<arch::efer>();
    efer = intrin::rdmsr(arch::efer::number);

    // address <-> 64 bit integer
    // address <-> void*
    // address <-| T*
    arch::address entrypoint{&DriverEntry};

    return ntstatus::success;
}
