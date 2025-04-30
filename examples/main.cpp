#include <wdk/wdk.hpp>

extern "C"
ntstatus DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING) {
    win::dbg_print("Processor count: %u\n", win::KeQueryActiveProcessorCount());

    driver_object->DriverUnload = [](PDRIVER_OBJECT) static {
        win::dbg_print("DriverUnload\n");
        return ntstatus::success;
    };

    intrin::wrmsr(0xC000'1011, intrin::rdmsr(0xC000'1011));
    intrin::halt();
    intrin::amd::clgi();
    //intrin::intel::...

    return ntstatus::success;
}
