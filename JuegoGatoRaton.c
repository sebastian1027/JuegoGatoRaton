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
int STATIC = 4;
int DINAMIC = 1;

void interrupt isr(void){
        INTCONbits.INTF = 0;
        if(PORTBbits.RB7&&DINAMIC!=128)
            DINAMIC = DINAMIC*2;
        if(PORTBbits.RB7==0&&DINAMIC!=1)
                DINAMIC = DINAMIC/2;
    }
void validar(){
    if(STATIC==DINAMIC){
            PORTC = STATIC;
            PORTDbits.RD0 = 1;
            __delay_ms(3000);
            PORTDbits.RD0 = 0;
        }
        else
            PORTC = STATIC + DINAMIC;
}
void main(void) {
    TRISC = 0;
    PORTC = 1;
    TRISB = 0xFF;
    ANSEL = 0;
    ANSELH = 0;
    TRISD = 0;
    PORTD = 0;    
    //INTCON = 10001000; //interrupciones de RB4 y RB7
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;
    //INTCONbits.RBIE = 1;
    //INTCONbits.RBIF = 0;
    INTCONbits.INTF = 0;
    int aux;
    int aux2=0;
    while (1){
        do
        {STATIC = rand()%7; 
        STATIC = pow(2, STATIC); //PORTC como 2 a la potencia(random)
        }while(STATIC == DINAMIC);
        aux = 0;
        while(aux<5){
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



       