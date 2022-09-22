/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG(int num);
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int count = 10, counter = 5;
  while (1)
  {
    /* USER CODE END WHILE */
    count--;
    if (count >= 7 && count <= 9) {
      	// led red_row, green_column turn on
    	// led yellow_row, yellow_column, red_column, green_row turn off
    	// when time is between 9->7
      	HAL_GPIO_WritePin(GPIOA, redr_Pin|greenc_Pin, RESET);
        HAL_GPIO_WritePin(GPIOA, yellowr_Pin|yellowc_Pin|redc_Pin|greenr_Pin, SET);
        display7SEG(counter--);
    }
    else if(count <= 6 && count >= 5){
        // turn off led green_column and turn on yellow_column
        // when time is between 6->5
        HAL_GPIO_WritePin(yellowc_GPIO_Port, yellowc_Pin, RESET);
        HAL_GPIO_WritePin(greenc_GPIO_Port, greenc_Pin, SET);
        display7SEG(counter--);
        // time for led red_row is end. set time for led green_row
        if(counter == 0)	counter = 3;
    }
    else if(count <= 4 && count >= 2){
        // turn off led: yellow_column, red_row
        // turn on led: red_column, green_row
    	// when time is between 2->4
    	HAL_GPIO_WritePin(GPIOA, redr_Pin|yellowc_Pin, SET);
        HAL_GPIO_WritePin(GPIOA, redc_Pin|greenr_Pin, RESET);
        display7SEG(counter--);
        // time for led green_row is end. set time for led yellow_row
        if(counter == 0)	counter = 2;
    }
    else if(count <= 1 && count >= 0){
    	// turn off led: green_row
    	// turn on led:	yellow_row
    	// when time is between 0->1
        HAL_GPIO_WritePin(greenr_GPIO_Port, greenr_Pin, SET);
        HAL_GPIO_WritePin(yellowr_GPIO_Port, yellowr_Pin, RESET);
        display7SEG(counter--);
        // time for led yellow_row is end. set time for led red_row
        if(counter == 0)	counter = 5;
        if(count == 0)	count = 10;
    }
    HAL_Delay(1000);
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, redr_Pin|yellowr_Pin|greenr_Pin|redc_Pin
                          |yellowc_Pin|greenc_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, a_Pin|b_Pin|c_Pin|d_Pin
                          |e_Pin|f_Pin|g_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : redr_Pin yellowr_Pin greenr_Pin redc_Pin
                           yellowc_Pin greenc_Pin */
  GPIO_InitStruct.Pin = redr_Pin|yellowr_Pin|greenr_Pin|redc_Pin
                          |yellowc_Pin|greenc_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : a_Pin b_Pin c_Pin d_Pin
                           e_Pin f_Pin g_Pin */
  GPIO_InitStruct.Pin = a_Pin|b_Pin|c_Pin|d_Pin
                          |e_Pin|f_Pin|g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7SEG(int num){
	if(num == 0){
		HAL_GPIO_WritePin(GPIOB, a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, g_Pin, 1);
	}
	else if(num == 1){
		HAL_GPIO_WritePin(GPIOB, b_Pin|c_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, a_Pin|g_Pin|d_Pin|e_Pin|f_Pin, 1);
	}
	else if(num == 2){
		HAL_GPIO_WritePin(GPIOB, a_Pin|g_Pin|d_Pin|e_Pin|b_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, f_Pin|c_Pin, 1);
	}
	else if(num == 3){
		HAL_GPIO_WritePin(GPIOB, a_Pin|g_Pin|d_Pin|b_Pin|c_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, e_Pin|f_Pin, 1);
	}
	else if(num == 4){
		HAL_GPIO_WritePin(GPIOB, f_Pin|b_Pin|c_Pin|g_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, a_Pin|d_Pin|e_Pin, 1);
	}
	else if(num == 5){
		HAL_GPIO_WritePin(GPIOB, a_Pin|g_Pin|d_Pin|f_Pin|c_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, e_Pin|b_Pin, 1);
	}
	else if(num == 6){
		HAL_GPIO_WritePin(GPIOB, a_Pin|g_Pin|d_Pin|e_Pin|f_Pin|c_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, b_Pin, 1);
	}
	else if(num == 7){
		HAL_GPIO_WritePin(GPIOB, a_Pin|b_Pin|c_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, g_Pin|d_Pin|e_Pin|f_Pin, 1);
	}
	else if(num == 8){
		HAL_GPIO_WritePin(GPIOB, a_Pin|g_Pin|d_Pin|e_Pin|f_Pin|b_Pin|c_Pin, 0);
	}
	else if(num == 9){
		HAL_GPIO_WritePin(GPIOB, a_Pin|g_Pin|d_Pin|b_Pin|c_Pin|f_Pin|b_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, e_Pin, 1);
	}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
