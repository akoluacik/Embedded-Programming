/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define		TEMP_MEASUREMENT	0xF3
#define		HUMI_MEASUREMENT	0xF5
#define		WRITE_REGISTER		0xE6
#define		READ_REGISTER		0xE7
#define		DEVICE_ADDRESS      0x40
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
DMA_HandleTypeDef hdma_i2c1_rx;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void HTU21D_SensorInit(void);
void HTU21D_MeasureTemp(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
float temp;
float humidity;
float g_temp = 20.00f;
float g_humidity;
char output[50];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HTU21D_SensorInit();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 HAL_UART_Transmit(&huart1, (uint8_t*)"In while\r\n!", 10, 100);
	//HAL_UART_Transmit(&huart1, (uint8_t*)"in while\r\n", 10, 100);
	HTU21D_MeasureTemp();
	HAL_UART_Transmit(&huart1, (uint8_t*)"after func\r\n", 13, 100);
	sprintf(output, "temp:%.2f\r\n", g_temp);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output), 100);
	HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void HTU21D_SensorInit(void)
{
	uint8_t pData[] = {0xFE}; // SOFT_RESET
	if(HAL_I2C_Master_Transmit(&hi2c2, (DEVICE_ADDRESS << 1), pData, 1, HAL_MAX_DELAY) != HAL_OK)
	{
		Error_Handler();
	}
	/*if(HAL_I2C_Mem_Write(&hi2c2, (DEVICE_ADDRESS << 1), WRITE_REGISTER, 1, pData, 1, HAL_MAX_DELAY) != HAL_OK)
	{
		Error_Handler();
	}*/
	HAL_Delay(15);
	HAL_UART_Transmit(&huart1, (uint8_t*)"Sensor initialized!\r\n", 21, 100);
	HAL_StatusTypeDef is_ready = HAL_I2C_IsDeviceReady(&hi2c2, (DEVICE_ADDRESS << 1), 10, 100);
	sprintf(output, "is_ready:%d\r\n", is_ready);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output), 100);
	uint32_t error = HAL_I2C_GetError(&hi2c2);
	sprintf(output, "error:%lu\n\r", error);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output), 100);
}
void HTU21D_MeasureTemp(void)
{
	uint8_t temp[3];
	uint8_t cmd[] = {TEMP_MEASUREMENT};
	uint16_t raw_temp;
	while(HAL_I2C_IsDeviceReady(&hi2c2, (DEVICE_ADDRESS << 1), 4, HAL_MAX_DELAY) != HAL_OK);
	HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(&hi2c2, (DEVICE_ADDRESS << 1), cmd, 1, 100);
	HAL_Delay(60000);
	while(HAL_I2C_IsDeviceReady(&hi2c2, (DEVICE_ADDRESS << 1), INT_LEAST16_MAX, HAL_MAX_DELAY) != HAL_OK);
	sprintf(output, "res:%d\r\n", res);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output), 100);
	HAL_StatusTypeDef is_ready = HAL_I2C_IsDeviceReady(&hi2c2, (DEVICE_ADDRESS << 1), 10, HAL_MAX_DELAY);
	sprintf(output, "is_ready:%d\r\n", is_ready);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output), 100);
	uint32_t error = HAL_I2C_GetError(&hi2c2);
	sprintf(output, "error:%lu\n\r", error);
	HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output), 100);
	if (res == HAL_OK)
	{
		res = HAL_I2C_Master_Receive(&hi2c2, (DEVICE_ADDRESS << 1) | 0x01, temp, 3, HAL_MAX_DELAY);
		if (res == HAL_OK)
		{
			raw_temp = (temp[1] << 8) | temp[0];
			g_temp = -46.85 + 175.72 * raw_temp / 65536;
		}
		else
			HAL_UART_Transmit(&huart1, (uint8_t*)"Receive Failed!\r\n", 17, 100);
	}
	else
	{
		HAL_UART_Transmit(&huart1, (uint8_t*)"Tx Failed!\r\n", 12, 100);
		uint32_t error = HAL_I2C_GetError(&hi2c2);
		sprintf(output, "error:%lu\n\r", error);
		HAL_UART_Transmit(&huart1, (uint8_t*)output, strlen(output), 100);
	}


	/*if (res == HAL_OK)
	{
		res = HAL_I2C_Mem_Read(&hi2c2, (DEVICE_ADDRESS << 1) | 0x01, TEMP_MEASUREMENT, 1, temp, 2, 100);
		if (res == HAL_OK)
		{
			raw_temp = (temp[1] << 8) | temp[0];
			g_temp = -46.85 + 175.72 * raw_temp / 65536;
		}
		else
			HAL_UART_Transmit(&huart1, (uint8_t*)"Mem Read Failed!", 17, 100);
	}
	else
		HAL_UART_Transmit(&huart1, (uint8_t*)"Mem Write Failed!", 18, 100);*/
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  HAL_UART_Transmit(&huart1, (uint8_t*)"Error Handler\r\n", 15, 100);
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
