
#include "delay.h"
#include "sys.h"
#include "oled.h"

	
 int main(void)
 {	u8 t;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	OLED_Init();			//��ʼ��OLED      
 	OLED_ShowString(0,0, "0.96' OLED TEST");  
 	OLED_ShowString(0,16,"imodule");  
 	OLED_ShowString(0,32,"2013/09/13");  
 	OLED_ShowString(0,48,"ASCII:");  
 	OLED_ShowString(63,48,"CODE:");  
	OLED_Refresh_Gram();	 
	t=' ';  
	while(1) 
	{		
		OLED_ShowChar(48,48,t,16,1);//��ʾASCII�ַ�	   
		OLED_Refresh_Gram();
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16);//��ʾASCII�ַ�����ֵ 
		delay_ms(300);

	}	  
	
}

