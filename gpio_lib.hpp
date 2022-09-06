#ifndef GPIOD_LIB_HPP_
#define GPIOD_LIB_HPP_

/* Inkluderingsdirektiv: */
#include <iostream>
#include <thread>
#include <cstdint>

#include <gpiod.h>
//#include <unistd.h> 


enum class GPIO_event_detection { RISING, FALLING, BOTH};
enum class GPIO_direction { in, out }

class GPIO
{
   /* Medlemmar: */
   gpiod_line* line = nullptr; /* GPIO-linjepekare. */
   GPIO_direction;

   /* Medlemsfunktioner: */
   gpiod_thread(void) { }
   ~gpiod_thread(void) { gpiod_line_release(this->line); }
   gpiod_thread(const std::uint8_t pin, const char* alias, const std::size_t blink_speed_ms); // Konstruktor för output
   gpiod_thread(const std::uint8_t pin, const GPIO_event_detection event_detection);
   void run(void);
};

#endif /* GPIOD_LIB_HPP_ */