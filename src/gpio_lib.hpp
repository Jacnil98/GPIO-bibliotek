#ifndef GPIOD_LIB_HPP_
#define GPIOD_LIB_HPP_

/* Include directives */
#include <iostream>
#include <thread>
#include <cstdint>
#include <gpiod.h>
#include <unistd.h>

/**
 * @brief enumerations for gpio_lib
 * @param event rising, falling, both edges of input event.
 * @param direction input or output component.
 * @param activeSignal active_high or active_low
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
      input,
      output
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
 * @param last_value (output) Used in event detection.
 * @param value (output) Used for toggling, if event is detected.
 */
class GPIO
{
private:
   struct gpiod_line *line = nullptr;
   GPIO_enum::direction direction = GPIO_enum::direction::output;
   GPIO_enum::event event_detection = GPIO_enum::event::rising;
   uint8_t last_value = 0;

public:
   bool value = 0; 
   GPIO(void) {}
   GPIO(const GPIO_enum::direction IO_direction, const std::uint8_t pin, const char *alias = nullptr,
        GPIO_enum::activeSignal active_signal = GPIO_enum::activeSignal::high, 
        const GPIO_enum::event event_detection = GPIO_enum::event::rising, bool default_val = 0);
   ~GPIO(void)
   {
      std::cout << "Destructor called for" << this->line;
      gpiod_line_release(this->line);
   }

   bool read();
   void blink(const uint16_t blink_speed);
   void on();
   void off();
   void toggle();
};

#endif /* GPIOD_LIB_HPP_ */