#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <galileo2io.h>
#include <libv1.h>

///
/// Main used to test the software; Receives a position, in Volts, to set the robot arm, and uses PID to reach the position
///
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

	///
	/// A desired position required;
	///
	if (argc != 2)
	{
		printf("Usage: ./pid <position>");
		return -1;
	}
	position = atoi(argv[1]);

	kp = - 0.05;
	kd = - 0.15;
	ki = - 0.0001;

	///
	/// For the set up, it needs to:
	/// Set up the PWM;
	///
	setPWM();

	///
	/// Move the arm until one its ends;
	///
	setMotorVoltage(-27);
	while (readEndOfCourse() == 0)
	{}
	setMotorVoltage(0);

	///
	/// Reset the counter and read its value, to mark it as Zero;
	///
	resetCount();
	angleRef = readCounter(1, 0);

	///
	/// Then, it moves the arm until the other end;
	///
	setMotorVoltage(27);
	while (readEndOfCourse() == 0)
	{}
	setMotorVoltage(0);

	///
	/// And reads the counter again, so now it knows how many counts are in a revolution
	///
	angleRef = readCounter(1, 0) - angleRef;

	while (1)
	{
		///
		/// Now, for the moving the arm to the desired location part, knowing the current position of the arm
		///
		angle = readCounter(0, angleRef);

		///
		/// it calculates the error of the position, compared to the desired one, and updates the current sum of the past errors;
		///
		error = position - angle;
		sumError += error;

		///
		/// Then, calculates, using PID, the required voltage to get there
		///
		u = kp * error + kd * (error - prevError) + ki * sumError;

		///
		/// Corrects the voltage, if it's superior to the robot's limits
		///
		if (u > 27)
			u = 27;
		if (u < -27)
			u = -27;

		///
		/// Finally, it sets the required voltage, so the arm can move to the desired spot
		///
		setMotorVoltage(u);

		///
		/// And updates the "previous error", to the current one, for the next iteraction of the loop (and sleeps for 100ms)
		///
		prevError = error;
		usleep(100000);

//		printf("Informe a voltagem:");
//		scanf("%d",position);
//		printf("\n");
	}
}
