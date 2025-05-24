cmake_minimum_required(VERSION 3.22)
project(example_driver LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../") # examples/../
find_package(WDK REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

wdk_add_driver(example_driver KMDF 1.15
        main.cpp
)

# target_link_libraries(KmdfCppDriver WDK::HAL) // this is how you link against other wdk libraries
target_compile_options(example_driver PRIVATE
        -O3
)
