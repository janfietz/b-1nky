/*
 * can_manager.h
 *
 * (c) Quantec Networks GmbH
 *
 *  Created on: 07.08.2012
 *      Author: DHA
 *
 * Purpose:
 * Handle can network communication
 *
 */

#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H
#include "config.h"

#define CAN_MANAGER_NUM_SUPPORTED_SLAVES    2
#define CAN_MANAGER_FIRST_SLAVE_ID          1

#define CAN_MANAGER_MAX_CAN_ERRORS          40
#define CAN_MANAGER_MAX_CAN_SLAVE_ERRORS    40

#define CAN_MANAGER_LAST_SLAVE_RX_RESET_TIMEOUT_S       20  // give slave enough time start/restart todo[high] check value
#define CAN_MANAGER_LAST_SLAVE_RX_ERROR_FLAG_TIMEOUT_S  40  // give slave enough time start/restart todo[high] check value

#define CAN_MANAGER_NUM_LED_VOLTAGES_PER_SLAVE              14
#define CAN_MANAGER_NUM_SUPPLY_VOLTAGES_PER_SLAVE           2
#define CAN_MANAGER_NUM_LED_TEMPERATURE_SENSORS_PER_SLAVE   14
#define CAN_MANAGER_NUM_BOARD_TEMPERATURE_SENSORS_PER_SLAVE 1

#define CAN_MANAGER_SLAVE_ADDRESS_PWM           0x2001005C
#define CAN_MANAGER_SLAVE_ADDRESS_SEQUENCE_TIME 0x20010060

#define CAN_MANAGER_SLAVE_ADDRESS_ADC_SENSORS   0x20010090

#define CAN_MANAGER_SLAVE_ADC_SENSORS_ENTRY_SIZE            8  // 4 byte value and 4 byte status
#define CAN_MANAGER_SLAVE_ADC_SENSORS_ENTRY_ELEMENT_SIZE    4  // 32 bit values

#define CAN_MANAGER_PS_BASE_ADDRESS_ANALOG_LED                  CAN_MANAGER_SLAVE_ADDRESS_ADC_SENSORS
#define CAN_MANAGER_PS_BASE_ADDRESS_ANALOG_VOLTAGE              (CAN_MANAGER_PS_BASE_ADDRESS_ANALOG_LED + (CAN_MANAGER_NUM_LED_VOLTAGES_PER_SLAVE * CAN_MANAGER_SLAVE_ADC_SENSORS_ENTRY_SIZE))
#define CAN_MANAGER_PS_BASE_ADDRESS_ANALOG_LED_TEMPERATURE      (CAN_MANAGER_PS_BASE_ADDRESS_ANALOG_VOLTAGE + (CAN_MANAGER_NUM_SUPPLY_VOLTAGES_PER_SLAVE * CAN_MANAGER_SLAVE_ADC_SENSORS_ENTRY_SIZE))
#define CAN_MANAGER_PS_BASE_ADDRESS_ANALOG_BOARD_TEMPERATURE    (CAN_MANAGER_PS_BASE_ADDRESS_ANALOG_LED_TEMPERATURE + (CAN_MANAGER_NUM_LED_TEMPERATURE_SENSORS_PER_SLAVE * CAN_MANAGER_SLAVE_ADC_SENSORS_ENTRY_SIZE))

typedef enum
{
    CAN_MANAGER_SLAVE_ID_ALL_SLAVES,
    CAN_MANAGER_SLAVE_ID_SLAVE_1,
    CAN_MANAGER_SLAVE_ID_SLAVE_2,
    CAN_MANAGER_SLAVE_ID_COUNT
} CAN_MANAGER_SLAVE_ID_E;

typedef enum
{
    CAN_MANAGER_ACCESS_GROUP_PS_ANALOG_LED,
    CAN_MANAGER_ACCESS_GROUP_PS_ANALOG_VOLTAGE,
    CAN_MANAGER_ACCESS_GROUP_PS_ANALOG_LED_TEMPERATURE,
    CAN_MANAGER_ACCESS_GROUP_PS_ANALOG_BOARD_TEMPERATURE,
    CAN_MANAGER_ACCESS_GROUP_COUNT
} CAN_MANAGER_ACCESS_GROUP_E;

void CAN_MANAGER_SetSlavePWM(uint32_t pwm);
void CAN_MANAGER_StartSlaveSequence(uint32_t time_ms);
void CAN_MANAGER_Task(void *pvParameters);

#endif