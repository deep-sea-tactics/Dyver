#ifndef H_SERVO
#define H_SERVO
#include <iostream>

class servo_t {
    /** 1500 µs is neutral position
        * 1530-1900 µs is open
        * 1470-1100 µs is closed
        needs range of -1 to 1 for values
        */
   private:
    int pin;

    public:
    servo_t(const int pin);
    

};


#endif