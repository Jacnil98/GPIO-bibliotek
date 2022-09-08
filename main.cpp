#include "gpio_lib.hpp"

int main(void)
{
    GPIO led1;
    //GPIO::GPIO(const std::uint8_t pin, const char* alias = nullptr)
    led1 = GPIO(17, "led1");
    led1.on();
    if (!led1.line)
        printf("No line in main");

    while (true)
    {
       // led1.blink(2);
       led1.blink(2);
    }
    return 0;
}