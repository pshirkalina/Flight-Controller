set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(MCU_FLAGS
    "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard"
)

set(CMAKE_C_FLAGS_INIT
    "${MCU_FLAGS} -ffunction-sections -fdata-sections"
)

set(CMAKE_CXX_FLAGS_INIT
    "${MCU_FLAGS} -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti"
)

set(CMAKE_ASM_FLAGS_INIT
    "${MCU_FLAGS} -x assembler-with-cpp"
)

set(CMAKE_EXE_LINKER_FLAGS_INIT
    "${MCU_FLAGS} -Wl,--gc-sections"
)