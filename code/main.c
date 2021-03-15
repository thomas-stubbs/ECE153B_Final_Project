#include "EXTI.h"
#include "LCD.h"
#include "LED.h"
#include "Input_Capture.h"
#include "I2C.h"
#include "SysClock.h"
#include "stm32l476xx.h"

int main(void){
	System_Clock_Init(); // System Clock = 80 MHz

	EXTI_Init();

	LCD_Initialization();
	LCD_Clear();

	LED_Init();

	Input_Capture_Init();

	I2C_GPIO_Init();
	I2C_Initialization();

	float speed;
	int cadence;
	char message[6];
	while(1){
		if(page == 0){ //Display speed
			speed = 4774863.64 / speed_time_interval;
			sprintf(message, "%2.1f mph", speed);
			LCD_DisplayString((uint8_t *) message);
		}
		if(page == 1){ //Display cadence
			cadence = 60000000 / cadence_time_interval;
			sprintf(message,"%.03d rpm", cadence);
			LCD_DisplayString((uint8_t *) message);
		}
		if(page == 2){ //Display Brake Temperature
		}
	}
}

