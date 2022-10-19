#include "mbed.h"

PwmOut servo(PTB2);
float offset=0.00;
float ofViejo=0.003;
float buffer;

Serial pc(USBTX, USBRX);

int main() {
    servo.period(0.050);
    
    while(1) {
        pc.printf("%f", offset);         
        servo.pulsewidth(0.001+offset);
        wait(2);
        
        buffer=offset;
        offset=ofViejo;
        ofViejo=buffer;
    }
}
