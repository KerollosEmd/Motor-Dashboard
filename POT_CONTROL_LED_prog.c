/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: POT_CONTROL_LEDS              ******************   	*/
/*	        ********************			Version: 1.0		                ******************   	*/
/********************************************************************************************************/

/*Libraries*/
#include "STD_Types.h"
#include "BIT_MATH.h"
#define	 F_CPU 8000000UL
#include <util/delay.h>

/*MCAL*/
#include "DIO_interface.h"
#include "ADC_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "KPD_interface.h"

/*APP layer*/
#include "POT_CTR_LED.h"

extern u16 APP_u16DigitalValue;

void APP_voidPotCTRLeds(void) {

	u16 Local_u8ADCValue;

	LCD_voidWriteCommand(LCD_Clear);
	LCD_voidGoToXY(0,LCD_u8_LINE_2);
	LCD_voidWriteString("DipSw1>>(BACK)");

	while (1) {

		if(APP_u16DigitalValue==POT_RETURN_FLAG){
			APP_u16DigitalValue=0;
			break;
		}

		if (ADC_u8GetDigitalValueSync(POT_u8_PIN,
				&APP_u16DigitalValue)) {

			Local_u8ADCValue = (APP_u16DigitalValue * 5000UL) / 1024;
			LCD_voidGoToXY(0,LCD_u8_LINE_1);
			LCD_voidWritNumber(Local_u8ADCValue);
			LCD_voidWriteString(" mV   ");

			if (Local_u8ADCValue == VOLTAGE_LEVEL_0) {
				DIO_u8SetPortValue(LED_u8_PORT, LED_u8_0);

			} else if ((Local_u8ADCValue > VOLTAGE_LEVEL_0)
					&& (Local_u8ADCValue < VOLTAGE_LEVEL_1)) {
				DIO_u8SetPortValue(LED_u8_PORT, LED_u8_1);

			} else if ((Local_u8ADCValue >= VOLTAGE_LEVEL_1)
					&& (Local_u8ADCValue < VOLTAGE_LEVEL_2)) {
				DIO_u8SetPortValue(LED_u8_PORT, LED_u8_2);

			} else if ((Local_u8ADCValue >= VOLTAGE_LEVEL_2)
					&& (Local_u8ADCValue < VOLTAGE_LEVEL_3)) {
				DIO_u8SetPortValue(LED_u8_PORT, LED_u8_3);

			} else if ((Local_u8ADCValue >= VOLTAGE_LEVEL_3)
					&& (Local_u8ADCValue < VOLTAGE_LEVEL_4)) {
				DIO_u8SetPortValue(LED_u8_PORT, LED_u8_4);

			} else if ((Local_u8ADCValue >= VOLTAGE_LEVEL_4)
					&& (Local_u8ADCValue < VOLTAGE_LEVEL_5)) {
				DIO_u8SetPortValue(LED_u8_PORT, LED_u8_5);

			} else if ((Local_u8ADCValue >= VOLTAGE_LEVEL_5)
					&& (Local_u8ADCValue < VOLTAGE_LEVEL_6)) {
				DIO_u8SetPinValue(DIO_u8_PORTA,LED_u8_6,DIO_u8_HIGH);

			} else if ((Local_u8ADCValue >= VOLTAGE_LEVEL_6)
					&& (Local_u8ADCValue < VOLTAGE_LEVEL_7)) {
				DIO_u8SetPortValue(LED_u8_PORT, LED_u8_7);

			} else if (Local_u8ADCValue >= VOLTAGE_LEVEL_7) {
				DIO_u8SetPortValue(LED_u8_PORT, LED_u8_8);
			}

		} else {
			LCD_voidWriteString("Error PotCTRLED");
		}
		_delay_ms(200);
	}
}
