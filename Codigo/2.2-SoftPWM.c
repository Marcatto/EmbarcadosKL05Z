//Autor : Gabriel Silva Marcatto
// e Rodrigo Almeida
 
#include "MKL05Z4.h"
 
#define LigaR()    (PTB_BASE_PTR->PDDR |= 1 << 8)
#define DesligaR() (PTB_BASE_PTR->PDDR &= ~(1 << 8))
#define LigaG()    (PTB_BASE_PTR->PDDR |= 1 << 9)
#define DesligaG() (PTB_BASE_PTR->PDDR &= ~(1 << 9))
#define LigaB()    (PTB_BASE_PTR->PDDR |= 1 << 10)
#define DesligaB() (PTB_BASE_PTR->PDDR &= ~(1 << 10))
 
void main(void) {
	//-------------------------Básico para fazer a placa funcionar------------------------------------------------------------------------
	SIM_BASE_PTR->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK); //init clock das portas
	MCG_BASE_PTR->C4 |= 0x80;   //configura para usar clock interno em 24MHz
	PORTB_PCR(5) = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);  //portb 5, remover o NMI
	//--------------------------------------------------------------------------------------------------------------------------------------
	//config R8 G9 B10
	PORTB_BASE_PTR->PCR[8] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK); &nbsp;&nbsp; //configura PortB 8 como Output
	PORTB_BASE_PTR->PCR[9] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK); &nbsp;&nbsp; //configura PortB 9 como Output
	PORTB_BASE_PTR->PCR[10] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK); &nbsp; //configura PortB 10 como Output
 
	int valorR = 0;
	int valorG = 0;
	int valorB = 0;
 
	int tempo = 0;
	int valor= 0;
	int cor=1;
	for (;;){
		LigaR();
		LigaG();
		LigaB();
 
		//liga g e b
		for (int i = 0; i < 256; i++){
			if (i > valorR){
				DesligaR();
			}
			if (i > valorG){
				DesligaG();
			}
			if (i > valorB){
				DesligaB();
			}
		}
		tempo++;
 
		if (tempo >= 10){
			//criando a rampa
			valor++;
			if (valor == 255){
				valor = 0;
				//rampa no maximo, troca a cor
				cor++;
				if (cor>0b111){
					cor = 0b1;
				}
			}
 
			//qual cor  acompanha a rampa;
			if (cor & 0b001){
				valorR = valor;
			}else{
				valorR = 0;
			}
			if (cor & 0b010){
				valorG = valor;
			}else{
				valorG = 0;
			}
			if (cor & 0b100){
				valorB = valor;
			}else{
				valorB = 0;
			}
			tempo = 0;
		}
	}
}