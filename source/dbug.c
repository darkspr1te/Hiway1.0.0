
#include "precomp.h"


#define FLASH_DBUGLOG_FILENAME		(ENROLLDATA_MOUNTPOINT "/dbuglog.txt")





extern void uiSL811_Remove(void);

//////////////////////////////////////////////////////////////////////////
BOOL DbugLogDelete(void)
{
	return 	DELETE_FILE(FLASH_DBUGLOG_FILENAME);
}

//////////////////////////////////////////////////////////////////////////
//ÅÅ³ýwarnning	
//DWORD DbugLogRead(UINT64 nID)
//{


//}

//////////////////////////////////////////////////////////////////////////
BOOL DbugLogWrite(void *pBuffer, int len)
{
#if (PrintfDbugEn== 1)

	int fd;
	int nFileSize;
	//int nCount;
	BOOL bRet;

	bRet = TRUE;

	fd = open(FLASH_DBUGLOG_FILENAME, O_RDWR | O_CREAT);
	if (fd == INVALID_HANDLE_VALUE)
		return 0;

	ioctl(fd, FIONREAD, &nFileSize);
	if (pwrite(fd, pBuffer, len, (off_t)nFileSize) != len)
	{
		bRet = FALSE;
	}
	FD_CLOSE(fd);

	return  bRet;
#endif	


}

BOOL uiSL811_DownloadDbugLog(void)
{
#if (PrintfDbugEn== 1)

	char strFileName[64];
	HFILE fi = INVALID_HANDLE_VALUE;
	int fd;
	int nFileSize;	
	BOOL bRet = TRUE;
	//ÅÅ³ýwarnning
	//DWORD dwMagic = MAGIC_ENROLLDB;
	//int nOffset = 0;
	//int i;
	//char *strTemp = NULL;

	if (!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}

/*
	if (FREE_SPACE(USB_MOUNTPOINT) < 
		(int)DWORD_ALIGN(4 + hdr.dwUIIndexSize + hdr.dwFPIndexSize + hdr.dwUserInfoSize + hdr.dwFPSize + uiSL811_VoiceAndPhotoSize()))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_USB_ISFULL, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}
*/	

	uiLcdProgressDlgShow(UISTR_MENU_DBUGLOGDOWNLOAD); g_bProgress = TRUE;

	strcpy(strFileName, USB_MOUNTPOINT "/" "DbugLog" ".txt");
	fi = open(strFileName, O_RDWR | O_CREAT | O_TRUNC);
	if (fi == INVALID_HANDLE_VALUE)
	{
		bRet = FALSE;
		goto _lExit;
	}

	BYTE  *pdata;	
	fd = open(FLASH_DBUGLOG_FILENAME, O_RDWR | O_CREAT);
	if (fd == INVALID_HANDLE_VALUE)
		return 0;
	ioctl(fd, FIONREAD, &nFileSize);

	pdata = (BYTE*)malloc(nFileSize);
	if (pdata == NULL)
	{
		bRet = FALSE;
		FD_CLOSE(fi);
		FD_CLOSE(fd);		
		goto _lExit;
	}
	memset(pdata, 0, nFileSize);
	bRet = _Db_FlashRead(fd, pdata, 0, 1, nFileSize, 0, NULL);
	//if (!_Db_FlashWrite(fi, pdata, 0, nFileSize/10, 10, NULL, 0))
	//{
	//	bRet = FALSE;
	//}
	if(pwrite(fd, pdata, (size_t)nFileSize, (off_t)0)!=nFileSize)
	{
	   bRet=FALSE;
	}
	FD_CLOSE(fi);
	FD_CLOSE(fd);

_lExit:
	FREE(pdata);
	uiSL811_Remove();

	uiLcdProgressDlgExit(); g_bProgress = FALSE;

	if (bRet)
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	else
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
	
	return bRet;
#endif	

	
}


void xprintf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
)
{
#if (PrintfDbugEn==1)
	va_list ap;
    	char string[256];

    	va_start(ap,str);
   	vsprintf(string,str,ap);
        comm_uartsend(0, &string, strlen(string)) ;
	//DbugLogWrite(&string, strlen(string)) ;
    	va_end(ap);
#endif	
}

void xfprintf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
)
{
	va_list ap;
    char string[256];

    va_start(ap,str);
    vsprintf(string,str,ap);
        comm_uartsend(0, &string, strlen(string)) ;
	//DbugLogWrite(&string, strlen(string)) ;
    va_end(ap);
}

void comm_sendtime (void)	
{
#if (PrintfDbugEn==1)

	int nYear,  nMonth,  nDay, nHour, nMinute,  nSecond,Weekday;
   // DWORD dwSeconds;
		
    //dwSeconds = uiTimeGetTickCount();
	//uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	RtcGet(&nYear, &nMonth, &nDay, &Weekday, &nHour, &nMinute, &nSecond);
	nYear += 2000;
	xprintf("\n%d-%d-%d %d:%d:%d\n",nYear,  nMonth,  nDay, nHour, nMinute,  nSecond);
    //xprintf(str,...);
 #endif	   
}





