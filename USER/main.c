/* LED 

核心板LED PA5,

*/

#include "stm32f10x.h"
 void Delay(u32 count)
 {
  u32 i=0;
  for(;i<count;i++);
 }
/**
 * 我就先设置3个LED两灭模式:
 * 红色D3常亮 0
 * 绿色D4常亮 1
 * 红绿交替亮 2
 */
 void light_LED(int select){
   switch(select){
     case 0:{
       GPIO_SetBits(GPIOB, GPIO_Pin_6);
       break;
     }
     case 1:{
       GPIO_SetBits(GPIOA, GPIO_Pin_6);
       break;
     }
     case 2:{
       while(1){
         GPIO_ResetBits(GPIOA, GPIO_Pin_6);
         GPIO_SetBits(GPIOB, GPIO_Pin_6);
         Delay(3000000);
         GPIO_ResetBits(GPIOB, GPIO_Pin6);
         GPIO_SetBits(GPIOA, GPIO_Pin_6);
         Delay(3000000);
       }
     }
   }

 }
 
 int main(void)
 {	
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA端口时钟

// 端口A初始化,
  /**
   * 直流电机:
   * 第一对: PA4, PB9
   * 第二对: PB7, PB8
   * LED
   * 红色D3：PB6
   * 绿色D4：PA6
   * 
   * 蜂鸣器
   * PC3
   * 
   * 主控板LED
   * PA5
   */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO口速度为50MHz
  /**
   * 讲道理，我觉得这样设置没有问题，虽然可能并不是每一组GPIO口都需要用到上面列举出来的所有io口，但是我觉得这样好像也没有问题。
   */
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA.5
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /**
   * 我先直接让蜂鸣器响
   *  */ 
  GPIO_SetBits(GPIOC, GPIO_Pin_3);

  while(1)
	{
	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		//Delay(3000000);
		light_LED(2);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		//Delay(3000000);	
	}
}
