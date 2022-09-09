#ifndef GPIOD_LIB_HPP_
#define GPIOD_LIB_HPP_

/* Inkluderingsdirektiv: */
#include <iostream>
#include <thread>
#include <cstdint>
#include <gpiod.h>
#include <unistd.h>

namespace GPIO_enum
{
   enum class event
   {
      rising,
      falling,
      both
   };

   enum class direction
   {
      in,
      out
   };

   enum class activeSignal
   {
      low,
      high
   };
};

class GPIO
{
protected:   

public:                               /* Medlemsfunktioner: */
   struct gpiod_line *line = nullptr; /* GPIO-linjepekare. */
   GPIO_enum::direction direction;
   uint8_t last_value;
   //bool enabled;
   GPIO_enum::event event_detection;

   GPIO(void) {}
   ~GPIO(void)
   {
      std::cout << "Destructor called\n";
      gpiod_line_release(this->line);
   }
   GPIO(const std::uint8_t pin, const char *alias); // Konstruktor för output
   GPIO(const std::uint8_t pin, const char *alias, const GPIO_enum::event event_detection);
   bool event_detected();
   void blink(const uint16_t blink_speed);
   void on();
   void off();
   void toggle();
};

#endif /* GPIOD_LIB_HPP_ */