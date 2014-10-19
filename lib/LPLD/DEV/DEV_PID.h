#ifndef  _DEV_PID_H_
#define  _DEV_PID_H_

//----------------------头文件----------------------//
#include "common.h"
#include "DEV_Motor.h"

//----------------------结构体声明----------------------//
typedef struct PID
{   
	float kp;		// 比例常数 Proportional Const
	float ki;		// 积分常数 Integral Const
	float kd;		// 微分常数 Derivative Const

	int32 point;	// 设定的目标 Desired Value
	int32 ek;
	int32 ek_1;		// e[k-1]
	int32 ek_2;		// e[k-2]

	float uk;
	float uk_1;

	int32 integral;
} pid_inittypedef;

#define INTEGRAL_SEPARATION_THRESHOLD		20
#define INTEGRAL_MAX						1000

//----------------------变量声明----------------------//
extern pid_inittypedef left_motor_pid;
extern pid_inittypedef right_motor_pid;

//----------------------函数声明----------------------//
void init_pid(pid_inittypedef *pid);
int pid_set_parameters(pid_inittypedef * pid, int32 setpoint, float setkp, float setki, float setkd);
int32 pid_increment(pid_inittypedef * pid, int32 feedback);
int32 pid_position(pid_inittypedef* pid, int32 feedback);

#endif
