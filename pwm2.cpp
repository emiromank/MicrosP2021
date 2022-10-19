#include "mbed.h"
#include <stdio.h>
#include <math.h>

PwmOut servo(PTB0);
AnalogIn pot(PTC1);
Ticker print;
float x, voltaje_pot;

int main() {
    servo.period_ms(20);
    while(1) {
        x = pot.read();
        voltaje_pot = x;
        x = (x*2 + 0.2) * 500;
        servo.pulsewidth_us(x);
    }
}
