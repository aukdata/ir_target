/* Name: main.cpp
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>

#include "port.hpp"

int main()
{
    gb7::port_writable<gb7::port_type::PortB> port_b;
    gb7::port_writable<gb7::port_type::PortC> port_c;
    gb7::port_writable<gb7::port_type::PortD> port_d;

    return 0;   /* never reached */
}
