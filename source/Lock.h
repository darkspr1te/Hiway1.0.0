#ifndef __LOCK_H__
#define __LOCK_H__

//////////////////////////////////////////////////////////////////////////
typedef struct {
	long			nLockOffTime;			//4*******************************, second
	long			nDoorOpenTime;			//4*******************************, second
	long			nAlarmDelay;			//4*******************************, second
	char			nDoorSensorType;		//4*******************************, T_LEVEL_VALID_TYPE
	char			nExitBTType;			//4*******************************, T_LEVEL_VALID_TYPE
	unsigned short	nTPW;					//2*******************************, uSecond
	unsigned short	nTPI;					//2*******************************, uSecond
} PACKED SB6000C_SETTING;

//////////////////////////////////////////////////////////////////////////
BOOL LOCK_INIT(DWORD dwPassword);
BOOL LOCK_DEINIT();
BOOL LOCK_GET_SETTING(SB6000C_SETTING *pBuf);
BOOL LOCK_SET_SETTING(SB6000C_SETTING *pBuf);
BOOL LOCK_DOOR_STATUS();
BOOL LOCK_DOOR_CONTROL(int nDoorStatus);
BOOL LOCK_DURESS_OPEN();
BOOL LOCK_ALARM_START();
BOOL LOCK_ALARM_STOP();
BOOL LOCK_ALARM_STATUS(int *pAlarmType = NULL);
BOOL LOCK_BELL_START();
BOOL LOCK_BELL_STOP();
BOOL LOCK_COMM_START();
BOOL LOCK_COMM_STOP();
BOOL LOCK_WIEGAND_SEND(BYTE *pData, int nBytes, int nBits);

#endif /*__LOCK_H__*/
