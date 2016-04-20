//Copyright (c) 2015, Freescale Semiconductor, Inc.
//Autor : Gabriel Silva Marcatto
// e Rodrigo Maximiano Antunes de Almeida 

#include "MKL05Z4.h"
#define bitSet(arg,bit) ((arg) |= (1<<bit))
#define bitClr(arg,bit) ((arg) &= ~(1<<bit))

static int i = 0;

void main(void)
{
//-------------------------Básico para fazer a placa funcionar-------------------------------------------------    SIM_BASE_PTR ->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK);          //init clock das portas
MCG_BASE_PTR ->C4 |= 0x80;                                     //configura para usar clock interno em 24MHz
PORTB_PCR(5) = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);           //portb 5, remover o NMI
//--------------------------------------------------------------------------------------------------------------------------------------
PORTB_BASE_PTR ->PCR[10] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);          bitSet(PTB_BASE_PTR ->PDDR, 10);
for(;;)
 {
bitSet(PTB_BASE_PTR ->PDOR, 10);
for(float i = 0; i<100000; i++);
     bitClr(PTB_BASE_PTR ->PDOR, 10);
for(float i = 0; i<100000; i++);
 }
}
