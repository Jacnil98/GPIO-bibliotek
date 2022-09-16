/* Include directives */
#include "header.hpp"

/**
 * @brief
 * @details Connects four leds to PIN 17, 22, 23 and 24 and two buttons to PIN 25 and 27.
 * The two buttons is gonna controll two leds each with the help of a thread. The leds are gonna switch between blinking and be off.
 * On every rising edge the mode is gonna switch.
 *
 */
void led_controll(std::vector<GPIO *> &leds, GPIO &button, const std::size_t blink_delay)
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

/**
 * @brief Switches between the different led states.
 * 
 * @details 
 */
void led_process(std::vector<GPIO *> &leds, key_selection &selection, std::size_t &delay_time)
{
    while (true)
    {
       switch (selection)
       {
            case NOTHING:
            {
                continue;
            }
            case OFF:
            {
                for (ALL_LEDS)
                    (*leds[i]).off();
                selection = NOTHING;
                break;
            }
            case ON:
            {
                for (ALL_LEDS)
                    (*leds[i]).on();
                selection = NOTHING;
                break;
            }
            case TOGGLE:
            {
                for (ALL_LEDS)
                    (*leds[i]).toggle();
                selection = NOTHING;
                break;
            }
            case BLINK:
            {
                for (ALL_LEDS)
                    (*leds[i]).blink(delay_time);
            }
            }
    }
}

/**
 * @brief Switches led state with the help of the keyboard
 * 
 * @details
 */
void keyboard_process(key_selection &selection, size_t &delay_time)
{
    std::uint8_t choice;
    while (true)
    {
        choice = display_menu();

        switch (choice)
        {
        case 1:
            selection = OFF;
            break;
        case 2:
            selection = ON;
            break;
        case 3:
            selection = TOGGLE;
            break;
        case 4:
            std::cout << "\nYou've selected blink.\n";
            std::cout << "Now select delay time between blinks\n";
            std::cout << "Number equals to 100ms.\n";
            std::cout << "Choose between 1-100: ";
            delay_time = get_number(1,100);
            selection = BLINK;
            break;
        default:
            selection = NOTHING;
            break;
        }
    }
}