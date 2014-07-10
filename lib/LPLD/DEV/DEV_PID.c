#include "DEV_PID.h"

void pid_init(pid_inittypedef * pid)
{
	bzero(pid, sizeof(pid_inittypedef));
}

int pid_set_parameters(pid_inittypedef * pid, uint16 setpoint, float setkp, float setki, float setkd)
{
	pid->point = setpoint;

	pid->kp = setkp;
	pid->ki = setki;
	pid->kd = setkd;

	return 0;
}

// return pid controller output
int16 pid_increment(pid_inittypedef * pid, uint16 feedback)
{
	int16 delta_uk = 0;
	
	pid->ek = pid->point - feedback;

	// formula
	delta_uk = pid->kp*(pid->ek-pid->ek_1) + pid->ki*pid->ek + pid->kd*(pid->ek-2*pid->ek_1+pid->ek_2)
	pid->uk = pid->uk_1 + delta_uk;

	if (pid->uk < 0)
		pid->uk = 0;
	else if (pid->uk > PID_CONTROLLER_MAX_OUTPUT)
		pid->uk = PID_CONTROLLER_MAX_OUTPUT;

	pid->uk_1 = pid->uk;

	pid->ek_2 = pid->ek_1;
	pid->ek_1 = pid->ek;

	return pid->uk;
}