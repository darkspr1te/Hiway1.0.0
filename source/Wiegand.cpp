#include "precomp.h"
#include <QByteArray>
#include <QHash>


char	wgbuf[40];
int		gLockStatus = T_DOOR_CLOSE;
int		gDoorStatus = T_DOOR_AUTO_RECOVER;
int		gbWarnCancel = FALSE;
BOOL	gbUncondFlag = FALSE;
DWORD	dwODIllegalWrnPrev = -1;
DWORD	gDoorUnlockStartTime, gDoorOpenStartTimePrev = -1;
DWORD	gIllegalDoorOpenStartTime, gIllegalDoorOpenStartTimePrev = -1;
DWORD	gDoorOpenTime;
//BOOL	gbManualOpen = FALSE;
BOOL	gbPrevDoorOpenStatus = FALSE;
char	wgbuf_temp[40];
DWORD	g_dwWiegandSendTime = 0;
int     gWgInLength;    
char WiegandCardType =CardType ;  // 1:id, 2:ic

//////////////////////////////////////////////////////////////////////////
void Wiegand_SendData(BYTE WiegandData[], int nLength)
{
	int i, k;

	memcpy(wgbuf_temp, WiegandData, MIN(sizeof(wgbuf_temp), nLength));
	g_dwWiegandSendTime = GetMainTickCount();

	if (dbSetupTotal.setSystem.dwBindingID)
	{
		int nBytes = (nLength + 7) / 8;
		int nBits = nLength;
		BYTE *pData = (BYTE*)malloc(nBytes);

		if (!pData)
			return;
		bzero(pData, nBytes);
		for (i=0; i<nBytes; i++)
		{
			for (k=0; k<8; k++)
			{
				if (WiegandData[i*8 + k])
					pData[i] |= (1 << (7 - k));
			}
		}
		LOCK_WIEGAND_SEND(pData, nBytes, nBits);
		FREE(pData);
	}
	else
		i = write(g_hWiegand, WiegandData, nLength);
}

/************************************************************************/
/* Wiegand26 Data Format                                                */
/************************************************************************/
//25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9   8  7  6  5  4  3  2  1  0
//P  D0 D1 D2 ...                                 D15 M0 M1 ...            M7 P
//D: ID, M: MachineID

//////////////////////////////////////////////////////////////////////////
void Wiegand_Send(DWORD dwOEM_Code, DWORD dwFC_Code, DWORD dwCC_Code)
{
	unsigned char count = 0;
	unsigned char oem_length = dbSetupTotal.setNoMenu.wiegand_type.byOEM_len;
	unsigned char fc_length = dbSetupTotal.setNoMenu.wiegand_type.byFC_len;
	unsigned char cc_length = dbSetupTotal.setNoMenu.wiegand_type.byCC_len;
	int total_length = (int)(oem_length + fc_length + cc_length + 2);
	unsigned char *data = (unsigned char*)malloc(total_length);
	int i, nPos;

	if (!data)
		return;

	memset(data, 0, total_length);

	nPos = 1;

	//OEM code
	for (i = oem_length - 1; i >= 0; i--)
	{
		if ((dwOEM_Code >> i) & 1)
			data[nPos] = 1;
		nPos++;
	}

	//FC code
	for (i = fc_length - 1; i >= 0; i--)
	{
		if ((dwFC_Code >> i) & 1)
			data[nPos] = 1;
		nPos++;
	}

	//CC code
	for (i = cc_length - 1; i >= 0; i--)
	{
		if ((dwCC_Code >> i) & 1)
			data[nPos] = 1;
		nPos++;
	}

	//Even Parity bit
	count = 0;
	for (i = 1; i < total_length / 2; i++)
	{
		if (data[i])
			count++;
	}
	if (count % 2)
		data[0] = 1;

	//Odd Parity bit
	count = 0;
	for (i = total_length / 2; i < total_length - 1; i++)
	{
		if (data[i])
			count++;
	}
	if (count % 2 == 0)
		data[total_length - 1] = 1;

	Wiegand_SendData(data, total_length);
	FREE(data);
}

//////////////////////////////////////////////////////////////////////////
int Wiegand_Read(DWORD* ID)
{
	BYTE count;
	int  i;
	int total_length;

if(dbSetupTotal.setSystem.byWiegandFormat==WIEGAND_34)
{
		if ((total_length = read(g_hWiegand, wgbuf, sizeof(wgbuf))) != 34)
			return -1;
}	
else if(dbSetupTotal.setSystem.byWiegandFormat==WIEGAND_26)
{
		if ((total_length = read(g_hWiegand, wgbuf, sizeof(wgbuf))) != 26)	
	return -1;
}	
else
{
		if ((total_length = read(g_hWiegand, wgbuf, sizeof(wgbuf))) < 26)
			return -1;
}

	if (GetMainTickCount() -  g_dwWiegandSendTime < 1000)
	{
		if (memcmp(wgbuf, wgbuf_temp, total_length) == 0)
			return -1;
	}

	//Even Parity bit
	count = 0;
	for(i = 1; i < total_length / 2; i++)
		count += wgbuf[i];
	if((count % 2) != wgbuf[0])
	{
		for (i=0; i<total_length; i++)
			wgbuf[i] = (wgbuf[i] ? 0 : 1);

		//re-calculate
		count = 0;
		for(i = 1; i < total_length / 2; i++)
			count += wgbuf[i];
		if((count % 2) != wgbuf[0])
		{
			memset(wgbuf, 0xFF, sizeof(wgbuf));
			return -1;
		}
	}

	//Odd Parity bit
	count = 0;
	for(i = total_length / 2; i < total_length - 1; i++)
		count += wgbuf[i];
	if((count % 2) == wgbuf[total_length - 1])
	{
		memset(wgbuf, 0xFF, sizeof(wgbuf));
		return -1;
	}

	if (total_length > 34)
		total_length = 34;

	gWgInLength = total_length;    

	for(i = 1; i < total_length - 1; i++)
		*ID |= (wgbuf[i] << (total_length - 2 - i));

	memset(wgbuf, 0xFF, sizeof(wgbuf));
	return 0;
}

//////////////////////////////////////////////////////////////////////////
WORD Wiegand_GetUserID(DWORD dwCardNumber)
{
	int i;
	WORD wID = 0;

	for (i=9; i<25; i++)
	{
		wID |= ((dwCardNumber >> i) & 0x1);
		wID <<= 1;
	}
	return wID;
}

//////////////////////////////////////////////////////////////////////////
DWORD GetOpenTime(void)
{
	return GetMainTickCount() / 1000;
}

//////////////////////////////////////////////////////////////////////////
BOOL IsLockKey(void)
{
	if(DOOR_ISNOT_EXIT()) return FALSE;

	uiTimeDelay(100);

	if(DOOR_ISNOT_EXIT()) return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL IsDoorOpened(void)
{
	BOOL bRet = TRUE;

	switch (dbSetupTotal.setSystem.nDoorSensorStatus)
	{
	case DOORSENSOR_TYPE_NONE:
		bRet = FALSE;
		break;
	case DOORSENSOR_TYPE_OPEN:
		bRet = (DOOR_IS_OPENED() == FALSE);
		break;
	case DOORSENSOR_TYPE_CLOSE:
		bRet = (DOOR_IS_OPENED() == TRUE);
		break;
	}
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
void LockControl(int nFunc)
{
	gDoorStatus  = nFunc;
	gbWarnCancel = FALSE;
	gbUncondFlag = FALSE;

	switch(nFunc)
	{
	case T_LOCK_UNCOND_OPEN:
//		uiLogGlogAdd(UI_GLOG_PROG_OPEN, 0);
		DOOR_OPEN();
		gbUncondFlag = TRUE;
		break;
	case T_LOCK_UNCOND_CLOSE:
//		uiLogGlogAdd(UI_GLOG_PROG_CLOSE, 0);
		DOOR_CLOSE();
		gbUncondFlag = TRUE;
		break;
	case T_LOCK_DOOR_OPEN:
//		uiLogGlogAdd(UI_GLOG_PROG_LOCK, 0);
		LockStatus(T_DOOR_UNLOCK);
		if (uiAlarmStop(UI_ALARM_NOCLOSE))
			uiEventSend_ALARM_OFF(UI_ALARM_NOCLOSE, ALARMRELEASE_AUTO, 0);
		if (uiAlarmStop(UI_ALARM_ILGOPEN))
			uiEventSend_ALARM_OFF(UI_ALARM_ILGOPEN, ALARMRELEASE_AUTO, 0);
		break;
	case T_LOCK_AUTO_RECOVER:
//		uiLogGlogAdd(UI_GLOG_AUTO_RECOVER, 0);
		LockStatus(T_DOOR_AUTO_RECOVER);
		break;
	case T_LOCK_RESTART:
		uiPowerReboot();
		break;
// 	case T_LOCK_WARN_CANCEL:
// 		uiAlarmStop(UI_ALARM_ILGOPEN);
// 		gbWarnCancel = TRUE;
// 		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
void LockStatus(int nStatus)
{
	if (gbUncondFlag)
		return;

	gLockStatus = nStatus;

	switch(gLockStatus)
	{
	case T_DOOR_CLOSE:
		DOOR_CLOSE();
		if (uiAlarmStop(UI_ALARM_NOCLOSE))
			uiEventSend_ALARM_OFF(UI_ALARM_NOCLOSE, ALARMRELEASE_AUTO, 0);
		g_uiProcStatus.nLastVerifiedUser = 0;
		break;
	case T_DOOR_UNLOCK:
		if (dbSetupTotal.setSystem.nLockTime)
		{
			DOOR_OPEN();
			gDoorUnlockStartTime = GetOpenTime();
		}
		break;
	case T_DOOR_ILLEGAL_OPEN:
		break;
	case T_DOOR_WATCH_OPEN_PASS_TIME:
		gDoorOpenTime = GetOpenTime();
		DOOR_CLOSE();
		break;
	case T_DOOR_AUTO_RECOVER:
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
void LockProc(void)
{
	if (TAMPER_IS_OFF())
	{
		if (uiAlarmStart(UI_ALARM_TAMPER))
			uiEventSend_ALARM_ON(UI_ALARM_TAMPER, 0);
	}

	if (gbUncondFlag && gDoorStatus == T_LOCK_UNCOND_CLOSE && IsDoorOpened())
	{
		if (uiAlarmStart(UI_ALARM_ILGOPEN))
			uiEventSend_ALARM_ON(UI_ALARM_ILGOPEN, 0);
		return;
	}

	if(IsLockKey())
	{
//		printf("LockKey is selected\n");
//		gbManualOpen = TRUE;
		g_uiProcStatus.nLastVerifiedUser = 0;
		LockStatus(T_DOOR_UNLOCK);
		if (uiAlarmStop(UI_ALARM_NOCLOSE))
			uiEventSend_ALARM_OFF(UI_ALARM_NOCLOSE, ALARMRELEASE_AUTO, 0);
// 		if (uiAlarmStop(UI_ALARM_ILGOPEN))
// 			uiEventSend_ALARM_OFF(UI_ALARM_ILGOPEN, ALARMRELEASE_AUTO, 0);
	}
// 	else
// 	{
// 		if(gbManualOpen) uiLogGlogAdd(UI_GLOG_HAND_LOCK, 0);
// 		gbManualOpen = FALSE;
// 	}

	switch(gLockStatus) //Current Door Status
	{
	case T_DOOR_CLOSE:
		gIllegalDoorOpenStartTime = 0;
		if (IsDoorOpened())
		{
			gIllegalDoorOpenStartTime = GetOpenTime();
			LockStatus(T_DOOR_ILLEGAL_OPEN);
// 			printf("Illegal Door Opening\n");
//			uiSoundOut(UISOUND_FORCED_DOOR_OPEN, BUZZER_NONE);
		}
		break;
	case T_DOOR_UNLOCK:
		if (!gbPrevDoorOpenStatus && IsDoorOpened())
		{
//			printf("Door is opening...\n");
		}

// 		if (dbSetupTotal.setSystem.nDoorOpenTime == 0)
// 		{
// 			gLockStatus = T_DOOR_WATCH_OPEN_PASS_TIME;
// 			break;
// 		}

		if ((GetOpenTime() - gDoorUnlockStartTime) > (DWORD)dbSetupTotal.setSystem.nLockTime)
			LockStatus(T_DOOR_WATCH_OPEN_PASS_TIME);
		break;
	case T_DOOR_ILLEGAL_OPEN:
		if (!IsDoorOpened())
		{
//			printf("Door is closed\n");
			LockStatus(T_DOOR_CLOSE);
			break;
		}

		if (gbWarnCancel)
			break;
// 		if (dbSetupTotal.setLock.nDoorIllegalOpenTimeout == 0)
// 			break;

		if (uiAlarmStart(UI_ALARM_ILGOPEN))
			uiEventSend_ALARM_ON(UI_ALARM_ILGOPEN, 0);
		break;

		if ((GetOpenTime() - gIllegalDoorOpenStartTime) > 2/*dbSetupTotal.setLock.nDoorIllegalOpenTimeout*/)
		{
			if (gIllegalDoorOpenStartTimePrev != gIllegalDoorOpenStartTime)
			{
//				uiLogGlogAdd(UI_GLOG_ILLEGAL_OPEN, 0);
				gIllegalDoorOpenStartTimePrev = gIllegalDoorOpenStartTime;
			}

			if (uiAlarmStart(UI_ALARM_ILGOPEN))
				uiEventSend_ALARM_ON(UI_ALARM_ILGOPEN, 0);
		}

		break;
	case T_DOOR_WATCH_OPEN_PASS_TIME:
		if (!gbPrevDoorOpenStatus && IsDoorOpened())
		{
//			printf("Door is opend\n");
		}

		if (!IsDoorOpened())
		{
			LockStatus(T_DOOR_CLOSE);
			break;
		}

		if (gbWarnCancel)
			break;
		if (dbSetupTotal.setSystem.nDoorOpenTime == 0)
			break;

 		if ((GetOpenTime() - gDoorOpenTime) > (DWORD)dbSetupTotal.setSystem.nDoorOpenTime)
		{
			if (uiAlarmStart(UI_ALARM_NOCLOSE))
			{
				uiEventSend_ALARM_ON(UI_ALARM_NOCLOSE, g_uiProcStatus.nLastVerifiedUser);
				g_uiProcStatus.nLastVerifiedUser = 0;
			}
		}
		break;
	case T_DOOR_AUTO_RECOVER:
		LockStatus(T_DOOR_CLOSE);
// 		if (!IsDoorOpened())
// 		{
// 			LockStatus(T_DOOR_CLOSE);
// //			uiSoundOut(UISOUND_DOOR_IS_CLOSED, BUZZER_NONE);
// 		}
// 		else
// 		{
// 			LockStatus(T_DOOR_UNLOCK);
// //			uiSoundOut(UISOUND_DOOR_IS_OPENED, BUZZER_NONE);
// 		}
		break;
	}

	if (gbPrevDoorOpenStatus && !IsDoorOpened())
	{
//		printf("Door is closed\n");
	}

	gbPrevDoorOpenStatus = IsDoorOpened();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define IOCTL_RF_HAND_SHAKE		1
#define IOCTL_RF_PERSONAL_CARD	2
#define IOCTL_RF_ID_CARD		3
#define IOCTL_RF_SUSPEND		4
#define IOCTL_RF_RESUME			5
typedef struct tagPostMem {
	int 	Result;//=0; success, else fail
	void *	pBuffAddr;//about 64byte size
	unsigned char 	Size;//Buffer size
	unsigned char 	Reserved;
} POSTMEM;

static POSTMEM	gPostMem;

BOOL RFMOD_EXIST()
{
	int nRet;

	nRet = ioctl(g_hRfmod, IOCTL_RF_HAND_SHAKE, (void*)&gPostMem);
	return (gPostMem.Result == 0);
}

DWORD RFMOD_READ(BOOL bReadCard /*= TRUE*/)
{
//	static DWORD __prev_time = 0;
	static DWORD __prev_card = 0;
	DWORD dwCardID = 0;
	BYTE gRFMOD_BUF[256];
	int nRet;

// 	if (uiTimeGetTickCount() - __prev_time < 500)
// 		return 0;
// 
// 	__prev_time = uiTimeGetTickCount();

	if (!RFMOD_EXIST())
		return 0;

	gPostMem.pBuffAddr = gRFMOD_BUF;

	nRet = ioctl(g_hRfmod, IOCTL_RF_PERSONAL_CARD, (void*)&gPostMem);
	if (gPostMem.Result == 0)
	{
//		QByteArray byArray((const char*)gRFMOD_BUF, gPostMem.Size);
		dwCardID = sb_hash(gRFMOD_BUF, gPostMem.Size);
		if (bReadCard && __prev_card != dwCardID)
		{
			__prev_card = dwCardID;
			return dwCardID;
		}
		else
			return 0;
	}

	nRet = ioctl(g_hRfmod, IOCTL_RF_ID_CARD, (void*)&gPostMem);
	if (gPostMem.Result == 0)
	{
		dwCardID = (*(DWORD*)&gRFMOD_BUF[3]);
		if (bReadCard && __prev_card != dwCardID)
		{
			__prev_card = dwCardID;
			return dwCardID;
		}
		else
			return 0;
	}

	__prev_card = 0;

	return 0;
}

BOOL RFMOD_SUSPEND()
{
	return (ioctl(g_hRfmod, IOCTL_RF_SUSPEND, 0) == 0);
}

BOOL RFMOD_RESUME()
{
	return (ioctl(g_hRfmod, IOCTL_RF_RESUME, 0) == 0);
}
