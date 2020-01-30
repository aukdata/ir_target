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
        
        uint32_t mask = 0;
        uint32_t timer_id = 0;

        static inline constexpr uint8_t prologue = 0b1011001;
        static inline constexpr uint8_t epilogue = 0b1001001;

    public:
        light_emitter()
        {
            gb7::timer::multitimer::init();;
        }
        ~light_emitter()
        {
            gb7::timer::multitimer::cancel_invocation(timer_id);
        }

        void stop() noexcept
        {
            gb7::timer::multitimer::cancel_invocation(timer_id);
            timer_id = 0;
        }

        void start(uint8_t data)
        {
            const uint16_t packet = 0b1010101010101010 |
                ((data & (1 << 0)) << 0) |
                ((data & (1 << 1)) << 1) |
                ((data & (1 << 2)) << 2) |
                ((data & (1 << 3)) << 3) |
                ((data & (1 << 4)) << 4) |
                ((data & (1 << 5)) << 5) |
                ((data & (1 << 6)) << 6) |
                ((data & (1 << 7)) << 7);
            sended_data =
                (static_cast<uint32_t>(prologue) << 24) |
                (static_cast<uint32_t>(packet)   << 8 ) |
                (static_cast<uint32_t>(epilogue) << 0 );

            using namespace gb7::timer::literals;
            gb7::timer::multitimer::cancel_invocation(timer_id);
            timer_id = gb7::timer::multitimer::invoke_every(1_ms, 0, +[](void* le) {
                Led pin;

                if (static_cast<decltype(this)>(le)->mask == 0)
                {
                    static_cast<decltype(this)>(le)->mask = (1UL << 31);
                }

                pin = (static_cast<decltype(this)>(le)->sended_data & static_cast<decltype(this)>(le)->mask) != 0;
                static_cast<decltype(this)>(le)->mask >>= 1;
            }, this);
        }
    };
} // namespace gb7

#endif // LIGHT_SENSOR_HPP
