# FindWDK

CMake module for building drivers with Windows Development Kit (WDK).

- [Introduction](#introduction)
- [Usage](#usage)
    - [Kernel driver](#kernel-driver)
- [License](#license)
- [Version history](#version-history)

# Introduction

FindWDK makes it possible to build kernel drivers with Windows Driver Kit (WDK) and CMake.

Requirements:

- WDK 8.0 and higher.
- CMake 3.0 and higher.

# Usage

Add FindWDK to the module search path and call `find_package`:

```cmake
list(APPEND CMAKE_MODULE_PATH "<path_to_FindWDK>")
find_package(WDK REQUIRED)
```

FindWDK will search for the latest installed Windows Development Kit (WDK) and expose commands for creating kernel
drivers and kernel libraries. Also the following variables will be defined:

- `WDK_FOUND` -- if false, do not try to use WDK
- `WDK_ROOT` -- where WDK is installed
- `WDK_VERSION` -- the version of the selected WDK
- `WDK_WINVER` -- the WINVER used for kernel drivers and libraries (default value is `0x0601` and can be changed per
  target or globally)
- `WDK_NTDDI_VERSION` -- the NTDDI_VERSION used for kernel drivers and libraries, if not set, the value will be
  automatically calculated by WINVER
- `FINDWDK_DIR` -- the directory where FindWDK.cmake is located
- `WDKContentRoot` environment variable overrides the default WDK search path.

## Kernel driver

The following command adds a kernel driver target called `<name>` to be built from the source files listed in the
command invocation:

```cmake
wdk_add_driver(<name>
        [EXCLUDE_FROM_ALL]
        [KMDF <kmdf_version>]
        [WINVER <winver_version>]
        [NTDDI_VERSION <ntddi_version>]
        source1 [source2 ...]
)
```

Options:

- `EXCLUDE_FROM_ALL` -- exclude from the default build target
- `KMDF <kmdf_version>` -- use KMDF and set KMDF version
- `WINVER <winver_version>` -- use specific WINVER version
- `NTDDI_VERSION <ntddi_version>` -- use specific NTDDI_VERSION

Example:

```cmake
wdk_add_driver(KmdfCppDriver
        KMDF 1.15
        WINVER 0x0602
        Main.cpp
)
```

```cmake
target_link_libraries(KmdfCppDriver WDK::HAL)
```

## Linking to WDK libraries

By default, **FindWDK** links only against `WDK::NTOSKRNL`.
However, it also generates imported targets for all available WDK libraries, using the naming convention
`WDK::<UPPERCASED_LIBNAME>`.
For example, linking a minifilter driver with `FltMgr.lib` can be done as shown below:

```cmake
target_link_libraries(MinifilterDriver WDK::FLTMGR)
```

# License

FindWDK is licensed under the OSI-approved 3-clause BSD license. You can freely use it in your commercial or opensource
software.
Additional components added by Hxnter999 are licensed under the MIT License, unless otherwise specified.

# Version history

## Version 2.0.0

- Remove msvc support.
- Add clang/gcc support.
- Remove the ability to include the headers provided by microsoft as they are obviously not compatible with other
  compilers and otherwise require a lot of things to be setup properly
- Add a small header library to provide useful intrinsics and declarations from the wdk.

## ~~Version 1.0.2 (TBD)~~

## ~~Version 1.0.1 (13 Mar 2018)~~

- ~~New: Add ability to link to WDK libraries~~
- ~~New: Add MinifilterDriver sample~~
- ~~Fix: W4 warnings in C version of the driver, add missing /W4 /WX for C compiler~~

## ~~Version 1.0.0 (03 Feb 2018)~~

- ~~Initial public release~~
