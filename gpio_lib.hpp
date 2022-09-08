#ifndef GPIOD_LIB_HPP_
#define GPIOD_LIB_HPP_

/* Inkluderingsdirektiv: */
#include <iostream>
#include <thread>
#include <cstdint>

#include <gpiod.hpp>
//#include <unistd.h>

enum class GPIO_event
{
   rising,
   falling,
   both
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
   bool last_value;
   const GPIO_event event_detection;

public: /* Medlemsfunktioner: */
   GPIO(void) {}
   ~GPIO(void) { gpiod_line_release(this->line); }
   GPIO(const std::uint8_t pin, const char *alias); // Konstruktor för output
   GPIO(const std::uint8_t pin, const char *alias, const GPIO_event event_detection);
   bool event_detected();
   void toggle();
   void blink(const uint16_t blink_speed);
   void on();
   void off();
   void toggle();
};

#endif /* GPIOD_LIB_HPP_ */