# sdlste: the Atari STE with SDL 3.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/sdlste --help
#
# The STE itself is esp32ste's (../esp32ste/components/atari_st, platform
# independent), the runtime sdlemu's (../sdlemu), the 68000 (Musashi)
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(sdlste C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32STE_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32ste" CACHE PATH "esp32ste checkout: the STE")
if(NOT EXISTS "${ESP32STE_DIR}/components/atari_st/include/st.h")
    message(FATAL_ERROR "No esp32ste at ${ESP32STE_DIR}: clone github.com/rlucencic/esp32ste beside sdlste")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../sdlemu" sdlemu)

file(GLOB ST_SOURCES CONFIGURE_DEPENDS "${ESP32STE_DIR}/components/atari_st/*.c")
add_executable(sdlste
    src/main.c
    src/settings.c
    src/tos_rom.c
    ${ST_SOURCES})
target_include_directories(sdlste PRIVATE
    src
    "${ESP32STE_DIR}/components/atari_st/include"
    "${ESP32STE_DIR}/components/atari_st")
sdlemu_add_cores(sdlste musashi diskspace)
target_link_libraries(sdlste PRIVATE sdlemu)
target_compile_options(sdlste PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)

install(TARGETS sdlste)
