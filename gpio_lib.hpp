#ifndef GPIOD_LIB_HPP_
#define GPIOD_LIB_HPP_

/* Inkluderingsdirektiv: */
#include <iostream>
#include <thread>
#include <cstdint>

#include <gpiod.h>
//#include <unistd.h>

enum class GPIO_event_detection
{
   RISING,
   FALLING,
   BOTH
};

enum class GPIO_direction
{
   in,
   out
};

class GPIO
{
protected:
   struct gpiod_line *line = nullptr; /* GPIO-linjepekare. */
   GPIO_direction direction;

public: /* Medlemsfunktioner: */
   GPIO(void) {}
   ~GPIO(void) { gpiod_line_release(this->line); }
   GPIO(const std::uint8_t pin, const char *alias); // Konstruktor för output
   GPIO(const std::uint8_t pin, const GPIO_event_detection event_detection);
   void event_detected(GPIO &self,)
};

#endif /* GPIOD_LIB_HPP_ */