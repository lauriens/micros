/* lib_v1.h: API with functions necessary to operate the robot Quanser 2DSFJ
 * 
 * Author: Laurien Santin
*/

#ifndef LIBV1_H
#define LIBV1_H

#ifdef __cplusplus
extern "C"
{
#endif

void setMotorVoltage(int voltage);
void setPWM(); 
int readCounter(int firstRead, int firstCount);
void resetCount();
int readEndOfCourse();

#ifdef __cplusplus
};
#endif

#endif
