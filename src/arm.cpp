#include "arm.h"

servo_t::servo_t(const int pin): pin(pin){
    std::cout << "Pin has been set to Pin:" << pin << std::endl;
}


int main(){
    int text;
    std::cout<<"enter pin number:";
    std::cin>>text;

    servo_t servo(text);

}