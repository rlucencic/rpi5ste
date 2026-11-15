# rpi5ste: the Atari STE on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5ste --help
#
# The STE itself is esp32ste's (../esp32ste/components/atari_st, platform
# independent), the runtime rpi5emu's (../rpi5emu), the 68000 (Musashi)
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5ste C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32STE_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32ste" CACHE PATH "esp32ste checkout: the STE")
if(NOT EXISTS "${ESP32STE_DIR}/components/atari_st/include/st.h")
    message(FATAL_ERROR "No esp32ste at ${ESP32STE_DIR}: clone github.com/rlucencic/esp32ste beside rpi5ste")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

file(GLOB ST_SOURCES "${ESP32STE_DIR}/components/atari_st/*.c")
add_executable(rpi5ste
    src/main.c
    src/settings.c
    src/tos_rom.c
    ${ST_SOURCES})
target_include_directories(rpi5ste PRIVATE
    src
    "${ESP32STE_DIR}/components/atari_st/include"
    "${ESP32STE_DIR}/components/atari_st")
rpi5emu_add_cores(rpi5ste musashi diskspace)
target_link_libraries(rpi5ste PRIVATE rpi5emu)
target_compile_options(rpi5ste PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)

install(TARGETS rpi5ste)
