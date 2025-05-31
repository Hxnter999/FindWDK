# FindWDK

CMake module for building drivers with Windows Development Kit (WDK).

---

## Introduction

FindWDK allows building Windows kernel drivers using the WDK and CMake.

**Requirements:**

* WDK 8.0 or higher
* CMake 3.0 or higher
* Ninja build system (recommended)

---

## Usage

Add the path to `FindWDK.cmake` to your `CMAKE_MODULE_PATH`, then:

```cmake
# Specify the path to the WDK libraries if neccessary. 
set(WDK_LIB_PATH "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/km/x64")

list(APPEND CMAKE_MODULE_PATH "<path_to_FindWDK>")
find_package(WDK REQUIRED)
```

**How FindWDK locates libraries:**

* If `WDK_LIB_PATH` is defined, it searches `${WDK_LIB_PATH}/*.lib`.
* Otherwise, it tries environment variable `WDKContentRoot` and common install locations on C: and D:.

If no `.lib` files are found, configuration fails with an error.

---

## Header Library

This project includes a lightweight header library designed to provide essential types, macros, and compiler intrinsics commonly needed for kernel development. It serves as a minimal alternative to Microsoft's official headers, ensuring compatibility with Clang and GCC.

---

## Adding a kernel driver target

Use the function:

```cmake
wdk_add_driver(<target_name> source1 [source2 ...])
```

This creates an executable with `.sys` as an extension, sets compiler and linker flags, links against `WDK::NTOSKRNL` by default, and includes a header library shipped with this project.

Example:

```cmake
wdk_add_driver(${PROJECT_NAME} Main.cpp)
```

---

## Linking additional WDK libraries

FindWDK automatically creates imported targets for all WDK `.lib` files found, named `WDK::<LIBNAME_UPPER>`.

To link additional libraries:

```cmake
target_link_libraries(${PROJECT_NAME} WDK::FLTMGR)
```

---

Let me know if you need further modifications or additional information!


## License

Licensed under the OSI-approved 3-clause BSD license. Additional components are under the MIT License.

---