#include "mbed.h"
#include "HCSR04.h"

//trig 8 echo9

HCSR04 sensor(PTC8,PTC9);
Serial pc(USBTX, USBRX);
int distancia;

int main() {
    while(1) {
        distancia=sensor.distance(CM);
        pc.printf("D=%.2f  \n",distancia);
        wait(0.5);
    }
}
