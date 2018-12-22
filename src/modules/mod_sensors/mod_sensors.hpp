/**
 * @brief
 *
 * @addtogroup
 * @{
 */

#ifndef MOD_SENSORS_H
#define MOD_SENSORS_H

#include "target_cfg.h"

#include "threadedmodule.h"
#include "singleton.h"

#if MOD_SENSORS

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Pre-compile time settings                                                 */
/*===========================================================================*/
#ifndef MOD_SENSORS_THREADSIZE
#define MOD_SENSORS_THREADSIZE 512
#endif

#ifndef MOD_SENSORS_THREADPRIO
#define MOD_SENSORS_THREADPRIO LOWPRIO
#endif

/*===========================================================================*/
/* Derived constants and error checks                                        */
/*===========================================================================*/

namespace blinky
{
/**
 * @brief
 */

class ModuleSensors : public qos::ThreadedModule<MOD_SENSORS_THREADSIZE>
{
    using Super = qos::ThreadedModule<MOD_SENSORS_THREADSIZE>;

  public:
    void Init() override;
    void Start() override;
    void Shutdown() override;

  protected:
    tprio_t GetThreadPrio() const override { return MOD_SENSORS_THREADPRIO; };
    void ThreadMain() override;
};

typedef qos::Singleton<ModuleSensors> ModuleSensorsSingelton;

} // namespace blinky

#endif /* MOD_SENSORS */

#endif /* MOD_SENSORS_H */
