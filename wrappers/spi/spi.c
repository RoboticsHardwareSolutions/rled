#include "spi.h"
#include "stm32g0xx_hal.h"

SPI_Status spi_transmit(SPI_Handle hspi, uint8_t* pData, uint16_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef status = HAL_SPI_Transmit((SPI_HandleTypeDef*) hspi, pData, Size, Timeout);
    return (status == HAL_OK) ? SPI_STATUS_OK : SPI_STATUS_ERROR;
}

SPI_Status spi_delay(SPI_Handle hspi)
{
    uint8_t delay_data[125] = {
        0,
    };
    HAL_StatusTypeDef status = HAL_SPI_Transmit((SPI_HandleTypeDef*) hspi, delay_data, 125, 1000);
    return (status == HAL_OK) ? SPI_STATUS_OK : SPI_STATUS_ERROR;
}
