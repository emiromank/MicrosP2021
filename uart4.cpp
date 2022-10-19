#include "mbed.h"

Serial pc(USBTX,USBRX);
Serial usrt(PTA2, PTA1);

int count = 1;

int main() {
    pc.printf("%d",count);
    while(1) {
        char str[125] = "";
        sprintf(str,"%d",count);
        if(usrt.writeable()){
            usrt.printf("%s\n",str);
        }
    }
}
