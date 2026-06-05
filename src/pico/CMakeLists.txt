cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(controller C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico)

pico_sdk_init()

add_executable(controller
    controller.c
)

target_link_libraries(controller
    pico_stdlib
)

pico_enable_stdio_usb(controller 1)
pico_enable_stdio_uart(controller 0)

pico_add_extra_outputs(controller)
