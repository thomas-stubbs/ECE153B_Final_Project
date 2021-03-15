#include "InputCapture.h"

uint32_t volatile speed_last_value = 0;
uint32_t volatile cadence_last_value = 0;
uint32_t volatile speed_current_value = 0;
uint32_t volatile cadence_current_value = 0;
uint32_t volatile speed_overflow_count = 0;
uint32_t volatile cadence_overflow_count = 0;
uint32_t volatile speed_time_interval = 0;
uint32_t volatile cadence_time_interval = 0;

void Input_Capture_Init() {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~(GPIO_MODER_MODE13 | GPIO_MODER_MODE14);
	GPIOE->MODER |= (GPIO_MODER_MODE13_1 | GPIO_MODER_MODE14_1);
	GPIOE->AFR[1] &= ~(GPIO_AFRH_AFSEL13 | GPIO_AFRH_AFSEL14);
	GPIOE->AFR[1] |= (GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL14_0);
	GPIOE->PUPDR &= ~(GPIO_PUPDR_PUPD13 | GPIO_PUPDR_PUPD14);
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1->PSC &= ~0xFFFF;
	TIM1->PSC |= 0x4F;
	TIM1->CR1 |= TIM_CR1_ARPE;
	TIM1->ARR |= 0xFFFF;
	TIM1->CCMR2 &= ~(TIM_CCMR2_CC3S | TIM_CCMR2_CC4S);
	TIM1->CCMR2 |= (TIM_CCMR2_CC3S_0 | TIM_CCMR2_CC4S_0);
	TIM1->CCER &= ~(TIM_CCER_CC3NP | TIM_CCER_CC3P | TIM_CCER_CC4NP | TIM_CCER_CC4P);
	TIM1->CCER |= (TIM_CCER_CC3E | TIM_CCER_CC4E);
	TIM1->DIER |= (TIM_DIER_CC3DE | TIM_DIER_CC4DE | TIM_DIER_CC3IE | TIM_DIER_CC4IE | TIM_DIER_UIE);
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->SR &= ~TIM_SR_UIF;
	TIM1->CR1 &= ~TIM_CR1_DIR;
	TIM1->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM1_IRQn);
	NVIC_SetPriority(TIM1_IRQn, 0);
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

