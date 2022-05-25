/*
 * HAMOKSHA_WALKS.c
 *
 *  Created on: Oct 18, 2021
 *      Author: KeroEmad
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#define	 F_CPU 8000000UL
#include <util/delay.h>

/*MCAL*/
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"

#include "LCD_interface.h"
#include "ADC_interface.h"

#include "HAMOKSHA_HEADER.h"

//Hamoksha Play football
static u8 Hamoksha_Au8Play1[]={
		0x0E,
		0x0E,
		0x04,
		0x0E,
		0x15,
		0x04,
		0x0A,
		0x11
};

static u8 Hamoksha_Au8Play2[]={
		0x0E,
		0x0E,
		0x04,
		0x0E,
		0x15,
		0x04,
		0x0A,
		0x0A
};

//ball
static u8 Hamoksha_Au8Ball3[]={
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x18,
		0x18
};
static u8 Hamoksha_Au8Ball4[]={
		0x00,
		0x00,
		0x00,
		0x00,
		0x06,
		0x06,
		0x00,
		0x00
};
//Hamoksha on Bed
static u8 Hamoksha_Au8Sleep5[]={
		0x00,
		0x00,
		0x19,
		0x1F,
		0x19,
		0x00,
		0x00,
		0x1F
};

static u8 Hamoksha_Au8Sleep6[]={
		0x08,
		0x11,
		0x02,
		0x1C,
		0x02,
		0x11,
		0x08,
		0x1F
};

static OHM_sympol[]={
		0x00,
		0x0E,
		0x11,
		0x11,
		0x11,
		0x0A,
		0x1B,
		0x00
};
/*void OHM_voidSympol(void){
	u8 Local_u8Index;
	LCD_voidWriteCommand(LCD_DrawChar);
		//char1
		for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
		{
			LCD_voidWriteChar(OHM_sympol[Local_u8Index]);
		}
}*/

void HAMOKSHA_voidWalksCHAR(void){
	u8 Local_u8Index;
	/*Draw special characters into the LCD*/
	/*scope of drawing*/
	LCD_voidWriteCommand(LCD_DrawChar);
	//char1
	for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
	{
		LCD_voidWriteChar(Hamoksha_Au8Play1[Local_u8Index]);
	}
	//char2
	for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
	{
		LCD_voidWriteChar(Hamoksha_Au8Play2[Local_u8Index]);
	}
	//char3
	for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
	{
		LCD_voidWriteChar(Hamoksha_Au8Ball3[Local_u8Index]);
	}
	//char4
	for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
	{
		LCD_voidWriteChar(Hamoksha_Au8Ball4[Local_u8Index]);
	}
	//char5
	for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
	{
		LCD_voidWriteChar(Hamoksha_Au8Sleep5[Local_u8Index]);
	}
	//char6
	for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
	{
		LCD_voidWriteChar(Hamoksha_Au8Sleep6[Local_u8Index]);
	}
	//char7
	for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
	{
		LCD_voidWriteChar(OHM_sympol[Local_u8Index]);
	}
}
extern APP_u16DigitalValue;

void HAMOKSHA_voidWalks(void){


	u16 Local_u8ADCValue;
	u16 Local_u16PreValue;

	u8 Local_u8Xpos=6;

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

			if(Local_u8ADCValue<(Local_u16PreValue-20)){
				Local_u8Xpos--;
				//LCD_voidWriteCommand(LCD_Clear);
				LCD_voidGoToXY(Local_u8Xpos,LCD_u8_LINE_1);
				LCD_voidWriteChar(' ');
				LCD_voidWriteChar(HAMOKSHA_PLAY1);
				LCD_voidWriteChar(' ');
			}else if(Local_u8ADCValue>(Local_u16PreValue+20)){
				Local_u8Xpos++;
				//LCD_voidWriteCommand(LCD_Clear);
				LCD_voidGoToXY(Local_u8Xpos,LCD_u8_LINE_1);
				LCD_voidWriteChar(' ');
				LCD_voidWriteChar(HAMOKSHA_PLAY1);
				LCD_voidWriteChar(' ');
			}
			Local_u16PreValue=Local_u8ADCValue;
			/*while(Local_u16PreValue==Local_u8ADCValue){
				ADC_u8GetDigitalValueSync(POT_u8_PIN,
						&APP_u16DigitalValue);
			}*/

		} else {
			LCD_voidWriteString("Error HAM_WALK");
		}
		_delay_ms(200);
	}

}


void HAMOKSHA_voidSLEEP(void){
	u16 Local_u8ADCValue;

	LCD_voidWriteCommand(LCD_Clear);
	LCD_voidGoToXY(0,LCD_u8_LINE_2);
	LCD_voidWriteString("DipSw1>>(BACK)");

	while (1) {
		if(APP_u16DigitalValue==POT_RETURN_FLAG){
			APP_u16DigitalValue=0;
			break;
		}

		if (ADC_u8GetDigitalValueSync(LDR_u8_PIN,
				&APP_u16DigitalValue)) {

			Local_u8ADCValue = (APP_u16DigitalValue * 5000UL) / 1024;

			if(Local_u8ADCValue>(4000)){

				LCD_voidGoToXY(0,LCD_u8_LINE_1);
				LCD_voidWriteChar(' ');
				LCD_voidWriteChar(HAMOKSHA_PLAY1);
				LCD_voidWriteChar(' ');
			}else if(Local_u8ADCValue<4000){

				LCD_voidGoToXY(0,LCD_u8_LINE_1);
				LCD_voidWriteChar(' ');
				LCD_voidWriteChar(HAMOKSHA_SLEEP1);
				LCD_voidWriteChar(HAMOKSHA_SLEEP2);
				LCD_voidWriteChar(' ');
			}
		} else {
			LCD_voidWriteString("Error HAM_WALK");
		}
		_delay_ms(200);
	}

}
