#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Configurar entradas y salidas
void config(void){
    DDRD|=0xF0;//PD4 a PD7 como salidas
    DDRB&=~0x70;//PB4 a PB6 como entrada
    PORTB|=0x70;//pull-up
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

int main(void){
    config();
    char sentido=0;//1=adelante, 2=reversa, 0=stop
    char previo=1;//estado previo
    direccion(sentido);//establecer dirección inicial

    while(1){
        if(!(PINB&0x10)&&previo){
            _delay_ms(50);
            if(!(PINB&0x10)){
                sentido++;
                if(sentido>2)
                    sentido=0;
                direccion(sentido);
                while (!(PINB&0x10));
                _delay_ms(50);
            }
        } 
    }
}