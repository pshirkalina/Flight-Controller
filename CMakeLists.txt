cmake_minimum_required(VERSION 3.25)

project(FlightController
    LANGUAGES C CXX ASM
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(cmake/stm32cubemx)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    SUFFIX ".elf"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex
        $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
        ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex

    COMMAND arm-none-eabi-objcopy -O binary
        $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
        ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
)

add_custom_target(flash
    COMMAND STM32_Programmer_CLI
        -c port=SWD
        -w $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
        -v
        -rst
    DEPENDS ${CMAKE_PROJECT_NAME}
    USES_TERMINAL
)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -T${CMAKE_SOURCE_DIR}/STM32H743XG_FLASH.ld
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--gc-sections
    -Wl,--print-memory-usage
)