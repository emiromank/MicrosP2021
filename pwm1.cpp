#include "mbed.h"

PwmOut servo(PTE20);
DigitalIn gnd(PTC1);
DigitalIn pb2(PTC2);
DigitalOut led(LED1);

DigitalOut led2(LED2);

int main() {
    while(1) {

        if(pb2==0){
            led=1;
            servo=+0.2;
            }
        if (servo>0){
            led2=1;
            servo=0;
            wait(0.2);
        }
        wait(0.2);
        led=0;
        if(servo==1) servo=0;
    }
}
