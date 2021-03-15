#include "EXTI.h"
#include "LCD.h"
#include "LED.h"
#include "Input_Capture.h"
#include "I2C.h"
#include "SysClock.h"
#include "stm32l476xx.h"

int volatile page = 0;
uint32_t volatile speed_last_value = 0;
uint32_t volatile cadence_last_value = 0;
uint32_t volatile speed_current_value = 0;
uint32_t volatile cadence_current_value = 0;
uint32_t volatile speed_overflow_count = 0;
uint32_t volatile cadence_overflow_count = 0;
uint32_t volatile speed_time_interval = 0;
uint32_t volatile cadence_time_interval = 0;

void EXTI1_IRQHandler(void) {
	EXTI->PR1 |= EXTI_PR1_PIF1;
	if(!page)
		page = 2;
	else
		page--;
}

void EXTI2_IRQHandler(void) {
	EXTI->PR1 |= EXTI_PR1_PIF2;
	if(page == 2)
		page = 0;
	else
		page++;
}

void TIM1_IRQHandler(void) {
	if(TIM4->SR & TIM_SR_UIF){
		TIM4->SR &= ~TIM_SR_UIF;
		speed_overflow_count++;
		cadence_overflow_count++;
	}if(TIM4->SR & TIM_SR_CC3IF){ //Wheel Magent
		TIM4->SR &= ~TIM_SR_CC3IF;
		if(!speed_last_value)
			speed_last_value = TIM1->CCR3;
		else{
			speed_current_value = TIM1->CCR3;
			speed_time_interval = (0x10000*speed_overflow_count)+(speed_current_value-speed_last_value);
			speed_overflow_count = 0;
			speed_last_value = speed_current_value;
		}
	}
	if(TIM4->SR & TIM_SR_CC4IF){ //Crank Magnet
		TIM4->SR &= ~TIM_SR_CC4IF;
		if(!cadence_last_value)
			cadnece_last_value = TIM1->CCR4;
		else{
			cadence_current_value = TIM1->CCR4;
			cadence_time_interval = (0x10000*cadence_overflow_count)+(cadence_current_value-cadence_last_value);
			cadence_overflow_count = 0;
			cadence_last_value = cadence_current_value;
		}
	}
}

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
