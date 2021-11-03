#ifndef __LED_H__
#define __LED_H__

#include "sys.h"

#define GREENLED PCout(0)	
#define REDLED   PCout(1)	

#define GreenLED_ON  PCout(0)=0
#define GreenLED_OFF PCout(0)=1
#define RedLED_ON    PCout(1)=0
#define RedLED_OFF   PCout(1)=1



void LED_Init(void);
void GreenLED_Toggle(void);
void RedLED_Toggle(void);		



#endif



