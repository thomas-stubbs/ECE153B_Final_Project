#include "EXTI.h"

int volatile page = 0;

void EXTI_Init(void) {
    // Initialize Joystick
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    GPIOA->MODER &= ~(GPIO_MODER_MODE1 | GPIO_MODER_MODE2);
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD2);
    GPIOA->PUPDR |= (GPIO_PUPDR_PUPD1_1 | GPIO_PUPDR_PUPD2_1);
	
    // Configure SYSCFG EXTI
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;
	
    // Configure EXTI Trigger
    EXTI->RTSR1 |= EXTI_RTSR1_RT1;
    EXTI->RTSR1 |= EXTI_RTSR1_RT2;
	
    // Enable EXTI
    EXTI->IMR1 |= EXTI_IMR1_IM1;
    EXTI->IMR1 |= EXTI_IMR1_IM2;
	
    // Configure and Enable in NVIC
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_SetPriority(EXTI1_IRQn, 1);
    NVIC_EnableIRQ(EXTI2_IRQn);
    NVIC_SetPriority(EXTI2_IRQn, 1);
}

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

