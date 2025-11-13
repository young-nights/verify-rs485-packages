/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-08     RT-Thread    first version
 */

#include <rtthread.h>
#include "bsp_sys.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>



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
//  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  rt_device_t rs485_dev = rt_device_find("rs485-1");
  if (rs485_dev == RT_NULL) {
      rt_kprintf("RS485 device not found!\n");
      return -1;
  }
  if (rt_device_open(rs485_dev, RT_DEVICE_FLAG_RDWR) != RT_EOK) {
      rt_kprintf("RS485 open failed!\n");
      return -1;
  }
  rs485_dev_t *pdev = (rs485_dev_t *)rs485_dev;
  rs485_inst_t *rs485_hinst = pdev->hinst;
  rs485_dev_tmo_param_t tmo = { .ack_tmo_ms = 500, .byte_tmo_ms = 10 };
  rt_device_control(rs485_dev, RS485_CTRL_SET_TMO, &tmo);

  rt_uint8_t frame[8] = "Hello!\r\n";
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
      rs485_send(rs485_hinst, frame, 8);
      rt_thread_mdelay(500);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
