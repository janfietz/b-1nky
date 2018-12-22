/**
 * @file    src/mod_effects.h
 * @brief
 *
 * @addtogroup
 * @{
 */

#ifndef _MOD_EFFECTS_H_
#define _MOD_EFFECTS_H_

#include "target_cfg.h"

#if MOD_EFFECTS

#include "threadedmodule.h"
#include "singleton.h"

#include "color.h"
#include "display.h"

#include "effect_randompixels.h"
#include "effect_wandering.h"
#include "effect_simplecolor.h"

#include <array>



/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/
#ifndef MOD_EFFECTS_THREADSIZE
#define MOD_EFFECTS_THREADSIZE 512
#endif

#ifndef MOD_EFFECTS_THREADPRIO
#define MOD_EFFECTS_THREADPRIO LOWPRIO
#endif

#ifndef LEDCOUNT
#error "LEDCOUNT driver must be specified for this target"
#endif

#ifndef DISPLAY_WIDTH
#error "DISPLAY_WIDTH driver must be specified for this target"
#endif

#ifndef DISPLAY_HEIGHT
#error "DISPLAY_HEIGHT driver must be specified for this target"
#endif

namespace blinky
{
/**
 * @brief
 */

class ModuleEffects : public qos::ThreadedModule<MOD_EFFECTS_THREADSIZE>
{
public:
    ModuleEffects() = default;
    ~ModuleEffects() = default;

    void Init() override;
    void Start() override;
    void Shutdown() override;

protected:
    using  BaseClass = qos::ThreadedModule<MOD_EFFECTS_THREADSIZE>;

    void ThreadMain() override;
    tprio_t GetThreadPrio() const override {return MOD_EFFECTS_THREADPRIO;}

private:
    void DrawEffects(systime_t current);
    static void TimerCallback(void* arg);

    bool switchEffect = false;

    std::array<Color, LEDCOUNT> displayPixel;

    /*Effects*/
    EffectRandomPixelsCfg effRandomCfg = {
            .spawninterval = TIME_MS2I(200),
            .color = {0xFF, 0xFF, 0xFF},
            .randomRed = true,
            .randomGreen = true,
            .randomBlue = true,
    };

    Color m_RandomPixelColors[LEDCOUNT];
    EffectRandomPixelsData effRandomData = {
            .lastspawn = 0,
            .pixelColors = m_RandomPixelColors,
    };

    Effect effRandomPixel =
    {
        .effectcfg = &effRandomCfg,
        .effectdata = &effRandomData,
        .update = &EffectRandomPixelsUpdate,
        .reset = &EffectRandomPixelsReset,
        .p_next = NULL,
    };

    EffectSimpleColorCfg effColorCfg = {
        .color = {0x00, 0x00, 0xFF},
        .fillbuffer = false,
    };
    EffectSimpleColorData effColorData;
    Effect effColor = {
        .effectcfg = &effColorCfg,
        .effectdata = &effColorData,
        .update = &EffectSimpleUpdate,
        .reset = &EffectSimpleReset,
        .p_next = NULL,
    };

    EffectWanderingCfg effWanderingCfg = {
        .speed = TIME_MS2I(100),
        .ledbegin = 0,
        .ledend = LEDCOUNT - 1,
        .dir = 0,
        .trailLength = 2,
        .turn = false,
    };

    EffectWanderingData effWanderingData;
    Effect effWandering =
    {
            .effectcfg = &effWanderingCfg,
            .effectdata = &effWanderingData,
            .update = &EffectWanderingUpdate,
            .reset = &EffectWanderingReset,
            .p_next = &effColor,
    };

    Effect* effCurrent = &effRandomPixel;

    virtual_timer_t effTimer;
};

typedef qos::Singleton<ModuleEffects> ModuleEffectsSingelton;

}
#endif /* MOD_EFFECTS */
#endif /* _MOD_EFFECTS_H_ */

/** @} */
