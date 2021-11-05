/******************** (C) COPYRIGHT 2014 CYF ********************
* File Name          : hx711.c
* Author             : CYF
* Version            : V1.0
* Date               : 2014-5-1
* Description        : hx711ѹ���ɼ����� 
* Email:             : cyf@gcp.edu.cn     
********************************************************************************/
   
//-----------------------------------------------------------------------------    
// Includes and Device-Specific Parameters    
//-----------------------------------------------------------------------------    
#include <hx711.h> 

ulong Read_711(void)
{
	ulong Count = 0;
	uchar i;
	ADDO = 1;
	ADSK = 0; //ʹ��AD��PD_SCK �õͣ�
	while(ADDO); //ADת��δ������ȴ�������ʼ��ȡ
	for (i=0;i<24;i++)
	{
		ADSK = 1; //PD_SCK �øߣ��������壩
		Count = Count<<1; //�½�����ʱ����Count����һλ���Ҳಹ��
		ADSK = 0; //PD_SCK �õ�
		if(ADDO) Count++;
	}
	ADSK = 1;
	Count = Count^0x800000;//��25�������½�����ʱ��ת������
	ADSK = 0;
	Count = Count>>4;	//	ADval = (int)(Count >> 8);//ȡ��16λ��Ч
	return(Count);
}
  
  
///**********************************************************/
//unsigned long ReadCount(void)
//{ 
//	unsigned long Count; 
//	unsigned int ADval;
//	unsigned char i; 
//	ADDO=1;
//	ADSK=0; 
//	Count=0; 
//	while(ADDO); 
//	for(i=0;i<24;i++)   //?24?bit
//	{ 
//		ADSK=1; 
//		Count=Count<<1; 
//		ADSK=0; 
//  		if(ADDO)Count++; 
//	} 
//	ADSK=1; //???25???,????????A??128db
////	Count=Count^0x800000; 
//	;
//	ADSK=0;	
///*	if((Count & 0x800000) == 0x800000)
//	{
//		Count = ~(Count - 1);
//	}  		*/
////	ADval = (int)(Count >> 8);//???????? 
//	ADval = (int)(Count>>8);
////	ADDO=1;
//	return(ADval); 
//}   
  
   
uint Weighing()
{	
	uint Avg;    
	uchar i,count=0;		
	ulong Temp711_Buffer[18];          //����������
	ulong Rt_Temp=0;	

    do{					                             //ѭ������10��				   
		Rt_Temp =  	Read_711(); // ReadCount();  //
		Temp711_Buffer[count++]=Rt_Temp;
	}while(count<18); 			  		 //ѭ������10��
			
	for(i=0;i<18;i++)	    	   //Xֵ��������
	{
		if(Temp711_Buffer[i]>Temp711_Buffer[i+1])//��������
		{
			Rt_Temp=Temp711_Buffer[i+1];
			Temp711_Buffer[i+1]=Temp711_Buffer[i];
			Temp711_Buffer[i]=Rt_Temp;
		}  
	}
	for(i=0;i<17;i++)	    	   //Xֵ��������
	{
		if(Temp711_Buffer[i]<Temp711_Buffer[i+1])//��������
		{
			Rt_Temp=Temp711_Buffer[i+1];
			Temp711_Buffer[i+1]=Temp711_Buffer[i];
			Temp711_Buffer[i]=Rt_Temp;
		}  
	}	
	/* �ź����������ȡǰ18������ƽ�� */
	Rt_Temp = 0;
	for(count = 0; count < 16; count++){
		Rt_Temp = Rt_Temp + Temp711_Buffer[count];
	}	
	Avg = Rt_Temp>>4;
	
 return Avg;
}      
/******************* (C) COPYRIGHT 2014 CYF *****END OF FILE****/