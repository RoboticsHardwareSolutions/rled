#ifndef SPI_H
#define SPI_H

#include <stdint.h>

typedef void* SPI_Handle;  // Opaque for SPI_HandleTypeDef

typedef enum
{
    SPI_STATUS_OK    = 0,
    SPI_STATUS_ERROR = 1
} SPI_Status;

SPI_Status spi_transmit(SPI_Handle hspi, uint8_t* pData, uint16_t Size, uint32_t Timeout);
SPI_Status spi_transmit_dma(SPI_Handle hspi, uint8_t* pData, uint16_t Size);
SPI_Status spi_wait_transmission_complete(SPI_Handle hspi, uint32_t Timeout);
SPI_Status spi_register_cb(SPI_Handle hspi);
SPI_Status spi_delay(SPI_Handle hspi);

#endif  // SPI_H
