#include "bsp_spi.h"
#include "stm32h7xx_hal.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi4;

typedef struct {
    SPI_HandleTypeDef *handle;
    uint32_t timeout_ms;
    bsp_status_t current_status;
} spi_bus_record_t;

static spi_bus_record_t record[BSP_SPI_COUNT] = {
    [BSP_SPI_SENSOR_BUS_1] = {
        .handle = &hspi1,
        .timeout_ms = 10,
        .current_status = BSP_UNINITIALIZED
    },

    [BSP_SPI_SENSOR_BUS_2] = {
        .handle = &hspi2,
        .timeout_ms = 10,
        .current_status = BSP_UNINITIALIZED
    },

    [BSP_SPI_STORAGE_BUS] = {
        .handle = &hspi4,
        .timeout_ms = 100,
        .current_status = BSP_UNINITIALIZED
    }
};

bsp_status_t bsp_spi_init(void) {

    bsp_status_t overall_status = BSP_OK;

    for (int i = 0; i < BSP_SPI_COUNT; i++) {

        if (record[i].handle == NULL) {
            record[i].current_status = BSP_ERROR;
            overall_status = BSP_ERROR;
        }
        else{
            HAL_SPI_StateTypeDef hal_state = HAL_SPI_GetState(record[i].handle);

            if (hal_state == HAL_SPI_STATE_READY) {
                record[i].current_status = BSP_OK;
            }
            else if (hal_state == HAL_SPI_STATE_BUSY || hal_state == HAL_SPI_STATE_BUSY_TX || hal_state == HAL_SPI_STATE_BUSY_RX || hal_state == HAL_SPI_STATE_BUSY_TX_RX) {
                record[i].current_status = BSP_BUSY;
                overall_status = BSP_ERROR;
            }
            else {
                record[i].current_status = BSP_ERROR;
                overall_status = BSP_ERROR;
            }
        }
    }

    return overall_status;
    
}

bsp_status_t bsp_spi_get_status(bsp_spi_bus_t bus) {
    if (bus >= BSP_SPI_COUNT) {
        return BSP_INVALID_ARG;
    }

    return record[bus].current_status;
}

bsp_status_t bsp_spi_transmit(bsp_spi_bus_t bus, const uint8_t* buffer, size_t length) {
    if (bus >= BSP_SPI_COUNT || buffer == NULL || length == 0 || length > UINT16_MAX) {
        return BSP_INVALID_ARG;
    }

    if (record[bus].current_status == BSP_BUSY) {
        return BSP_BUSY;
    }

    if (record[bus].current_status == BSP_UNINITIALIZED) {
        return BSP_UNINITIALIZED;
    }

    HAL_StatusTypeDef hal_state = HAL_SPI_Transmit(record[bus].handle, buffer, length, record[bus].timeout_ms);

    if (hal_state == HAL_TIMEOUT){
        record[bus].current_status = BSP_TIMEOUT;
        return BSP_TIMEOUT;
    }

    if (hal_state == HAL_BUSY){
        record[bus].current_status = BSP_BUSY;
        return BSP_BUSY;
    }

    if (hal_state == HAL_ERROR){
        record[bus].current_status = BSP_ERROR;
        return BSP_ERROR;
    }

    if (hal_state == HAL_OK){
        record[bus].current_status = BSP_OK;
        return BSP_OK;
    }

    record[bus].current_status = BSP_ERROR;
    return BSP_ERROR;
}

bsp_status_t bsp_spi_receive(bsp_spi_bus_t bus, uint8_t* buffer, size_t length) {
    if (bus >= BSP_SPI_COUNT || buffer == NULL || length == 0 || length > UINT16_MAX) {
        return BSP_INVALID_ARG;
    }

    if (record[bus].current_status == BSP_BUSY) {
        return BSP_BUSY;
    }

    if (record[bus].current_status == BSP_UNINITIALIZED) {
        return BSP_UNINITIALIZED;
    }

    HAL_StatusTypeDef hal_state = HAL_SPI_Receive(record[bus].handle, buffer, length, record[bus].timeout_ms);

    if (hal_state == HAL_TIMEOUT){
        record[bus].current_status = BSP_TIMEOUT;
        return BSP_TIMEOUT;
    }

    if (hal_state == HAL_BUSY){
        record[bus].current_status = BSP_BUSY;
        return BSP_BUSY;
    }

    if (hal_state == HAL_ERROR){
        record[bus].current_status = BSP_ERROR;
        return BSP_ERROR;
    }

    if (hal_state == HAL_OK){
        record[bus].current_status = BSP_OK;
        return BSP_OK;
    }

    record[bus].current_status = BSP_ERROR;
    return BSP_ERROR;
}

bsp_status_t bsp_spi_transmit_receive(bsp_spi_bus_t bus, const uint8_t* tx_buffer, uint8_t* rx_buffer, size_t length) {
    if (bus >= BSP_SPI_COUNT || tx_buffer == NULL || rx_buffer == NULL || length == 0 || length > UINT16_MAX) {
        return BSP_INVALID_ARG;
    }

    if (record[bus].current_status == BSP_BUSY) {
        return BSP_BUSY;
    }

    if (record[bus].current_status == BSP_UNINITIALIZED) {
        return BSP_UNINITIALIZED;
    }

    HAL_StatusTypeDef hal_state = HAL_SPI_TransmitReceive(record[bus].handle, tx_buffer, rx_buffer, length, record[bus].timeout_ms);

    if (hal_state == HAL_TIMEOUT){
        record[bus].current_status = BSP_TIMEOUT;
        return BSP_TIMEOUT;
    }

    if (hal_state == HAL_BUSY){
        record[bus].current_status = BSP_BUSY;
        return BSP_BUSY;
    }

    if (hal_state == HAL_ERROR){
        record[bus].current_status = BSP_ERROR;
        return BSP_ERROR;
    }

    if (hal_state == HAL_OK){
        record[bus].current_status = BSP_OK;
        return BSP_OK;
    }

    record[bus].current_status = BSP_ERROR;
    return BSP_ERROR;
}
