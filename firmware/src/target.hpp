#ifndef TAEGET_HPP
#define TAEGET_HPP

#include <util/delay.h>

#include "port.hpp"
#include "light_emitter.hpp"

namespace gb7
{
    class target_interface {
    public:
        target_interface() = default;
        virtual ~target_interface() = default;

        virtual void activate(uint8_t duration) = 0;
        virtual bool update() = 0;
        virtual void deactivate() = 0;
    };

    template<class Speaker_Pin, class Indicator_Pin, class Sender_Pin>
    class target: public target_interface
    {
        Indicator_Pin indicator;
        light_emitter<Sender_Pin> sender;
        Speaker_Pin speaker;

        uint8_t duration = 0;
        uint8_t point = 0;

    public:
        void activate(uint8_t d) noexcept override
        {
            duration = 256 + 2 * d;
            point = min(max(255 - d, 255), 0);

            indicator.set_high();
            sender.start(point);
        }
        bool update() noexcept override
        {
            if (duration-- == 0)
            {
                deactivate();
                return false;
            }
            else
            {
                sender.start(point);
                return true;
            }
        }
        void deactivate() noexcept override
        {
            indicator.set_low();
            sender.stop();
        }
    };
}

#endif // TAEGET_HPP
