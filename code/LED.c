#include "LED.h"

void LED_Init(void) {
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; //Enable clock for port B
	//RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN; //Enable clock for port E
	
	// Initialize Red LED
	GPIOB->MODER &= ~GPIO_MODER_MODE2; //Clear mode bits for pin 2
	GPIOB->MODER |= GPIO_MODER_MODE2_0; //Set mode bits to 01 (output)
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT2; //Set output type bit  to 0 (push pull)
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD2; //Set pull up pull down bits to 00 (no PUPD)
	
	// Initialize Green LED
	/*GPIOE->MODER &= ~GPIO_MODER_MODE8; //Clear mode bits for pin 2
	GPIOE->MODER |= GPIO_MODER_MODE8_0; //Set mode bits to 01 (output)
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT8; //Set output type bit  to 0 (push pull)
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD8; //Set pull up pull down bits to 00 (no PUPD)*/
}

void Red_LED_Off(void) {
	GPIOB->ODR &= ~GPIO_ODR_OD2;
}

void Red_LED_On(void) {
	GPIOB->ODR |= GPIO_ODR_OD2;
}

void Red_LED_Toggle(void){
	GPIOB->ODR ^= GPIO_ODR_OD2;
}

void Green_LED_Off(void) {
	GPIOE->ODR &= ~GPIO_ODR_OD8;
}

void Green_LED_On(void) {
	GPIOE->ODR |= GPIO_ODR_OD8;
}

void Green_LED_Toggle(void) {
	GPIOE->ODR ^= GPIO_ODR_OD8;
}
