/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "fatfs.h"
#include "gpio.h"
#include "spi.h"
#include "tim.h"
#include <display_ssd1963.h>
#include <draw_display.h>
#include <navigate_robot.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs_sd.h"
#include "stdio.h"
#include "string.h"
#include "xpt2046.h"
#include <iostream>
#include "menu_parts.h"
#include <objects.h>

#include "008_Open_Sans_Bold.h"
#include "009_Open_Sans_Bold.h"
#include "010_Open_Sans_Bold.h"
#include "012_Open_Sans_Bold.h"
#include "014_Open_Sans_Bold.h"
#include "016_Open_Sans_Bold.h"
#include "018_Open_Sans_Bold.h"
#include "020_Open_Sans_Bold.h"
#include "022_Open_Sans_Bold.h"
#include "024_Open_Sans_Bold.h"
#include "026_Open_Sans_Bold.h"
#include "028_Open_Sans_Bold.h"
#include "036_Open_Sans_Bold.h"
#include "048_Open_Sans_Bold.h"
#include "072_Open_Sans_Bold.h"
#include "096_Open_Sans_Bold.h"
#include "112_Open_Sans_Bold.h"
#include "128_Open_Sans_Bold.h"
#include "bitmap_arrays.h"
#include "math.h"
#include "servo.h"

#define _Open_Sans_Bold_8 &Open_Sans_Bold_8
#define _Open_Sans_Bold_9 &Open_Sans_Bold_9
#define _Open_Sans_Bold_10 &Open_Sans_Bold_10
#define _Open_Sans_Bold_11 &Open_Sans_Bold_11
#define _Open_Sans_Bold_12 &Open_Sans_Bold_12
#define _Open_Sans_Bold_14 &Open_Sans_Bold_14
#define _Open_Sans_Bold_16 &Open_Sans_Bold_16
#define _Open_Sans_Bold_18 &Open_Sans_Bold_18
#define _Open_Sans_Bold_20 &Open_Sans_Bold_20
#define _Open_Sans_Bold_22 &Open_Sans_Bold_22
#define _Open_Sans_Bold_24 &Open_Sans_Bold_24
#define _Open_Sans_Bold_26 &Open_Sans_Bold_26
#define _Open_Sans_Bold_28 &Open_Sans_Bold_28
#define _Open_Sans_Bold_36 &Open_Sans_Bold_36
#define _Open_Sans_Bold_48 &Open_Sans_Bold_48
#define _Open_Sans_Bold_72 &Open_Sans_Bold_72
#define _Open_Sans_Bold_96 &Open_Sans_Bold_96
#define _Open_Sans_Bold_112 &Open_Sans_Bold_112
#define _Open_Sans_Bold_128 &Open_Sans_Bold_128

#define BUFFER_SIZE 128

#define COLOR565(r, g, b)                                                      \
  (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
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
int liczba_krokow_osi[5];
uint8_t kalibracja_osi[5] =
{ 1, 1, 1, 1, 1 };
int givenSteps[6] =
{ 0, 0, 0, 0, 0, 0 };
int8_t factor[5];
uint8_t was_touched = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int i = 0;

int bufsize(char *buf)
{
	int i = 0;
	while (*buf++ != '\0')
		i++;
	return i;
}

void clear_buffer(char buffer[BUFFER_SIZE])
{
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		buffer[i] = '\0';
	}
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */
	uint16_t max_licz_krokow_osi[6] =
	{ 6400 * 2, 6400 * 2, 8000, 6400 * 2, 6400 * 2, 0 };
	double currentPosition[6];
	double givenPosition[6];
	uint16_t touchX = 0, touchY = 0;
	int kalibracja = 0;
	FIL fil; // File
	FILINFO fno;
	FRESULT fresult; // result
	UINT br, bw;     // File read/write count
	FATFS *pfs;
	DWORD fre_clust;
	uint32_t total, free_space;
	char buffer[BUFFER_SIZE]; // to store strings..
	int number_of_files;
	DIR directory;

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick.
	 */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure the peripherals common clocks */
	PeriphCommonClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	MX_TIM1_Init();
	MX_TIM6_Init();
	MX_FATFS_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_RESET);
	//	/************* The following operation is using PUTS and GETS
	//*********************/
	//
	//	/* Open file to write/ create a file if it doesn't exist */
	//  	fresult = f_open(&fil, "file1.txt", FA_OPEN_ALWAYS | FA_READ |
	//  FA_WRITE);
	//
	//	/* Writing text */
	//	f_puts("This data is from the FILE1.txt. And it was written using
	//...f_puts... ", &fil);
	//
	//	/* Close file */
	//	fresult = f_close(&fil);
	//
	//	if (fresult == FR_OK){}//send_uart ("File1.txt created and the data is
	// written \n");
	//
	//	/* Open file to read */
	//	fresult = f_open(&fil, "file1.txt", FA_READ);
	//
	//	/* Read string from the file */
	//	f_gets(buffer, f_size(&fil), &fil);
	//
	//	//send_uart("File1.txt is opened and it contains the data as shown
	// below\n");
	//	//send_uart(buffer);
	//	//send_uart("\n\n");
	//
	//	/* Close file */
	//	f_close(&fil);
	//
	//	clear_buffer(buffer);
	//
	//
	//
	//
	//
	//	/**************** The following operation is using f_write and f_read
	//**************************/
	//
	//	/* Create second file with read write access and open it */
	//	fresult = f_open(&fil, "file2.txt", FA_CREATE_ALWAYS | FA_WRITE);
	//
	//	/* Writing text */
	//	strcpy (buffer, "This is File2.txt, written using ...f_write... and it
	// says Hello from Controllerstech\n");
	//
	//	fresult = f_write(&fil, buffer, bufsize(buffer), &bw);
	//
	//	//send_uart ("File2.txt created and data is written\n");
	//
	//	/* Close file */
	//	f_close(&fil);
	//
	//
	//
	//	// clearing buffer to show that result obtained is from the file
	//	clear_buffer(buffer);
	//
	//	/* Open second file to read */
	//	fresult = f_open(&fil, "file2.txt", FA_READ);
	//	if (fresult == FR_OK){}//send_uart ("file2.txt is open and the data is
	// shown below\n");
	//
	//	/* Read data from the file
	//	 * Please see the function details for the arguments */
	//	f_read (&fil, buffer, f_size(&fil), &br);
	//	//send_uart(buffer);
	//	//send_uart("\n\n");
	//
	//	/* Close file */
	//	f_close(&fil);
	//
	//	clear_buffer(buffer);
	//
	//
	//	/*********************UPDATING an existing file
	//***************************/
	//
	//	/* Open the file with write access */
	//	fresult = f_open(&fil, "file2.txt", FA_OPEN_EXISTING | FA_READ |
	// FA_WRITE);
	//
	//	/* Move to offset to the end of the file */
	//	fresult = f_lseek(&fil, f_size(&fil));
	//
	//	if (fresult == FR_OK){}//send_uart ("About to update the file2.txt\n");
	//
	//	/* write the string to the file */
	//	fresult = f_puts("This is updated data and it should be in the end",
	//&fil);
	//
	//	f_close (&fil);
	//
	//	//clear_buffer();
	//
	//	/* Open to read the file */
	//	fresult = f_open (&fil, "file2.txt", FA_READ);
	//
	//	/* Read string from the file */
	//	fresult = f_read (&fil, buffer, f_size(&fil), &br);
	//	if (fresult == FR_OK){}//send_uart ("Below is the data from updated
	// file2.txt\n");
	//	//send_uart(buffer);
	//	//send_uart("\n\n");
	//
	//	/* Close file */
	//	f_close(&fil);
	//
	//	clear_buffer(buffer);

	/* to z nieznajomych przyczyn zawiesza mi cały system :C
	 ************************REMOVING FILES FROM THE DIRECTORY
	 ***************************

	 fresult = f_unlink("/file1.txt");
	 if (fresult == FR_OK) {}//send_uart("file1.txt removed
	 successfully...\n");

	 fresult = f_unlink("/file2.txt");
	 if (fresult == FR_OK) {}//send_uart("file2.txt removed
	 successfully...\n");

	 Unmount SDCARD
	 fresult = f_mount(NULL, "/", 1);
	 if (fresult == FR_OK) {}//send_uart ("SD CARD UNMOUNTED
	 successfully...\n");
	 */

	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET); // Ustawienie F_CS na low
	Init_SSD1963();


	init_objects();
	main_top_menu.draw();
	main_left_menu.draw();
	main_right_menu.draw();
	project_explorer_menu.draw();
	projects_explorer main_file_explorer;
//	while(1)
//	{
//
//	}



	//init_SD_card();
	//create_file("text21.txt");
	//draw_file_list(1, 12, false, by_name);
	//unmount_SD_card();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	int allertX = 220; // MAX size is 220x200 - with bigger tabs malloc has
					   // problem
	int allertY = 200;
	//uint16_t *save = (uint16_t*) malloc(allertX * allertY * sizeof(uint16_t));
	// kalibracja robota
	//        	HAL_Delay(5000);
	//        	kalibracja_robota(givenSteps, liczba_krokow_osi,
	//        kalibracja_osi); 	givenPosition[0]=30; 	givenPosition[1]=0;
	//        	givenPosition[2]=22;
	//        	givenPosition[3]=0;
	//        	givenPosition[4]=90;
	//        	givenPosition[5]=90;
	//        	licz_kroki(givenPosition, givenSteps, currentPosition);
	//        	kalibracja =1;
	allert first_allert =
			allert(10, 10, 250, 0xD6BA, "UWAGA",
					"niemozliwe ze to zadzialalo za pierwszym razem. to jest naprawde niesamowite",
					10, YELLOW, const_cast<GFXfont*>(_Open_Sans_Bold_18));
	first_allert.draw();
	// przygotowanie dotyku
	XPT2046_Init();
	__HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin); // czyszczenie zgłoszonego przerwania
	was_touched = 0;
	//main_file_explorer.create_file("testowy_plik_z_nowego_obiektowego_softu.txt");
	while (1)//moje oszukane menu
	{
		if (was_touched == 1)
		{

			uint16_t touchx, touchy;
			was_touched = 0;
			NVIC_DisableIRQ(EXTI9_5_IRQn);
			touchx = getX();
			touchy = getY();
			if (first_allert.check_pressed(touchx, touchy))
			{
//				HAL_Delay(5000);
//				first_allert.draw();
			}
			if(project_explorer_menu.check_pressed(
					touchx, touchy)==2){
				main_file_explorer.delete_file();
			}
			main_file_explorer.handle_pressed(touchx, touchy);
			XPT2046_Init();
			__HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin); // czyszczenie zgłoszonego przerwania
			NVIC_EnableIRQ(EXTI9_5_IRQn);
		}
	}
	list_dialog first_list = list_dialog(300, 10, 200, 0xD6BA, "testowa lista",
	{ "nie wierze", "a jednak", "no popatrz" }, 10, BLACK,
			const_cast<GFXfont*>(_Open_Sans_Bold_18));
	first_list.draw();


	while (1)//tego menu nie usuwać
	{
		if (was_touched == 1)
		{
			was_touched = 0;
			NVIC_DisableIRQ(EXTI9_5_IRQn);
			uint16_t touchx, touchy;
			char buffer1[10] = ""; // Bufor na konwertowaną wartość
			char buffer2[10] = ""; // Bufor na konwertowaną wartość
			TFT_Draw_Fill_Round_Rect(280, 180, 200, 60, 10, 0xCFFF);
			touchx = getX();
			sprintf(buffer1, "X%d", touchx); // Konwersja wartości do ciągu znaków
			touchy = getY();
			sprintf(buffer2, "Y%d", touchy); // Konwersja wartości do ciągu znaków

			LCD_Font(300, 200, buffer1, _Open_Sans_Bold_28, 1, BLACK);
			LCD_Font(300, 220, buffer2, _Open_Sans_Bold_28, 1, BLACK);
			HAL_Delay(100);



			int value = first_list.check_pressed(touchx, touchy);
			if (value > -1)
			{
				TFT_Draw_Fill_Round_Rect(280, 280, 250, 60, 10, 0xCFFF);
				sprintf(buffer1, "choosen: %i", value);
				LCD_Font(300, 300, buffer1, _Open_Sans_Bold_28, 1, BLACK);
				HAL_Delay(5000);
				first_list.draw();
			}
			if (touchx >= 696 && touchx <= 696 + 88 && touchy >= 9
					&& touchy <= 9 + 47)
			{ // 696, pos_y, 88, 47,
//				uint16_t counter =
//						TFT_Draw_List(400, 200, 100, "TYPE:",
//								"to jest nowe powitanie które zawiera znaki nowej\n lini",
//								save, _Open_Sans_Bold_14);
//				HAL_Delay(3000);
//				TFT_Restore_Area(400, 200, 100, 47 + 1 + 34 + 35 * counter,
//						save);
			}
			XPT2046_Init();
			__HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin); // czyszczenie zgłoszonego przerwania
			NVIC_EnableIRQ(EXTI9_5_IRQn);
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
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
	{
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType =
	RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 100;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
	RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
	RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief Peripherals Common Clock Configuration
 * @retval None
 */
void PeriphCommonClock_Config(void)
{
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct =
	{ 0 };

	/** Initializes the peripherals clock
	 */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CKPER;
	PeriphClkInitStruct.CkperClockSelection = RCC_CLKPSOURCE_HSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if (GPIO_Pin == M1_S_Pin && kalibracja_osi[0] == 0)
	{
		liczba_krokow_osi[0] = 0;
		givenSteps[0] = 0;
		kalibracja_osi[0] = 1;
	}
	if (GPIO_Pin == M2_S_Pin && kalibracja_osi[1] == 0)
	{
		liczba_krokow_osi[1] = 10; // 20
		givenSteps[1] = 10;        // 20
		kalibracja_osi[1] = 1;
	}
	if (GPIO_Pin == M3_S_Pin && kalibracja_osi[2] == 0)
	{
		liczba_krokow_osi[2] = 0;
		givenSteps[2] = 0;
		kalibracja_osi[2] = 1;
	}
	if (GPIO_Pin == M4_S_Pin && kalibracja_osi[3] == 0)
	{
		liczba_krokow_osi[3] = 300;
		givenSteps[3] = 300;
		kalibracja_osi[3] = 1;
	}
	if (GPIO_Pin == M5_S_Pin && kalibracja_osi[4] == 0)
	{
		liczba_krokow_osi[4] = 1600; // 1790
		givenSteps[4] = 1600;        // 1790
		kalibracja_osi[4] = 1;
	}

	if (GPIO_Pin == T_IRQ_Pin)
	{
		was_touched = 1;
		//		__HAL_GPIO_EXTI_CLEAR_IT(EXTI15_10_IRQn);//czyszczenie
		// zgłoszonego przerwania 		NVIC_DisableIRQ(EXTI15_10_IRQn);
		// uint16_t touchx, touchy; 		char buffer1[10]=""; // Bufor na
		// konwertowaną wartość 		char buffer2[10]=""; // Bufor na
		// konwertowaną wartość 		TFT_Draw_Fill_Round_Rect (280, 180, 200,
		// 60, 10,  0xCFFF); 		touchx = getX();//pobrannie wartości X
		//		sprintf(buffer1, "X%d", touchx); // Konwersja wartości do ciągu
		// znaków 		touchy = getY();//pobrannie wartości Y
		// sprintf(buffer2, "Y%d", touchy); // Konwersja wartości do ciągu znaków
		//
		//		LCD_Font(300, 200,  buffer1, _Open_Sans_Bold_28, 1, BLACK);
		//		LCD_Font(300, 220,  buffer2, _Open_Sans_Bold_28, 1, BLACK);
		//		HAL_Delay(1000);
		//		XPT2046_Init();//włączenie przerwań
		//		__HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin);//czyszczenie zgłoszonego
		// przerwania 		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin); // czyszczenie zgłoszonego przerwania
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM6)
	{
		if (givenSteps[0] != liczba_krokow_osi[0])
		{
			setDuration(M1_DIR_GPIO_Port, M1_DIR_Pin, liczba_krokow_osi[0],
					givenSteps[0], &factor[0]);
			moveMotorWithPosition(M1_STEP_GPIO_Port, M1_STEP_Pin,
					&liczba_krokow_osi[0], factor[0]);
		}
		if (givenSteps[1] != liczba_krokow_osi[1])
		{
			setDuration(M2_DIR_GPIO_Port, M2_DIR_Pin, liczba_krokow_osi[1],
					givenSteps[1], &factor[1]);
			moveMotorWithPosition(M2_STEP_GPIO_Port, M2_STEP_Pin,
					&liczba_krokow_osi[1], factor[1]);
		}
		if (givenSteps[2] != liczba_krokow_osi[2])
		{
			setDuration(M3_DIR_GPIO_Port, M3_DIR_Pin, liczba_krokow_osi[2],
					givenSteps[2], &factor[2]);
			setDuration(M5_DIR_GPIO_Port, M5_DIR_Pin, liczba_krokow_osi[2],
					givenSteps[2], &factor[2]);
			moveMotorWithPosition(M3_STEP_GPIO_Port, M3_STEP_Pin,
					&liczba_krokow_osi[2], factor[2]);
			// opcjonalny delay - możliwe że trzeba dołożyć
			simpleMoveMotor(M5_STEP_GPIO_Port, M5_STEP_Pin);
			simpleMoveMotor(M3_STEP_GPIO_Port, M3_STEP_Pin);
		}
		if (givenSteps[3] != liczba_krokow_osi[3])
		{
			setDuration(M4_DIR_GPIO_Port, M4_DIR_Pin, liczba_krokow_osi[3],
					givenSteps[3], &factor[3]);
			moveMotorWithPosition(M4_STEP_GPIO_Port, M4_STEP_Pin,
					&liczba_krokow_osi[3], factor[3]);
		}
		if (givenSteps[4] != liczba_krokow_osi[4])
		{
			setDuration(M5_DIR_GPIO_Port, M5_DIR_Pin, liczba_krokow_osi[4],
					givenSteps[4], &factor[4]);
			moveMotorWithPosition(M5_STEP_GPIO_Port, M5_STEP_Pin,
					&liczba_krokow_osi[4], factor[4]);
			// opcjonalny delay - możliwe że trzeba dołożyć
			simpleMoveMotor(M5_STEP_GPIO_Port, M5_STEP_Pin);
		}
		set_ang(givenSteps[5], 0);
		HAL_GPIO_WritePin(M6_STEP_GPIO_Port, M6_STEP_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(M6_STEP_GPIO_Port, M6_STEP_Pin, GPIO_PIN_RESET);
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

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
