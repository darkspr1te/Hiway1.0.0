#include "precomp.h"
#include <QtCore/QMutex>
#include <QtCore/QQueue>

int comm_uartrecv(int iUART, void *pBuffer, int len, int nTimeout);
int comm_uartsend(int iUART, void *pBuffer, int len);
void comm_uartclear(int iUART);
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define SERIAL_DEVICE	(0)

int lock_comm_send(BYTE* pbuf, int nsize, int /*ntimeout*/)
{
//	int nReqSize = nsize;
	int nWrittenSize = 0;
	BYTE* pBufIdx = (BYTE*)pbuf;
	HFILE s_handle = g_hUart[SERIAL_DEVICE];

	if (s_handle == INVALID_HANDLE_VALUE)
		return 0;

//	g_ComMutex.lock();
// 
// 	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

	while (nsize > 0)
	{
		int nCurrentWrittenSize = MIN(1024, nsize);

// 		uiLcdProgress(LCDPROG_PERCENT(nWrittenSize, nReqSize));

		nCurrentWrittenSize = write(s_handle, pBufIdx, nCurrentWrittenSize);

		if (nCurrentWrittenSize > 0)
		{
			pBufIdx += nCurrentWrittenSize;
			nsize -= nCurrentWrittenSize;
			nWrittenSize += nCurrentWrittenSize;
			continue;
		}
		else if (nCurrentWrittenSize < 0)
		{
			if (errno == -EWOULDBLOCK)
				continue;
		}

		break;
	}

// 	uiLcdProgressEnd();
// 
//	g_ComMutex.unlock();

	return nWrittenSize;
}

int lock_comm_recv(BYTE* pbuf, int nsize, int ntimeout)
{
	int i;
	unsigned char* pTemp = (unsigned char*)pbuf;
	fd_set s_fd_in;
	struct timeval s_timeval;
	int s_check, s_read_bytes;
	HFILE s_handle = g_hUart[SERIAL_DEVICE];
	
	if (s_handle == INVALID_HANDLE_VALUE)
		return 0;

//	g_ComMutex.lock();
// 
// 	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

	i = 0;
	while (i < nsize)
	{
//		uiLcdProgress(LCDPROG_PERCENT(i, nsize));

		FD_ZERO(&s_fd_in);
		FD_SET(s_handle, &s_fd_in);
		s_timeval.tv_sec = (long)(ntimeout / 1000), s_timeval.tv_usec = (long)(ntimeout % 1000) * 1000;
		s_check = select(s_handle + 1, (fd_set *)(&s_fd_in), (fd_set *)0, (fd_set *)0, (struct timeval *)(&s_timeval)); 
		if (s_check <= 0)
			break;
		s_read_bytes = read(s_handle, (void*)&pTemp[i], (size_t)(nsize - i));
		if (s_read_bytes > 0)
			i += s_read_bytes;
	}
	
// 	uiLcdProgressEnd();
// 
//	g_ComMutex.unlock();

	return i;
}

int lock_comm_recv_valid_data(BYTE Data, int ntimeout)
{
	int nResult;
	BYTE Buf;
	DWORD dwTimeout = uiTimeGetTickCount() + ntimeout;

	while (uiTimeGetTickCount() < dwTimeout)
	{
		nResult = lock_comm_recv(&Buf, 1, ntimeout);
		if (nResult)
		{
			if (Buf != Data)
			{
				dwTimeout = uiTimeGetTickCount() + ntimeout;
				continue;
			}
			return 1;
		}
	}
	return 0;
}

void lock_comm_clear(void)
{
	comm_uartclear(SERIAL_DEVICE);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
enum 
{
	SETTING_LOCKTIME,
	SETTING_DOOROPENTIME,
	SETTING_ALARMDELAY,
	SETTING_DOORSENSORTYPE,
	SETTING_EXITBTTYPE,
	SETTING_WIEGANDTYPE
};

typedef enum
{
	LEVEL_VALID_NONE,
	HIGH_LEVEL_1,
	LOW_LEVEL_1
}T_LEVEL_VALID_TYPE;

enum 
{
	CMD_OPEN = 1,
	CMD_CLOSE,
	CMD_SETTING,
	CMD_SETUP,
	CMD_LOCKCTRL,
	CMD_WIEGAND,
	CMD_PASSWORD,
	CMD_DOORSTATUS,
	CMD_ALARMSTATUS,
	CMD_BELL,
	CMD_POWER
};

typedef struct {		
	UINT16	wDevId;
	UINT16 	wCmdOrAck;
	unsigned long	nParam1;
	unsigned long	nParam2;
	UINT16 	wChkSum;
} PACKED SB_CMD_ACK_PKT;

#define SB_AC_PKT_SIZE			sizeof(SB_CMD_ACK_PKT)
#define SB_AC_DEV_ID_SIZE		2
#define SB_AC_CHK_SUM_SIZE		2

#define PKT_ERR_START	-500
#define PKT_COMM_ERR	PKT_ERR_START+1
#define PKT_DEV_ID_ERR	PKT_ERR_START+2
#define PKT_CHK_SUM_ERR	PKT_ERR_START+3
#define PKT_PARAM_ERR	PKT_ERR_START+4
#define PKT_SIZE_ERR	PKT_ERR_START+5

#define SB_AC_PKT_MAXSIZE		48

#define SWAPW(w)	(((w<<8)&0xff00) | ((w>>8)&0x00ff))
#define SWAPL(lw)	(((lw<<24)&0xff000000L) | ((lw<<8 )&0x00ff0000L) | ((lw>>8 )&0x0000ff00L) | ((lw>>24)&0x000000ffL))

SB6000C_SETTING gSetup;
unsigned long gPassword = 0x09010701;
char gbPassword;//Security Or No Security


/*
*	sb_com.cpp
*
*	Beijing Smackbio Technology Co.,Ltd @ 2004-2009
*
*	2009-01-10 By JuChan Kim. 
*
*	Homepage:	http://www.smackbio.com
*	Tel:		86-10-58816265/67
*	Fax:		86-10-58816270
*	E-mail:		tech@smackbio.com
*/

#define COM_TIME_OUT 1000
#define COM_DATA_START1 0x5A //Header
#define COM_DATA_START2 0x55 //Security
#define COM_DATA_START3 0x58 //No Security

int sb_com_read(unsigned char* pBuf, unsigned char nSize)
{
	unsigned char Data, Data1;
	int nCnt=0;
	int i;

	//Check start1
	if(lock_comm_recv_valid_data(COM_DATA_START1, COM_TIME_OUT) != 1)
		return -1;

//	if(comm_recv(&Data, 1, COM_TIME_OUT) != 1)
//		return -3;

//	if(Data != COM_DATA_START1)
//		return -2;

	//Check start2
	if(lock_comm_recv(&Data, 1, COM_TIME_OUT) != 1)
		return -3;
	
	if(gbPassword)
	{
		if(Data != COM_DATA_START3)
			return -4;
	}
	else
	{
		if(Data != COM_DATA_START2)
			return -4;
	}
	
	//Check size
	if(lock_comm_recv(&Data, 1, COM_TIME_OUT) != 1)
		return -5;
	Data = (Data << 4);
	if(lock_comm_recv(&Data1, 1, COM_TIME_OUT) != 1)
		return -6;
	Data |= (Data1 & 0x0F);
	
	if(Data != nSize)
		return -7;

	nCnt=0;
	for(i=0;i<nSize;i++)
	{
		if(lock_comm_recv(&Data, 1, COM_TIME_OUT) != 1)
			return -8;
		Data = (Data << 4);
		if(lock_comm_recv(&Data1, 1, COM_TIME_OUT) != 1)
			return -9;
		Data |= (Data1 & 0x0F);

		pBuf[nCnt++] = Data;
	}

	return 0;
}

int sb_com_write(unsigned char* pBuf, unsigned char nSize)
{
	int i;
	unsigned char Data[64];

	Data[0] = COM_DATA_START1;
	if(gbPassword)
		Data[1] = COM_DATA_START3;
	else
		Data[1] = COM_DATA_START2;
	Data[2] = (nSize >> 4) | 0xA0;
	Data[3] = (nSize & 0x0F) | 0xA0;
	
	for(i=0;i<nSize;i++)
	{
		Data[4+i*2] = (pBuf[i] >> 4) | 0xA0;
		Data[4+i*2+1] = (pBuf[i] & 0x0F) | 0xA0;
	}

	if(lock_comm_send(Data, 4+nSize*2, COM_TIME_OUT) != (4+nSize*2))
		return -1;

	return 0;
}

/*
*	sb_protocol.cpp
*
*	Beijing Smackbio Technology Co.,Ltd @ 2004-2009
*
*	2009-01-10 By JuChan Kim. 
*
*	Homepage:	http://www.smackbio.com
*	Tel:		86-10-58816265/67
*	Fax:		86-10-58816270
*	E-mail:		tech@smackbio.com
*/

void SwapCMDOrAck(SB_CMD_ACK_PKT* pPkt)
{
	pPkt->wDevId = SWAPW(pPkt->wDevId);
	pPkt->wCmdOrAck= SWAPW(pPkt->wCmdOrAck);
	pPkt->nParam1= SWAPL(pPkt->nParam1);
	pPkt->nParam2 = SWAPL(pPkt->nParam2);
	pPkt->wChkSum = SWAPW(pPkt->wChkSum);
}

void SwapSetupInfo(SB6000C_SETTING* pSetup)
{
	pSetup->nLockOffTime = SWAPL(pSetup->nLockOffTime);
	pSetup->nDoorOpenTime = SWAPL(pSetup->nDoorOpenTime);
	pSetup->nAlarmDelay = SWAPL(pSetup->nAlarmDelay);
	//pSetup->nDoorSensorType = SWAPL(pSetup->nDoorSensorType);
	//pSetup->nExitBTType = SWAPL(pSetup->nExitBTType);
	pSetup->nTPW = SWAPW(pSetup->nTPW);
	pSetup->nTPI = SWAPW(pSetup->nTPI);
}

void sbpkt_Security(unsigned char* pBuf, int nsize)
{
	int i;
	int j;
	unsigned char* pCrypto = (unsigned char*)&gPassword;

	if(gbPassword)
		return;

	for(i=0;i<nsize;i++)
	{
		j = i%4;
		pBuf[i] = pCrypto[3-j] ^ pBuf[i];
	}
}

UINT16 sbpkt_CalcChkSumOfCmdAckPkt( SB_CMD_ACK_PKT* pPkt )
{
	UINT16 wChkSum = 0;
	unsigned char* pBuf = (unsigned char*)pPkt;
	int i;
	
	for(i=0;i<(int)(sizeof(SB_CMD_ACK_PKT)-SB_AC_CHK_SUM_SIZE);i++)
		wChkSum += pBuf[i];
	return wChkSum;
}

UINT16 sbpkt_CalcChkSumOfDataPkt( unsigned char* pDataPkt, int nSize )
{
	int i;
	UINT16 wChkSum = 0;
	unsigned char* pBuf = (unsigned char*)pDataPkt;
	
	for(i=0;i<nSize;i++)
		wChkSum += pBuf[i];
	return wChkSum;
}

int sbpkt_CheckCmdAckPkt( UINT16 wDevID, SB_CMD_ACK_PKT* pPkt )
{
	if( pPkt->wDevId != wDevID ) 
		return PKT_DEV_ID_ERR;
	
	if( pPkt->wChkSum != sbpkt_CalcChkSumOfCmdAckPkt( pPkt ) ) 
		return PKT_CHK_SUM_ERR;

	return 0;
}

int sbpkt_SendCmdOrAck( UINT16 wDevID, UINT16 wCmdOrAck, unsigned long nParam1,  unsigned long nParam2)
{
	SB_CMD_ACK_PKT pkt;

	pkt.wDevId = wDevID;
	pkt.wCmdOrAck = wCmdOrAck;
	pkt.nParam1 = nParam1;
	pkt.nParam2 = nParam2;
	pkt.wChkSum = sbpkt_CalcChkSumOfCmdAckPkt( &pkt );
	SwapCMDOrAck(&pkt);

	sbpkt_Security( (unsigned char*)&pkt, SB_AC_PKT_SIZE );
	
	if( sb_com_write( (unsigned char*)&pkt, SB_AC_PKT_SIZE) < 0 )
		return PKT_COMM_ERR;

	return 0;
}

int sbpkt_ReceiveCmdOrAck( UINT16 wDevID, UINT16* pwCmdOrAck, unsigned long* pnParam1,  unsigned long* pnParam2)
{
	SB_CMD_ACK_PKT pkt;
		
	if( ( pwCmdOrAck == NULL ) || 
		( pnParam1 == NULL ) ||
		( pnParam2 == NULL ) )
	{
		return PKT_PARAM_ERR;
	}

	if( sb_com_read( (unsigned char*)&pkt, SB_AC_PKT_SIZE) < 0 )
		return PKT_COMM_ERR;
	
	sbpkt_Security( (unsigned char*)&pkt, SB_AC_PKT_SIZE );

	SwapCMDOrAck(&pkt);
	if( pkt.wDevId != wDevID ) 
		return PKT_DEV_ID_ERR;

	if( pkt.wChkSum != sbpkt_CalcChkSumOfCmdAckPkt( &pkt ) ) 
		return PKT_CHK_SUM_ERR;
	
	*pwCmdOrAck = pkt.wCmdOrAck;
	*pnParam1 = pkt.nParam1;
	*pnParam2 = pkt.nParam2;
	
	return 0;
}

int sbpkt_SendData( UINT16 wDevID, unsigned char* pBuf, int nSize )
{
	UINT16 wChkSum = 0;
	unsigned char Buf[SB_AC_PKT_MAXSIZE];
	
	if( pBuf == NULL )
		return PKT_PARAM_ERR;
	
	if( (SB_AC_DEV_ID_SIZE+nSize+SB_AC_CHK_SUM_SIZE) > SB_AC_PKT_MAXSIZE )
		return PKT_SIZE_ERR;

	*((UINT16*)(&Buf[0])) = wDevID;
	wChkSum = sbpkt_CalcChkSumOfDataPkt( Buf, SB_AC_DEV_ID_SIZE  );
	wChkSum += sbpkt_CalcChkSumOfDataPkt( pBuf, nSize );
	memcpy(&Buf[SB_AC_DEV_ID_SIZE], pBuf, nSize);
	*((UINT16*)(&Buf[SB_AC_DEV_ID_SIZE+nSize])) = wChkSum;

	*((UINT16*)(&Buf[0])) = SWAPW(wDevID);
	*((UINT16*)(&Buf[SB_AC_DEV_ID_SIZE+nSize])) = SWAPW(wChkSum);
	sbpkt_Security( Buf, SB_AC_DEV_ID_SIZE + nSize + SB_AC_CHK_SUM_SIZE );

	if( sb_com_write( Buf, SB_AC_DEV_ID_SIZE + nSize + SB_AC_CHK_SUM_SIZE ) < 0 )
		return PKT_COMM_ERR;
	
	return 0;
}

int sbpkt_ReceiveData( UINT16 wDevID, unsigned char* pBuf, int nSize )
{
	UINT16 wChkSum;
	unsigned char Buf[SB_AC_PKT_MAXSIZE];
	
	if( pBuf == NULL )
		return PKT_PARAM_ERR;
	
	if( (SB_AC_DEV_ID_SIZE+nSize+SB_AC_CHK_SUM_SIZE) > SB_AC_PKT_MAXSIZE )
		return PKT_SIZE_ERR;

	if( sb_com_read( Buf, SB_AC_DEV_ID_SIZE+nSize+SB_AC_CHK_SUM_SIZE) < 0 )
		return PKT_COMM_ERR;

	sbpkt_Security( Buf, SB_AC_DEV_ID_SIZE + nSize + SB_AC_CHK_SUM_SIZE );

	*((UINT16*)(&Buf[0])) = SWAPW(*((UINT16*)(&Buf[0])));
	*((UINT16*)(&Buf[SB_AC_DEV_ID_SIZE+nSize])) = SWAPW(*((UINT16*)(&Buf[SB_AC_DEV_ID_SIZE+nSize])));

	if( *((UINT16*)(&Buf[0])) != wDevID ) 
		return PKT_DEV_ID_ERR;
	
	wChkSum = sbpkt_CalcChkSumOfDataPkt( Buf, SB_AC_DEV_ID_SIZE+nSize );
	
	if( wChkSum != *((UINT16*)(&Buf[SB_AC_DEV_ID_SIZE+nSize])) ) 
		return PKT_CHK_SUM_ERR;
	
	memcpy(pBuf, &Buf[SB_AC_DEV_ID_SIZE], nSize);
	return 0;
}

/*
*	sb_ui_proc.cpp
*
*	Beijing Smackbio Technology Co.,Ltd @ 2004-2009
*
*	2009-01-10 By JuChan Kim. 
*
*	Homepage:	http://www.smackbio.com
*	Tel:		86-10-58816265/67
*	Fax:		86-10-58816270
*	E-mail:		tech@smackbio.com
*/

#define SB3500A_DEVID	(dbComm_machineID)
#define SET_SETTING		0x8000
#define GET_SETTING		0x0000

#define SET_SETUP		0x8000
#define GET_SETUP		0x0000

#define SET_PASSWORD	0x8000
#define GET_PASSWORD	0x0000

unsigned short gwDevID = SB3500A_DEVID;
unsigned short gwCmd;
unsigned short gwAck;
unsigned long gnParam1;
unsigned long gnParam2;

BYTE  WIEGAND_BUF[8];
DWORD WIEGAND_BYTESIZE;
DWORD WIEGAND_BITSIZE;

#define COM_SECURITY (gbPassword = 0)
#define COM_NO_SECURITY (gbPassword = 1)

unsigned short gwCommAlive  = 0;

void UI_COMM_IS_ALIVE(void)
{
	if(gwCommAlive & 0x8000)
		gwCommAlive = 0;
	else
		gwCommAlive = 0x8000;
}

int UI_SendCmdAndReceiveAck(void)
{
	gwCmd |= gwCommAlive;
	
	lock_comm_clear();

	if(sbpkt_SendCmdOrAck( gwDevID, gwCmd, gnParam1,  gnParam2 ) < 0)
		return -1;
	
	if(sbpkt_ReceiveCmdOrAck( gwDevID, &gwAck, &gnParam1,  &gnParam2 ) < 0)
		return -1;
	
	if(gwAck != 0)
		return -1;
	
	return 0;
}

int UI_Open(void) 
{
	return 0;	
}

int UI_Close(void) 
{
	return 0;
}

int UI_SetPassword(DWORD dwPassword) 
{
	COM_NO_SECURITY;

	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_PASSWORD;
	gnParam1 = SET_PASSWORD;
	gnParam2 = dwPassword;
	
	if(UI_SendCmdAndReceiveAck()<0)
		return -1;

	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_GetPassword(DWORD* pdwPassword)
{
	COM_NO_SECURITY;

	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_PASSWORD;
	gnParam1 = GET_PASSWORD;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck() < 0)
		return -1;
		
	*pdwPassword = gnParam2;
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_Setting(DWORD dwSet, DWORD dwType, DWORD dwSetParam, DWORD* pdwGetParam )
{
	COM_SECURITY;

	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_SETTING;
	gnParam1 = dwType | dwSet;
	gnParam2 = dwSetParam;
	
	if(UI_SendCmdAndReceiveAck() < 0)
		return -1;
	
	if(pdwGetParam != 0)
		*pdwGetParam = gnParam2;

	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_SetLockofftime(DWORD dwLockofftime)
{
	return UI_Setting(SET_SETTING, SETTING_LOCKTIME, dwLockofftime, 0);
}

int UI_GetLockofftime(DWORD* pdwLockofftime)
{
	return UI_Setting(GET_SETTING, SETTING_LOCKTIME, 0, pdwLockofftime);
}

int UI_SetDooropenedtime(DWORD dwDooropendtime) 
{
	return UI_Setting(SET_SETTING, SETTING_DOOROPENTIME, dwDooropendtime, 0);
}

int UI_GetDooropenedtime(DWORD* pdwDooropendtime)
{
	return UI_Setting(GET_SETTING, SETTING_DOOROPENTIME, 0, pdwDooropendtime);
}

int UI_SetAlarmdelaytime(DWORD dwAlarmdelaytime) 
{
	return UI_Setting(SET_SETTING, SETTING_ALARMDELAY, dwAlarmdelaytime, 0);
}

int UI_GetAlarmdelaytime(DWORD* pdwAlarmdelaytime) 
{
	return UI_Setting(GET_SETTING, SETTING_ALARMDELAY, 0, pdwAlarmdelaytime);
}

int UI_SetDoorsensortype(DWORD dwDoorsensortype) 
{
	return UI_Setting(SET_SETTING, SETTING_DOORSENSORTYPE, dwDoorsensortype, 0);
}

int UI_GetDoorsensortype(DWORD* pdwDoorsensortype) 
{
	return UI_Setting(GET_SETTING, SETTING_DOORSENSORTYPE, 0, pdwDoorsensortype);
}

int UI_SetExitbuttontype(DWORD dwExitbuttontype)
{
	return UI_Setting(SET_SETTING, SETTING_EXITBTTYPE, dwExitbuttontype, 0);
}

int UI_GetExitbuttontype(DWORD* pdwExitbuttontype)
{
	return UI_Setting(GET_SETTING, SETTING_EXITBTTYPE, 0, pdwExitbuttontype);
}

int UI_SetWiegandtype(DWORD dwWiegandtype)
{
	return UI_Setting(SET_SETTING, SETTING_WIEGANDTYPE, dwWiegandtype, 0);
}

int UI_GetWiegandtype(DWORD* pdwWiegandtype)
{
	return UI_Setting(GET_SETTING, SETTING_WIEGANDTYPE, 0, pdwWiegandtype);
}

int UI_GetSetupinfo(SB6000C_SETTING* pSetup)
{
	COM_SECURITY;

	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_SETUP;
	gnParam1 = GET_SETUP;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck() < 0)
		return -1;

	if( sbpkt_ReceiveData( gwDevID, (unsigned char*)pSetup, sizeof(SB6000C_SETTING) )<0)
		return -1;

	if(sbpkt_ReceiveCmdOrAck( gwDevID, &gwAck, &gnParam1,  &gnParam2 ) < 0)
		return -1;

	if(gwAck!=0)
		return -1;

	SwapSetupInfo(pSetup);
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_SetSetupinfo(SB6000C_SETTING* pSetup) 
{
	SB6000C_SETTING Setup;

	memcpy(&Setup, pSetup, sizeof(SB6000C_SETTING));

	COM_SECURITY;

	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_SETUP;
	gnParam1 = SET_SETUP;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck() < 0)
		return -1;

	SwapSetupInfo(&Setup);
	if( sbpkt_SendData( gwDevID, (unsigned char*)&Setup, sizeof(SB6000C_SETTING) )<0)
		return -1;
	
	if(sbpkt_ReceiveCmdOrAck( gwDevID, &gwAck, &gnParam1,  &gnParam2 ) < 0)
		return -1;
	
	if(gwAck != 0)
		return -1;
	
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_GetDoorstatus(DWORD* pdwDoorSatus)
{
	COM_SECURITY;

	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_DOORSTATUS;
	gnParam1 = 0;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck() < 0)
		return -1;
	
	*pdwDoorSatus = gnParam1;
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_GetAlarmstatus(DWORD* pdwAlarmType, DWORD* pdwAliveTime)
{
	COM_SECURITY;
	
	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_ALARMSTATUS;
	gnParam1 = 0;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck() < 0)
		return -1;
	
	*pdwAlarmType = gnParam1;	
	*pdwAliveTime = gnParam2;
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_LockControl(DWORD dwType, DWORD dwParam)
{
	COM_SECURITY;

	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_LOCKCTRL;
	gnParam1 = dwType;
	gnParam2 = dwParam;
	
	if(UI_SendCmdAndReceiveAck() < 0)
		return -1;
	
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_DoorOpen(void)
{
	return UI_LockControl(T_LOCK_DOOR_OPEN, 0);
}

int UI_UncondOpen(void)
{
	return UI_LockControl(T_LOCK_UNCOND_OPEN, 0);
}

int UI_AutoRecover(void)
{
	return UI_LockControl(T_LOCK_AUTO_RECOVER, 0);
}

int UI_WarningStart(void)
{
	return UI_LockControl(T_LOCK_WARN_START, 0);
}

int UI_WarningCancel(void)
{
	return UI_LockControl(T_LOCK_WARN_CANCEL, 0);
}

int UI_UncondClose(void)
{
	return UI_LockControl(T_LOCK_UNCOND_CLOSE, 0);
}

int UI_Reboot(void)
{
	return UI_LockControl(T_LOCK_RESTART, 0);
}

int UI_ForcedDoorOpen(void)
{
	return UI_LockControl(T_LOCK_DOOR_OPEN, 1);
}

int UI_WiegandOut(void)
{
	BYTE *buf = WIEGAND_BUF;
	DWORD dwByteSize = WIEGAND_BYTESIZE;
	DWORD dwBitsSize = WIEGAND_BITSIZE;

	COM_SECURITY;

	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_WIEGAND;
	gnParam1 = dwByteSize;
	gnParam2 = dwBitsSize;
	
	if(UI_SendCmdAndReceiveAck() < 0)
		return -1;
	
	if( sbpkt_SendData( gwDevID, buf, dwByteSize )<0)
		return -1;
	
	if(sbpkt_ReceiveCmdOrAck( gwDevID, &gwAck, &gnParam1,  &gnParam2 ) < 0)
		return -1;
	
	if(gwAck != 0)
		return -1;
	
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_BellStart(void)
{
	COM_SECURITY;
	
	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_BELL;
	gnParam1 = 1;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck()<0)
		return -1;

	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_BellCancel(void)
{
	COM_SECURITY;
	
	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_BELL;
	gnParam1 = 0;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck()<0)
		return -1;
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_CommStart(void)
{
	COM_SECURITY;
	
	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_POWER;
	gnParam1 = 1;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck()<0)
		return -1;
	UI_COMM_IS_ALIVE();
	return 0;
}

int UI_CommStop(void)
{
	COM_SECURITY;
	
	gwDevID = SB3500A_DEVID;
	gwCmd = CMD_POWER;
	gnParam1 = 0;
	gnParam2 = 0;
	
	if(UI_SendCmdAndReceiveAck()<0)
		return -1;
	UI_COMM_IS_ALIVE();
	return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define LOCK_WRAPPER(_p_) ({BOOL __RET; LOCK_MUTEX.lock(); __RET = (_p_); LOCK_MUTEX.unlock(); __RET;})

typedef int (*fnLockCtrlFunc)(void);

#define DOOR_CLOSE_EVENT	0x100
#define EXIT_BUTTON_EVENT	0x101

static BOOL LOCK_CONTROLLER_INITED = FALSE;
static BOOL LOCK_MUST_RESET = FALSE;
static pthread_t LOCK_THREAD_ID = 0;
static QMutex LOCK_MUTEX;
static QQueue<fnLockCtrlFunc> LOCK_QUEUE;
static SB6000C_SETTING LOCK_SETTING;

extern int __DOOR_STATUS[4];

//////////////////////////////////////////////////////////////////////////
void* LOCK_THREAD(void */*arg*/)
{
	int i;
	int nResult;
	DWORD dwAlarmType, dwAliveTime, dwAliveTimePrev = 0;
	fnLockCtrlFunc fn;
	DWORD dwPrevCallTime = 0;
	int nConnectFailCount = 0;

	while (dbSetupTotal.setSystem.dwBindingID && LOCK_CONTROLLER_INITED)
	{
		nResult = 0;
		dwAlarmType = 0;

		if (g_uiProcStatus.bControllerCommError1 || LOCK_MUST_RESET)
		{
			//if communication error, retry it per 5 seconds.
			if (uiTimeGetTickCount() - dwPrevCallTime > 5000)
			{
				dwPrevCallTime = uiTimeGetTickCount();
				g_uiProcStatus.bControllerCommError1 = !LOCK_SET_SETTING(NULL);
				nConnectFailCount = 0;
			}
		}
		else
		{
			LOCK_MUTEX.lock();
			if (!LOCK_QUEUE.isEmpty())
				fn = LOCK_QUEUE.dequeue();
			else
				fn = NULL;
			LOCK_MUTEX.unlock();

			if (fn) //queue is not empty
			{
				for (i=0; i<3; i++)
				{
					LOCK_MUTEX.lock();
					nResult = fn();
					LOCK_MUTEX.unlock();

					if (nResult == 0)
						break;
					usleep((__useconds_t)(100000));
				}
			}
			else //queue is empty, so check the door status per 2 seconds
			{
				if (uiTimeGetTickCount() - dwPrevCallTime > 2000)
				{
					dwPrevCallTime = uiTimeGetTickCount();

// 					for (i=0; i<3; i++)
					{
						LOCK_MUTEX.lock();
						nResult = UI_GetAlarmstatus(&dwAlarmType, &dwAliveTime);
						LOCK_MUTEX.unlock();

// 						if (nResult == 0)
// 							break;
						if (nResult == 0)
						{
							nConnectFailCount = 0;
							if (dwAliveTime < dwAliveTimePrev)
								LOCK_MUST_RESET = TRUE;
							dwAliveTimePrev = dwAliveTime;
						}
						else
							nConnectFailCount++;
//						usleep((__useconds_t)(100000));
					}
				}
			}

			if (nResult != 0)
			{
				if (nConnectFailCount > 4)
				{
					g_uiProcStatus.bControllerCommError = TRUE;
					g_uiProcStatus.bControllerCommError1 = TRUE;
				}
			}
			else
			{
				g_uiProcStatus.bControllerCommError1 = FALSE;

				if (dwAlarmType == DOOR_CLOSE_EVENT)
					g_uiProcStatus.nLastVerifiedUser = 0;
				else if (dwAlarmType == EXIT_BUTTON_EVENT)
					g_uiProcStatus.nLastVerifiedUser = 0;

				dwAlarmType -= 1;
				if (((int)dwAlarmType >= UI_ALARM_START && (int)dwAlarmType <= UI_ALARM_END) ||
					((int)dwAlarmType >= UI_ALARM_START + 128 && (int)dwAlarmType <= UI_ALARM_END + 128)) //Autostopped alarm
					g_uiProcStatus.nAlarmStatusFromController = (int)dwAlarmType;
			}
		}

		usleep((__useconds_t)(500000));
	}

	UI_CommStop();

	LOCK_MUTEX.lock();
	LOCK_QUEUE.clear();
	LOCK_MUTEX.unlock();

	g_uiProcStatus.bControllerCommError1 = FALSE;
	LOCK_THREAD_ID = 0;
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
BOOL LOCK_QUEUE_ADD(fnLockCtrlFunc fn)
{
	if (!fn)
		return FALSE;

	LOCK_MUTEX.lock();
	LOCK_QUEUE.enqueue(fn);
	LOCK_MUTEX.unlock();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

BOOL LOCK_INIT(DWORD dwPassword)
{
	LOCK_DEINIT();

	SB6000C_SETTING LockSetting;
	LockSetting.nLockOffTime = dbSetupTotal.setSystem.nLockTime;
	LockSetting.nDoorOpenTime = dbSetupTotal.setSystem.nDoorOpenTime;
	LockSetting.nAlarmDelay = dbSetupTotal.setSystem.nAlarmDelay;
	LockSetting.nDoorSensorType = dbSetupTotal.setSystem.nDoorSensorStatus;
	LockSetting.nExitBTType = 2;
	LockSetting.nTPW = dbSetupTotal.setNoMenu.wiegand_type.dwTpw;
	LockSetting.nTPI = dbSetupTotal.setNoMenu.wiegand_type.dwTpi;

	gPassword = dwPassword;
	LOCK_CONTROLLER_INITED = xuartconfig(g_hUart[SERIAL_DEVICE], B19200, CS8, 0);
	if (LOCK_CONTROLLER_INITED)
	{
		if (!LOCK_SET_SETTING(&LockSetting))
			g_uiProcStatus.bControllerCommError = TRUE;

		if (pthread_create(&LOCK_THREAD_ID, NULL, LOCK_THREAD, NULL))
		{
//			printf("LOCK_INIT: pthread_create fail !\n");
			LOCK_THREAD_ID = 0;
			LOCK_CONTROLLER_INITED = FALSE;
		}
	}
	return LOCK_CONTROLLER_INITED;
}

BOOL LOCK_DEINIT()
{
	void *ret;

	LOCK_CONTROLLER_INITED = FALSE;

	if (LOCK_THREAD_ID)
	{
//		pthread_detach(LOCK_THREAD_ID);
		pthread_join(LOCK_THREAD_ID, &ret);
		LOCK_THREAD_ID = 0;
	}

	LOCK_QUEUE.clear();

	return TRUE;
}

BOOL LOCK_SET_SETTING(SB6000C_SETTING *pBuf)
{
	BOOL bRet;

	if (!LOCK_CONTROLLER_INITED)
		return FALSE;

	LOCK_MUTEX.lock();
	if (pBuf)
		memcpy(&LOCK_SETTING, pBuf, sizeof(SB6000C_SETTING));
	bRet = (UI_SetSetupinfo(&LOCK_SETTING) == 0);
	bRet = (bRet && (UI_CommStart() == 0));
	if (bRet)
	{
		LOCK_MUST_RESET = FALSE;
	}
	else
		LOCK_MUST_RESET = TRUE;
	LOCK_MUTEX.unlock();

	if (bRet)
		LOCK_DOOR_CONTROL(__DOOR_STATUS[dbSetupTotal.setNoMenu.byDoorStatus]);

	return bRet;
}

BOOL LOCK_DOOR_STATUS()
{
	int nRet;
	DWORD dwStatus;

	if (!LOCK_CONTROLLER_INITED)
		return FALSE;
	LOCK_MUTEX.lock();
	nRet = UI_GetDoorstatus(&dwStatus);
	LOCK_MUTEX.unlock();

	if (nRet < 0 || gwAck != 0)
		return FALSE;
	return (dwStatus ? TRUE : FALSE);
}

BOOL LOCK_DOOR_CONTROL(int nDoorStatus)
{
	BOOL bRet = TRUE;

	if (!LOCK_CONTROLLER_INITED)
		return FALSE;

	switch (nDoorStatus)
	{
	case T_LOCK_UNCOND_OPEN:
		bRet = LOCK_QUEUE_ADD(UI_UncondOpen);
		break;
	case T_LOCK_UNCOND_CLOSE:
		bRet = LOCK_QUEUE_ADD(UI_UncondClose);
		break;
	case T_LOCK_DOOR_OPEN:
		bRet = LOCK_QUEUE_ADD(UI_DoorOpen);
		break;
	case T_LOCK_AUTO_RECOVER:
		bRet = LOCK_QUEUE_ADD(UI_AutoRecover);
		break;
	case T_LOCK_RESTART:
		bRet = LOCK_QUEUE_ADD(UI_Reboot);
		break;
	}

	return bRet;
}

BOOL LOCK_DURESS_OPEN()
{
	if (!LOCK_CONTROLLER_INITED)
		return FALSE;
	return LOCK_QUEUE_ADD(UI_ForcedDoorOpen);
}

BOOL LOCK_ALARM_START()
{
	if (!LOCK_CONTROLLER_INITED)
		return FALSE;
	return LOCK_QUEUE_ADD(UI_WarningStart);
}

BOOL LOCK_ALARM_STOP()
{
	if (!LOCK_CONTROLLER_INITED)
		return FALSE;
	return LOCK_QUEUE_ADD(UI_WarningCancel);
}

BOOL LOCK_BELL_START()
{
	if (!LOCK_CONTROLLER_INITED)
		return FALSE;
	return LOCK_QUEUE_ADD(UI_BellStart);
}

BOOL LOCK_BELL_STOP()
{
	if (!LOCK_CONTROLLER_INITED)
		return FALSE;
	return LOCK_QUEUE_ADD(UI_BellCancel);
}

BOOL LOCK_COMM_START()
{
	if (!LOCK_CONTROLLER_INITED)
		return FALSE;
	return LOCK_QUEUE_ADD(UI_CommStart);
}

BOOL LOCK_COMM_STOP()
{
	if (!LOCK_CONTROLLER_INITED)
		return FALSE;
	return LOCK_QUEUE_ADD(UI_CommStop);
}

BOOL LOCK_WIEGAND_SEND(BYTE *pData, int nBytes, int nBits)
{
	if (!LOCK_CONTROLLER_INITED)
		return FALSE;

	LOCK_MUTEX.lock();
	memcpy(WIEGAND_BUF, pData, nBytes);
	WIEGAND_BYTESIZE = nBytes;
	WIEGAND_BITSIZE = nBits;
	LOCK_MUTEX.unlock();

	return LOCK_QUEUE_ADD(UI_WiegandOut);
}
