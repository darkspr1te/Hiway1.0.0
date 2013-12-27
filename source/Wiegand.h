#ifndef __WIEGAND_H__
#define __WIEGAND_H__

// from wiegand driver
#define WIEGAND_MODE_SET	1
//#define WiegandType  26
#define CardType  1   // 1:id, 2:ic

typedef enum
{
	T_DOOR_CLOSE = -1,
	T_DOOR_UNLOCK	= 1,
	T_DOOR_ILLEGAL_OPEN,
	T_DOOR_WATCH_OPEN_PASS_TIME,
	T_DOOR_AUTO_RECOVER,

	T_LOCK_UNCOND_OPEN = 1,
	T_LOCK_UNCOND_CLOSE,
	T_LOCK_DOOR_OPEN,
	T_LOCK_AUTO_RECOVER,
	T_LOCK_RESTART,
	T_LOCK_WARN_START,
	T_LOCK_WARN_CANCEL
}T_LOCK_STATUS;

void Wiegand_Init(void);
void Wiegand_Send(DWORD dwOEM_Code, DWORD dwFC_Code, DWORD dwCC_Code);
void Wiegand_SendData(BYTE WiegandData[]);
int  Wiegand_Read(DWORD* ID);
WORD Wiegand_GetUserID(DWORD dwCardNumber);
void LockControl(int nFunc);
void LockStatus(int nStatus);
void LockProc(void);

BOOL RFMOD_EXIST();
DWORD RFMOD_READ(BOOL bReadCard = TRUE);
BOOL RFMOD_SUSPEND();
BOOL RFMOD_RESUME();

BOOL IsDoorOpened(void);

#endif /*__WIEGAND_H__*/
