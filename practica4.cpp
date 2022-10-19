#include "mbed.h"
#include "TextLCD.h"

TextLCD lcd(PTB0,PTB1,PTB2,PTE29,PTE3,PTC7,TextLCD::LCD16x2);

//PB's
InterruptIn pb1(PTA4); 
InterruptIn pb2(PTA5);

AnalogIn sens(PTC1);

float tempActualC=0.0;
char grados='C';

/**
    *DEBOUNCE https://loossquis1958.blogspot.com/2022/04/how-to-debounce-button-hardware.html
    * https://easierwithpractice.com/what-is-debouncing-in-push-button/
    * ANALOG IN https://os.mbed.com/handbook/AnalogIn
    */
    
 void imprimirCoF();
 void imprimirTemp(float ss);   
 void pressPB1();
 void pressPB2();
 void sondaTemp();
     
int main() {
    pb1.rise(&pressPB1);
    pb2.rise(&pressPB2);
    
    while(1) {
    sondaTemp();
    }
}

void sondaTemp(){
    tempActualC = (sens*100)/3.3;
    return;
    }

void pressPB1(){
    float ss;
    ss=tempActualC;
    
    if (grados=='C'){
        imprimirTemp(ss);
        }
    else if(grados=='F'){
        ss=32+(9*ss/5);
        imprimirTemp(ss);
        }
        
    return;
    }
    

void pressPB2(){
        
    if (grados=='C'){
        grados='F';
        }
    else if(grados=='F'){
        grados='C';
        }
        
    lcd.cls();
    return;
    }
    
 void imprimirTemp(float ss){
    lcd.cls();     
    lcd.locate(1,1);
    lcd.printf("TEMP=");
     
     if(ss<=0.0){
        lcd.locate(7,1);
        lcd.printf("< 0");
         }
     if(ss>=99.9){
        lcd.locate(6,1);
        lcd.printf(">99.9");
         }
        else{
        lcd.locate(7,1);
        lcd.printf("%.1f",ss);
     }
     
     imprimirCoF();
     return;
     }
     
void imprimirCoF(){
    lcd.locate(12,1);
    lcd.printf("%c", grados);
    
    return;
    }