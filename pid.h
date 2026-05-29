#include <main.h>
#include <tim.h>
void Pid_start();
#define Max_Pid_Value 10000//根据Cube中定时器CouterPeriod设置
typedef struct
{
	float Target_Val;   //目标值
	float Error;          /*第 k 次偏差 */
	float LastError;     /* Error[-1],第 k-1 次偏差 */
	float PrevError;    /* Error[-2],第 k-2 次偏差 */
	float Kp,Ki,Kd;     //比例、积分、微分系数
	float Integral;     //积分值
	float Output_Val;   //输出值
}PID;//定义结构体数据类型
void PID_Init(void);
extern char Uart3_Rx_Buf[5];
extern PID L_AddPID;
extern PID R_AddPID;//增量式PID，控制速度
extern  int8_t sensor_state;
