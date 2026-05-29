#include "sensor.h"

#define SENSOR_BLACK  GPIO_PIN_SET  // 检测到黑线（高电平）
#define SENSOR_WHITE  GPIO_PIN_RESET    // 检测到白底（低电平）
#define SENSOR_ERROR  32              // 传感器异常状态
uint8_t state =0;
/**
 * @brief  读取5路灰度传感器状态（IN1/IN2/MID/IN3/IN4）
 * @note   状态映射：二进制位从高到低→IN1 IN2 MID IN3 IN4，对应十进制0~31
 * @retval 0~31：正常状态；32：防抖失败
 */
int8_t sensor(void)
{
    // 第一步：读取5路引脚状态（包含你遗漏的MID）
    GPIO_PinState IN1  = HAL_GPIO_ReadPin(IN1_GPIO_Port, IN1_Pin);
    GPIO_PinState IN2  = HAL_GPIO_ReadPin(IN2_GPIO_Port, IN2_Pin);
    GPIO_PinState MID  = HAL_GPIO_ReadPin(MID_GPIO_Port, MID_Pin);
    GPIO_PinState IN3  = HAL_GPIO_ReadPin(IN3_GPIO_Port, IN3_Pin);
    GPIO_PinState IN4  = HAL_GPIO_ReadPin(IN4_GPIO_Port, IN4_Pin);

    state = ((IN1==SENSOR_BLACK)<<4) | ((IN2==SENSOR_BLACK)<<3) | 
                     ((MID==SENSOR_BLACK)<<2) | ((IN3==SENSOR_BLACK)<<1) | 
                     (IN4==SENSOR_BLACK);

    // 第三步：验证状态并返回（两次一致则返回，否则异常）
//    if(state == 0x00 || state == 0x1F)
//    {
//        return 1;  // 检测异常/直行
//    }
    // 优先级2：大幅度左拐（只要IN1(bit4)=1）
    if((state & 0x10) != 0)
    {
        return -43;  // 偏移-43mm，大幅度左拐
    }
    // 优先级3：大幅度右拐（只要IN4(bit0)=1，且IN1=0）
    else if((state & 0x01) != 0)
    {
        return 43;  // 偏移43mm，大幅度右拐
    }
    // 优先级4：微调左拐（只要IN2(bit3)=1，且IN1=0、IN4=0）
    else if((state & 0x08) != 0)
    {
        return -15;  // 偏移-15mm，微调左拐
    }
    // 优先级5：微调右拐（只要IN3(bit1)=1，且IN1=0、IN4=0、IN2=0）
    else if((state & 0x02) != 0)
    {
        return 15;  // 偏移15mm，微调右拐
    }
    // 优先级6：剩余所有情况（仅MID、或其他混合）→ 直行
    else
    {
        return 0;  // 偏移0mm，直行
    }
			
	
}