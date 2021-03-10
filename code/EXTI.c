#include "EXTI.h"

#include "DAC.h"

void EXTI_Init(void) {
    // Initialize Joystick
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    GPIOA->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE3);
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD3);
    GPIOA->PUPDR |= (GPIO_PUPDR_PUPD0_1 | GPIO_PUPDR_PUPD3_1);
	
    // Configure SYSCFG EXTI
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;
	
    // Configure EXTI Trigger
    EXTI->RTSR1 |= EXTI_RTSR1_RT0;
    EXTI->RTSR1 |= EXTI_RTSR1_RT3;
	
    // Enable EXTI
    EXTI->IMR1 |= EXTI_IMR1_IM0;
    EXTI->IMR1 |= EXTI_IMR1_IM3;
	
    // Configure and Enable in NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_SetPriority(EXTI0_IRQn, 0);
    NVIC_EnableIRQ(EXTI3_IRQn);
    NVIC_SetPriority(EXTI3_IRQn, 0);
}

#define DAC_MIN 0
#define DAC_MAX 4095
#define DAC_INCREMENT 256

static uint32_t dac_value = 0;

void EXTI0_IRQHandler(void) {
	EXTI->PR1 |= EXTI_PR1_PIF0;
	if((DAC->DHR12R2 - DAC_INCREMENT) > DAC_MIN)
		DAC->DHR12R2 -= DAC_INCREMENT;
}

void EXTI3_IRQHandler(void) {
	EXTI->PR1 |= EXTI_PR1_PIF3;
	if((DAC->DHR12R2 + DAC_INCREMENT) < DAC_MAX)
		DAC->DHR12R2 += DAC_INCREMENT;
}

