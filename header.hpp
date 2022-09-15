#ifndef _HEADER_HPP_
#define _HEADER_HPP_

/* Include directives */
#include <vector>
#include "gpio_lib.hpp"

/* Global objects of GPIO class. */

enum class key_sel
{
    NOTHING,
    OFF,
    ON,
    TOGGLE,
    BLINK,
    CREDITS
};


#endif /* _HEADER_HPP_ */