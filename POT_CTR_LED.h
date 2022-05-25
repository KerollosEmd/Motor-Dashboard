/*
 * POT_CTR_LED.h
 *
 *  Created on: Oct 18, 2021
 *      Author: KeroEmad
 */

#ifndef POT_CTR_LED_H_
#define POT_CTR_LED_H_

#define LED_u8_PORT    	DIO_u8_PORTB
#define POT_u8_PIN		ADC_u8_SINGLE_ADC7

#define LED_u8_0		0x00
#define LED_u8_1		0x01
#define LED_u8_2		0x03
#define LED_u8_3		0x07
#define LED_u8_4		0x0F
#define LED_u8_5		0x1F
#define LED_u8_6		0x3F
#define LED_u8_7		0x7F
#define LED_u8_8		0xFF

#define VOLTAGE_LEVEL_0		0
#define VOLTAGE_LEVEL_1		625
#define VOLTAGE_LEVEL_2		1250
#define VOLTAGE_LEVEL_3		1875
#define VOLTAGE_LEVEL_4		2500
#define VOLTAGE_LEVEL_5		3125
#define VOLTAGE_LEVEL_6		3750
#define VOLTAGE_LEVEL_7		4375

#define POT_RETURN_FLAG		0xFFFF

void APP_voidPotCTRLeds(void);


#endif /* POT_CTR_LED_H_ */
