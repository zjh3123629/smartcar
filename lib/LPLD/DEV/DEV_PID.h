#ifndef  _DEV_PID_H_
#define  _DEV_PID_H_

//----------------------ͷ�ļ�----------------------//
#include "common.h"
#include "DEV_Motor.h"

//----------------------�ṹ������----------------------//
typedef struct PID
{   
	float kp;		// �������� Proportional Const
	float ki;		// ���ֳ��� Integral Const
	float kd;		// ΢�ֳ��� Derivative Const

	int32 point;	// �趨��Ŀ�� Desired Value
	int32 ek;
	int32 ek_1;		// e[k-1]
	int32 ek_2;		// e[k-2]

	float uk;
	float uk_1;

	int32 integral;
} pid_inittypedef;

#define INTEGRAL_SEPARATION_THRESHOLD		20
#define INTEGRAL_MAX						1000

//----------------------��������----------------------//
extern pid_inittypedef left_motor_pid;
extern pid_inittypedef right_motor_pid;

//----------------------��������----------------------//
void init_pid(pid_inittypedef *pid);
int pid_set_parameters(pid_inittypedef * pid, int32 setpoint, float setkp, float setki, float setkd);
int32 pid_increment(pid_inittypedef * pid, int32 feedback);
int32 pid_position(pid_inittypedef* pid, int32 feedback);

#endif
