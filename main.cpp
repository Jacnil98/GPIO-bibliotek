#include "header.hpp"

extern GPIO led1, led2, led3, led4, button1, button2;

GPIO led1(17, "led1");
GPIO led2(22, "led2");
GPIO led3(23, "led3");
GPIO led4(24, "led4");

GPIO button1(27, "button1", GPIO_enum::event::rising);
GPIO button2(25, "button2", GPIO_enum::event::rising);

/**
 * @authors Jacob Nilsson & Jacob Lundkvist. 
 * 
 *
 * @brief 
 * 
 */
int main(void)
{
    std::thread t1(led_controll, led1, led2, button1, 1);
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
 * @details Anslut fyra lysdioder till PIN 17, 22, 23 och 24 samt två tryckknappar till PIN 25 samt 27. Varje tryckknapp skall styra två
 *  lysdioder via var sin tråd, där lysdioderna skall togglas mellan att blinka och vara släckta vid stigande flank på motsvarande
 *  tryckknapp. Varannan knapptryckning börjar alltså lysdioderna blinka, annars hålls de släckta.
 *
 * @return int
 */
static void led_controll(GPIO led1, GPIO led2, GPIO button, const std::size_t blink_delay)
{
    static bool enabled = 0;
    while (true)
    {
        
        if (button.event_detected())
        {
            enabled = !enabled;
            std::cout << enabled;
            std::cout << "\nButton event detected\n";
        }
        if (enabled)
        {
            if (button.event_detected()) 
                enabled = !enabled;
            led1.blink(blink_delay);
            if (button.event_detected()) 
                enabled = !enabled;
            led2.blink(blink_delay);
        }
        else continue;
    }
    return;
}

/** 
 * @brief  KVAR ATT GÖRA:
 * Implementera aktivt hög/aktivt låg knapptryck.
 * Se möjligheter att implementera class i en vektor utan att anropa destruktor.
 *
 */