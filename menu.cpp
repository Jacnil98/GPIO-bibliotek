/* Include directives */
#include "header.hpp"

/**
 * @brief @brief Displays the interface to the user.
 * 
 * @return uint8_t - grabs input from user in terminal.
 */
uint8_t display_menu()
{
    std::cout << "\n\n====================================\n\n";
    std::cout << "\t  LED CONTROL MENU\n\n";
    std::cout << "====================================\n";
    std::cout << "1. LEDS OFF\n";
    std::cout << "2. LEDS ON\n";
    std::cout << "3. LEDS TOGGLE\n";
    std::cout << "4. LEDS BLINK\n\n";
    std::cout << "Enter your choice (1-4): ";

return static_cast<uint8_t>(get_number(1,4));
}

/**
 * @brief Get the number object and sorts out
 * so that the keyboard input is valid
 * 
 * @param min_val Defines max min value
 * @param max_val Defines the max value
 */
uint16_t get_number(uint16_t min_val, uint16_t max_val)
{
    uint16_t val = 0;
    while (true)
    {
        std::cin >> val;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "\nIncorrect input\nGive it another go: ";
        }
        else if (val < min_val || val > max_val)
        {
            std::cout << "\nValue not in range\nGive it another go: ";
        }
        else
        {
            break;
        }
    }
    return val;
}