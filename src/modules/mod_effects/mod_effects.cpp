/**
 * @file    src/mod_effects.c
 * @brief
 *
 * @addtogroup
 * @{
 */

#include "mod_effects.h"

#if MOD_EFFECTS

#include "ch_tools.h"
#include "watchdog.h"
#include "module_init_cpp.h"

#include "qhal.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace blinky
{
template <>
ModuleEffects ModuleEffectsSingelton::instance = blinky::ModuleEffects();


/**
 * @brief
 */

ModuleEffects::ModuleEffects()
{

}

ModuleEffects::~ModuleEffects()
{

}

void ModuleEffects::Init()
{
    watchdog_register(WATCHDOG_MOD_EFFECTS);
}

void ModuleEffects::Start()
{
    BaseClass::Start();
}

void ModuleEffects::Shutdown()
{
    BaseClass::Shutdown();
}

void ModuleEffects::ThreadMain()
{
    chRegSetThreadName("effects");

    while (!chThdShouldTerminateX())
    {
        watchdog_reload(WATCHDOG_MOD_EFFECTS);

        DrawEffects();
        chibios_rt::BaseThread::sleep(MS2ST(10));
    }
}

void ModuleEffects::DrawEffects()
{
    int i;
    systime_t current = chVTGetSystemTime();
    
    memset(display.pixels, 0, sizeof(struct Color) * LEDCOUNT);

    EffectUpdate(&effRandomPixel, 0, 0, current, &display);

#if HAL_USE_WS281X
    for (i = 0; i < LEDCOUNT; i++)
    {
        const Color* color = &display.pixels[i];
        ws281xSetColor(&ws281x, i, color->R, color->G, color->B);
    }

    ws281xUpdate(&ws281x);
#endif /* HAL_USE_WS281X */
}

}

MODULE_INITCALL(6, qos::ModuleInit<blinky::ModuleEffectsSingelton>::Init,
        qos::ModuleInit<blinky::ModuleEffectsSingelton>::Start,
        qos::ModuleInit<blinky::ModuleEffectsSingelton>::Shutdown)

#endif

/** @} */
