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
#include "threadedmodule.h"
#include "singleton.h"

#include "color.h"
#include "display.h"

#include "effect_randompixels.h"


#if MOD_EFFECTS

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/
#ifndef MOD_EFFECTS_THREADSIZE
#define MOD_EFFECTS_THREADSIZE 256
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
    ModuleEffects();
    ~ModuleEffects();

    virtual void Init();
    virtual void Start();
    virtual void Shutdown();

protected:
    typedef qos::ThreadedModule<MOD_EFFECTS_THREADSIZE> BaseClass;

    virtual void ThreadMain();
    virtual tprio_t GetThreadPrio() const {return MOD_EFFECTS_THREADPRIO;}

private:
    void DrawEffects();

    Color displayPixel[LEDCOUNT];
    DisplayBuffer display =
    {
        .width = DISPLAY_WIDTH,
        .height = DISPLAY_HEIGHT,
        .pixels = displayPixel,
    };

    /*Effects*/
    EffectRandomPixelsCfg effRandomCfg = {
            .spawninterval = MS2ST(1000),
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
};

typedef qos::Singleton<ModuleEffects> ModuleEffectsSingelton;

}
#endif /* MOD_EFFECTS */
#endif /* _MOD_EFFECTS_H_ */

/** @} */
