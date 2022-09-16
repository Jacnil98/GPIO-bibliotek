/* Include directives */
#include "header.hpp"

/**
 * @authors Jacob Nilsson & Jacob Lundkvist.
 *
 * @brief Multithreaded program that is supposed to demonstrate the use of
 * self-created library "gpio_lib" that builds on libgpiod.
 * 
 * @details This program creates four threads, t1-t4.
 * t1 controls vector led_group1 with button 1,
 * t2 controls vector led_group2 with button 2,
 * t3 takes input from terminal and updates variables used in thread t4,
 * t4 controls vector leds through terminal input from thread t3.
 * 
 * GPIO objects uses default values and values can be added in the
 * constructor GPIO.
 * 
 * GPIO pins used:
 * Output: 17, 22, 23, 24.
 * Input : 27, 5.
 */  
int main(void)
{
    GPIO led1(GPIO_enum::direction::output, led1_pin, "led1");
    GPIO led2(GPIO_enum::direction::output, led2_pin, "led2");
    GPIO led3(GPIO_enum::direction::output, led3_pin, "led3");
    GPIO led4(GPIO_enum::direction::output, led4_pin, "led4");
    GPIO button1(GPIO_enum::direction::input, btn1_pin, "button1");
    GPIO button2(GPIO_enum::direction::input, btn2_pin, "button2");
    std::size_t delay_time = 0;
    key_selection selection = NOTHING;
    std::vector<GPIO *> led_group1
    {
        &led1,
        &led2
    };

    std::vector<GPIO *> led_group2
    {
        &led3,
        &led4
    };

    std::vector<GPIO *> leds
    {
        &led1,
        &led2,
        &led3,
        &led4
    };

    std::thread t1(&led_controll, std::ref(led_group1), std::ref(button1), 1);
    std::thread t2(&led_controll, std::ref(led_group2), std::ref(button2), 5);
    std::thread t3(&keyboard_process, std::ref(selection), std::ref(delay_time));
    std::thread t4(&led_process, std::ref(leds), std::ref(selection), std::ref(delay_time));
    t1.join();
    t2.join(); 
    t3.join();
    t4.join();

    while (true)
    {

    }

    t1.detach();
    t2.detach();
    t3.detach();
    t4.detach();
    return 0;
}