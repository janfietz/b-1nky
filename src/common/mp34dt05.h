
/**
 * @file    mp34dt05.h
 * @brief   MP34DT05 Driver macros and structures.
 *
 * Driver for MP34DT05 MEMS audio sensor omnidirectional digital microphone.
 * It can be used on STM32 platforms.
 *
 * @addtogroup MP34DT05
 * @{
 */

#ifndef _MP34DT05_H_
#define _MP34DT05_H_

#include "ch.h"
#include "hal.h"

#if HAL_USE_MP34DT05 || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/
/**
 * @brief   Size of RX bufer as number of samples
 */
#if !defined(MP34DT05_RX_BUFFER_SAMPLES) || defined(__DOXYGEN__)
#define MP34DT05_RX_BUFFER_SAMPLES 8
#endif

#if !HAL_USE_I2S
#error "HAL_USE_MP34DT05 requires HAL_USE_I2S"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver state machine possible states.
 */
typedef enum
{
    MP34DT05_UNINIT = 0, /**< Not initialized.                   */
    MP34DT05_STOP = 1,   /**< Stopped.                           */
    MP34DT05_READY = 2,  /**< Ready.                             */
    MP34DT05_ACTIVE = 3, /**< Active.                            */
} mp34dt05State_t;
/**
 * @brief   Type of a structure representing an mp34dt05Driver driver.
 */
typedef struct mp34dt05Driver MP34DT05Driver;

/**
 * @brief   Driver configuration structure.
 */
typedef struct
{
    /**
     * @brief SPI driver associated to this MP34DT05.
     */
    I2SDriver *i2sp;

    /**
     * @brief   Callback function called during streaming.
     */
    i2scallback_t end_cb;

    /**
     * @brief   Configuration of the I2SCFGR register.
     * @details See the STM32 reference manual, this register is used for
     *          the I2S configuration, the following bits must not be
     *          specified because handled directly by the driver:
     *          - I2SMOD
     *          - I2SE
     *          - I2SCFG
     *          .
     */
    int16_t i2scfgr;
    /**
     * @brief   Configuration of the I2SPR register.
     * @details See the STM32 reference manual, this register is used for
     *          the I2S clock setup.
     */
    int16_t i2spr;

} mp34dt05Config;

/**
 * @brief   Structure representing an ws281x driver.
 */
struct mp34dt05Driver
{
    /**
     * @brief   Driver state.
     */
    mp34dt05State_t state;
    /**
     * @brief   Current configuration data.
     */
    const mp34dt05Config *config;
    /* End of the mandatory fields.*/

    /**
    * @brief   receive buffer
    */
    int16_t rx_buffer[MP34DT05_RX_BUFFER_SAMPLES];

    /**
     * @brief   I2S driver configuration
     */
    I2SConfig i2scfg;
};
/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif
    void mp34dt05Init(void);
    void mp34dt05ObjectInit(MP34DT05Driver *mp34dt05p);
    void mp34dt05Start(MP34DT05Driver *mp34dt05p, const mp34dt05Config *config);
    void mp34dt05Stop(MP34DT05Driver *mp34dt05p);
    void mp34dt05StartExchange(MP34DT05Driver *mp34dt05p);
    void mp34dt05StopExchange(MP34DT05Driver *mp34dt05p);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_MP34DT05 */

#endif /* _MP34DT05_H_ */

/** @} */
