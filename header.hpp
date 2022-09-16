#ifndef _HEADER_HPP_
#define _HEADER_HPP_

/* Include directives */
#include <vector>
#include "gpio_lib.hpp"


/* enumeration of key selections */
enum key_selection
{
    NOTHING,
    OFF,
    ON,
    TOGGLE,
    BLINK,
};

/* Const expressions for pins */
constexpr uint8_t led1_pin = 17;
constexpr uint8_t led2_pin = 22;
constexpr uint8_t led3_pin = 23;
constexpr uint8_t led4_pin = 24;
constexpr uint8_t btn1_pin = 27;
constexpr uint8_t btn2_pin = 5;

/* Macro used in for loop to iterate through array named leds */
#define ALL_LEDS uint8_t i = 0; i < (end(leds) - begin(leds)); i++

/* Global functions */

void led_controll(std::vector<GPIO *> &leds, GPIO &button, const std::size_t blink_delay);
void keyboard_process(key_selection &selection, size_t &delay_time);
void led_process(std::vector<GPIO *> &leds, key_selection &selection, std::size_t &delay_time);
uint8_t display_menu();
uint16_t get_number(uint16_t min_val, uint16_t max_val);


#endif /* _HEADER_HPP_ */