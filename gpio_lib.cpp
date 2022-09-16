/* Include directives */
#include "gpio_lib.hpp"

static gpiod_line *gpiod_line_new(const std::uint8_t pin);

/**
 * @brief Creates a new instance of the class GPIO.
 *
 * @param pin GPIO pin.
 * @param alias same as object name.
 */
static gpiod_line *gpiod_line_new(const std::uint8_t pin)
{
    static gpiod_chip *chip0 = nullptr;
    if (!chip0)
    {
        chip0 = gpiod_chip_open("/dev/gpiochip0");
    }
    gpiod_line *self = gpiod_chip_get_line(chip0, pin);
    return self;
}

/**
 * @brief Construct a new GPIO::GPIO object of either input or output, first IO_direction and PIN is required.
 * Default values are applied if constructor is not filled out.
 * 
 * @param IO_direction (both) GPIO_enum for selecting input/output.
 * @param pin (both) GPIO pin on raspberry 4.
 * @param alias (both) Mame for object as a string.
 * @param active_signal (both) GPIO_enum, default high, set to low to invert function of pin.
 * @param event_detection (input) GPIO_enum rising default, else falling or both
 * @param default_val (output) boolean, start value for output, on = 1.
 */
GPIO::GPIO(const GPIO_enum::direction IO_direction, const std::uint8_t pin, const char *alias,
           GPIO_enum::activeSignal active_signal, GPIO_enum::event event_detection, bool default_val)
{
    this->line = gpiod_line_new(pin);
    if (!this->line)
    {
        std::cerr << "ERROR, Line for pin " << std::to_string(pin) << "is null\n";
        return;
    }
    /* Configure output */
    if (IO_direction == GPIO_enum::direction::output)
    {
        if (active_signal == GPIO_enum::activeSignal::high)
        {
            gpiod_line_request_output(this->line, alias, default_val);
            std::cout << "Output is set to active high on pin: " << std::to_string(pin) << std::endl;
        }
        else
        {
            gpiod_line_request_output_flags(this->line, alias, GPIOD_LINE_REQUEST_FLAG_ACTIVE_LOW, default_val);
            std::cout << "Output is set to active low on pin: " << std::to_string(pin) << std::endl;
        }
    }
    /* Configure input */
    else
    {
        this->event_detection = event_detection;
        if (active_signal == GPIO_enum::activeSignal::high)
        {
            gpiod_line_request_input(this->line, alias);
            std::cout << "Input is set to active high on pin: " << std::to_string(pin) << std::endl;
        }
        else
        {
            gpiod_line_request_input_flags(this->line, alias, GPIOD_LINE_REQUEST_FLAG_ACTIVE_LOW);
            std::cout << "Input is set to active low on pin: " << std::to_string(pin) << std::endl;
        }
    }

    return;
}

/**
 * @brief Detectes if a input changed state.
 *
 */
bool GPIO::read_input()
{
    const auto old_value = this->last_value;
    const auto current_value = gpiod_line_get_value(this->line);
    this->last_value = current_value;
    if (current_value == old_value)
        return false;
    usleep(50000);
    if (this->event_detection == GPIO_enum::event::rising && current_value && !old_value)
    {
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
 * @brief Blinks the output.
 *
 * @param blink_speed Wished time between blinks in ms.
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
 * @brief Turns on output.
 *
 */
void GPIO::on()
{

    gpiod_line_set_value(this->line, 1);
    return;
}

/**
 * @brief Turns off output.
 *
 */
void GPIO::off()
{
    gpiod_line_set_value(this->line, 0);
    return;
}

/**
 * @brief Toggles the output.
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
