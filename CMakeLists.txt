# sdlcoco: the Tandy Color Computer 2 and 3 with SDL 3.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/sdlcoco --help
#
# The CoCo itself is esp32coco's (../esp32coco/components/coco, platform
# independent), the runtime sdlemu's (../sdlemu), the 6809/6309
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(sdlcoco C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32COCO_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32coco" CACHE PATH "esp32coco checkout: the CoCo")
if(NOT EXISTS "${ESP32COCO_DIR}/components/coco/include/coco.h")
    message(FATAL_ERROR "No esp32coco at ${ESP32COCO_DIR}: clone github.com/rlucencic/esp32coco beside sdlcoco")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../sdlemu" sdlemu)

# The core and its parts' folders (cpu, gime, vdg, ...), not its host build
file(GLOB COCO_SOURCES "${ESP32COCO_DIR}/components/coco/*.c" "${ESP32COCO_DIR}/components/coco/*/*.c")
list(FILTER COCO_SOURCES EXCLUDE REGEX "/host/")
add_executable(sdlcoco
    src/main.c
    src/settings.c
    src/rom_store.c
    ${COCO_SOURCES})
target_include_directories(sdlcoco PRIVATE
    src
    "${ESP32COCO_DIR}/components/coco/include"
    "${ESP32COCO_DIR}/components/coco")
sdlemu_add_cores(sdlcoco m6809 diskspace)
target_link_libraries(sdlcoco PRIVATE sdlemu)
target_compile_options(sdlcoco PRIVATE -Wall -Wextra -Wno-unused-parameter)

install(TARGETS sdlcoco)
