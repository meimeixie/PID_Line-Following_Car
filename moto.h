#include <tim.h>
#define MOTOR_GO_STRAIGHT_R 200
#define MOTOR_GO_STRAIGHT_L 200
#define MOTOR_STOP_R 0
#define MOTOR_STOP_L 0
#define MOTOR_TURN_RIGHT_SOFT_R 200
#define MOTOR_TURN_RIGHT_SOFT_L 100
#define MOTOR_TURN_LEFT_SOFT_R 100
#define MOTOR_TURN_LEFT_SOFT_L 200
#define MOTOR_TURN_RIGHT_HARD_R 200
#define MOTOR_TURN_RIGHT_HARD_L 0
#define MOTOR_TURN_LEFT_HARD_R 0
#define MOTOR_TURN_LEFT_HARD_L 200
void Moto_Init(void);
void L_Moto_Control(int16_t Speed);
void R_Moto_Control(int16_t Speed);
void motor_go_straight();
void motor_stop();
void motor_turn_right_soft();
void motor_turn_left_soft();
void motor_turn_right_hard();
void motor_turn_left_hard();
void motor_turn();
