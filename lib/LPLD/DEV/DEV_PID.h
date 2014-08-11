#ifndef  _DEV_PID_H_
#define  _DEV_PID_H_

#include "common.h"

//----------------------头文件----------------------//

//----------------------结构体声明----------------------//
typedef struct PID
{   
	float kp;		// 比例常数 Proportional Const
	float ki;		// 积分常数 Integral Const
	float kd;		// 微分常数 Derivative Const

	uint16 point;	// 设定的目标 Desired Value
	int16 ek;
	int16 ek_1;		// e[k-1]
	int16 ek_2;		// e[k-2]

	float uk;
	float uk_1;
} pid_inittypedef;

//----------------------变量声明----------------------//

//----------------------函数声明----------------------//

#define PID_CONTROLLER_MAX_EK			40
#define PID_CONTROLLER_MAX_OUTPUT		1000

void init_pid(pid_inittypedef *pid);
int pid_set_parameters(pid_inittypedef * pid, uint16 setpoint, float setkp, float setki, float setkd);
int16 pid_increment(pid_inittypedef * pid, uint16 feedback);

#endif