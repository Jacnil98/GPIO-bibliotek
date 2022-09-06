#include "gpio_lib.hpp"

static gpiod_line* gpiod_line_new(const std::uint8_t pin);

GPIO::GPIO(const std::uint8_t pin, const char* alias, const std::size_t blink_speed_ms)
{
    this->line = gpiod_line_new(pin);
    this->blink_speed_ms = blink_speed_ms;
    gpiod_line_request_output(this->line, alias, 0);
    return;
}

GPIO::GPIO(const std::uint8_t pin, const GPIO_event_detection event_detection)
{
    this->line = gpiod_line_new(pin);
    this->event_detection = event_detection;
    return;
}

static gpiod_line* gpiod_line_new(const std::uint8_t pin)
{
    statuc gpiod_chip* chip0 = nullptr;
    if (!chip0) 
    {
        chip0 = gpiod_chip_open("/dev/gpiodchip0");
    }
    gpiod_line* self = gpiod_chip_get_line(chip0, pin);
    return self;
}

void event_detected()