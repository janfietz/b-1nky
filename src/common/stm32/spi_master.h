/*
 * spi_master.h
 *
 *  Created on: 28.09.2010
 *      Author: vinz
 */

#ifndef SPI_MASTER_H_
#define SPI_MASTER_H_

#include <stdint.h>
#include <stdbool.h>
#if defined(STM32F2XX)
#include <stm32f2xx_spi.h>
#elif defined(STM32F4XX)
#include <stm32f4xx_spi.h>
#else
#error "Unsupported chip"
#endif

//enable this to protect against concurrent access
#define SPI_MASTER_USE_LOCKING

#define SPI_MASTER_TIMEOUT      SEMAPHORE_TIMEOUT_MAX  // no timeout

typedef enum
{
    SPI_MASTER_BUS_1,
#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL) || defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F2XX) || defined(STM32F4XX)
    SPI_MASTER_BUS_2,
#endif
#if defined(STM32F10X_HD) || defined(STM32F10X_XL) || defined(STM32F2XX) || defined(STM32F4XX)
    SPI_MASTER_BUS_3,
#endif
    SPI_MASTER_BUS_COUNT
} SPI_MASTER_BUS_E;


void SPI_MASTER_Init(SPI_MASTER_BUS_E SpiBus, SPI_InitTypeDef* SPI_InitStruct);
void SPI_MASTER_Deinit(SPI_MASTER_BUS_E SpiBus);
void SPI_MASTER_Set_clockphase(SPI_MASTER_BUS_E SpiBus, uint16_t SPI_CPHA);

bool SPI_MASTER_Transceive(SPI_MASTER_BUS_E SpiBus, const uint8_t *pDataMOSI, uint8_t *pDataMISO, uint16_t Length);
#define SPI_MASTER_Transmit(SpiBus, pDataMOSI, Length) SPI_MASTER_Transceive(SpiBus, pDataMOSI, 0, Length)
#define SPI_MASTER_Receive(SpiBus, pDataMISO, Length) SPI_MASTER_Transceive(SpiBus, 0, pDataMISO, Length)

#define SPI_MASTER_TransceiveByte(SpiBus, pDataMOSI, pDataMISO) SPI_MASTER_Transceive(SpiBus, pDataMOSI, pDataMISO, 1)
#define SPI_MASTER_TransmitByte(SpiBus, pDataMOSI) SPI_MASTER_Transmit(SpiBus, pDataMOSI, 1)
#define SPI_MASTER_ReceiveByte(SpiBus, pDataMISO) SPI_MASTER_Receive(SpiBus, pDataMISO, 1)

#ifdef SPI_MASTER_USE_LOCKING
void SPI_MASTER_Lock(SPI_MASTER_BUS_E SpiBus);
bool SPI_MASTER_LockTimeout(SPI_MASTER_BUS_E SpiBus, uint32_t timeout_ms);
void SPI_MASTER_Unlock(SPI_MASTER_BUS_E SpiBus);
#endif


#endif /* SPI_MASTER_H_ */
