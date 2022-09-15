#include "header.hpp"

static void led_controll(std::vector<GPIO *> &leds, GPIO &button, const std::size_t blink_delay);
static void keyboard_process(key_sel &selection, size_t &delay_time);
static void led_process(std::vector<GPIO *> &leds, key_sel &selection, std::size_t &delay_time);
static void display_menu();
/**
 * @authors Jacob Nilsson & Jacob Lundkvist.
 *
 *
 * @brief Construct a multi threaded program. The program consist of two threads that
 * controlls different leds and buttons simultaneously with the help of libgpiod.
 *
 */

/** --------------------------------------------------------------------------
 * @brief  KVAR ATT GÖRA:

 ** --------------------------------------------------------------------------
 */
int main(void)
{
    /* Creates object of GPIO class  */
    GPIO led1(GPIO_enum::direction::output, 17, "led1");
    GPIO led2(GPIO_enum::direction::output, 22, "led2");
    GPIO led3(GPIO_enum::direction::output, 23, "led3");
    GPIO led4(GPIO_enum::direction::output, 24, "led4");

    GPIO button1(GPIO_enum::direction::input, 27, "button1");
    GPIO button2(GPIO_enum::direction::input, 5, "button2");

    std::size_t delay_time = 0;

    std::vector<GPIO *> leds_g1 =
        {
            &led1,
            &led2};

    std::vector<GPIO *> leds_g2 =
        {
            &led3,
            &led4};

    std::vector<GPIO *> leds{
        &led1,
        &led2,
        &led3,
        &led4};

    std::thread t1(&led_controll, std::ref(leds_g1), std::ref(button1), 1);
    std::thread t2(&led_controll, std::ref(leds_g2), std::ref(button2), 5);
    display_menu();
    t1.join();
    t2.join();
    display_menu();

    while (true)
    {
    }

    return 0;
}

/**
 * @brief
 * @details Connects four leds to PIN 17, 22, 23 and 24 and two buttons to PIN 25 and 27.
 * The two buttons is gonna controll two leds each with the help of a thread. The leds are gonna switch between blinking and be off.
 * On every rising edge the mode is gonna switch.
 *
 */
static void led_controll(std::vector<GPIO *> &leds, GPIO &button, const std::size_t blink_delay)
{
    while (true)
    {
        if (button.read_input())
        {
            button.value = !button.value;
        }
        if (button.value)
        {
            for (uint8_t i = 0; i < (end(leds) - begin(leds)); i++)
            {
                if (button.read_input())
                    button.value = !button.value;
                (*leds[i]).blink(blink_delay);
            }
        }
    }
    return;
}

static void keyboard_process(key_sel &selection, size_t &delay_time)
{
    std::uint8_t choice;
    while(true)
    {
        display_menu();
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;
        switch (choice)
        {
            case 1: selection = key_sel::OFF;
            case 2: selection = key_sel::ON;
            case 3: selection = key_sel::TOGGLE;
            case 4: 
            {
                std::cout << "You've selected blink, select delay time between blinks\n";
                std::cout << "number entered is one tenth of a second\n";
                std::cout << "Recommended(10 for 1 between blinks): ";
                std::cin >> delay_time;
                std::cout << "\n";

                while(delay_time == 0)
                {
                    std::cout << "\nNot a valid number try again: ";
                    std::cin >> delay_time;
                }
                selection = key_sel::BLINK;

            }
            
        }
    }
}

static void led_process(std::vector<GPIO *> &leds, key_sel &selection, std::size_t &delay_time)
{
    /* for (uint8_t i = 0; i < (end(leds) - begin(leds)); i++) */
    while (true)
    {
       switch (selection)
       {
            case key_sel::NOTHING: 
            {
                continue;
            }
            case key_sel::OFF: 
            {
                for (uint8_t i = 0; i < (end(leds) - begin(leds)); i++)
                    (*leds[i]).off();
                selection = key_sel::NOTHING;
            }
            case key_sel::ON: 
            {
                for (uint8_t i = 0; i < (end(leds) - begin(leds)); i++)
                    (*leds[i]).on();
                selection = key_sel::NOTHING;
            }
            case key_sel::TOGGLE: 
            {
                for (uint8_t i = 0; i < (end(leds) - begin(leds)); i++)
                    (*leds[i]).toggle();
                selection = key_sel::NOTHING;
            }
            case key_sel::BLINK: 
            {
                for (uint8_t i = 0; i < (end(leds) - begin(leds)); i++)
                    (*leds[i]).blink(delay_time);
            }
       }
    }
}

static void display_menu()
{
    std::cout << "===================================\n\n";
    std::cout << "\tLED CONTROL MENU\n\n";
    std::cout << "===================================\n";
    std::cout << "1. LEDS OFF\n";
    std::cout << "2. LEDS ON\n";
    std::cout << "3. LEDS TOGGLE\n";
    std::cout << "4. LEDS BLINK\n";
}