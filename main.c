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
#include "CustomStepperLib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/*
/*
    tryby
    0 - manual
    1 - otworz maks
    2 - zamknij maks
    3 - wedlug czasu
*/
int mode = 0;

int aktualna_pozycja = 0;
int maksymalna_pozycja = 100;

int aktualny_czas = 0;
int czas_otwarcia = 150000;
int czas_zamkniecia = 100000;
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
void otworz(){
    stepper_motor_rotate_by_angle(10, 0, gRPM);
    aktualna_pozycja -= 10;
}

void zamknij(){
    stepper_motor_rotate_by_angle(10, 1, gRPM);
    aktualna_pozycja += 10;
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//k0 - A5,k1-A6,k2-A7,k3-A8,k4-A9,k5-A10,k6-A13,k7-A14
	/*
	    przyciski
	    k0 - tryb manual
	    k1 - tryb otworz maks
	    k2 - tryb zamknij maks
	    k3 - tryb czasu
	    k4 - ustaw pozycje otwartego maks (tylko manual)
	    k5 - ustaw pozycje zamknietego maks (tylko manual)
	    k6 - przesun w dol
	    k7 - przesun w gore
	*/
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET) {//k0
	    mode = 0;
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET) {//k1
	    mode = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_SET) {//k2
	    mode = 2;
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {//k3
	    mode = 3;
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET) {//k4
	    if(mode == 0){
	        aktualna_pozycja = 0;
	    }
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET) {//k5
	    if(mode == 0){
	        maksymalna_pozycja = aktualna_pozycja;
	    }
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == GPIO_PIN_SET) {//k6
	    if(mode == 0){
	        otworz();
	    }
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14) == GPIO_PIN_SET) {//k7
	    if(mode == 0){
	        zamknij();
	    }
	}


}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
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
  while (1)
  {
	  //PD12 - zielony,PD13-pomarañczowy,PD14-czerwony,PD15-niebieski
	  	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == GPIO_PIN_SET) {//k6
	        otworz();
	  	}
	  	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14) == GPIO_PIN_SET) {//k7
	  	        zamknij();

	  	}
	  if(mode == 0){
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, SET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, RESET);

	  } else if(mode == 1){
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, RESET);

	      if(aktualna_pozycja > 0){
	          otworz();
	      }

	  } else if(mode == 2){
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, SET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, RESET);

	      if(aktualna_pozycja < maksymalna_pozycja){
	          zamknij();
	      }

	  } else if(mode == 3){
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, SET);

	     if(aktualny_czas > czas_zamkniecia){
	             if(aktualny_czas > czas_otwarcia){
	                 if(aktualna_pozycja > 0){
	                     otworz();
	                 }

	             }else{
	                 if(aktualna_pozycja < maksymalna_pozycja){
	                     zamknij();
	                 }
	             }
	         }else{
	             if(aktualna_pozycja > 0){
	                otworz();
	             }
	         }

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Silnik_1_Pin|Silnik_2_Pin|Silnik_3_Pin|Silnik_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Silnik_1_Pin Silnik_2_Pin Silnik_3_Pin Silnik_4_Pin */
  GPIO_InitStruct.Pin = Silnik_1_Pin|Silnik_2_Pin|Silnik_3_Pin|Silnik_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 PA7 PA8 
                           PA9 PA10 PA13 PA14 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8 
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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
