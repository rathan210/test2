/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MAX31855.h"
#include<stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char temp_buff[200];
char printBuff[200]={};
char temp_buff_1[200];
uint16_t Temperature_value;
uint16_t temp_val, temp_val1;
uint16_t temp_k1;
uint8_t k2_flag=0,k1_flag=0;
char pData[10]={"rathan"};
unsigned char data[5]={'#',0,'$',0,'@'};
char data_2[2]={"$"};
char data_3[2]={"@"};
volatile uint16_t Temperature1, Temperature2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void read_k1()
{
//	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
//	HAL_GPIO_WritePin(K_SEL_GPIO_Port, K_SEL_Pin, RESET);
	k1_flag=1;
	k2_flag=0;
	HAL_Delay(50);
// 	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, RESET);
//    ReadTemperature(&temp);
	//   	ReadTemperature();
	HAL_Delay(500);
}
void read_k2()
{
	 //  HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
	    HAL_GPIO_WritePin(K_SEL_GPIO_Port, K_SEL_Pin, SET);
	    k2_flag=1;
	    HAL_Delay(50);
	//    HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, RESET);
	    ReadTemperature(&temp_k1);
	//    ReadTemperature(&tempk1);
	    HAL_Delay(500);
	//    HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
}
uint16_t read_temp(uint8_t Temp_no)
{
	uint16_t temp_value = 0;
//	temp = 0, temp1  = 0;
	if(Temp_no == 1)
	{
//		HAL_GPIO_WritePin(K_SEL_GPIO_Port, K_SEL_Pin, RESET);
//		HAL_Delay(500);
//	   	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, RESET);
		ReadTemperature(&temp_val);
		temp_value = temp_val;
	}
	else if(Temp_no == 2)
	{
//		HAL_GPIO_WritePin(K_SEL_GPIO_Port, K_SEL_Pin, SET);
//		HAL_Delay(500);
//	   	HAL_GPIO_WritePin(CS2_p_GPIO_Port, CS2_p_Pin, RESET);
		ReadTemperature(&temp_val1);
		temp_value = temp_val1;
	}
	return temp_value;
}
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
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_SPI_Init(&hspi1);

//  HAL_GPIO_WritePin(K_SEL_GPIO_Port, K_SEL_Pin, SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  HAL_UART_Transmit(&huart2, (uint8_t *)pData, sizeof(pData), HAL_MAX_DELAY);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin(CS_T2_GPIO_Port, CS_T2_Pin, SET);
	  HAL_GPIO_WritePin(CS_T1_GPIO_Port, CS_T1_Pin, RESET);
	  Temperature1 = read_temp(1);
	//  HAL_UART_Transmit(&huart2, (uint8_t *)data_1, sizeof(data_1), HAL_MAX_DELAY);
	 // HAL_UART_Transmit(&huart2, Temperature1, 1 , HAL_MAX_DELAY);
//	  sprintf(printBuff, " \r\n",Temperature1);
//	  HAL_UART_Transmit(&huart2, (uint16_t *)&printBuff, sizeof(printBuff), 1000);
//	  HAL_UART_Transmit(&huart2, (uint8_t *)data_2, sizeof(data_2), HAL_MAX_DELAY);
	  HAL_Delay(500);

	  HAL_GPIO_WritePin(CS_T1_GPIO_Port, CS_T1_Pin, SET);
	  HAL_GPIO_WritePin(CS_T2_GPIO_Port, CS_T2_Pin, RESET);
	  Temperature2 = read_temp(2);
	//  HAL_UART_Transmit(&huart2, Temperature2, 2, HAL_MAX_DELAY);
	 // HAL_UART_Transmit(&huart2, (uint8_t *)data_3, sizeof(data_3), HAL_MAX_DELAY);
data[1]=Temperature1;
data[3]=Temperature2;
HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data), HAL_MAX_DELAY);

//	  sprintf(printBuff, " \r\n",Temperature2);
//	  HAL_UART_Transmit(&huart2, (uint16_t *)&printBuff, sizeof(printBuff), 1000);
/* 	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
 	HAL_GPIO_WritePin(K_SEL_GPIO_Port, K_SEL_Pin, RESET);
 	k1_flag=1;
 	HAL_Delay(50);
//   	HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, RESET);
    ReadTemperature(&temp);
//   	ReadTemperature();
    HAL_Delay(500);

    HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);
    HAL_GPIO_WritePin(K_SEL_GPIO_Port, K_SEL_Pin, SET);
    k2_flag=1;
    HAL_Delay(50);
    HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, RESET);
    ReadTemperature(&temp_k1);
//   ReadTemperature(&tempk1);
    HAL_Delay(500);
    HAL_GPIO_WritePin(CS_pin_GPIO_Port, CS_pin_Pin, SET);*/
	  /////////////
//	  read_k1();
//	  read_k2();

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CS_T1_Pin|K_SEL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_T2_GPIO_Port, CS_T2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_T1_Pin K_SEL_Pin */
  GPIO_InitStruct.Pin = CS_T1_Pin|K_SEL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : CS_T2_Pin */
  GPIO_InitStruct.Pin = CS_T2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_T2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/