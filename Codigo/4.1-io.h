/*
 * io.h
 *
 *  Created on: Sep 2, 2015
 *      Author: Rodrigo
 */

#ifndef IO_H_
#define IO_H_


#define bitSet(arg,bit) ((arg) |= (1<<bit))
#define bitClr(arg,bit) ((arg) &= ~(1<<bit)) 
#define bitFlp(arg,bit) ((arg) ^= (1<<bit)) 
#define bitTst(arg,bit) ((arg) & (1<<bit)) 

#define OUTPUT 0
#define INPUT  1

#define LOW 0
#define HIGH 1

void pinMode(int pin, int type);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void systemInit(void);
#endif /* IO_H_ */
