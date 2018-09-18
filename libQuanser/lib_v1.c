#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <galileo2io.h>

#define PWM_FREQ 1500
#define PWM_PERIOD "/sys/class/pwm/pwmchip0/device/pwm_period"
#define DUTY_CYCLE "/sys/class/pwm/pwmchip0/pwm11/duty_cycle"
#define PWM_ENABLE "/sys/class/pwm/pwmchip0/pwm11/enable"
#define DECODER0 "/sys/class/gpio/gpio11/value"
#define DECODER1 "/sys/class/gpio/gpio12/value"
#define DECODER2 "/sys/class/gpio/gpio13/value"
#define DECODER3 "/sys/class/gpio/gpio16/value"
#define DECODER4 "/sys/class/gpio/gpio6/value"
#define DECODER5 "/sys/class/gpio/gpio0/value"
#define DECODER6 "/sys/class/gpio/gpio1/value"
#define DECODER7 "/sys/class/gpio/gpio4/value"
#define SEL "/sys/class/gpio/gpio7/value"
#define OE "/sys/class/gpio/gpio5/value"
#define RST "/sys/class/gpio/gpio7/value"
#define END_OF_COURSE1 "/sys/class/gpio/gpio38/value"
#define END_OF_COURSE2 "/sys/class/gpio/gpio40/value"


void setMotorVoltage (int voltage)
{
	int duty_cycle;
	int period = 1000000000 / PWM_FREQ;
	char str[50];
	
	if (-27 > voltage || voltage > 27)
	{
		printf ("Voltage not suported! Please enter a value between -27 and 27\n");
		return;
	}
	
	duty_cycle = (int) ((1.0 / 54.0) * voltage + 0.5) * period;
	snprintf(str, sizeof(str), "%d\n", duty_cycle);
	pputs(DUTY_CYCLE, duty_cycle);
	
	setPWM();
}

void setPWM ()
{
	char pwm_period[50];
	int period = 1000000000 / PWM_FREQ;
	
	snprintf(pwm_period, sizeof(pwm_period), "%d\n", period);
	pputs(PWM_PERIOD, pwm_period);
	pputs(PWM_ENABLE, "1");
}

int readCounter_firstversion(int firstRead, int firstCount)
{
	int count = 0;
	char countBit;
	
	pputs(SEL, "0");
	
	count += atoi(pgets(&countBit, sizeof(countBit), DECODER0);
	count += 2 * atoi(pgets(&countBit, sizeof(countBit), DECODER1);
	count += 4 * atoi(pgets(&countBit, sizeof(countBit), DECODER2);
	count += 8 * atoi(pgets(&countBit, sizeof(countBit), DECODER3);
	count += 16 * atoi(pgets(&countBit, sizeof(countBit), DECODER4);
	count += 32 * atoi(pgets(&countBit, sizeof(countBit), DECODER5);
	count += 64 * atoi(pgets(&countBit, sizeof(countBit), DECODER6);
	count += 128 * atoi(pgets(&countBit, sizeof(countBit), DECODER7);
	
	puts(SEL, "1");
	
	count += 256 * atoi(pgets(&countBit, sizeof(countBit), DECODER0);
	count += 512 * atoi(pgets(&countBit, sizeof(countBit), DECODER1);
	count += 1024 * atoi(pgets(&countBit, sizeof(countBit), DECODER2);
	count += 2048 * atoi(pgets(&countBit, sizeof(countBit), DECODER3);
	count += 4096 * atoi(pgets(&countBit, sizeof(countBit), DECODER4);
	count += 8192 * atoi(pgets(&countBit, sizeof(countBit), DECODER5);
	count += 16384 * atoi(pgets(&countBit, sizeof(countBit), DECODER6);
	count += 32768 * atoi(pgets(&countBit, sizeof(countBit), DECODER7);
	
	if(firstRead)
	    return count;
	else
	    count = (count - firstCount) * 0.0015;
	
	return count;
}

void resetCount()
{
	pputs(RST, "0");
	usleep(10);
	pputs(RST, "1");
}



int readEndOfCourse(){
	char end_bit1;
	char end_bit2;

	return ((atoi(pgets(&end_bit1,sizeof(end_bit1),ENDOFCOURSE1))) || (atoi(pgets(&end_bit2,sizeof(end_bit2),ENDOFCOURSE2))));
}








