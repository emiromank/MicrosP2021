#include "mbed.h"
#include "WS2812.h"
#include "PixelArray.h"
#include "HCSR04.h" 
 
#define WS2812_BUF 48
#define NUM_COLORS 3
#define NUM_LEDS_PER_COLOR 16
#define VELOCIDAD "c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'||c=='0'"

//Timer
Timer t;

//BT y motores
DigitalOut Motor1A(PTA12);
DigitalOut Motor1B(PTA4);
PwmOut Velocidad(PTB0);

DigitalOut Motor2A(PTC10);
DigitalOut Motor2B(PTC11);
PwmOut Velocidad2(PTB1);

Serial bt(PTC4, PTC3); //RDX, TXD
char c;
int v;
float vel;

//Rueda LED y Ultrasonico
WS2812 ws(PTB3, WS2812_BUF, 0, 5, 5, 0);
PixelArray px(WS2812_BUF);
HCSR04 sensor(PTC8,PTC9);
Ticker proximidad;
float distancia;

//Matriz LED
SPI spi(PTD2, PTD3, PTD1); // MOSI, MISO, SCLK
DigitalOut cs(PTC2); 

const unsigned char numeros[9][8]= {
    {0x0, 0x18, 0x28, 0x8, 0x8, 0x8, 0x3e, 0x0}, //1
    {0x0, 0x18, 0x24, 0x44, 0x18, 0x20, 0x7e, 0x0}, //2
    {0x0, 0x38, 0x44, 0x1c, 0x4, 0x4, 0x78, 0x0}, //3
    {0x0, 0x24, 0x24, 0x24, 0x1c, 0x4, 0x4, 0x0}, //4
    {0x0, 0x3c, 0x20, 0x18, 0x4, 0x4, 0x38, 0x0}, //5
    {0x0, 0xc, 0x10, 0x20, 0x3c, 0x24, 0x38, 0x0}, //6
    {0x0, 0x3c, 0x4, 0x8, 0x8, 0x10, 0x10, 0x0}, //7
    {0x0, 0x18, 0x24, 0x24, 0x18, 0x24, 0x24, 0x18}, //8
    {0x0, 0x3c, 0x24, 0x3c, 0x4, 0x4, 0x4, 0x0} //9
};

Serial pc(USBTX, USBRX); 

void sensorProximidad();
void motoAdelante();
void motoAtras();
void motoDerecha();
void motoIzquierda();
void motoDetener();
void pala();
void SPI_Write2(unsigned char MSB, unsigned char LSB);
void Init_MAX7219();
void imprimirMatriz();

int main() {
    
    //Inicializar Matriz
    cs = 1;                         
    spi.format(8,0);                
    spi.frequency(1000000);         
    Init_MAX7219();                 

    //Inicializar Rueda LED y Ultrasonico
    HCSR04 sensor(PTC8,PTC9);
    int colorbuf[NUM_COLORS] = {0x002f00,0x2f0000,0x2f2f00};
    for (int i = 0; i < WS2812_BUF; i++) {
        px.Set(i, colorbuf[(i / NUM_LEDS_PER_COLOR) % NUM_COLORS]);
        px.SetI(i%WS2812_BUF, 0xf+(0xf*(i%NUM_LEDS_PER_COLOR)));
    }
    
    //Inicializar BT
    bt.baud(9600);
    pc.printf("Dispositivo conectado\n");

    t.start(); 
     
    while(1) {
        sensorProximidad();
        
        Velocidad.write(vel);
        Velocidad2.write(vel);
        
        c = bt.getc();
        pc.printf("  Entro %c\n\n", c); 
        if(c == 'A'){
            pc.printf("Adelante\n");
            motoAdelante();
            t.stop();
            pc.printf("\nTiempo desde el ultimo cambio de direccion: %.2f",t.read());
             t.reset();
             t.start();
        }
        else if(c == 'R'){
            pc.printf("\nAtras\n");
            motoAtras();
            t.stop();
            pc.printf("Tiempo desde el ultimo cambio de direccion: %.2f",t.read());
             t.reset();
             t.start();
                    }
        else if(c == 'D'){
            pc.printf("\nDerecha\n");
            motoDerecha();
            t.stop();
            pc.printf("Tiempo desde el ultimo cambio de direccion: %.2f",t.read());
             t.reset();
             t.start();
        }
        else if(c == 'I'){
            pc.printf("\nIzquierda\n");
            motoIzquierda();
            t.stop();
            pc.printf("  Tiempo desde el ultimo cambio de direccion: %.2f",t.read());
             t.reset();
             t.start();
        }
        else if(c == 'P'){
            pc.printf("\nStop\n");
            motoDetener();
            t.stop();
            pc.printf("Tiempo desde el ultimo cambio de direccion: %.2f",t.read());
             t.reset();
             t.start();
        }
        else if(VELOCIDAD){
            v=atoi(&c);
            vel=((v+1)*0.10);   
            imprimirMatriz();
            Velocidad.write(vel);
            Velocidad2.write(vel);
        }
    }

}

void sensorProximidad(){
    int LED;
    
    distancia=sensor.distance(CM);
    distancia=distancia/4.68;
    LED=distancia+16;
        if (LED>48) LED=48;
        if (LED<16) LED=16;
    //pc.printf("SENSOR PROX %d  ",LED);
    ws.write_offsets(px.getBuf(),LED,LED,LED);
    }
    
    
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
    
void SPI_Write2(unsigned char MSB, unsigned char LSB)
{
    cs = 0;                        
    spi.write(MSB);                
    spi.write(LSB);
    cs = 1;                         
}

void Init_MAX7219(void)
{
    SPI_Write2(0x09, 0x00);         
    SPI_Write2(0x0A, 0x08);         
    SPI_Write2(0x0B, 0x07);         
    SPI_Write2(0x0C, 0x01);         
    SPI_Write2(0x0F, 0x0F);         
    wait_ms(500);                   
    SPI_Write2(0x01, 0x00);         
    SPI_Write2(0x02, 0x00);         
    SPI_Write2(0x03, 0x00);         
    SPI_Write2(0x04, 0x00);         
    SPI_Write2(0x05, 0x00);         
    SPI_Write2(0x06, 0x00);         
    SPI_Write2(0x07, 0x00);         
    SPI_Write2(0x08, 0x00);         
    SPI_Write2(0x0F, 0x00);         
    wait_ms(500);                   
}

void imprimirMatriz(){
        for(int i=1; i<9; i++){      // Write first character (8 rows)
            SPI_Write2(i,numeros[v-1][i-1]);          
        }        
}