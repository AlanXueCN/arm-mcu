/* Simple serial console I/O test program */

// $Id$

#include <assert.h>
#include <conio.h>
#include <cpu.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  char buf[32];

  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(2, 115200);

  puts("\033[H\033[2JSTM32F103 Console I/O Test (" __DATE__ " " __TIME__ ")\n");

  for (;;)
  {
    printf("Enter a string: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    printf("You entered %ld bytes, '%s'\n", strlen(buf), buf);
    if (!strcasecmp(buf, "quit")) break;
  }

  assert(0);
}
