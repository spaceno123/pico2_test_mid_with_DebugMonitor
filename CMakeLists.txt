# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico2_text_midi_with_DebugMonitor C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pico2_text_midi_with_DebugMonitor)

target_sources(pico2_text_midi_with_DebugMonitor PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/src/DebugMonitor.c
        ${CMAKE_CURRENT_LIST_DIR}/src/DebugMonitorStdio.c
        ${CMAKE_CURRENT_LIST_DIR}/src/DebugMonitorUsbMidi.c
        ${CMAKE_CURRENT_LIST_DIR}/src/usbmidi.c
        ${CMAKE_CURRENT_LIST_DIR}/src/mididecode.c
        )

# Make sure TinyUSB can find tusb_config.h
target_include_directories(pico2_text_midi_with_DebugMonitor PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

pico_set_program_name(pico2_text_midi_with_DebugMonitor "pico2_text_midi_with_DebugMonitor")
pico_set_program_version(pico2_text_midi_with_DebugMonitor "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico2_text_midi_with_DebugMonitor 1)
pico_enable_stdio_usb(pico2_text_midi_with_DebugMonitor 0)

# Add the standard library to the build
target_link_libraries(pico2_text_midi_with_DebugMonitor
        PUBLIC pico_stdlib pico_unique_id tinyusb_device tinyusb_board)

# Add the standard include files to the build
target_include_directories(pico2_text_midi_with_DebugMonitor PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(pico2_text_midi_with_DebugMonitor)

