#include <pid.h>
#include <uart.h>
#include <moto.h>
#include <sensor.h>

//系统检测时间和控制时间为10ms
int16_t L_Encoder_Speed =0;//左电机编码器速，500线编码器，减速比30，单位是脉冲/10ms
int16_t R_Encoder_Speed =0;//右电机编码器速，500线编码器，减速比30，单位是脉冲/10ms
int32_t Position =0;//位置控制
int16_t L_Output_Val,R_Output_Val;//u(k),PID计算出的输出控制PWM占空比的值
PID PosionPID;//申明结构体变量PosionPID,位置式PID
PID L_AddPID,R_AddPID;//增量式PID，控制速度

char Rx_Data[5];
int8_t Sensor_Sta;
/**
  * @brief  PID参数初始化
  *	@note 	无
  * @retval 无
  */
void PID_Init(void)
{
	PosionPID.Target_Val=0;				
	PosionPID.Output_Val=0.0;
	PosionPID.Error=0.0;
	PosionPID.LastError=0.0;
	PosionPID.Integral=0.0;
	PosionPID.Kp = 20;
	PosionPID.Ki = 1;
	PosionPID.Kd = 10;

	
	L_AddPID.Target_Val=100;//编码器500ppr,减速比30，测速频率100ms			
	L_AddPID.Output_Val=0.0;//-10000到10000给到moto_control的speed参数
	L_AddPID.Error=0.0;//当前偏差
	L_AddPID.LastError=0.0;//上次偏差
	L_AddPID.PrevError=0.0;//上上次偏差
	L_AddPID.Integral=0.0;//积分
	L_AddPID.Kp = 26;//比例系数
	L_AddPID.Ki = 1;//积分系数
	L_AddPID.Kd = 0.1;//微分系数
	
	R_AddPID.Target_Val=100;//编码器500ppr,减速比30，测速频率100ms			
	R_AddPID.Output_Val=0.0;
	R_AddPID.Error=0.0;
	R_AddPID.LastError=0.0;
	R_AddPID.PrevError=0.0;
	R_AddPID.Integral=0.0;
	R_AddPID.Kp = 27;
	R_AddPID.Ki = 1;
	R_AddPID.Kd = 0.1;
}
/**
  * @brief  位置PID算法实现
  * @param  Current_Val:当前实际测量值
  *	@note 	无
  * @retval 通过PID计算后的输出
  */
float PosionPID_realize(PID *pid, float Current_Val)
{
	/*计算目标值与实际值的误差*/
	pid->Error = pid->Target_Val - Current_Val;
	/*积分项*/
	pid->Integral += pid->Error;
	/*PID算法实现*/
	pid->Output_Val = pid->Kp * pid->Error +
	                  pid->Ki * pid->Integral +
	                  pid->Kd *(pid->Error -pid->LastError);
	/*误差传递*/
	pid-> LastError = pid->Error;
	/*返回当前实际值*/
	if(pid->Output_Val>Max_Pid_Value)
	{
		pid->Output_Val=Max_Pid_Value;
		return Max_Pid_Value;
	}
	else 	if(pid->Output_Val<(-1)*Max_Pid_Value)
	{
		pid->Output_Val=(-1)*Max_Pid_Value;
		return (-1)*Max_Pid_Value;
	}
	else
		return pid->Output_Val;
}
/**
  * @brief  速度PID算法实现
  * @param  pid,参数配置，actual_val:实际速度值
  *	@note 	无
  * @retval 通过PID计算后的输出
  */
float AddPID_Realize(PID *pid, float Actual_val)
{
	/*计算目标值与实际值的误差*/
	pid->Error = pid->Target_Val - Actual_val;
	/*PID算法实现，照搬公式*/
	pid->Output_Val += pid->Kp * (pid->Error - pid-> LastError) +
	                  pid->Ki * pid->Error +
	                  pid->Kd *(pid->Error -2*pid->LastError+pid->PrevError);
	/*误差传递*/
	pid-> PrevError = pid->LastError;
	pid-> LastError = pid->Error;
	/*返回当前实际值,限制输出幅度，
	输出幅度一定要小于等于CounterPeriod*/
	if(pid->Output_Val>Max_Pid_Value)
	{
		pid->Output_Val=Max_Pid_Value;
		return Max_Pid_Value;
	}
	else 	if(pid->Output_Val<(-1)*Max_Pid_Value)
	{
		pid->Output_Val=(-1)*Max_Pid_Value;
		return (-1)*Max_Pid_Value;
	}
	else
		return pid->Output_Val;
}
void Pid_start()
{
		L_Encoder_Speed=(-1)*(int16_t)__HAL_TIM_GET_COUNTER(&htim4);
		__HAL_TIM_SET_COUNTER(&htim4,0);
		R_Encoder_Speed=(int16_t)__HAL_TIM_GET_COUNTER(&htim1);//获取右电机编码器数值
		__HAL_TIM_SET_COUNTER(&htim1,0);//右编码器数值清0
		printf("O:%d,%d,%d,%d\r\n",L_Encoder_Speed,(int)L_AddPID.Target_Val,R_Encoder_Speed,(int)R_AddPID.Target_Val);//串口打印电机转速
		static int8_t Value;
		L_Output_Val=AddPID_Realize(&L_AddPID,L_Encoder_Speed);//4.输入速度式PID计算
		R_Output_Val=AddPID_Realize(&R_AddPID,R_Encoder_Speed);//4.输入速度式PID计算
		L_Moto_Control (L_Output_Val);
		R_Moto_Control (R_Output_Val);
		
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM10)
	{
		sensor_state = sensor();
		switch(sensor_state) 
		{
			case 0  : motor_go_straight();;    break;            	
			case 15 : motor_turn_right_soft(); break;    	
			case -15: motor_turn_left_soft();  break;    		 
			case 43 : motor_turn_right_hard(); break;  		 
			case -43: motor_turn_left_hard();  break;  			 
			case 1  : motor_turn(); break;  
		}
		Pid_start();
	}
}


