//Autor: Gabriel Silva Marcatto
//    Rodrigo Almeida
#include "MKL05Z4.h"
#define bitSet(arg,bit) ((arg) |= (1<<bit))
#define bitClr(arg,bit) ((arg) &= ~(1<<bit))
static int i = 0;
void main(void){
//-------------------------Config para boot minimo da placa -------------------------------------------------------
   MCG_BASE_PTR ->C4 |= MCG_C4_DMX32_MASK;
   SIM_BASE_PTR ->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK);
   PORTB_BASE_PTR-> PCR[5] = PORT_PCR_MUX(1);
   SIM_BASE_PTR -> COPC &=~ SIM_COPC_COPT_MASK;
//-----------------------------------------------------------------------------------------------------------
   PORTB_BASE_PTR ->PCR[10] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
   bitSet(PTB_BASE_PTR ->PDDR, 10);
   for(;;){
       bitSet(PTB_BASE_PTR ->PDOR, 10);
       for(float i = 0; i<100000; i++);
       bitClr(PTB_BASE_PTR ->PDOR, 10);
       for(float i = 0; i<100000; i++);
   }
}
