#ifndef __BUZZER_H__
#define __BUZZER_H__

enum {BUZZER_NONE = -1, BUZZER_ON = 1, BUZZER_OFF = 0};

#define IOCTL_BUZZER	1

typedef struct _buzzer_ctrl
{
	int type;		//ON | OFF | NONE
	int miliseconds;//
	int next;		//offset
	int level;
	int sync;
}BUZZER_CTRL;

#endif /*__BUZZER_H__*/
