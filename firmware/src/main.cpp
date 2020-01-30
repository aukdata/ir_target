/* Name: main.cpp
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>

#define GB7_TIMER_USE_INVOKE

#include "port.hpp"
#include "target.hpp"
#include "random.hpp"

int main()
{
    gb7::port_writable<gb7::port_type::PortB> port_b;
    auto port_b0 = port_b.get_writable_pin<0>();
    auto port_b1 = port_b.get_writable_pin<1>();
    auto port_b2 = port_b.get_writable_pin<2>();
    auto port_b3 = port_b.get_writable_pin<3>();
    auto port_b4 = port_b.get_writable_pin<4>();
    auto port_b5 = port_b.get_writable_pin<5>();
    auto port_b6 = port_b.get_writable_pin<6>();
    auto port_b7 = port_b.get_writable_pin<7>();

    gb7::port_writable<gb7::port_type::PortC> port_c;
    auto port_c0 = port_c.get_writable_pin<0>();
    auto port_c1 = port_c.get_writable_pin<1>();
    auto port_c2 = port_c.get_writable_pin<2>();
    auto port_c3 = port_c.get_writable_pin<3>();
    auto port_c4 = port_c.get_writable_pin<4>();
    auto port_c5 = port_c.get_writable_pin<5>();
    auto port_c6 = port_c.get_writable_pin<6>();

    gb7::port_writable<gb7::port_type::PortD> port_d;
    auto port_d0 = port_d.get_writable_pin<0>();
    auto port_d1 = port_d.get_writable_pin<1>();
    auto port_d2 = port_d.get_writable_pin<2>();
    auto port_d3 = port_d.get_writable_pin<3>();
    auto port_d4 = port_d.get_writable_pin<4>();
    auto port_d5 = port_d.get_writable_pin<5>();
    auto port_d6 = port_d.get_writable_pin<6>();
    auto port_d7 = port_d.get_writable_pin<7>();

    auto target1 = gb7::target<decltype(port_d0), decltype(port_d1), decltype(port_d2)> {};
    auto target3 = gb7::target<decltype(port_c5), decltype(port_c4), decltype(port_c3)> {};
    auto target4 = gb7::target<decltype(port_c2), decltype(port_c1), decltype(port_c0)> {};
    auto target5 = gb7::target<decltype(port_b1), decltype(port_b0), decltype(port_d7)> {};

    gb7::target_interface* targets[4] = {
        &target1, &target3, &target4, &target5
    };
    gb7::random rand {};

    int target_id = -1;
    for (int i = 0;; i++)
    {
        target_id = rand(4);
        targets[target_id]->activate(rand(256));
        
        do
        {
            _delay_ms(10);
        } while (targets[target_id]->update());
        target_id = -1;

        delay_ms(rand(2000));
    }

    for (;;);
    return 0;   /* never reached */
}
