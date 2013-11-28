/*
    FreeRTOS V7.0.1 - Copyright (C) 2011 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Library includes. */
#include "stm32f2xx.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION           1
#define configUSE_IDLE_HOOK            0
#define configUSE_TICK_HOOK            1
#define configCPU_CLOCK_HZ             ((unsigned long)SystemCoreClock)
#define configTICK_RATE_HZ             ((portTickType)1000)
#define configMAX_PRIORITIES           ((unsigned portBASE_TYPE)5)
#define configMINIMAL_STACK_SIZE       ((unsigned short)128)
#define configTOTAL_HEAP_SIZE          ((size_t)(20 * 1024))
#define configMAX_TASK_NAME_LEN        (16 + 1)
#define configUSE_TRACE_FACILITY       1
#define configUSE_16_BIT_TICKS         0
#define configUSE_64_BIT_TICKS         1
#define configIDLE_SHOULD_YIELD        1
#define configUSE_MUTEXES              1
#define configUSE_COUNTING_SEMAPHORES  1
#define configQUEUE_REGISTRY_SIZE      50
#define configCHECK_FOR_STACK_OVERFLOW 2
#define configGENERATE_RUN_TIME_STATS  1
#define configUSE_TIMERS               0    // ToDo: Get timers running. Problem: does not work with MPU. On timer create an illegal instruction error occurs.
#define configTIMER_TASK_PRIORITY      ((configMAX_PRIORITIES - 2) | portPRIVILEGE_BIT)
#define configTIMER_QUEUE_LENGTH       16
#define configTIMER_TASK_STACK_DEPTH   128



#if (configGENERATE_RUN_TIME_STATS == 1)
void vConfigureTimerForRunTimeStats(void);
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()

unsigned long vGetRunTimeCounterValue(void);
#define portGET_RUN_TIME_COUNTER_VALUE() vGetRunTimeCounterValue()
#endif

#if (configUSE_TRACE_FACILITY == 1)
#define configUSE_APPLICATION_TASK_TAG 1

void vTraceQueueCreateFailed(unsigned char ucQueueType);
#define traceQUEUE_CREATE_FAILED(x) vTraceQueueCreateFailed(x)

void vTraceCreateMutexFailed(void);
#define traceCREATE_MUTEX_FAILED() vTraceCreateMutexFailed()

void vTraceTaskCreateFailed(void);
#define traceTASK_CREATE_FAILED() vTraceTaskCreateFailed()

void vSetAnalogueOutput(int);
#define traceTASK_SWITCHED_IN() vSetAnalogueOutput((int)pxCurrentTCB->pxTaskTag)
#define traceTASK_SWITCHED_OUT() vSetAnalogueOutput(0)
#endif


/* Co-routine definitions. */
#define configUSE_CO_ROUTINES               0
#define configMAX_CO_ROUTINE_PRIORITIES     2

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet            0
#define INCLUDE_uxTaskPriorityGet           0
#define INCLUDE_vTaskDelete                 0
#define INCLUDE_vTaskCleanUpResources       0
#define INCLUDE_vTaskSuspend                1
#define INCLUDE_vTaskDelayUntil             1
#define INCLUDE_vTaskDelay                  1
#define INCLUDE_xTaskGetSchedulerState      1
#define INCLUDE_xTaskGetCurrentTaskHandle   1
#define INCLUDE_uxTaskGetStackHighWaterMark 1

/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
(lowest) to 0 (1?) (highest). */
#define configKERNEL_INTERRUPT_PRIORITY         (15 << 4)  // 255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    (11 << 4)  // 176 /* equivalent to 0xb0, or priority 11. */


/* This is the value being used as per the ST library which permits 16
priority values, 0 to 15.  This must correspond to the
configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
NVIC value of 255. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY 15

//Fix interrupt named according to CMSIS startup code
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler


#endif /* FREERTOS_CONFIG_H */

