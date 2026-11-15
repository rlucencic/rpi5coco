# rpi5coco: the Tandy Color Computer 2 and 3 on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5coco --help
#
# The CoCo itself is esp32coco's (../esp32coco/components/coco, platform
# independent), the runtime rpi5emu's (../rpi5emu), the 6809/6309
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5coco C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32COCO_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32coco" CACHE PATH "esp32coco checkout: the CoCo")
if(NOT EXISTS "${ESP32COCO_DIR}/components/coco/include/coco.h")
    message(FATAL_ERROR "No esp32coco at ${ESP32COCO_DIR}: clone github.com/rlucencic/esp32coco beside rpi5coco")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

# The core and its parts' folders (cpu, gime, vdg, ...), not its host build
file(GLOB COCO_SOURCES "${ESP32COCO_DIR}/components/coco/*.c" "${ESP32COCO_DIR}/components/coco/*/*.c")
list(FILTER COCO_SOURCES EXCLUDE REGEX "/host/")
add_executable(rpi5coco
    src/main.c
    src/settings.c
    src/rom_store.c
    ${COCO_SOURCES})
target_include_directories(rpi5coco PRIVATE
    src
    "${ESP32COCO_DIR}/components/coco/include"
    "${ESP32COCO_DIR}/components/coco")
rpi5emu_add_cores(rpi5coco m6809 diskspace)
target_link_libraries(rpi5coco PRIVATE rpi5emu)
target_compile_options(rpi5coco PRIVATE -Wall -Wextra -Wno-unused-parameter)

install(TARGETS rpi5coco)
