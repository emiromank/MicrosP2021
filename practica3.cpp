#include "mbed.h"

DigitalOut   pt2[7]={PTB0,PTB1,PTB2,PTE29,PTE3,PTC7,PTC0};
DigitalOut   pt1[7]={PTC10,PTC11,PTC12,PTC17,PTA16,PTA17,PTE31};

DigitalIn pb1(PTA12);
DigitalIn pb2(PTA4);
DigitalIn pb3(PTA5);

//DEBUG
Serial pc(USBTX,USBRX);


int cont=0;
int opcion=1;
float velocidad=1;

int seg[16][7]={
   //g,b,d,f,e,a,c
    {0,1,1,1,1,1,1}, //0
    {0,1,0,0,0,0,1}, //1
    {1,1,1,0,1,1,0}, //2
    {1,1,1,0,0,1,1}, //3
    {1,1,0,1,0,0,1}, //4
    {1,0,1,1,0,1,1}, //5
    {1,0,1,1,1,1,1}, //6    
    {0,1,0,0,0,1,1}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,1,0,1,1}, //9
    {1,1,0,1,1,1,1}, //A
    {1,0,1,1,1,0,1}, //B
    {0,0,1,1,1,1,0}, //C
    {1,1,1,0,1,0,1}, //D
    {1,0,1,1,1,1,0}, //E
    {1,0,0,1,1,1,0}  //F
};

void print(){
    int i,j;
    int res = cont%256;
    int dec = (res-(res%16))/16;
    int uni = res%16;
    
    for(i=0;i<=7;i++){
        pt1[i]=seg[dec][i];
        }
    for(j=0;j<=7;j++){
        pt2[j]=seg[uni][j];
    }
    return;
}
 int validar(){
    if((cont>255)==1){
        return 0;
    }
    if(cont<0){
         return 255;
    }
 return cont;   
 }
 
void pressPB1(){
    opcion=!opcion;
    return;
}

float pressPB2(){
    if (velocidad>0.4)return velocidad-0.2;
    return 0.2;
    }
    
float pressPB3(){
    if (velocidad<1.8)return velocidad+0.2;
    return 2;
    }

void contar(int a, int b, int c){   
        if(a==0){
            pressPB1();
            }
       if(b==0){
        velocidad=pressPB2();
           }
        
        if(c==0){
        velocidad=pressPB3();
        }
        
        
       
        if (opcion==1){

            cont++;
            cont=validar();
            print();
            pc.printf("%x\n",cont);

        }
        if (opcion==0){
            
            cont--;
            cont=validar();
            print();
            pc.printf("%x\n",cont);

        } 
        
    return;
}

int main()
{
    int a,b,c;
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    
    while(1){
        a=pb1;
        b=pb2;
        c=pb3;
         
        contar(a,b,c);
        
        wait(velocidad);
        
        }
    }



