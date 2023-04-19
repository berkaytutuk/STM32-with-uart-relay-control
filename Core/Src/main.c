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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t Uart_Data[30]="";

uint16_t data,flash_data=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

uint16_t Read_Flash(uint32_t  adr)
{
  uint16_t * Pntr = (uint16_t *)adr;
  return(*Pntr);
}





void Erase_Flash (uint32_t adr)
{
	FLASH->KEYR=0x45670123;  					// Silme veya yazma islemi yapilmadan önce Flash kilidi mutlaka açilmalidir.
  FLASH->KEYR=0xCDEF89AB;						// FLASH->KEYR registerine KEY1 ve KEY2 degerleri atandiginda Flash kilidi açilir.
  FLASH->CR|=0x00000002;            //PER enable
  FLASH->AR=adr;                    //FLASH->AR registerine silinmek istenen adres yazilir
  FLASH->CR|=0x00000040;            //STRT anable
  while((FLASH->SR&0x00000001));    //Islem bitene kadar bekle(BUSY kontrol ediliyor)
  FLASH->CR &= ~0x00000042;         //FLASH->CR ilk durumuna aliniyor (kilit hala açik!)
	FLASH->CR=0x00000080;  						//FLASH_CR registeri resetlendiginde FLASH kiltlenmis olur
}

void Write_Flash (uint32_t adr, uint16_t data)
{
	FLASH->KEYR=0x45670123;  					// Silme veya yazma islemi yapilmadan önce Flash kilidi mutlaka açilmalidir.
  FLASH->KEYR=0xCDEF89AB;						// FLASH->KEYR registerine KEY1 ve KEY2 degerleri atandiginda Flash kilidi açilir.
  FLASH->CR|=0x00000001;            //PG enable
  *(__IO uint16_t*)adr = data;      //istenen adrese istenen data yaziliyor
  while((FLASH->SR&0x00000001));    //Islem bitene kadar bekle(BUSY kontrol ediliyor)
	FLASH->CR=0x00000080;  					  //FLASH_CR registeri resetlendiginde FLASH kiltlenmis olur
}


//relay1 flash on
void flash()
{

			   Erase_Flash(0x0800FC00); // adresteki değer silindi.
			   data = 9;
			   Write_Flash(0x0800FC00,data); // 16 bitlik veri adrese yazıldı.
			   //HAL_Delay(500); // flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
			  // flash_data =Read_Flash(0x0800FC00);

}

//relay1 flash off
void flash2()
{

	 		   Erase_Flash(0x0800FC00); // adresteki değer silindi.
	 		   data = 7;
	 		   Write_Flash(0x0800FC00,data); // 16 bitlik veri adrese yazıldı.
	 		   //HAL_Delay(500); // flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
	 		  // flash_data =Read_Flash(0x0800FC00);
}

/*
//////////////////////////////////////////////////////////////////

//relay2 flash on
void flash()
{

			   Erase_Flash(0x0800FC00); // adresteki değer silindi.
			   data = 9;
			   Write_Flash(0x0800FC00,data); // 16 bitlik veri adrese yazıldı.
			   //HAL_Delay(500); // flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
			   flash_data =Read_Flash(0x0800FC00);

}

//relay2 flash off
void flash2()
{

	 		   Erase_Flash(0x0800FC00); // adresteki değer silindi.
	 		   data = 7;
	 		   Write_Flash(0x0800FC00,data); // 16 bitlik veri adrese yazıldı.
	 		   //HAL_Delay(500); // flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
	 		   flash_data =Read_Flash(0x0800FC00);
}

//////////////////////////////////////////////////////////////////
//relay3 flash on
void flash()
{

			   Erase_Flash(0x0800FC00); // adresteki değer silindi.
			   data = 9;
			   Write_Flash(0x0800FC00,data); // 16 bitlik veri adrese yazıldı.
			   //HAL_Delay(500); // flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
			   flash_data =Read_Flash(0x0800FC00);

}

//relay3 flash off
void flash2()
{

	 		   Erase_Flash(0x0800FC00); // adresteki değer silindi.
	 		   data = 7;
	 		   Write_Flash(0x0800FC00,data); // 16 bitlik veri adrese yazıldı.
	 		   //HAL_Delay(500); // flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
	 		   flash_data =Read_Flash(0x0800FC00);
}

//////////////////////////////////////////////////////////////////
//relay4 flash on
void flash()
{

			   Erase_Flash(0x0800FC00); // adresteki değer silindi.
			   data = 9;
			   Write_Flash(0x0800FC00,data); // 16 bitlik veri adrese yazıldı.
			   //HAL_Delay(500); // flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
			   flash_data =Read_Flash(0x0800FC00);

}

//relay4 flash off
void flash2()
{

	 		   Erase_Flash(0x0800FC00); // adresteki değer silindi.
	 		   data = 7;
	 		   Write_Flash(0x0800FC00,data); // 16 bitlik veri adrese yazıldı.
	 		   //HAL_Delay(500); // flash_data degiskeninin baslangiçta sifir oldugunu görebilmek için gecikme eklendi.
	 		   flash_data =Read_Flash(0x0800FC00);
}

//////////////////////////////////////////////////////////////////
*/




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
HAL_Delay(3000);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
//  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  flash_data =Read_Flash(0x0800FC00);
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	//  HAL_UART_Receive(&huart2, Uart_Data, 21, 1000);
	  HAL_UART_Receive(&huart1, Uart_Data, 30, 1000);

	  //relay1 on

	  if(Uart_Data[0]==0x6F&&Uart_Data[1]==0x6E)
	  {
		 //  flash();

			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
			  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, SET);
			  HAL_Delay(1500);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
			  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, RESET);
			  HAL_UART_Init(&huart1);
			 // HAL_UART_Init(&huart2);

	  }

	  //relay1 off

	/* if((Uart_Data[0]==0x55&&Uart_Data[1]==0xaa&&Uart_Data[2]==0x08&&Uart_Data[3]==0x02&&Uart_Data[4]==0x04&&Uart_Data[5]==0x01&&Uart_Data[6]==0x01&&Uart_Data[7]==0x00&&Uart_Data[8]==0x01&&Uart_Data[9]==0x10)||(flash_data==7))
	  {

		  flash2();

			   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
			   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, SET);
			   HAL_UART_Init(&huart1);
	  }
*/
	  for(int i=0;i<31;i++){

		  Uart_Data[i]=0;

	  }
/*
	  if(Uart_Data[8]==0x0&&Uart_Data[9]==0x18)
	  {

		  HAL_NVIC_SystemReset();
	  }*/

/*
////////////////////////////////////////////////////////
	  //relay2 on
	  	  if((Uart_Data[0]==0x55&&Uart_Data[1]==0xaa&&Uart_Data[2]==0x9&&Uart_Data[3]==0x1&&Uart_Data[4]==0x2&&Uart_Data[5]==0x1&&Uart_Data[6]==0x1&&Uart_Data[7]==0xd)||(flash_data==9))
	  	  {
	  		      flash();
	  			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
	  			  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, SET);
	  	  }

	  //relay2 off
	  	  if((Uart_Data[0]==0x55&&Uart_Data[1]==0xaa&&Uart_Data[2]==0x9&&Uart_Data[3]==0x1&&Uart_Data[4]==0x2&&Uart_Data[5]==0x2&&Uart_Data[6]==0x1&&Uart_Data[7]==0xe)||(flash_data==7))
	  	  {
	  		       flash2();
	  			   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
	  			   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, RESET);
	  	  }
/////////////////////////////////////////////////////////
	  //relay3 on
	  	  if((Uart_Data[0]==0x55&&Uart_Data[1]==0xaa&&Uart_Data[2]==0x9&&Uart_Data[3]==0x1&&Uart_Data[4]==0x2&&Uart_Data[5]==0x1&&Uart_Data[6]==0x1&&Uart_Data[7]==0xd)||(flash_data==9))
	  		  {
	  			   flash();
	  			   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
	  			   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, SET);
	  		  }

	   //relay3 off
	      if((Uart_Data[0]==0x55&&Uart_Data[1]==0xaa&&Uart_Data[2]==0x9&&Uart_Data[3]==0x1&&Uart_Data[4]==0x2&&Uart_Data[5]==0x2&&Uart_Data[6]==0x1&&Uart_Data[7]==0xe)||(flash_data==7))
	  		  {
	  			  flash2();
                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
	  			  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, RESET);
	  		  }
/////////////////////////////////////////////////////////
		  //relay4 on
		  	  if((Uart_Data[0]==0x55&&Uart_Data[1]==0xaa&&Uart_Data[2]==0x9&&Uart_Data[3]==0x1&&Uart_Data[4]==0x2&&Uart_Data[5]==0x1&&Uart_Data[6]==0x1&&Uart_Data[7]==0xd)||(flash_data==9))
		  		  {
		  			   flash();
		  			   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
		  			   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, SET);
		  		  }

		   //relay4 off
		      if((Uart_Data[0]==0x55&&Uart_Data[1]==0xaa&&Uart_Data[2]==0x9&&Uart_Data[3]==0x1&&Uart_Data[4]==0x2&&Uart_Data[5]==0x2&&Uart_Data[6]==0x1&&Uart_Data[7]==0xe)||(flash_data==7))
		  		  {
		  			  flash2();
	                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		  			  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, RESET);
		  		  }
*/
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

  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Initializes the CPU, AHB and APB busses clocks 
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
  huart1.Init.BaudRate = 9600;
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
  huart2.Init.BaudRate = 9600;
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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, relay4_Pin|relay3_Pin|relay2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(relay1_GPIO_Port, relay1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(redled_GPIO_Port, redled_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : relay4_Pin relay3_Pin relay2_Pin */
  GPIO_InitStruct.Pin = relay4_Pin|relay3_Pin|relay2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : relay1_Pin */
  GPIO_InitStruct.Pin = relay1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(relay1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : redled_Pin */
  GPIO_InitStruct.Pin = redled_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(redled_GPIO_Port, &GPIO_InitStruct);

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
