#include "spi.h"
#include "stm32g0xx_hal.h"
#include <stdbool.h>
#include "SEGGER_RTT.h"

// Flag to track DMA transmission completion
static volatile bool spi_dma_complete = true;

SPI_Status spi_transmit(SPI_Handle hspi, uint8_t* pData, uint16_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef status = HAL_SPI_Transmit((SPI_HandleTypeDef*) hspi, pData, Size, Timeout);
    return (status == HAL_OK) ? SPI_STATUS_OK : SPI_STATUS_ERROR;
}

SPI_Status spi_transmit_dma(SPI_Handle hspi, uint8_t* pData, uint16_t Size)
{
    if (!hspi || !pData || Size == 0)
    {
        return SPI_STATUS_ERROR;
    }

    SPI_HandleTypeDef* spi = (SPI_HandleTypeDef*) hspi;

    // Ensure SPI is idle before starting DMA transfer
    // Wait for previous transfer to complete (max 100ms)
    uint32_t timeout = 100;
    uint32_t start   = HAL_GetTick();
    while ((spi->State != HAL_SPI_STATE_READY) && (HAL_GetTick() - start < timeout))
    {
        HAL_Delay(1);
    }

    if (spi->State != HAL_SPI_STATE_READY)
    {
        SEGGER_RTT_printf(0, "spi not ready\n");
        return SPI_STATUS_ERROR;  // SPI not ready
    }

    // Reset completion flag and initiate DMA transfer
    spi_dma_complete         = false;
    HAL_StatusTypeDef status = HAL_SPI_Transmit_DMA(spi, pData, Size);
    return (status == HAL_OK) ? SPI_STATUS_OK : SPI_STATUS_ERROR;
}

SPI_Status spi_wait_transmission_complete(SPI_Handle hspi, uint32_t Timeout)
{
    if (!hspi)
    {
        return SPI_STATUS_ERROR;
    }

    uint32_t start_tick = HAL_GetTick();

    // Wait for DMA completion flag with timeout
    // Check flag without tight busy-wait to allow other tasks to run
    while (!spi_dma_complete)
    {
        if (HAL_GetTick() - start_tick > Timeout)
        {
            return SPI_STATUS_ERROR;  // Timeout
        }
        // Yield CPU briefly - HAL_Delay(1) will use vTaskDelay in RTOS environment
        HAL_Delay(1);
    }

    return SPI_STATUS_OK;
}

SPI_Status spi_delay(SPI_Handle hspi)
{
    uint8_t delay_data[125] = {
        0,
    };
    HAL_StatusTypeDef status = HAL_SPI_Transmit((SPI_HandleTypeDef*) hspi, delay_data, 125, 1000);
    return (status == HAL_OK) ? SPI_STATUS_OK : SPI_STATUS_ERROR;
}

/**
 * @brief HAL SPI Tx Complete Callback
 * Called by HAL when DMA transmission is complete
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi)
{
    spi_dma_complete = true;
}

SPI_Status spi_register_cb(SPI_Handle hspi)
{
    /* Register SPI callbacks for DMA transfers */
    HAL_StatusTypeDef status =
        HAL_SPI_RegisterCallback((SPI_HandleTypeDef*) hspi, HAL_SPI_TX_COMPLETE_CB_ID, HAL_SPI_TxCpltCallback);

    return HAL_OK == status ? SPI_STATUS_OK : SPI_STATUS_ERROR;
}
