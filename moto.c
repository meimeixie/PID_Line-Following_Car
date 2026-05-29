#include "moto.h" 
#include "tim.h" 
#include "pid.h" 
void Moto_Init(void)
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
}

void L_Moto_Control(int16_t Speed)
{
	if(Speed>0)//逆时针
	{
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,Speed);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);
	}
	else//顺时针
		{
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,-Speed);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
	}
}

void R_Moto_Control(int16_t Speed)
{
	if(Speed>0)//逆时针
	{
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,Speed);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,0);
	}
	else//顺时针
		{
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,-Speed);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,0);
	}
}
void motor_go_straight()
{
	L_AddPID.Target_Val = MOTOR_GO_STRAIGHT_R;   
    R_AddPID.Target_Val = MOTOR_GO_STRAIGHT_L; 
}
void motor_stop()
{
	L_AddPID.Target_Val = MOTOR_STOP_R;   
    R_AddPID.Target_Val = MOTOR_STOP_L; 
}
void motor_turn_right_soft()
{
	L_AddPID.Target_Val = MOTOR_TURN_RIGHT_SOFT_R;   
    R_AddPID.Target_Val = MOTOR_TURN_RIGHT_SOFT_L; 
}
void motor_turn_left_soft()
{
	L_AddPID.Target_Val = MOTOR_TURN_LEFT_SOFT_R;   
    R_AddPID.Target_Val = MOTOR_TURN_LEFT_SOFT_L; 
}
void motor_turn_right_hard()
{
	L_AddPID.Target_Val = MOTOR_TURN_RIGHT_HARD_R;   
    R_AddPID.Target_Val = MOTOR_TURN_RIGHT_HARD_L; 
}
void motor_turn_left_hard()
{
	L_AddPID.Target_Val = MOTOR_TURN_LEFT_HARD_R;   
    R_AddPID.Target_Val = MOTOR_TURN_LEFT_HARD_L; 
}
void motor_turn()
{
	L_AddPID.Target_Val = 10;   
    R_AddPID.Target_Val = 10; 
}









