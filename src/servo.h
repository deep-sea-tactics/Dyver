#ifndef H_SERVO
#define H_SERVO

#include <iostream>
#include <cstdint>

class servo_t 
{
    /*
    1500 µs is neutral position
    1530-1900 µs is open
    1470-1100 µs is closed
    needs range of -1 to 1 for values
    */

private:
    uint8_t m_pin{0};

public:
    servo_t(const uint8_t pin)
    {
        m_pin = pin;
        std::cout << "Pin has been set to Pin:" << pin << std::endl;
    }

    auto get_pin() -> uint8_t
    {
        return m_pin;
    }
};

#endif