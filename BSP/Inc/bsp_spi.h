#pragma once

#include <stdint.h>
#include <stddef.h>
#include "bsp.h"

typedef enum {
    BSP_SPI_SENSOR_BUS_1 = 0,
    BSP_SPI_SENSOR_BUS_2,
    BSP_SPI_STORAGE_BUS,
    BSP_SPI_COUNT
} bsp_spi_bus_t;

/**
 * @brief Initializes all configured SPI buses and records their status.
 * 
 * @return BSP status indicating whether initialization completed successfully.
 */
bsp_status_t bsp_spi_init(void);

/** 
 * @brief Returns the current status of the selected SPI bus.
 * @param bus SPI bus whose status should be checked. 
 * @return BSP status of the selected SPI bus.
 */ 
bsp_status_t bsp_spi_get_status(bsp_spi_bus_t bus);

/**
 * @brief Transmits a sequence of bytes over the selected SPI bus.
 * @param bus SPI bus to use. 
 * @param buffer Pointer to the transmit data buffer. 
 * @param length Number of bytes to transmit.
 * @return BSP status indicating the result of the transmission.
 */
bsp_status_t bsp_spi_transmit(bsp_spi_bus_t bus, const uint8_t* buffer, size_t length);

/**
 * @brief Receives a sequence of bytes over the selected SPI bus.
 * @param bus SPI bus to use.
 * @param buffer Pointer to the receive data buffer.
 * @param length Number of bytes to receive. 
 * @return BSP status indicating the result of the reception.
 */
bsp_status_t bsp_spi_receive(bsp_spi_bus_t bus, uint8_t* buffer, size_t length);

/**
 * @brief Simultaneously transmits and receives a sequence of bytes over the selected SPI bus. 
 * @param bus SPI bus to use. 
 * @param tx_buffer Pointer to the transmit data buffer.
 * @param rx_buffer Pointer to the receive data buffer. 
 * @param length Number of bytes to transfer. 
 * @return BSP status indicating the result of the transfer.
 */
bsp_status_t bsp_spi_transmit_receive(bsp_spi_bus_t bus, const uint8_t* tx_buffer, uint8_t* rx_buffer, size_t length);

