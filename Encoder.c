#include <Encoder.h>
#include <stm32f4xx.h>

int16_t Encoder1_cnt;
int16_t Encoder2_cnt;
void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);//左电机
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_1);//右电机
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim10);//定时器中断开启
}



