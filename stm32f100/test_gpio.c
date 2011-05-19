/* Simple bit twiddler test program */

// $Id: test_gpio.c 2649 2011-05-19 16:21:44Z svn $

static const char revision[] = "$Id: test_gpio.c 2649 2011-05-19 16:21:44Z svn $";

#include <cpu.h>

void main(void)
{
  GPIO_InitTypeDef config;
  volatile unsigned long i;

// Initialize CPU core

  cpu_init(DEFAULT_CPU_FREQ);

// Enable peripheral clock

#ifdef BOARD_STM32_VALUE_LINE_DISCOVERY
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

// Configure PC.9 as output push-pull (LED)

  GPIO_StructInit(&config);
  config.GPIO_Pin =  GPIO_Pin_9;
  config.GPIO_Mode = GPIO_Mode_Out_PP;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &config);

  for (;;)
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_9);
    for (i = 0; i < 500000; i++);

    GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    for (i = 0; i < 500000; i++);
  }
#endif
}