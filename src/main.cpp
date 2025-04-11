#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Configurar entradas y salidas
void config(void){
    DDRD|=0xF0;//PD4 a PD7 como salidas
    DDRB&=~0x07;//PB0 a PB2 como entrada
    PORTB|=0x07;//pull-up
}
//Cambiar dirección del motor
void direccion(char sentido){
    switch(sentido){
    case 0:
        PORTD&=~0xF0;//apagar motores
        break;
    case 1:
        PORTD&=~0xF0;//apagar motores
        PORTD|=0x50;//PD4 y PD6 en alto
        break;
    case 2:
        PORTD&=~0xF0;//apagar motores
        PORTD|=0xA0;//PD5 y PD7 en alto
        break;
    }
}
void izquierda(char giro1){
    switch(giro1){
    case 0:
        PORTD&=~0xF0;//apagar motores
        break;
    case 1:
        PORTD&=~0xF0;//apagar motores
        PORTD|=0x40;//PD6 en alto
        break;
    case 2:
        PORTD&=~0xF0;//apagar motores
        PORTD|=0x60;//PD5 y PD6 en alto
        break;
    }
}
void derecha(char giro2){
    switch(giro2){
    case 0:
        PORTD&=~0xF0;//apagar motores
        break;
    case 1:
        PORTD&=~0xF0;//apagar motores
        PORTD|=0x80;//PD7 en alto
        break;
    case 2:
        PORTD&=~0xF0;//apagar motores
        PORTD|=0x90;//PD4 y PD7 en alto
        break;
    }
}
int main(void){
    config();
    char sentido=0;//0=stop, 1=adelante y 2=reversa
    char previo=1;//estado previo
    char giro1=0;//0=stop, 1=giro largo izquierda y 2=giro corto izquierda
    char giro1a=1;//estado previo
    char giro2=0;//0=stop, 1=giro largo derecha y 2=giro corto derecha
    char giro2a=1;//estado previo
    direccion(sentido);//establecer valor inicial
    izquierda(giro1);//establecer valor inicial
    derecha(giro2);//establecer valor inicial

    while(1){
        if(!(PINB&0x01)&&previo){//revisa el estado anterior
            _delay_ms(50);
            if(!(PINB&0x01)){
                sentido++;
                if(sentido>2)
                sentido=0;
                direccion(sentido);
                while(!(PINB&0x01));
                _delay_ms(50);
            }
        }
        else if(!(PINB&0x02)&&giro1a){//revisa el estado anterior
            _delay_ms(50);
            if(!(PINB&0x02)){
                giro1++;
                if(giro1>2)
                giro1=0;
                izquierda(giro1);
                while(!(PINB&0x02));
                _delay_ms(50);
            }
        }
        else if(!(PINB&0x04)&&giro2a){//revisa el estado anterior
            _delay_ms(50);
            if(!(PINB&0x04)){
                giro2++;
                if(giro2>2)
                giro2=0;
                derecha(giro2);
                while(!(PINB&0x04));
                _delay_ms(50);
            }
        }
    }
}