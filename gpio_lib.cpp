#include "gpio_lib.hpp"

static gpiod_line *gpiod_line_new(const std::uint8_t pin, const GPIO_enum::direction direction, const char *alias);

/**
 * @brief Creates a nre instance of the class GPIO.
 *
 * @param pin
 * @param alias
 */
static gpiod_line *gpiod_line_new(const std::uint8_t pin, const GPIO_enum::direction direction, const char *alias = nullptr)
{
    static gpiod_chip *chip0 = nullptr;
    if (!chip0)
    {
        chip0 = gpiod_chip_open("/dev/gpiochip0");
    }
    gpiod_line *self = gpiod_chip_get_line(chip0, pin);

    if (direction == GPIO_enum::direction::out)
    {
        gpiod_line_request_output(self, alias, 0);
    }
    else
    {
        gpiod_line_request_input(self, alias);
    }

    return self;
}

/**
 * @brief Constructs a new GPIO OUTPUT object.
 *
 * @param pin GPIO pin.
 * @param alias same as object name.
 */
GPIO::GPIO(const std::uint8_t pin, const char *alias = nullptr)
{
    this->line = gpiod_line_new(pin, GPIO_enum::direction::out, alias);

    this->last_value = 0;
    printf("Initialize output\n");
    if (!this->line)
    {
        printf("Line is null\n");
    }

    return;
}

/**
 * @brief Construct a new GPIO input object
 *
 * @param pin
 * @param alias
 * @param event_detection rising edge standard value
 */
GPIO::GPIO(const std::uint8_t pin, const char *alias, const GPIO_enum::event event_detection)
{
    this->line = gpiod_line_new(pin, GPIO_enum::direction::in, alias);
    this->event_detection = event_detection;
    printf("Initialize input\n");
    printf("On pin %d\n\n", pin);
    return;
}

/**
 * @brief Detectes if a input changed state
 *
 * @return true
 * @return false
 */
bool GPIO::event_detected()
{
    const auto old_value = this->last_value;
    const auto current_value = gpiod_line_get_value(this->line);
    this->last_value = current_value;
    if (current_value == old_value) return false;
    usleep(50000);
    // static uint8_t current_value = gpiod_line_get_value(this->line); // Ta reda på current value
    // printf("Button value %d\nCurrent value is: %d\n",gpiod_line_get_value(this->line) ,current_value);
    if (this->event_detection == GPIO_enum::event::rising && current_value && !old_value)
    {
        printf("TRUE\n");
        return true;
    }
    else if (this->event_detection == GPIO_enum::event::falling && !current_value && old_value)
        return true;
    else if (this->event_detection == GPIO_enum::event::both && current_value != old_value)
        return true;
    else
        return false;
}

/**
 * @brief Blinks the output
 *
 * @param blink_speed Wished time between blinks in ms
 */
void GPIO::blink(const uint16_t blink_speed)
{
    uint32_t seconds = blink_speed * 100000;
    this->on();
    usleep(seconds);
    this->off();
    usleep(seconds);
    return;
}

/**
 * @brief Turns on output
 *
 */
void GPIO::on()
{

    gpiod_line_set_value(this->line, 1);
    return;
}

/**
 * @brief Turns off output
 * 
 */
void GPIO::off()
{
    gpiod_line_set_value(this->line, 0);
    return;
}

/**
 * @brief Toggles the output
 *
 */
void GPIO::toggle()
{
    bool current_value = gpiod_line_get_value(this->line);

    if (current_value == 1)
    {
        off();
    }
    else if (current_value == 0)
    {
        on();
    }

    return;
}
