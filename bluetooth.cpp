#include "mbed.h"

#define VELOCIDAD "c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'||c=='0'"


Serial bt(PTC4, PTC3); //RDX, TXD
char c;
float v;

//COSO SPI
SPI spi(PTD2,PTD3,PTD1); //MOSI, MISO, SCLK
DigitalOut cs(PTC2);

char buff[]="Hello World! desde el micro";

Serial pc(USBTX, USBRX);

void mandaSPI(char arduino);

int main() {
    bt.baud(9600);
    cs=1;
    spi.format(8,3);
    spi.frequency(1000000);
    pc.printf("Dispositivo conectado\n");
    
    
    
        
       // c = bt.getc();
        
    c='x';
    cs=0;
    for(int i=0; i<sizeof buff;i++){
        spi.write(buff[i]);
    }
    cs=1;
    pc.printf("Termine de mandar A");
    wait(10);
        /**
    while(1) {    
        if(c == 'A'){
            pc.printf("Adelante\n");
        }
        else if(c == 'R'){
            pc.printf("Atras\n");
        }
        else if(c == 'D'){
            pc.printf("Derecha\n");
        }
        else if(c == 'I'){
            pc.printf("Izquierda\n");
        }
        else if(c == 'P'){
            pc.printf("Stop\n");
        }
        else if(VELOCIDAD){
            v=(c+1)/10;
            pc.printf("%f\n",v);   
        }
        
    }
    */
}

void mandaSPI(char arduino){

    }