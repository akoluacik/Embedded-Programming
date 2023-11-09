#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"
#include "dma.h"

static const uint32_t aSRC_Const_Buffer[BUFFER_SIZE] = {
					0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
					0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
					0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
					0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
					0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
					0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
					0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
					0x71727334, 0x75767778, 0x797A7B7C, 0x7D7E7F80
};

static uint32_t aDST_Const_Buffer[BUFFER_SIZE];

DMA_HandleTypeDef dma_handle;

int main()
{

	HAL_Init();
	uart_init();
	DMA_Struct_t DMA_InitStruct_t = {DMA_STREAM, DMA_CHANNEL, DMA_MEMORY_TO_MEMORY, DMA_PINC_ENABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_WORD,
			DMA_MDATAALIGN_WORD, DMA_NORMAL, DMA_PRIORITY_HIGH, DMA_FIFOMODE_ENABLE};
	dma_config(DMA_InitStruct_t);

	HAL_DMA_Start_IT(&dma_handle, (uint32_t*)aSRC_Const_Buffer, (uint32_t*)aDST_Const_Buffer, BUFFER_SIZE);

	while(1)
	{

	}

}


// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}

