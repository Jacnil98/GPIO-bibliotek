#include "gpio_lib.hpp"
extern GPIO led1;
GPIO led1(17, "led1");
int main(void)
{
    
    //GPIO::GPIO(const std::uint8_t pin, const char* alias = nullptr)
   // led1 = GPIO(17, "led1");
    //led1.on();
    /*
    if (!led1.line)
        printf("No line in main");
*/
    while (true)
    {
       led1.blink(2);
     //  led1.blink(2);
    }

    return 0;
}