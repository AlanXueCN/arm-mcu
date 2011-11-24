/* Simple bit twiddler test program */

// $Id: test_gpio.c 3199 2011-10-18 11:28:12Z svn $

static const char revision[] = "$Id: test_gpio.c 3199 2011-10-18 11:28:12Z svn $";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef STM32F4_DISCOVERY
  gpiopin_configure(GPIOPIN60, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN61, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN62, GPIOPIN_OUTPUT);
  gpiopin_configure(GPIOPIN63, GPIOPIN_OUTPUT);

  for (i = 0;; i++)
  {
    GPIOPIN60OUT = i >> 19;
    GPIOPIN61OUT = i >> 20;
    GPIOPIN62OUT = i >> 21;
    GPIOPIN63OUT = i >> 22;
  }
#endif
}