/*
 * HAMOKSHA_WALKS_HEADER.h
 *
 *  Created on: Oct 18, 2021
 *      Author: KeroEmad
 */

#ifndef HAMOKSHA_HEADER_H_
#define HAMOKSHA_HEADER_H_

#define POT_u8_PIN		ADC_u8_SINGLE_ADC7
#define LDR_u8_PIN		ADC_u8_SINGLE_ADC6

/*Hamoksha characters addresses*/
#define HAMOKSHA_PLAY1		0
#define HAMOKSHA_PLAY2		1
#define HAMOKSHA_BALL1		2
#define HAMOKSHA_BALL2		3
#define HAMOKSHA_SLEEP1		4
#define HAMOKSHA_SLEEP2		5

#define POT_RETURN_FLAG		0xFFFF


void HAMOKSHA_voidWalksCHAR(void);
void HAMOKSHA_voidWalks(void);
void HAMOKSHA_voidSLEEP(void);

#endif /* HAMOKSHA_HEADER_H_ */
