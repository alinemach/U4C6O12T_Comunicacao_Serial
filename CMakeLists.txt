# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================




cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(U4C6O12T_Comunicacao_Serial C CXX ASM)
pico_sdk_init()
add_executable(U4C6O12T_Comunicacao_Serial U4C6O12T_Comunicacao_Serial.c inc/ssd1306.c)
# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(U4C6O12T_Comunicacao_Serial 1)
pico_enable_stdio_usb(U4C6O12T_Comunicacao_Serial 1)

# Adicionar os diretórios de include
include_directories(inc)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)
pico_generate_pio_header(U4C6O12T_Comunicacao_Serial ${CMAKE_CURRENT_LIST_DIR}/U4C6O12T_Comunicacao_Serial.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)
target_sources(U4C6O12T_Comunicacao_Serial PRIVATE U4C6O12T_Comunicacao_Serial.c)
target_link_libraries(U4C6O12T_Comunicacao_Serial PRIVATE pico_stdlib hardware_pio hardware_uart hardware_i2c hardware_pwm)
pico_add_extra_outputs(U4C6O12T_Comunicacao_Serial) 