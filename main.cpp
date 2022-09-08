#include "gpiod_lib.hpp"

int main(void)
{
    //GPIO::GPIO(const std::uint8_t pin, const char* alias = nullptr)
    GPIO::led1(17, "led1");
    while (true)
    {
        led1.blink(2);
    }
    return 0;
}