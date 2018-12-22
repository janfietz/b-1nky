/**
 * @brief
 *
 * @addtogroup
 * @{
 */

#include "mod_sensors.hpp"

#if MOD_SENSORS

#include "ch_tools.h"
#include "watchdog.h"
#include "module_init_cpp.h"

#include "qhal.h"

namespace blinky
{
template <>
ModuleSensors ModuleSensorsSingelton::instance = blinky::ModuleSensors();

/**
 * @brief
 */

void ModuleSensors::Init()
{
    watchdog_register(WATCHDOG_MOD_SENSORS);
}

void ModuleSensors::Start()
{
    Super::Start();
}

void ModuleSensors::Shutdown()
{
    Super::Shutdown();
}

void ModuleSensors::ThreadMain()
{
    chRegSetThreadName("sensors");
    while (!chibios_rt::BaseThread::shouldTerminate())
    {
        watchdog_reload(WATCHDOG_MOD_SENSORS);

        chibios_rt::BaseThread::sleep(TIME_MS2I(25));
    }
}

} // namespace blinky

MODULE_INITCALL(6, qos::ModuleInit<blinky::ModuleSensorsSingelton>::Init,
                qos::ModuleInit<blinky::ModuleSensorsSingelton>::Start,
                qos::ModuleInit<blinky::ModuleSensorsSingelton>::Shutdown)

#endif // MOD_SENSORS

/** @} */
