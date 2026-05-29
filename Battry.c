#include <Battry.h>
#include <stm32f4xx.h>
#include <uart.h>

uint16_t value;
float voltage;

uint8_t Battry_Test(void)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,1);
	value=HAL_ADC_GetValue(&hadc1);
//	voltage=6.1*3.3*value/4095;			
	voltage=9.2*3.3*value/4095;				//VOL=1.4V----VAL=1737
	
	printf("ADC VOLTAGE RESULT:%.3f\r\n",voltage);
	if(voltage>12.8)
		return 100;
	else if(voltage<11.8)
		return 0;
	else
		return (voltage-11.8)*100;
}
