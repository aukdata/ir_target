#ifndef LIGHT_SENSOR_HPP
#define LIGHT_SENSOR_HPP

#define GB7_TIMER_USE_INVOKE

#include "timer.hpp"

namespace gb7
{
    template<class Led>
    class light_emitter
    {
        Led pin;
        uint32_t sended_data = 0;
        int timer_id = 0;

        static inline constexpr uint8_t prologue = 0b1011101;
        static inline constexpr uint8_t epilogue = 0b1001001;

    public:
        light_emitter()
        {
            gb7::timer::multitimer::init();

            using namespace gb7::timer::literals;
            timer_id = gb7::timer::multitimer::invoke_every(500_us, 0_ms, +[](void* le) {
                Led pin;
                static uint32_t mask = 0;

                if (mask == 0)
                {
                    mask = 1UL << 31;
                }

                pin = (static_cast<light_emitter<Led>*>(le)->sended_data & mask) != 0;
                mask >>= 1;
            }, this);
        }
        ~light_emitter()
        {
            gb7::timer::multitimer::cancel_invocation(timer_id);
        }

        void set_sended_data(uint8_t data)
        {
            const uint16_t packet = 0b1010101010101010 |
                ((sended_data & (1 << 0)) << 0) |
                ((sended_data & (1 << 1)) << 1) |
                ((sended_data & (1 << 2)) << 2) |
                ((sended_data & (1 << 3)) << 3) |
                ((sended_data & (1 << 4)) << 4) |
                ((sended_data & (1 << 5)) << 5) |
                ((sended_data & (1 << 6)) << 6) |
                ((sended_data & (1 << 7)) << 7);
            sended_data =
                (static_cast<uint32_t>(prologue) << 24) |
                (static_cast<uint32_t>(packet)   << 8 ) |
                (static_cast<uint32_t>(epilogue) << 0 );
        }
    };
} // namespace gb7

#endif // LIGHT_SENSOR_HPP
