#include "mbed.h"

Serial pc(USBTX,USBRX);
PwmOut led(PTC2);

float brightness = 3.0;

int main() {
    pc.printf("Presiona u para subir el brillo, d para bajarlo\n");
    led = 1;
    
    while(1) {
        char c = pc.getc();
        if((c=='u') && (brightness<0.5)){
            brightness += 0.1;
            led = brightness;
            printf("u\n");}
            
        if((c=='d') && (brightness>0.0)){
            brightness -= 0.1;
            led = brightness;
            printf("d\n");}
    }
}
