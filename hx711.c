/******************** (C) COPYRIGHT 2014 CYF ********************
* File Name          : hx711.c
* Author             : CYF
* Version            : V1.0
* Date               : 2014-5-1
* Description        : hx711压力采集程序 
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
	ADSK = 0; //使能AD（PD_SCK 置低）
	while(ADDO); //AD转换未结束则等待，否则开始读取
	for (i=0;i<24;i++)
	{
		ADSK = 1; //PD_SCK 置高（发送脉冲）
		Count = Count<<1; //下降沿来时变量Count左移一位，右侧补零
		ADSK = 0; //PD_SCK 置低
		if(ADDO) Count++;
	}
	ADSK = 1;
	Count = Count^0x800000;//第25个脉冲下降沿来时，转换数据
	ADSK = 0;
	Count = Count>>4;	//	ADval = (int)(Count >> 8);//取高16位有效
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
	ulong Temp711_Buffer[18];          //采样缓冲区
	ulong Rt_Temp=0;	

    do{					                             //循环读数10次				   
		Rt_Temp =  	Read_711(); // ReadCount();  //
		Temp711_Buffer[count++]=Rt_Temp;
	}while(count<18); 			  		 //循环读数10次
			
	for(i=0;i<18;i++)	    	   //X值升序排列
	{
		if(Temp711_Buffer[i]>Temp711_Buffer[i+1])//升序排列
		{
			Rt_Temp=Temp711_Buffer[i+1];
			Temp711_Buffer[i+1]=Temp711_Buffer[i];
			Temp711_Buffer[i]=Rt_Temp;
		}  
	}
	for(i=0;i<17;i++)	    	   //X值降序排列
	{
		if(Temp711_Buffer[i]<Temp711_Buffer[i+1])//升序排列
		{
			Rt_Temp=Temp711_Buffer[i+1];
			Temp711_Buffer[i+1]=Temp711_Buffer[i];
			Temp711_Buffer[i]=Rt_Temp;
		}  
	}	
	/* 排好序的数组中取前18个，求平均 */
	Rt_Temp = 0;
	for(count = 0; count < 16; count++){
		Rt_Temp = Rt_Temp + Temp711_Buffer[count];
	}	
	Avg = Rt_Temp>>4;
	
 return Avg;
}      
/******************* (C) COPYRIGHT 2014 CYF *****END OF FILE****/