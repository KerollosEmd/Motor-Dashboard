/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: OHM_METER		                ******************   	*/
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
#include "OHM_METER.h"

extern u16 APP_u16DigitalValue;

/*static OHM_sympol[]={
		0x00,
		0x0E,
		0x11,
		0x11,
		0x11,
		0x0A,
		0x1B,
		0x00
};
void OHM_voidSympol(void){
	u8 Local_u8Index;
	LCD_voidWriteCommand(LCD_DrawChar);
		//char1
		for(Local_u8Index=0; Local_u8Index<8;Local_u8Index++)
		{
			LCD_voidWriteChar(OHM_sympol[Local_u8Index]);
		}
}*/
void OhmMeter_voidCall(void){
	u16 Local_u16ADCVoltage;
	u32 Local_u32ADCResistance;

	LCD_voidWriteCommand(LCD_Clear);
	LCD_voidGoToXY(0,LCD_u8_LINE_1);
	LCD_voidWriteString("Vo=");
	LCD_voidGoToXY(0,LCD_u8_LINE_2);
	LCD_voidWriteString("R1=");

	LCD_voidGoToXY(12,LCD_u8_LINE_1);
	LCD_voidWriteString("Vol");
	LCD_voidGoToXY(12,LCD_u8_LINE_2);
	LCD_voidWriteString("Div");


	while (1) {

		if(APP_u16DigitalValue==POT_RETURN_FLAG){
			APP_u16DigitalValue=0;
			break;
		}

		if (ADC_u8GetDigitalValueSync(POT_u8_PIN,
				&APP_u16DigitalValue)) {

			Local_u16ADCVoltage = (APP_u16DigitalValue * 5000UL) / 1024;
			LCD_voidGoToXY(3,LCD_u8_LINE_1);
			LCD_voidWritNumber(Local_u16ADCVoltage);
			LCD_voidWriteString(" mV  ");
			/* 1   ohm= 4995 mVolt
			 * 10 Kohm=	1	 mVolt
			 * x   ohm= */
			Local_u32ADCResistance=10000UL-(2*Local_u16ADCVoltage);
			if(Local_u32ADCResistance<1000){
				LCD_voidGoToXY(3,LCD_u8_LINE_2);
				LCD_voidWritNumber(Local_u32ADCResistance);
			}else if(Local_u32ADCResistance>1000){
				LCD_voidGoToXY(3,LCD_u8_LINE_2);
				LCD_voidWriteDivWithFloatNum(Local_u32ADCResistance,1000UL);
				LCD_voidWriteChar('K');
			}
			LCD_voidWriteChar(OHM_SYMPOL);
			LCD_voidWriteString("  ");


		} else {
			LCD_voidWriteString("Error OHMETER");
		}
		_delay_ms(200);
	}
}
