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
#define DECODER3 "/sys/class/gpio/gpio14/value"
#define DECODER4 "/sys/class/gpio/gpio6/value"
#define DECODER5 "/sys/class/gpio/gpio0/value"
#define DECODER6 "/sys/class/gpio/gpio1/value"
#define DECODER7 "/sys/class/gpio/gpio4/value"
#define SEL "/sys/class/gpio/gpio7/value"
#define OE "/sys/class/gpio/gpio5/value"
#define RST "/sys/class/gpio/gpio7/value"
#define END_OF_COURSE1 "/sys/class/gpio/gpio38/value"
#define END_OF_COURSE2 "/sys/class/gpio/gpio40/value"
#define R_EN "/sys/class/gpio/gpio48/value"
#define L_EN "/sys/class/gpio/gpio50/value"

///
/// Function to initialize the PWM
///
void setPWM()
{
	char pwm_period[50];
	int period = 1000000000 / PWM_FREQ;

	///
	/// Creates a string with the defined period
	///
	snprintf(pwm_period, sizeof(pwm_period), "%d\n", period);

	///
	/// Sets the PWM period, enables it and enables the Right and Left pins of the H-bridge (so the hardware will determine to which direction the arm should go)
	///
	pputs(PWM_PERIOD, pwm_period);
	pputs(PWM_ENABLE, "1");
	pputs(R_EN, "1");
	pputs (L_EN, "1");
}

///
/// Function to change the pwm voltage 
///
void setMotorVoltage (int voltage)
{
	int duty_cycle;
	float period = 1000000000 / PWM_FREQ;
	char str[50];

///
/// The voltage can't be bigger than 27, or lesser than -27
///
	if (-27 > voltage || voltage > 27)
	{
		printf ("Voltage not suported! Please enter a value between -27 and 27\n");
		return;
	}

	pputs(PWM_ENABLE, "0");

	///
	/// Uses a basic proportion, to determine the desired duty cycle;
	///
	duty_cycle = ((1.0 / 54.0) * voltage + 0.5) * period;

	///
	/// Converts the found result into a string;
	///
	snprintf(str, sizeof(str), "%d\n", duty_cycle);

	///
	/// Saves the string into the file;
	///
	pputs(DUTY_CYCLE, str);

	///
	/// Re-enables the PWM
	///
	pputs(PWM_ENABLE, "1");
}

///
/// Function to read the position of the arm, based on the output of the counter
///
int readCounter(int firstRead, int totalCount)
{
	int count = 0;
	char countBit;

	pputs(OE, "1");

	///
	/// First read the 8 least significant bits
	///
	pputs(SEL, "1"); // para o htcl-2017 o bit sel eh 1 para o byte "baixo"

	count += atoi(pgets(&countBit, sizeof(countBit), DECODER0));
	count += 2 * atoi(pgets(&countBit, sizeof(countBit), DECODER1));
	count += 4 * atoi(pgets(&countBit, sizeof(countBit), DECODER2));
	count += 8 * atoi(pgets(&countBit, sizeof(countBit), DECODER3));
	count += 16 * atoi(pgets(&countBit, sizeof(countBit), DECODER4));
	count += 32 * atoi(pgets(&countBit, sizeof(countBit), DECODER5));
	count += 64 * atoi(pgets(&countBit, sizeof(countBit), DECODER6));
	count += 128 * atoi(pgets(&countBit, sizeof(countBit), DECODER7));

	///
	/// Then, the 8 most significant bits
	///
	pputs(SEL, "0"); // para o htcl-2017 o bit sel eh 0 para o byte "alto"

	count += 256 * atoi(pgets(&countBit, sizeof(countBit), DECODER0));
	count += 512 * atoi(pgets(&countBit, sizeof(countBit), DECODER1));
	count += 1024 * atoi(pgets(&countBit, sizeof(countBit), DECODER2));
	count += 2048 * atoi(pgets(&countBit, sizeof(countBit), DECODER3));
	count += 4096 * atoi(pgets(&countBit, sizeof(countBit), DECODER4));
	count += 8192 * atoi(pgets(&countBit, sizeof(countBit), DECODER5));
	count += 16384 * atoi(pgets(&countBit, sizeof(countBit), DECODER6));
	count += 32768 * atoi(pgets(&countBit, sizeof(countBit), DECODER7));

	///
	/// If it's the first, or second time reading the position, returns the raw reading, to store the value equivalent to zero (first position)
	///
	if(firstRead)
	    return count;
	///
	/// If it's not the first, or second reading, calculates the actual position, in degrees
	///
	else
	    count = count * (totalCount / 180.0);

	pputs(OE, "0");

	return count;
}

///
/// Function to reset the counters
///
void resetCount()
{
	pputs(RST, "0");
	usleep(10);
	pputs(RST, "1");
}


///
/// Function to read the end of course sensors
///
int readEndOfCourse()
{
	char end_bit1;
	char end_bit2;

	///
	/// Returns "1" if the robot reached any of the end of course sensors
	///
	return ((atoi(pgets(&end_bit1,sizeof(end_bit1),END_OF_COURSE1))) || (atoi(pgets(&end_bit2,sizeof(end_bit2),END_OF_COURSE2))));
}
