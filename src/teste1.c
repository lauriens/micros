#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <galileo2io.h>
#include <libv1.h>

#define DECODER0 "/sys/class/gpio/gpio11/value"
#define DECODER1 "/sys/class/gpio/gpio12/value"
#define OE "/sys/class/gpio/gpio5/value"

int main(int argc,char *argv[])
{
	char countBit;
	int t;
	//while(1)
	//{
		setMotorVoltage(atoi(argv[1]));
		sleep(1);
	//}
	//setMotorVoltage(0);
	sleep(10);
  
	/*int led_fd;
	int button_fd;
	char s;
	
	led_fd=open("/sys/class/gpio/gpio62/value",O_WRONLY);
	button_fd=open("/sys/class/gpio/gpio13/value",O_RDONLY);

	for(;;)
	{
		lseek(button_fd,0,SEEK_SET);
		read(button_fd,&s,sizeof s);
	
		lseek(led_fd,0,SEEK_SET);
		write(led_fd,&s,sizeof s);

		sleep(1);
	}
	
	close(led_fd);
	close(button_fd);

	return 0;*/
}
