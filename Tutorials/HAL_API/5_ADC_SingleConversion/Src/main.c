#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include <stdlib.h>
#include <string.h>
uint32_t sensorValue;
ADC_HandleTypeDef hadc1;
char value[5];
int main()
{

	HAL_Init();
	uart_init();

	adc_pa0_single_conv_init();

	while(1)
	{
		// 1. Start ADC
		HAL_ADC_Start(&hadc1); // start ADC for each time

		// 2. Poll for Conversion
		HAL_ADC_PollForConversion(&hadc1, 1);

		// 3. Get Conversion
		sensorValue = pa0_adc_read();

		printf("Sensor Value: %d\r\n", sensorValue);
	}

}


// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}

