/* Simple FreeRTOS test program for the STM32 ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#ifndef FREERTOS
#error You must define FREERTOS to compile this FreeRTOS application
#endif

#include <assert.h>
#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#define MESSAGE_PERIOD	4000

xSemaphoreHandle console_lock;

void putsTaskFunction(void *parameters)
{
  char *message = parameters;

  portTickType waketime = xTaskGetTickCount();

  for (;;)
  {
    vTaskDelayUntil(&waketime, (MESSAGE_PERIOD/2 + (lrand48() % (MESSAGE_PERIOD/2)))/portTICK_RATE_MS);

    xSemaphoreTake(console_lock, portMAX_DELAY);
    puts(message);
    xSemaphoreGive(console_lock);
  }
}

void LEDTaskFunction(void *parameters)
{
  portTickType waketime = xTaskGetTickCount();

// Configure LED(s)

#ifdef OLIMEX_STM32_P103
// Enable GPIOC peripheral clock

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

// Configure PC.12 as output push-pull (LED)

  GPIO_InitTypeDef config;

  GPIO_StructInit(&config);
  config.GPIO_Pin =  GPIO_Pin_12;
  config.GPIO_Mode = GPIO_Mode_Out_PP;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &config);

// Turn LED off

  GPIO_SetBits(GPIOC, GPIO_Pin_12);
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
// Enable GPIOC peripheral clock

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

// Configure PC.9 as output push-pull (LED)

  GPIO_InitTypeDef config;

  GPIO_StructInit(&config);
  config.GPIO_Pin =  GPIO_Pin_9;
  config.GPIO_Mode = GPIO_Mode_Out_PP;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &config);

// Turn LED off

  GPIO_SetBits(GPIOC, GPIO_Pin_9);
#endif

  for (;;)
  {
    vTaskDelayUntil(&waketime, 1000/portTICK_RATE_MS);

// Toggle LED(s)

#ifdef OLIMEX_STM32_P103
      GPIO_WriteBit(GPIOC, GPIO_Pin_12, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_12));
#endif

#ifdef STM32_VALUE_LINE_DISCOVERY
      GPIO_WriteBit(GPIOC, GPIO_Pin_9, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9));
#endif
  }
}

int main(void)
{
  xTaskHandle task1;
  xTaskHandle task2;
  xTaskHandle task3;

  cpu_init(DEFAULT_CPU_FREQ);

  serial_stdio(CONSOLE_PORT, 115200);

// Display version information

  puts("\033[H\033[2JSTM32 FreeRTOS Test (" __DATE__ " " __TIME__ ")\n");
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s  FreeRTOS:%s\n\n", CPUFREQ, __VERSION__,
    tskKERNEL_VERSION_NUMBER);

// Create mutex to arbitrate console output

  console_lock = xSemaphoreCreateMutex();
  if (console_lock == NULL)
  {
    puts("ERROR: xSemaphoreCreateMutex() for console_lock failed!");
    fflush(stdout);
    assert(0);
  }

// Create a couple of tasks

  if (xTaskCreate(putsTaskFunction, (signed char *) "task1", 256, "This is Task 1", 1, &task1) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task1 failed!");
    fflush(stdout);
    assert(0);
  }

  if (xTaskCreate(putsTaskFunction, (signed char *) "task2", 256, "This is Task 2", 1, &task2) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task2 failed!");
    fflush(stdout);
    assert(0);
  }

  if (xTaskCreate(LEDTaskFunction, (signed char *) "task3", 256, NULL, 1, &task3) != pdPASS)
  {
    puts("ERROR: xTaskCreate() for task3 failed!");
    fflush(stdout);
    assert(0);
  }

  vTaskStartScheduler();
  assert(0);
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
  printf("ERROR: vApplicationStackOverflowHook(): Task \"%s\" overflowed its stack\n", pcTaskName);
  fflush(stdout);
  assert(0);
}
