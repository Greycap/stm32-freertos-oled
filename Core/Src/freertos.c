/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "oled.h"
#include "stdio.h"
#include "font.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Task_LED */
osThreadId_t Task_LEDHandle;
const osThreadAttr_t Task_LED_attributes = {
  .name = "Task_LED",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_OLED */
osThreadId_t Task_OLEDHandle;
const osThreadAttr_t Task_OLED_attributes = {
  .name = "Task_OLED",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask_LED(void *argument);
void StartTask_OLED(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_LED */
  Task_LEDHandle = osThreadNew(StartTask_LED, NULL, &Task_LED_attributes);

  /* creation of Task_OLED */
  Task_OLEDHandle = osThreadNew(StartTask_OLED, NULL, &Task_OLED_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartTask_LED */
/**
  * @brief  Function implementing the Task_LED thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask_LED */
void StartTask_LED(void *argument)
{
  /* USER CODE BEGIN StartTask_LED */
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(GPIOA, LED_G_Pin); // 板载LED，根据你的实际引脚改
    osDelay(1000);
  }
  /* USER CODE END StartTask_LED */
}

/* USER CODE BEGIN Header_StartTask_OLED */
/**
* @brief Function implementing the Task_OLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_OLED */
void StartTask_OLED(void *argument)
{
  /* USER CODE BEGIN StartTask_OLED */
	
	/* 必须在任务内初始化OLED */
  OLED_Init();
  uint32_t run_sec = 0; // 运行秒数计数
	
	
  /* Infinite loop */
  for(;;)
  {
	  
	  /* 1. 清空显存，开始新一帧 */
    OLED_NewFrame();

    /* 2. 绘制内容 */
    OLED_PrintASCIIString(0, 0, "FreeRTOS OLED", &afont16x8, OLED_COLOR_NORMAL);
    
    // 显示运行时间
    char buf[20];
    snprintf(buf, sizeof(buf), "Run: %d s", run_sec);
    OLED_PrintASCIIString(0, 16, buf, &afont16x8, OLED_COLOR_NORMAL);

    // 底部装饰图形
    OLED_DrawRectangle(0, 48, 100, 12, OLED_COLOR_NORMAL);
    OLED_DrawFilledCircle(110, 54, 6, OLED_COLOR_NORMAL);

    /* 3. 把显存刷新到屏幕 */
    OLED_ShowFrame();

    run_sec++;
    osDelay(1000);
  }
  /* USER CODE END StartTask_OLED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

