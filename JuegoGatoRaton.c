/*
 * File:   JuegoGatoRaton.c
 * Author: Sebastián López, Danny Martinez
 *
 * Created on 21 de septiembre de 2017, 03:32 PM
 */


#include <xc.h>
#include "config.h"
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

int STATIC = 4; //luz encendida que representa al raton
int DINAMIC = 1;  //Luz encendidad durante un segundo que representa al gato

void interrupt isr(void){
        INTCONbits.INTF = 0; //interrupcion
        if(PORTBbits.RB7&&DINAMIC!=128) //verifica que no haya desborade, es decir si llega al led MSB no pase y no genere error
            DINAMIC = DINAMIC*2;    //para avanzar hacia la derecha
        if(PORTBbits.RB7==0&&DINAMIC!=1) //verifica que no haya desborade, es decir si llega al led LSB no pase y no genere error
                DINAMIC = DINAMIC/2;    //para la izquierda
    }
void validar(){ //funcion validar
    if(STATIC==DINAMIC){ //verifica que los 2 leds esten en la misma posicion
            PORTC = STATIC; //el puerto c toma el valor de "DINAMIC"
            PORTDbits.RD0 = 1;  //en el momento que los 2 leds esten en la misma posicion enciende otro led que esta en el pin 0 del puerto D
            __delay_ms(3000);   //enciende el led por 3 segundos
            PORTDbits.RD0 = 0;  //pasados los 3 segundos apague el led
        }
        else
            PORTC = STATIC + DINAMIC;   //de no atraparlo siga con el juego
}
void main(void) {
    TRISC = 0;  //puerto c como salidas
    PORTC = 1;  
    TRISB = 0xFF;   //puerto B como entrada
    ANSEL = 0;      //desactiva entradas analogicas
    ANSELH = 0;
    TRISD = 0;      //puerto D como salidas
    //PORTD = 0;    
    //INTCON = 10001000; //interrupciones de RB4 y RB7
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;        //banderas de interrupcion
    //INTCONbits.RBIE = 1;
    //INTCONbits.RBIF = 0;
    INTCONbits.INTF = 0;
    int aux;    //variables auxiliar
    int aux2=0; //variables auxiliar2
    while (1){
        do
        {STATIC = rand()%7; //ejecuta la funcion random
        STATIC = pow(2, STATIC); //PORTC como 2 a la potencia(random)
        }while(STATIC == DINAMIC);
        aux = 0;
        while(aux<5){   // hace que el led que representa al raton este con una luz intermitente
            validar(); 
            __delay_ms(50);
            aux2 = STATIC;
            STATIC = 0;
            validar();
            __delay_ms(50);
            STATIC = aux2;
            aux++;
        }   
    }   
}



       