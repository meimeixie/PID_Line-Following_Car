#include<uart.h>
//__asm (".global __use_no_semihosting\n\t"); 

////避免使用半主机模式
//void _sys_exit(int x)
//{
//	x = x;
//}
////标准库需要支持的函数
//FILE __stdout; 


//重定向print
int fputc(int ch, FILE *f)//printf
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1,0xffff);  //发送一个字节的数据到你希望的串口
	return (ch);
}
int fgetc(FILE *f)
{
  uint8_t  ch;
	HAL_UART_Receive(&huart1,(uint8_t *)&ch, 1, 0xFFFF);
	return  ch;
}
