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

void ModuleEffects::Start() {
    BaseClass::Start();

    // start timer
    chVTSet(&effTimer, TIME_MS2I(30), ModuleEffects::TimerCallback,
        reinterpret_cast<void*>(this));
}

void ModuleEffects::Shutdown() {
    BaseClass::Shutdown();
}

void ModuleEffects::ThreadMain() {
    chRegSetThreadName("effects");
    uint8_t effectId = 0;
    while (!chThdShouldTerminateX()) {
        watchdog_reload(WATCHDOG_MOD_EFFECTS);
        systime_t current = chibios_rt::System::getTime();
        if (switchEffect == true) {
            switchEffect = false;

            ++effectId;
            if (effectId > 1) {
                effectId = 0;
            }

            switch (effectId) {
                case 0:
                {
                    effCurrent = &effRandomPixel;
                }break;
                case 1:
                {
                    effCurrent = &effWandering;
                    ColorRandom(&effColorCfg.color);
                    effWanderingCfg.dir = 1 - effWanderingCfg.dir;
                    effWanderingCfg.turn = !effWanderingCfg.turn;
                }
                break;
            }

            EffectReset(effCurrent, 0, 0, current);

            // start timer
            chVTSet(&effTimer, TIME_S2I(30), ModuleEffects::TimerCallback,
                reinterpret_cast<void*>(this));
        }

        DrawEffects(current);
        chibios_rt::BaseThread::sleep(TIME_MS2I(10));
    }
}

void ModuleEffects::DrawEffects(systime_t current) {
    memset(display.pixels, 0, sizeof(struct Color) * LEDCOUNT);

    EffectUpdate(effCurrent, 0, 0, current, &display);

#if HAL_USE_WS281X
    for (int i = 0; i < LEDCOUNT; i++) {
        const Color* color = &display.pixels[i];
        ws281xSetColor(&ws281x, i, color->R, color->G, color->B);
    }

    ws281xUpdate(&ws281x);
#endif /* HAL_USE_WS281X */
}

void ModuleEffects::TimerCallback(void* arg) {
    auto mod = reinterpret_cast<ModuleEffects*>(arg);
    mod->switchEffect = true;
}

}  // namespace blinky

MODULE_INITCALL(6, qos::ModuleInit<blinky::ModuleEffectsSingelton>::Init,
        qos::ModuleInit<blinky::ModuleEffectsSingelton>::Start,
        qos::ModuleInit<blinky::ModuleEffectsSingelton>::Shutdown)

#endif

/** @} */
