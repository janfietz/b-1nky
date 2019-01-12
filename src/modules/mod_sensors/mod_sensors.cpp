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

#include "lis3dh.h"
#include "mp34dt05.h"

#include <array>

namespace blinky
{
template <>
ModuleSensors ModuleSensorsSingelton::instance = blinky::ModuleSensors();

extern "C"
{
void mp34dt05ReceiveEnd(I2SDriver *i2sp, size_t offset, size_t n)
{
// do decimation here
}
}

/**
 * @brief
 */

void ModuleSensors::Init()
{
    watchdog_register(WATCHDOG_MOD_SENSORS);
}

void ModuleSensors::Start()
{
    mp34dt05StartExchange(&mp34dt05);
    Super::Start();
}

void ModuleSensors::Shutdown()
{
    Super::Shutdown();
    mp34dt05StopExchange(&mp34dt05);
}

void ModuleSensors::ThreadMain()
{
    chRegSetThreadName("sensors");
    
    while (!chibios_rt::BaseThread::shouldTerminate())
    {
        watchdog_reload(WATCHDOG_MOD_SENSORS);

        std::array<int32_t, LIS3DH_NUMBER_OF_AXES> accelData;;
        lis3dhReadRaw(&lis3dh, accelData.data());

        int16_t temp = 0;
        lis3dhReadTemp(&lis3dh, &temp);

        chibios_rt::BaseThread::sleep(TIME_MS2I(25));
    }
}

} // namespace blinky

MODULE_INITCALL(6, qos::ModuleInit<blinky::ModuleSensorsSingelton>::Init,
                qos::ModuleInit<blinky::ModuleSensorsSingelton>::Start,
                qos::ModuleInit<blinky::ModuleSensorsSingelton>::Shutdown)

#endif // MOD_SENSORS

/** @} */
