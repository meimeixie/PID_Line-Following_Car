#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//
//////////////////////////////////////////////////////////////////////////////////  


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
//void WFI_SET(void)
//{
//	__ASM volatile("WFI");		  
//}
////关闭所有中断(但是不包括fault和NMI中断)
//void INTX_DISABLE(void)
//{
//	__ASM volatile("CPSID   I");
//	__ASM volatile("BX      LR");
//		  
//}
////开启所有中断
//void INTX_ENABLE(void)
//{
//	__ASM volatile("CPSIE   I");
//	__ASM volatile("BX      LR"); 
//}
////设置栈顶地址
////addr:栈顶地址
//void MSR_MSP(u32 addr) 
//{
//	__ASM volatile("MSR MSP, r0");
//	__ASM volatile("BX r14");
//}

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
 void WFI_SET(void)
{
	__asm("WFI");		  
}
//关闭所有中断(但是不包括fault和NMI中断)
void INTX_DISABLE(void)
{
	__asm("CPSID   I");
	__asm("BX      LR");	  
}
//开启所有中断
void INTX_ENABLE(void)
{
	__asm("CPSIE   I");
	__asm("BX      LR "); 
}
//设置栈顶地址
//addr:栈顶地址
void MSR_MSP(u32 addr) 
{
	__asm("MSR MSP, r0 ");			//set Main Stack value
	__asm("BX r14");
}















