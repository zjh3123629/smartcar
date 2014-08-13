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
// origin
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

// origin
uint32 pid_position(pid_inittypedef* pid, uint32 feedback)
{
	pid->ek = pid->point - feedback;

	// u(t) = kp * e(t) + ki * [e(1) + e(2) + ....+ e(t)] + kd * [e(t) - e(t-1)]
	pid->integral += pid->ek;
	pid->uk = pid->kp*pid->ek + pid->ki*pid->integral + pid->kd*(pid->ek-*pid->ek_1);

	// limit
	if (pid->uk < 0)
		pid->uk = 0;
	else if (pid->uk > PID_CONTROLLER_MAX_OUTPUT)
		pid->uk = PID_CONTROLLER_MAX_OUTPUT;

	//pid->ek_2 = pid->ek_1;
	pid->ek_1 = pid->ek;

	return pid->uk;
}

float pid_calc(struct _pid *pid)
{
	int err;
	float pterm, dterm, result, ferror;

	err = (pid->sp) - (pid->pv);

	// deadband
	if (abs(err) > pid->deadband) {
		ferror = (float) err;

		pterm = pid->pgain * ferror;
		// integral separation
		if (pterm > 100 || pterm < -100)
			pid->integral = 0.0;
		else {
			pid->integral += pid->igain * ferror;

			// limit integral item
			if (pid->integral > 100.0)
				pid->integral = 100.0;
			else if (pid->integral < 0.0)
				pid->integral = 0.0;
		}

		dterm = ((float)(err - pid->last_error)) * pid->dgain;
		result = pterm + pid->integral + dterm;
	}
	else
		result = pid->integral;

	pid->last_error = err;

	return (result);
}


