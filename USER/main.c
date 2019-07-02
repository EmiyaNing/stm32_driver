/* LED 

?????LED PA5,

*/


#include "stm32f10x.h"
#define KEY_ON 1

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
 
 void left_head(){
	 GPIO_SetBits(GPIOB,GPIO_Pin_7);
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
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);	 //???PA,B,C??????

// ???A?????,	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_4 | GPIO_Pin_9 | GPIO_Pin_7 | GPIO_Pin_8;//PA.5 - ?????LED;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //???????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO??????50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //?????څ?????????GPIOA.5
	 
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;//PA.6 - ?????LED;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //?????څ?????????GPIOA.5
	 
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;//PC.3 - ?????LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //?????څ?????????GPIOA.5
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
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0){
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
			GPIO_SetBits(GPIOA,GPIO_Pin_6);
			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		}else{
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			Delay(300000);
		}
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0){
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
			GPIO_ResetBits(GPIOB,GPIO_Pin_9);
			GPIO_SetBits(GPIOB,GPIO_Pin_6);
			//GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		}else{
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);
			GPIO_ResetBits(GPIOB,GPIO_Pin_9);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			Delay(300000);
		}
	}
}
