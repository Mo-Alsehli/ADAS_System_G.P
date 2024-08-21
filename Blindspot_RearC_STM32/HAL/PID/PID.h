/*
 * PID.h
 *
 *  Created on: Mar 28, 2024
 *      Author: Mohamed Magdi
 */

#ifndef PID_PID_H_
#define PID_PID_H_

#define SAMPLE_TIME_S 0.025f
// PID Parameters:
/* Controller parameters */
#define PID_KP  2.0f
#define PID_KI  0.5f
#define PID_KD  0.25f

#define PID_TAU 0.02f

#define PID_LIM_MIN  0.0f
#define PID_LIM_MAX  1000.0f

#define PID_LIM_MIN_INT -50.0f
#define PID_LIM_MAX_INT  50.0f

#define SAMPLE_TIME_S 20

/* Maximum run-time of simulation */
#define SIMULATION_TIME_MAX 4.0f


typedef struct {

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

	/* Derivative low-pass filter time constant */
	float tau;

	/* Output limits */
	float limMin;
	float limMax;

	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* Sample time (in seconds) */
	float T;

	/* Controller "memory" */
	float integrator;
	float prevError;			/* Required for integrator */
	float differentiator;
	float prevMeasurement;		/* Required for differentiator */

	/* Controller output */
	float out;

} PIDController;

void  PIDController_Init(PIDController *pid);
float PIDController_Update(PIDController *pid, float setpoint, float measurement);
float TestSystem_Update(float inp);

#endif /* PID_PID_H_ */
