#include ".\Headers\appli.h"
char buf[512];
int main (void)
{
	/*Insert system clock initialization code here (sysclk_init()). */
	cpu_irq_disable();
	wdt_disable(WDT);
	sysclk_init();
	board_init();
	delay_init(sysclk_get_cpu_hz());

	/*Insert application code here, after the board has been initialized. */
	Taskman(TASKMAN_NEW);
	Shell(SHELL_NEW);
	
	cpu_irq_enable();
	PushTask(Appli, APPLI_NEW, 0, 0);
	for(;;)
	{
		PopTask();
	}
}
