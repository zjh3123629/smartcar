#include "DEV_PID.h"

pid_inittypedef left_motor_pid;
pid_inittypedef right_motor_pid;

void init_pid(pid_inittypedef * pid)
{
	bzero(pid, sizeof(pid_inittypedef));
}

int pid_set_parameters(pid_inittypedef * pid, int32 setpoint, float setkp, float setki, float setkd)
{
	pid->point = setpoint;

	pid->kp = setkp;
	pid->ki = setki;
	pid->kd = setkd;

	return 0;
}

// return pid controller output
// origin
int32 pid_increment(pid_inittypedef *pid, int32 feedback)
{
	int16 delta_uk = 0;
	
	pid->ek = pid->point - feedback;

	// formula
	delta_uk = pid->kp*(pid->ek-pid->ek_1) + pid->ki*pid->ek + pid->kd*(pid->ek-2*pid->ek_1+pid->ek_2);
	pid->uk = pid->uk_1 + delta_uk;

	if (pid->uk < -MOTOR_PWM_MAX)
		pid->uk = -MOTOR_PWM_MAX;
	else if (pid->uk > MOTOR_PWM_MAX)
		pid->uk = MOTOR_PWM_MAX;

	pid->uk_1 = pid->uk;

	pid->ek_2 = pid->ek_1;
	pid->ek_1 = pid->ek;

	return pid->uk;
	//return delta_uk;
}

// origin
int32 pid_position(pid_inittypedef* pid, int32 feedback)
{
	pid->ek = pid->point - feedback;

	// u(t) = kp * e(t) + ki * [e(1) + e(2) + ....+ e(t)] + kd * [e(t) - e(t-1)]
	if (abs(pid->ek) > INTEGRAL_SEPARATION_THRESHOLD) {
		//pid->integral = 0;
	} else {
		pid->integral += pid->ek;
		
		if (pid->integral < -INTEGRAL_MAX)
			pid->integral = -INTEGRAL_MAX;
		else if (pid->integral > INTEGRAL_MAX)
			pid->integral = INTEGRAL_MAX;
	}
	
	pid->uk = pid->kp*(float)pid->ek + pid->ki*(float)pid->integral + pid->kd*(float)(pid->ek-pid->ek_1);
	
	// limit
	if (pid->uk < -MOTOR_PWM_MAX)
		pid->uk = -MOTOR_PWM_MAX;
	else if (pid->uk > MOTOR_PWM_MAX)
		pid->uk = MOTOR_PWM_MAX;

	//pid->ek_2 = pid->ek_1;
	pid->ek_1 = pid->ek;

	return pid->uk;
}

#if 0
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
#endif

