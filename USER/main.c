/* LED 

���İ�LED PA5,

*/

#include "stm32f10x.h"
 void Delay(u32 count)
 {
  u32 i=0;
  for(;i<count;i++);
 }
/**
 * �Ҿ�������3��LED����ģʽ:
 * ��ɫD3���� 0
 * ��ɫD4���� 1
 * ���̽����� 2
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
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA�˿�ʱ��

// �˿�A��ʼ��,
  /**
   * ֱ�����:
   * ��һ��: PA4, PB9
   * �ڶ���: PB7, PB8
   * LED
   * ��ɫD3��PB6
   * ��ɫD4��PA6
   * 
   * ������
   * PC3
   * 
   * ���ذ�LED
   * PA5
   */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO���ٶ�Ϊ50MHz
  /**
   * �������Ҿ�����������û�����⣬��Ȼ���ܲ�����ÿһ��GPIO�ڶ���Ҫ�õ������оٳ���������io�ڣ������Ҿ�����������Ҳû�����⡣
   */
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA.5
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /**
   * ����ֱ���÷�������
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
