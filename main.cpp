#include "header.hpp"

static void led_controll(GPIO led1, GPIO led2, GPIO button, const std::size_t blink_delay);

/* Sets object to extern */


/* Creates object of GPIO class  */
GPIO led1(17, "led1", GPIO_enum::activeSignal::high, 0);
GPIO led2(22, "led2", GPIO_enum::activeSignal::high, 0);
GPIO led3(23, "led3", GPIO_enum::activeSignal::high, 0);
GPIO led4(24, "led4", GPIO_enum::activeSignal::high, 0);

GPIO button1(27, "button1", GPIO_enum::activeSignal::low, GPIO_enum::event::falling);
GPIO button2(25, "button2", GPIO_enum::activeSignal::high, GPIO_enum::event::rising);

/**
 * @authors Jacob Nilsson & Jacob Lundkvist.
 *
 *
 * @brief Construct a multi threaded program. The program consist of two threads that
 * controlls different leds and buttons simultaneously with the help of libgpiod.
 *
 */
int main(void)
{
    std::thread t1(led_controll, led1, led2, button1, 3);
    std::thread t2(led_controll, led3, led4, button2, 5);
    t1.join();
    t2.join();

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
static void led_controll(GPIO led1, GPIO led2, GPIO button, const std::size_t blink_delay)
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
            if (button.read_input())
                enabled = !enabled;
            led1.blink(blink_delay);
            if (button.read_input())
                enabled = !enabled;
            led2.blink(blink_delay);
        }
        else
            continue;
    }
    return;
}

/**
 * @brief  KVAR ATT GÖRA:
 * Implementera aktivt hög/aktivt låg knapptryck.
 * Se möjligheter att implementera class i en vektor utan att anropa destruktor.
 *
 */