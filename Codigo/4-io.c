/*
 * io.c
 *
 *  Created on: Sep 2, 2015
 *      Author: Rodrigo
 */

#include "io.h"

#include "MKL05Z4.h"

/*
 UART	PWM 	GPIO	Interrupt	I2C	SPI		A/D
 A0					PTB8						ADC0_SE11
 A1					PTB9						ADC0_SE10
 A2					PTA8						ADC0_SE3/TSI0_IN1
 A3					PTA0	IRQ_0				ADC0_SE12/CMP0_IN2
 A4					PTA9						ADC0_SE2/TSI0_IN0
 A5		TPM1_CH1	PTB13						ADC0_SE13
 D0	UART0_RX		PTB2	IRQ_10				ADC0_SE4/TSI0_IN2
 D1	UART0_TX		PTB1	IRQ_9				ADC0_SE5/TSI0_IN3/DAC0_OUT
 D2					PTA11	IRQ_13			
 D3		TPM1_CH1	PTB5	IRQ_16				ADC0_SE1
 D4					PTA10	IRQ_12			
 D5		TPM1_CH0	PTA12	IRQ_17			
 D6		TPM0_CH3	PTB6	IRQ_2			
 D7		FTM0_CH2	PTB7	IRQ_3			
 D8		TPM0_CH1	PTB10						ADC0_SE9/TSI0_IN7
 D9		TPM0_CH0	PTB11						ADC0_SE8/TSI0_IN6
 D10	TPM0_CH5	PTA5			SPI0_SS_b	
 D11				PTA7	IRQ_7	SPI0_MOSI	ADC0_SE7/TSI0_IN5
 D12	TPM0_CH4	PTA6			SPI0_MISO	
 D13				PTB0	IRQ_8	SPI0_SCK	ADC0_SE6/TSI0_IN4
 */

void systemInit(void) {
 //init clock das portas
 SIM_BASE_PTR ->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK);
 //configura para usar clock interno em 24MHz
 MCG_BASE_PTR ->C4 |= 0x80;
 //portb 5, remover o NMI
 PORTB_PCR(5) = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
}

void pinMode(int pin, int type) {
	if (type == OUTPUT) {
		switch (pin) {
		case 0:
			PORTB_BASE_PTR ->PCR[2] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTB_BASE_PTR ->PDDR, 2);
			break;
		case 1:
			PORTB_BASE_PTR ->PCR[1] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTB_BASE_PTR ->PDDR, 1);
			break;
		case 2:
			PORTA_BASE_PTR ->PCR[11] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTA_BASE_PTR ->PDDR, 11);
			break;
		case 3:
			PORTB_BASE_PTR ->PCR[5] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTB_BASE_PTR ->PDDR, 5);
			break;
		case 4:
			PORTA_BASE_PTR ->PCR[10] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTA_BASE_PTR ->PDDR, 10);
			break;
		case 5:
			PORTA_BASE_PTR ->PCR[12] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTA_BASE_PTR ->PDDR, 12);
			break;
		case 6:
			PORTB_BASE_PTR ->PCR[6] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTB_BASE_PTR ->PDDR, 6);
			break;
		case 7:
			PORTB_BASE_PTR ->PCR[7] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTB_BASE_PTR ->PDDR, 7);
			break;
		case 8:
			PORTB_BASE_PTR ->PCR[10] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTB_BASE_PTR ->PDDR, 10);
			break;
		case 9:
			PORTA_BASE_PTR ->PCR[11] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTA_BASE_PTR ->PDDR, 11);
			break;
		case 10:
			PORTA_BASE_PTR ->PCR[5] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTA_BASE_PTR ->PDDR, 5);
			break;
		case 11:
			PORTA_BASE_PTR ->PCR[7] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTA_BASE_PTR ->PDDR, 7);
			break;
		case 12:
			PORTA_BASE_PTR ->PCR[6] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTA_BASE_PTR ->PDDR, 6);
			break;
		case 13:
			PORTB_BASE_PTR ->PCR[0] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitSet(PTB_BASE_PTR ->PDDR, 0);
			break;
		default:
			break;
		}
	}
	if (type == INPUT) {
		switch (pin) {
		case 12:
			PORTA_BASE_PTR ->PCR[6] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitClr(PTA_BASE_PTR ->PDDR, 6);
			break;
		case 13:
			PORTB_BASE_PTR ->PCR[0] = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);
			bitClr(PTB_BASE_PTR ->PDDR, 0);
			break;
		default:
			break;
		}
	}
}

void digitalWrite(int pin, int value) {
	if (value) {
		switch (pin) {
		case 0:
			bitSet(PTB_BASE_PTR ->PDOR, 2);
			break;
		case 1:
			bitSet(PTB_BASE_PTR ->PDOR, 1);
			break;
		case 2:
			bitSet(PTA_BASE_PTR ->PDOR, 11);
			break;
		case 3:
			bitSet(PTB_BASE_PTR ->PDOR, 5);
			break;
		case 4:
			bitSet(PTA_BASE_PTR ->PDOR, 10);
			break;
		case 5:
			bitSet(PTA_BASE_PTR ->PDOR, 12);
			break;
		case 6:
			bitSet(PTB_BASE_PTR ->PDOR, 6);
			break;
		case 7:
			bitSet(PTB_BASE_PTR ->PDOR, 7);
			break;
		case 8:
			bitSet(PTB_BASE_PTR ->PDOR, 10);
			break;
		case 9:
			bitSet(PTB_BASE_PTR ->PDOR, 11);
			break;
		case 10:
			bitSet(PTA_BASE_PTR ->PDOR, 5);
			break;
		case 11:
			bitSet(PTA_BASE_PTR ->PDOR, 7);
			break;
		case 12:
			bitSet(PTA_BASE_PTR ->PDOR, 6);
			break;
		case 13:
			bitSet(PTB_BASE_PTR ->PDOR, 0);
			break;
		default:
			break;
		}
	} else {
		switch (pin) {
		case 0:
			bitClr(PTB_BASE_PTR ->PDOR, 2);
			break;
		case 1:
			bitClr(PTB_BASE_PTR ->PDOR, 1);
			break;
		case 2:
			bitClr(PTA_BASE_PTR ->PDOR, 11);
			break;
		case 3:
			bitClr(PTB_BASE_PTR ->PDOR, 5);
			break;
		case 4:
			bitClr(PTA_BASE_PTR ->PDOR, 10);
			break;
		case 5:
			bitClr(PTA_BASE_PTR ->PDOR, 12);
			break;
		case 6:
			bitClr(PTB_BASE_PTR ->PDOR, 6);
			break;
		case 7:
			bitClr(PTB_BASE_PTR ->PDOR, 7);
			break;
		case 8:
			bitClr(PTB_BASE_PTR ->PDOR, 10);
			break;
		case 9:
			bitClr(PTB_BASE_PTR ->PDOR, 11);
			break;
		case 10:
			bitClr(PTA_BASE_PTR ->PDOR, 5);
			break;
		case 11:
			bitClr(PTA_BASE_PTR ->PDOR, 7);
			break;
		case 12:
			bitClr(PTA_BASE_PTR ->PDOR, 6);
			break;
		case 13:
			bitClr(PTB_BASE_PTR ->PDOR, 0);
			break;
		default:
			break;
		}
	}
}

int digitalRead(int pin) {
	switch (pin) {
	case 0:
		return bitTst(PTB_BASE_PTR ->PDIR, 2);
	case 1:
		return bitTst(PTB_BASE_PTR ->PDIR, 1);
	case 2:
		return bitTst(PTA_BASE_PTR ->PDIR, 11);
	case 3:
		return bitTst(PTB_BASE_PTR ->PDIR, 5);
	case 4:
		return bitTst(PTA_BASE_PTR ->PDIR, 10);
	case 5:
		return bitTst(PTA_BASE_PTR ->PDIR, 12);
	case 6:
		return bitTst(PTB_BASE_PTR ->PDIR, 6);
	case 7:
		return bitTst(PTB_BASE_PTR ->PDIR, 7);
	case 8:
		return bitTst(PTB_BASE_PTR ->PDIR, 10);
	case 9:
		return bitTst(PTB_BASE_PTR ->PDIR, 11);
	case 10:
		return bitTst(PTA_BASE_PTR ->PDIR, 5);
	case 11:
		return bitTst(PTA_BASE_PTR ->PDIR, 7);
	case 12:
		return bitTst(PTA_BASE_PTR ->PDIR, 6);
	case 13:
		return bitTst(PTB_BASE_PTR ->PDIR, 0);
	default:
		break;
	}
}

