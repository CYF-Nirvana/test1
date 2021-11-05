/******************** (C) COPYRIGHT 2014 CYF ********************
* File Name          : HX711.h
* Author             : CYF
* Version            : V1.0
* Date               : 2014-5-1
* Description        : HX711Í·ÎÄ¼þ
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HX711_H
#define __HX711_H

#include <def.h>  

sbit ADDO = P1^2;
sbit ADSK = P1^1;

ulong Read_711(void);
uint Weighing();
				  
#endif /* __MAX6675_H */

/******************* (C) COPYRIGHT 2014 CYF *****END OF FILE****/




