#ifndef  _DEV_PID_H_
#define  _DEV_PID_H_

#include "common.h"

//----------------------ͷ�ļ�----------------------//

//----------------------�ṹ������----------------------//
typedef struct PID
{   
	float kp;		// �������� Proportional Const
	float ki;		// ���ֳ��� Integral Const
	float kd;		// ΢�ֳ��� Derivative Const

	uint16 point;	// �趨��Ŀ�� Desired Value
	int16 ek;
	int16 ek_1;		// e[k-1]
	int16 ek_2;		// e[k-2]

	float uk;
	float uk_1;
} pid_inittypedef;

//----------------------��������----------------------//

//----------------------��������----------------------//

#define PID_CONTROLLER_MAX_EK			40
#define PID_CONTROLLER_MAX_OUTPUT		1000

void init_pid(pid_inittypedef *pid);
int pid_set_parameters(pid_inittypedef * pid, uint16 setpoint, float setkp, float setki, float setkd);
int16 pid_increment(pid_inittypedef * pid, uint16 feedback);

#endif