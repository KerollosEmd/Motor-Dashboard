/********************************************************************************************************/
/*	        ********************			Name: Kerollos Emad                 ******************   	*/
/* 	        ********************			Date: 9-10-2021		                ******************   	*/
/*	        ********************			SWC	: Motor Dash board			            ******************   	*/
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
#include "GIE_interface.h"
#include "EXTI_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "KPD_interface.h"

/*APP LAYER*/
#include "LIS_header.h"
#include "DC_MOTOR_HEADER.h"
#include "POT_CTR_LED.h"
#include "HAMOKSHA_HEADER.h"
#include "OHM_METER.h"

/**********MACROS************/
/*Home Screen choices*/
#define DC_MOTOR_CONTROL	1
#define POT_CTRL			2
#define NEXT				3
#define EXIT				4
/*Pot Screen*/
#define OHM_METER			1
#define POT_CTRL_LED		2
/*Next screen2*/
#define HAMOKSHA_LDR		2
#define HAMOKSHA_POT		1

/*arrows control*/
#define OPTION1_ARROW_POS 	0
#define OPTION2_ARROW_POS 	0
#define OPTION3_ARROW_POS 	7
#define OPTION4_ARROW_POS 	7

#define OPTION1				1
#define OPTION2				2
#define OPTION3				3
#define OPTION4				4

void App_voidArrow(u8 Copy_u8SelectedOption);

u16 APP_u16DigitalValue=0;

void APP_voidReturn(void){
	APP_u16DigitalValue=POT_RETURN_FLAG;
}



void main(void){

	//Set Call back
	EXTI_u8SetCallBack(EXTI_u8_EXTI_0,&APP_voidReturn);

	//select trigger source for EXTI 0 and enable it
	EXTI_u8INIT(EXTI_u8_EXTI_0,EXTI_u8_FALLING_EDGE);

	/*initialize the DIO */
	DIO_voidInit();
	/*initialize the LCD in 4 bit mode */
	LCD_voidInit();
	/*Initialize the ADC peripheral*/
	ADC_voidInit();
	ADC_u8SetREF(ADC_u8_AVCC);
	/*Enabling the General Interrupt Flag*/
	GIE_voidEnable();

	HAMOKSHA_voidWalksCHAR();
	/*OHM_voidSympol();*/

	u8 Local_u8KeyValue;
	/*
	u8 Local_u8Index=0;
	u16 Local_u16ADCValue;
	u16 Local_u16DigitalValue;
	 */


	/*Logging in the system*/
	if(LogInSystem()){
		/*Entering the System*/
		LCD_voidWriteCommand(LCD_Clear);
		LCD_voidWriteString("Welcome To MIT");
		LCD_voidGoToXY(0,LCD_u8_LINE_2);
		LCD_voidWriteString("Naughty Kit");
		_delay_ms(3000);

		/*Supper Loop of the Home screen*/
		while(1){
			LCD_voidWriteCommand(LCD_Clear);
			LCD_voidWriteString(" 1-DC_M 3-Next");
			LCD_voidGoToXY(0,LCD_u8_LINE_2);
			LCD_voidWriteString(" 2-POT  4-Exit");

			do {
				Local_u8KeyValue = KPD_u8GetPressedKey();
			} while (Local_u8KeyValue == 0xff);

			if(DC_MOTOR_CONTROL==Local_u8KeyValue){
				App_voidArrow(OPTION1);
				DC_Motor_app();

			}else if(POT_CTRL==Local_u8KeyValue){
				App_voidArrow(OPTION2);
				while(1){
					LCD_voidWriteCommand(LCD_Clear);
					LCD_voidWriteString(" 1-VDiv 3-Next");
					LCD_voidGoToXY(0,LCD_u8_LINE_2);
					LCD_voidWriteString(" 2-LEDs 4-Back");

					do {
						Local_u8KeyValue = KPD_u8GetPressedKey();
					} while (Local_u8KeyValue == 0xff);

					if(POT_CTRL_LED==Local_u8KeyValue){
						App_voidArrow(OPTION2);
						APP_voidPotCTRLeds();
					}else if(OHM_METER==Local_u8KeyValue){
						App_voidArrow(OPTION1);
						OhmMeter_voidCall();
					}else if(NEXT==Local_u8KeyValue){
						App_voidArrow(OPTION3);
					}else if(EXIT==Local_u8KeyValue){
						App_voidArrow(OPTION4);
						break;
					}
				}
			}else if (NEXT==Local_u8KeyValue){
				while(1){
					LCD_voidWriteCommand(LCD_Clear);
					LCD_voidWriteString(" 1-PLAY 3-Next");
					LCD_voidGoToXY(0,LCD_u8_LINE_2);
					LCD_voidWriteString(" 2-TIME 4-Back");

					do {
						Local_u8KeyValue = KPD_u8GetPressedKey();
					} while (Local_u8KeyValue == 0xff);

					if(HAMOKSHA_POT==Local_u8KeyValue){
						App_voidArrow(OPTION1);

						HAMOKSHA_voidWalks();
					}else if(HAMOKSHA_LDR==Local_u8KeyValue){
						App_voidArrow(OPTION2);

						HAMOKSHA_voidSLEEP();
					}else if(NEXT==Local_u8KeyValue){
						App_voidArrow(OPTION3);
					}else if(EXIT==Local_u8KeyValue){
						App_voidArrow(OPTION4);
						break;
					}
				}
			}else if(EXIT==Local_u8KeyValue){
				App_voidArrow(OPTION4);
				break;
			}
		}

	}/*else if user forgets the password*/
	else {

	}
}


void App_voidArrow(u8 Copy_u8SelectedOption){
	switch(Copy_u8SelectedOption){
	case OPTION1:{
		LCD_voidGoToXY(OPTION1_ARROW_POS,LCD_u8_LINE_1);
		LCD_voidWriteChar(LCD_u8_RIGHT_ARROW);

		LCD_voidGoToXY(OPTION2_ARROW_POS,LCD_u8_LINE_2);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION3_ARROW_POS,LCD_u8_LINE_1);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION4_ARROW_POS,LCD_u8_LINE_2);
		LCD_voidWriteChar(' ');
		_delay_ms(200);
	}break;
	case OPTION2:{
		LCD_voidGoToXY(OPTION1_ARROW_POS,LCD_u8_LINE_1);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION2_ARROW_POS,LCD_u8_LINE_2);
		LCD_voidWriteChar(LCD_u8_RIGHT_ARROW);

		LCD_voidGoToXY(OPTION3_ARROW_POS,LCD_u8_LINE_1);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION4_ARROW_POS,LCD_u8_LINE_2);
		LCD_voidWriteChar(' ');
		_delay_ms(200);
	}break;
	case OPTION3:{
		LCD_voidGoToXY(OPTION1_ARROW_POS,LCD_u8_LINE_1);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION2_ARROW_POS,LCD_u8_LINE_2);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION3_ARROW_POS,LCD_u8_LINE_1);
		LCD_voidWriteChar(LCD_u8_RIGHT_ARROW);

		LCD_voidGoToXY(OPTION4_ARROW_POS,LCD_u8_LINE_2);
		LCD_voidWriteChar(' ');
		_delay_ms(200);
	}break;
	case OPTION4:{
		LCD_voidGoToXY(OPTION1_ARROW_POS,LCD_u8_LINE_1);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION2_ARROW_POS,LCD_u8_LINE_2);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION3_ARROW_POS,LCD_u8_LINE_1);
		LCD_voidWriteChar(' ');

		LCD_voidGoToXY(OPTION4_ARROW_POS,LCD_u8_LINE_2);
		LCD_voidWriteChar(LCD_u8_RIGHT_ARROW);
		_delay_ms(200);
	}break;
	}
}





