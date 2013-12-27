#ifndef __PORTCTL_H__
#define __PORTCTL_H__

typedef struct _gpio_ctrl
{
	BYTE	len;	//1, 2, 4
	BYTE	bRes[3];
	DWORD	dwValue;
	DWORD	dwAddress;
}gpio_ctrl;

#define GPIO_READ		0x01
#define GPIO_WRITE		0x02
#define TIMER_READ		0x03
#define TIMER_WRITE		0x04

#endif /*__PORTCTL_H__*/
