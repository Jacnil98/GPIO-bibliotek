#include "header.hpp"

static void led_controll(std::vector<GPIO> leds, GPIO button, const std::size_t blink_delay);

/* Sets object to extern */
//GPIO led1, led2, led3, led4, button1, button2;

/* Creates object of GPIO class  */
GPIO led1(GPIO_enum::direction::output, 17, "led1", GPIO_enum::activeSignal::high, GPIO_enum::event::falling, 0);
GPIO led2(GPIO_enum::direction::output, 22, "led2", GPIO_enum::activeSignal::high, GPIO_enum::event::falling, 0);
GPIO led3(GPIO_enum::direction::output, 23, "led3", GPIO_enum::activeSignal::high, GPIO_enum::event::falling, 0);
GPIO led4(GPIO_enum::direction::output, 24, "led4", GPIO_enum::activeSignal::high, GPIO_enum::event::falling, 0);

GPIO button1(GPIO_enum::direction::input, 27, "button1", GPIO_enum::activeSignal::low, GPIO_enum::event::falling, 0);
GPIO button2(GPIO_enum::direction::input, 25, "button2", GPIO_enum::activeSignal::high, GPIO_enum::event::rising, 0);

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
 * 
 * Se möjligheter att implementera class i en vektor utan att anropa destruktor.
 * 09-12 .. Anropar inte destruktor men lyckas inte komma åt indexering av vector och sedan tända led
 * med hjälp av leds[i].blink(delay_time);
 ** --------------------------------------------------------------------------
 */
int main(void)
{
    std::vector<GPIO> leds1 =
   {
      std::ref(led1),
      std::ref(led2)
   };
    std::thread t1(&led_controll, std::ref(leds1), std::ref(button1), 1);
    //std::thread t2(&led_controll, std::ref(led3), std::ref(led4), std::ref(button2), 5);
    t1.join();
    //t2.join();

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
static void led_controll(std::vector<GPIO> leds, GPIO button, const std::size_t blink_delay)
{
    static bool enabled = 0;
    while (true)
    {
        if (button.read_input())
        {
            enabled = !enabled;
        }
        if (enabled)
        {
            for (uint8_t i = 0; i < 2; i++)
            {
                if (button.read_input())
                enabled = !enabled;
                leds[i].blink(blink_delay);
                if (button.read_input())
                enabled = !enabled;
                leds[i].blink(blink_delay);
            }
            
        }
    }
    return;
}

/*  std::ref(led1), std::ref(led2) */
/* if (button.read_input())  GAMLA FUNKTION AV DEN OVAN
        enabled = !enabled;
    leds.blink(blink_delay);
    if (button.read_input())
        enabled = !enabled;
    led2.blink(blink_delay); */ 

