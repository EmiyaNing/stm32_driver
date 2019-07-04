/* LED 

核心板LED PA5,

*/


#include "stm32f10x.h"
#define KEY_ON 1
int speed_count;

 void Delay(u32 count)
 {
  u32 i=0;
  for(;i<count;i++);
 }

 void light_PWM(){
	 GPIO_SetBits(GPIOC, GPIO_Pin_3);
 }
 
 void stop_PWM(){
	 GPIO_ResetBits(GPIOC, GPIO_Pin_3);
 }
 
 void right_head(){
	  GPIO_SetBits(GPIOA,GPIO_Pin_4);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_9);
 }
 
 void stop_right(){
	  GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_9);
 }
 
 
 void left_head(){
	 GPIO_SetBits(GPIOB,GPIO_Pin_7);
   GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
 }
 
 void stop_left(){
	 GPIO_ResetBits(GPIOB,GPIO_Pin_7);
   GPIO_ResetBits(GPIOB,GPIO_Pin_8);
 }
 
 void right_back(){
	  GPIO_SetBits(GPIOA,GPIO_Pin_9);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_4);
 }
 
 void left_back(){
	 GPIO_SetBits(GPIOB,GPIO_Pin_8);
   GPIO_ResetBits(GPIOB,GPIO_Pin_7);	
 }
 
 void stop_driver(){
	 GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_8);
   GPIO_ResetBits(GPIOB,GPIO_Pin_7);
 }
 
 void control_driver(int select){
	 switch(select){
		 case 0:{
			 right_head();
			 left_head();
			 break;
		 }
		 case 1:{
			 right_back();
			 left_back();
			 break;
		 }
		 case 2:{
			 right_head();
			 left_back();
			 break;
		 }
		 case 3:{
			 right_back();
			 left_head();
			 break;
		 }
		 default:{
			 right_head();
			 left_head();
		 }
	 }	 
 }
 
 
 int main(void)
 {
	int count_i = 0;	
  GPIO_InitTypeDef  GPIO_InitStructure;
 	int result_right,result_left;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,B,C端口时钟

// 端口A初始化,	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_4 | GPIO_Pin_9 | GPIO_Pin_7 | GPIO_Pin_8;//PA.5 - 核心板LED;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA.5
	 
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;//PA.6 - 核心板LED;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA.5
	 
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;//PC.3 - 核心板LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA.5
	 /**
	 * set btn input
	 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	 /**
	 * set find way input
	 **/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
  while(1)
	{
			result_right = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
			result_left  = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
			if((result_right == 0)&&(result_left == 0)){
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
				GPIO_ResetBits(GPIOB,GPIO_Pin_6);
				right_head();
				left_head();
				Delay(30000);
				stop_driver();
				Delay(30000);
			}else if((result_right != 0)&&(result_left == 0)){
				Delay(300000);
				GPIO_SetBits(GPIOB, GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				left_head();
				right_back();
				Delay(30000);
				stop_driver();
				Delay(60000);
			}else if((result_right == 0)&&(result_left != 0)){
				Delay(300000);
				GPIO_SetBits(GPIOB, GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				right_head();
				left_back();
				Delay(30000);
				stop_driver();
				Delay(60000);
			}else{
				Delay(30000);
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				GPIO_ResetBits(GPIOB,GPIO_Pin_6);
				stop_driver();
			}
	}
}
