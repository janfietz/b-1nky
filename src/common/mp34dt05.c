/**
 * @file    mp34dt05.c
 * @brief   MP34DT05 Driver code.
 *
 * @addtogroup MP34DT05
 * @{
 */

#include "hal.h"
#include "mp34dt05.h"

#if HAL_USE_MP34DT05 || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

// /**
//  * @brief   Reads a generic register value using SPI.
//  * @pre     The SPI interface must be initialized and the driver started.
//  *
//  * @param[in] spip      pointer to the SPI interface
//  * @param[in] reg       starting register address
//  * @param[in] n         number of adjacent registers to write
//  * @param[in] b         pointer to a buffer.
//  */
// static void mp34dt05SPIReadRegister(SPIDriver *spip, uint8_t reg, size_t n,
//                                    uint8_t* b) {
//   uint8_t cmd;
//   cmd = reg | MP34DT05_RW;
//   if (n > 1) {
//      cmd |= MP34DT05_MS;
//   }
//   spiSelect(spip);
//   spiSend(spip, 1, &cmd);
//   spiReceive(spip, n, b);
//   spiUnselect(spip);
// }


/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   MP34DT05 Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void mp34dt05Init(void) {}

/**
 * @brief   Initializes the standard part of a @p MP34DT05Driver structure.
 *
 * @param[out] mp34dt05p     pointer to the @p MP34DT05Driver object
 *
 * @init
 */
void mp34dt05ObjectInit(MP34DT05Driver *mp34dt05p) {
    mp34dt05p->config = NULL;
    mp34dt05p->state = MP34DT05_STOP;
}

/**
 * @brief   Configures and activates the MP34DT05 peripheral.
 *
 * @param[in] mp34dt05p   pointer to the @p MP34DT05Driver object
 * @param[in] config    pointer to the @p MP34DT05Config object
 *
 * @api
 */

void mp34dt05Start(MP34DT05Driver *mp34dt05p, const mp34dt05Config *config) {
    osalDbgCheck((mp34dt05p != NULL) && (config != NULL));

    
    osalDbgAssert((mp34dt05p->state == MP34DT05_STOP) ||
        (mp34dt05p->state == MP34DT05_READY), "invalid state");
    mp34dt05p->config = config;

    mp34dt05p->i2scfg.i2scfgr = config->i2scfgr;
    mp34dt05p->i2scfg.i2spr = config->i2spr;
    mp34dt05p->i2scfg.end_cb = config->end_cb;
    mp34dt05p->i2scfg.rx_buffer = &mp34dt05p->rx_buffer;
    mp34dt05p->i2scfg.size = MP34DT05_RX_BUFFER_SAMPLES;

    i2sStart(mp34dt05p->config->i2sp, &mp34dt05p->i2scfg);
    
    mp34dt05p->state = MP34DT05_ACTIVE;
}

/**
 * @brief   Deactivates the MP34DT05 peripheral.
 *
 * @param[in] mp34dt05p      pointer to the @p MP34DT05Driver object
 *
 * @api
 */
void mp34dt05Stop(MP34DT05Driver *mp34dt05p) {
    osalDbgCheck(mp34dt05p != NULL);

    osalSysLock();
    osalDbgAssert((mp34dt05p->state == MP34DT05_STOP) ||
        (mp34dt05p->state == MP34DT05_READY),
            "invalid state");

    if (mp34dt05p->state == MP34DT05_READY) {

        i2sStop(mp34dt05p->config->i2sp);
    }	

    mp34dt05p->state = MP34DT05_STOP;
    osalSysUnlock();
}


void mp34dt05StartExchange(MP34DT05Driver *mp34dt05p)
{
    i2sStartExchange(mp34dt05p->config->i2sp);
}

void mp34dt05StopExchange(MP34DT05Driver *mp34dt05p)
{
    i2sStopExchange(mp34dt05p->config->i2sp);
}

#endif /* HAL_USE_MP34DT05 */

/** @} */
