#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <galileo2io.h>
#include <libv1.h>

int main(int argc, char **argv)
{
	int angleRef = 0;
	int angle;
	double kp, ki, kd;
	double error = 0;
	double prevError = 0;
	double sumError = 0;
	int position;
	int u;

	if (argc != 2)
	{
		printf("Usage: ./pid <position>");
		return -1;
	}
	position = atoi(argv[1]);

	kp = - 0.05;
	kd = - 0.15;
	ki = - 0.0001;

	setMotorVoltage(-27);
	while (readEndOfCourse() == 0)
	{}
	setMotorVoltage(0);
	resetCount();
	angleRef = readCounter(1, 0);

	while (1)
	{

		angle = readCounter(0, angleRef);

		error = position - angle;
		sumError += error;
		u = kp * error + kd * (error - prevError) + ki * sumError;

		if (u > 27)
			u = 27;
		if (u < -27)
			u = -27;

		setMotorVoltage(u);

		prevError = error;
		usleep(100000);

//		printf("Informe a voltagem:");
//		scanf("%d",position);
//		printf("\n");
	}
}
