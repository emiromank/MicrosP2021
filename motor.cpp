#include "mbed.h"

DigitalOut Motor1A(PTA12);
DigitalOut Motor1B(PTA4);
PwmOut Velocidad(PTB0);

DigitalOut Motor2A(PTC10);
DigitalOut Motor2B(PTC11);
PwmOut Velocidad2(PTB1);

Serial bt(PTC4, PTC3); //RDX, TXD
char c;
float v;

Serial pc(USBTX, USBRX);

void motoAdelante();
void motoAtras();
void motoDerecha();
void motoIzquierda();
void motoDetener();




int main() {
    bt.baud(9600);
    pc.printf("Dispositivo conectado\n");
  
  
    while(1) {
    
        Velocidad.write(v);
        Velocidad2.write(v);
        
        c = bt.getc();
        if(c == 'A'){
            pc.printf("Adelante\n");
            motoAdelante();
            
        }
        else if(c == 'R'){
            pc.printf("Atras\n");
            motoAtras();
        }
        else if(c == 'D'){
            pc.printf("Derecha\n");
            motoDerecha();
        }
        else if(c == 'I'){
            pc.printf("Izquierda\n");
            motoIzquierda();
        }
        else if(c == 'P'){
            pc.printf("Stop\n");
            motoDetener();
        }
        else if(VELOCIDAD){
            v=(c+1)/10;   
            pc.printf("V= %f", v);
            Velocidad.write(v);
            Velocidad2.write(v);
        }
    }
}

/**
DigitalOut Motor1A(PTC13);
DigitalOut Motor1B(PTC12);
PwmOut Velocidad */

void motoAdelante(){
    Motor1A=1;
    Motor1B=0;
    
    Motor2A=1;
    Motor2B=0;
    
    }


void motoAtras(){
    Motor1A=0;
    Motor1B=1;
    
    Motor2A=0;
    Motor2B=1;
    }
    
void motoDerecha(){
    Motor1A=0;
    Motor1B=1;
    
    Motor2A=1;
    Motor2B=0;
    
    
    
    
    }
    
void motoIzquierda(){
    Motor1A=1;
    Motor1B=0;
    
    Motor2A=0;
    Motor2B=1;
    
    
    }
    
void motoDetener(){
    Motor1A=0;
    Motor1B=0;
    
    Motor2A=0;
    Motor2B=0;
    }    