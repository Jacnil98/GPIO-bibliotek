#include "gpio_lib.hpp"

static gpiod_line *gpiod_line_new(const std::uint8_t pin, const GPIO_direction direction, const char *alias);

/**
 * @brief
 *
 * @param pin
 * @param alias
 * @return gpiod_line*
 */
static gpiod_line *gpiod_line_new(const std::uint8_t pin, const GPIO_direction direction, const char *alias = nullptr)
{
    static gpiod_chip *chip0 = nullptr;
    if (!chip0)
    {
        chip0 = gpiod_chip_open("/dev/gpiochip0");
    }
    gpiod_line *self = gpiod_chip_get_line(chip0, pin);

    if (direction == GPIO_direction::out)
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
    this->line = gpiod_line_new(pin, GPIO_direction::out, alias);
    
    this->last_value = 0;
    printf("Initialize output\n");
    if (!this->line)
    {
        printf("Line is null\n");
    }
   
    return;
}

/**
 * @brief Construct a new GPIO::GPIO object
 *
 * @param pin
 * @param alias
 * @param event_detection rising edge standard value
 */
GPIO::GPIO(const std::uint8_t pin, const char *alias, const GPIO_event event_detection = GPIO_event::rising)
{
    this->line = gpiod_line_new(pin, GPIO_direction::in, alias);
    this->event_detection = event_detection;
    //gpiod_line_request_input(this->line, alias);
    printf("Initialize input\n");
    printf("On pin %d\n\n", pin);
    return;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool GPIO::event_detected()
{
    const bool old_value = this->last_value;
    const bool current_value = gpiod_line_get_value(this->line); // Ta reda på current value
    this->last_value = current_value;
    if (this->event_detection == GPIO_event::rising)
    {
        if (current_value && !old_value)
            return true;
        else
            return false;
    }
    else if (this->event_detection == GPIO_event::falling)
    {
        if (!current_value && old_value)
            return true;
        else
            return false;
    }
    else if (this->event_detection == GPIO_event::both)
    {
        if (current_value != old_value)
            return true;
        else
            return false;
    }

    return false;
}

/**
 * @brief
 *
 * @param blink_speed
 */
void GPIO::blink(const uint16_t blink_speed)
{
    uint32_t seconds = blink_speed * 1000000;
    this->on();
    usleep(seconds);
    this->off();
    usleep(seconds);
    printf("Blink mf\n");
    return;
}

/**
 * @brief
 *
 */
void GPIO::on()
{
   
    gpiod_line_set_value(this->line,1);
    
    /*
    if (!this->line)
        printf("NULLPTR in GPIO::ON");
    if(gpiod_line_set_value(this->line, 1) == 0)
    {
        printf("Great succes");
    }
    */
    //printf("%d\n", gpiod_line_set_value(this->line, 1));
    return;
}

void GPIO::off()
{
    gpiod_line_set_value(this->line, 0);
    return;
}

/**
 * @brief
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