#ifndef GPIOD_LIB_HPP_
#define GPIOD_LIB_HPP_

/* Include directives */
#include <iostream>
#include <thread>
#include <cstdint>
#include <gpiod.h>
#include <unistd.h>

/**
 * @brief 
 * 
 */
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

/**
 * @brief GPIO class defintion.
 *
 * @param direction The direction of the Pin.
 * @param event_detection Edge detection defintion.
 */
class GPIO
{
protected:
   GPIO_enum::direction direction;
   GPIO_enum::event event_detection;
   uint8_t last_value;
public:                               /* Medlemsfunktioner: */
   struct gpiod_line *line = nullptr; /* GPIO-linjepekare. */
   GPIO(void) {}
   ~GPIO(void) /* Destructor */
   {
      std::cout << "Destructor called for" << this->line;
      gpiod_line_release(this->line);
   }
   GPIO(const std::uint8_t pin, const char *alias, GPIO_enum::activeSignal active_signal, bool default_val); /* Constructor for output */
   GPIO(const std::uint8_t pin, const char *alias, GPIO_enum::activeSignal active_signal, const GPIO_enum::event event_detection); /* Constructor for input */
   bool read_input();
   void blink(const uint16_t blink_speed);
   void on();
   void off();
   void toggle();
};

#endif /* GPIOD_LIB_HPP_ */