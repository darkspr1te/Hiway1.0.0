#include "precomp.h"
#include <QtCore/QtGlobal>
#include <QtCore/QTranslator>
#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QRegion>
#include <QtCore/QDir>
#include "gui/MainWindow.h"

#define IOCTL_SD_CARD_RESET			1
#define IOCTL_SD_CARD_CHANGED		2
#define IOCTL_SD_CARD_PRESENT		3
#define IOCTL_SD_CARD_LOCKED		4
#define IOCTL_SD_DETECT_CARD		5

#define IOCTL_CAMMOD_RESET			1
#define IOCTL_CAMMOD_CHANGED		2
#define IOCTL_CAMMOD_PRESENT		3

extern speed_t __UART_BAUDRATE_MAP[];
extern CMainWindow *g_MainWindow;
static DWORD g_dwReadKeyTime=0;

//////////////////////////////////////////////////////////////////////////
static char __TEMP_BUF[1024];

//
//
//////////////////////////////////////////////////////////////////////////
typedef struct {
	u_int32_t	main_chunk;		/* 'RIFF' */
	u_int32_t	length;			/* Length of rest of file */
	u_int32_t	chunk_type;		/* 'WAVE' */
	
	u_int32_t	sub_chunk;		/* 'fmt ' */
	u_int32_t	sc_len;			/* length of format chunk = 16 or 18 (rest of chunk) */
} _wavefile_header;

typedef struct {
	u_int16_t	wFormatTag;
	u_int16_t	nChannels;
	u_int32_t	nSamplesPerSec;
	u_int32_t	nAvgBytesPerSec;
	u_int16_t	nBlockAlign;
	u_int16_t	wBitsPerSample;
} _fmt_chunk_body;

typedef struct {
	u_int32_t	chunk_mark;		/* 'fmt ', 'fact', 'data' */
	u_int32_t	chunk_length;	/* length of rest of chunk */
} _chunk_header;

#if BYTE_ORDER == LITTLE_ENDIAN
#define cpu_to_le32(x) (x)
#define cpu_to_le16(x) (x)
#else
#define cpu_to_le32(x) bswap_32((x))
#define cpu_to_le16(x) bswap_16((x))
#endif

#define le32_to_cpu(x) cpu_to_le32((x))
#define le16_to_cpu(x) cpu_to_le16((x))

#define DEF_SNDBUF_SIZE		8192
#define	WAVE_FORMAT_UNKNOWN		0x0000  /*  Microsoft Corporation  */
#define	WAVE_FORMAT_ADPCM		0x0002  /*  Microsoft Corporation  */
#define	WAVE_FORMAT_IEEE_FLOAT	0x0003  /*  Microsoft Corporation  */
#define	WAVE_FORMAT_PCM			0x0001

//////////////////////////////////////////////////////////////////////////
int check_wave(int thefd, int* pspeed, int* pbits, int* pstereo, int* pTotalCount)
{
	int count, k, nRet = 0;
	char *riff = (char*)"RIFF";
	char *wave = (char*)"WAVE";
	char *fmt = (char*)"fmt ";
	char *data = (char*)"data";
	_wavefile_header header;
	char stream[2][DEF_SNDBUF_SIZE];

	lseek(thefd, 0, SEEK_SET);
	count = read(thefd, &header, sizeof(header));
	if (count < (int)sizeof(header) || 
		memcmp(&(header.main_chunk), riff, 4) != 0) 
	{
		nRet = 0;
		goto l_exit;
	}
	
	nRet = -1;
	if (memcmp(&(header.chunk_type), wave, 4) != 0 || memcmp(&(header.sub_chunk), fmt, 4) != 0) goto l_exit;
	
	count = le32_to_cpu(header.sc_len);
	if (count != 0x10 && count != 0x12) goto l_exit;
	
	if (read(thefd, stream[0], count) < count) goto l_exit;
	
	count =  le16_to_cpu (((_fmt_chunk_body*)stream[0])->wFormatTag);
	if (count != WAVE_FORMAT_PCM) goto l_exit;
	
	if (pstereo) *pstereo = le16_to_cpu (((_fmt_chunk_body*)stream[0])->nChannels) - 1;
	
	if (pspeed) *pspeed = le32_to_cpu (((_fmt_chunk_body*)stream[0])->nSamplesPerSec);
	if (pbits) *pbits = le16_to_cpu (((_fmt_chunk_body*)stream[0])->wBitsPerSample);
	
	for (k = 0; k < 3; k++)
	{
		if (read(thefd, stream[0], sizeof(_chunk_header)) < (int)sizeof(_chunk_header)) break;
		if (memcmp(stream[0], data, 4) == 0) {
			nRet = 1;
			break;
		}
		count = le32_to_cpu(((_chunk_header*)stream[0])->chunk_length);
		if (count > (int)sizeof(stream)) break;
		if (read(thefd, stream[0], count) < count) break;
	}
	
	if (nRet == 1 && pTotalCount)
	{
		*pTotalCount = le32_to_cpu(((_chunk_header*)stream[0])->chunk_length);
	}
	
l_exit:
	return nRet;
}

//////////////////////////////////////////////////////////////////////////
int check_wave_buf(BYTE* pbyBuf, int* pspeed, int* pbits, int* pstereo, int*/* pTotalCount*/)
{
	int count, nRet = 0;
//	char *riff = (char*)"RIFF";
	char *wave = (char*)"WAVE";
	char *fmt = (char*)"fmt ";
//	char *data = (char*)"data";
	_wavefile_header header;
	char stream[2][DEF_SNDBUF_SIZE];
				
	memcpy(&header, pbyBuf, sizeof(header));
	
	nRet = -1;
	if (memcmp(&(header.chunk_type), wave, 4) != 0 || memcmp(&(header.sub_chunk), fmt, 4) != 0) goto l_exit;
	
	count = le32_to_cpu(header.sc_len);
	if (count != 0x10 && count != 0x12) goto l_exit;
	
	memcpy(stream[0], pbyBuf+sizeof(header), count);
	
	count =  le16_to_cpu (((_fmt_chunk_body*)stream[0])->wFormatTag);
	if (count != WAVE_FORMAT_PCM) goto l_exit;
	
	if (pstereo) *pstereo = le16_to_cpu (((_fmt_chunk_body*)stream[0])->nChannels) - 1;
	
	if (pspeed) *pspeed = le32_to_cpu (((_fmt_chunk_body*)stream[0])->nSamplesPerSec);
	if (pbits) *pbits = le16_to_cpu (((_fmt_chunk_body*)stream[0])->wBitsPerSample);
	nRet = 1;
l_exit:
	return nRet;
}



void InitOther(void)
{
	g_hOther = open("/dev/other", O_RDWR);
	if (g_hOther == -1)
	{
		printf("other Device Open Error !\r\n");
		return ;
	}
	//ioctl(g_hOther, IOCTL_LED_ON, 0);    // 点亮它
	//close(g_hOther);
}


//////////////////////////////////////////////////////////////////////////
static BOOL InitRtcClock(void)
{
	g_hRtcClock = open(DEVNAME_RTCCLOCK, O_RDWR);
	if (g_hRtcClock == -1)
	{
		printf("RTC Device Open Error !\r\n");
		return FALSE;
	}

//	xrtcalarmconfig(dbSetupTotal.setSystem.dwAutoPoweronTime);

	return TRUE;
}

static BOOL InitRtc1Clock(void)
{
	g_hRtc1Clock = open(DEVNAME_RTC1CLOCK, O_RDWR);
	if (g_hRtc1Clock == -1)
	{
		printf("own RTC Device Open Error !\r\n");
		return FALSE;
	}
	
	return TRUE;
}

static BOOL InitUart(int iUART)
{
	if (iUART == 0)
	{
		if (dbSetupTotal.setSystem.bRS232Use && g_params.nConsoleUse != 1)
			g_hUart[iUART] = open(DEVNAME_UART0, O_RDWR);
		else
		{
			g_hUart[iUART] = INVALID_HANDLE_VALUE;
			return TRUE;
		}
	}
	else if (iUART == 1)
	{
		if (dbSetupTotal.setSystem.bRS485Use && g_params.nConsoleUse != 2)
			g_hUart[iUART] = open(DEVNAME_UART1, O_RDWR);
		else
		{
			g_hUart[iUART] = INVALID_HANDLE_VALUE;
			return TRUE;
		}
	}

	if (g_hUart[iUART] == -1)
	{
		printf("UART Device[%d] Open Error !\r\n", iUART);
		return FALSE;
	}

	if (iUART == 0)
		tcgetattr(g_hUart[iUART], (struct termios *)(&g_ttyConsoleStatus[iUART]));

	if (iUART == 0 && dbSetupTotal.setSystem.dwBindingID)
	{
		LOCK_INIT(dbSetupTotal.setSystem.dwBindingID);
	}
	else
		xuartconfig(g_hUart[iUART], __UART_BAUDRATE_MAP[dbSetupTotal.setSystem.nBaudrate], CS8, 0);

	return TRUE;
}
static BOOL InitKeyboard(void)
{
	g_hKeyboard = open(DEVNAME_KEYBOARD, O_RDWR);
	if (g_hKeyboard == -1)
	{
		printf("Keyboard Device Open Error !\r\n");
		return FALSE;
	}

	return TRUE;
}
static BOOL InitBuzzer(void)
{
	g_hBuzzer = open(DEVNAME_BUZZER, O_RDWR);
	if (g_hBuzzer == -1)
	{
		printf("Buzzer Device Open Error !\r\n");
		return FALSE;
	}
	
	return TRUE;
}
// static BOOL InitMonoLcd(void)
// {
// 	g_hMonoLcd = open(DEVNAME_MONOLCD, O_RDWR);
// 	if (g_hMonoLcd == -1)
// 	{
// 		printf("LCD Device Open Error !\r\n");
// 		return FALSE;
// 	}
// 	return TRUE;
// }
static BOOL InitTftLcd(void)
{
	g_hTftLcd = open(DEVNAME_TFTLCD, O_RDWR);
	if (g_hTftLcd == -1)
	{
		printf("TFT LCD Device Open Error !\r\n");
		return FALSE;
	}
	return TRUE;
}
static BOOL InitWiegand(void)
{
	g_hWiegand = open(DEVNAME_WIEGAND, O_RDWR);
	if (g_hWiegand == -1)
	{
		printf("Wiegand Device Open Error !\r\n");
		return FALSE;
	}

//	xwiegandconfig(&dbSetupTotal.setNoMenu.wiegand_type);

	return TRUE;
}
static BOOL InitWatchdog(void)
{
	g_hWatchdogP = open(DEVNAME_PWATCHDOG, O_RDWR);
	if (g_hWatchdogP == -1)
	{
		printf("Physical Watchdog Device Open Error !\r\n");
		return FALSE;
	}

// 	g_hWatchdog = open(DEVNAME_WATCHDOG, O_RDWR);
// 	if (g_hWatchdog == -1)
// 	{
// 		printf("Watchdog Device Open Error !\r\n");
// 		return FALSE;
// 	}

//	fp_setlivecheck(TRUE, TRUE);

	return TRUE;
}
static BOOL InitRFMod(void)
{
	g_hRfmod = open(DEVNAME_RFMODULE, O_RDWR);
	if (g_hRfmod == -1)
	{
		printf("Rfmod Device Open Error !\r\n");
		return FALSE;
	}
	return TRUE;
}
//static BOOL InitSDMod(void)
//{
//	g_hSdmod = open(DEVNAME_SDMODULE, O_RDWR);
//	if (g_hSdmod == INVALID_HANDLE_VALUE)
//	{
//		printf("Sdmod Device Open Error !\r\n");
//		return FALSE;
//	}
//
//	SDCARD_RESET();
//
//	return TRUE;
//}
static BOOL InitCAMMod(void)
{
	g_hCammod = open(DEVNAME_CAMMODULE, O_RDWR);
	if (g_hCammod == -1)
	{
		printf("Cammod Device Open Error !\r\n");
		return FALSE;
	}
	
	ioctl(g_hCammod, IOCTL_CAMMOD_RESET, 0);
	return TRUE;
}
static BOOL InitPort(void)
{
	g_hPort = open(DEVNAME_GPIO, O_RDWR);
	if (g_hPort == -1)
	{
		printf("Port Device Open Error !\r\n");
		return FALSE;
	}
	
	return TRUE;
}
static BOOL InitSBUM(void)
{
	g_hUSBDevice = open(DEVNAME_SBUM, O_RDWR);
	if (g_hUSBDevice == INVALID_HANDLE_VALUE)
	{
		printf("USB Device handle open error !\r\n");
		return FALSE;
	}

	return TRUE;
}
// static BOOL InitServerSocket(void)
// {
// 	return comm_tcpserver_init();
// }
BOOL InitFpLibrary(void)
{
	BOOL bRet = TRUE;

	g_hFpLibrary = dlopen(FPLIB_FILENAME, RTLD_NOW);
	if (g_hFpLibrary == NULL)
	{
		printf("Can't load Engine Library, filename=%s, err:%s\r\n", FPLIB_FILENAME, dlerror());
		bRet = FALSE;
		goto _lExit;
	}

	fnSB_fp = (pfnENGINE)dlsym(g_hFpLibrary, "SB_fp");
	if (fnSB_fp == NULL)
	{
		printf("Can't find symbol name [SB_fp]\r\n");
		bRet = FALSE;
		goto _lExit;
	}

	pthread_t thread_id;
	if (pthread_create(&thread_id, NULL, ENGINE_THREAD, NULL))
	{
		printf("Can't create engine thread\r\n");
		bRet = FALSE;
		goto _lExit;
	}

	gFpVersion = SB_FP_GETVERSION(&gFpReleaseDate, &gFpMaximum);

_lExit:
	return bRet;
}

#define DEVINIT_WRAPPER(_f_, _e_)	{nRet = (_e_); bResult = (_f_); if (!bResult) goto _lExit;}
//////////////////////////////////////////////////////////////////////////
int SB3000DEV_INIT1()
{
	int nRet;
	BOOL bResult;
	
	DEVINIT_WRAPPER(InitRtcClock(),		DEVERR_RTC);
        //DEVINIT_WRAPPER(InitRtc1Clock(),	DEVERR_RTC);
        DEVINIT_WRAPPER(InitKeyboard(),		DEVERR_KEYBOARD);
        //DEVINIT_WRAPPER(InitBuzzer(),		DEVERR_BUZZER);
        DEVINIT_WRAPPER(InitTftLcd(),		DEVERR_LCD);
        //DEVINIT_WRAPPER(InitWiegand(),		DEVERR_WIEGAND);
        //DEVINIT_WRAPPER(InitWatchdog(),		DEVERR_WATCHDOG);
        //DEVINIT_WRAPPER(InitRFMod(),		DEVERR_RFMOD);
        //DEVINIT_WRAPPER(InitCAMMod(),		DEVERR_CAMMOD);
        //DEVINIT_WRAPPER(InitPort(),			DEVERR_GPIO);
        //DEVINIT_WRAPPER(InitSBUM(),			DEVERR_SBUM);
        //InitOther();   //zwh 2010.10.14

	return DEVERR_SUCCESS;

_lExit:
	return nRet;
}

//////////////////////////////////////////////////////////////////////////
int SB3000DEV_INIT2()
{
	int nRet;
	BOOL bResult;
        //DEVINIT_WRAPPER(InitUart(0),		DEVERR_UART0);
        //DEVINIT_WRAPPER(InitUart(1),		DEVERR_UART1);
	return DEVERR_SUCCESS;
_lExit:
	return nRet;
}

//////////////////////////////////////////////////////////////////////////
void SB30000DEV_DEINIT(BOOL /*bPoweroff*/)
{
	WEBSERVER_STOP();
	if (g_hFpLibrary)
		dlclose(g_hFpLibrary);
	FD_CLOSE(g_hRtcClock);
	FD_CLOSE(g_hRtc1Clock);
	FD_CLOSE(g_hKeyboard);
	FD_CLOSE(g_hBuzzer);
	FD_CLOSE(g_hMonoLcd);
	FD_CLOSE(g_hWiegand);
	fp_setlivecheck(FALSE);
	FD_CLOSE(g_hWatchdogP);
	FD_CLOSE(g_hSdmod);
	FD_CLOSE(g_hCammod);

	if (g_hUart[0] != INVALID_HANDLE_VALUE)
		tcsetattr(g_hUart[0], TCSANOW, (struct termios *)(&g_ttyConsoleStatus[0]));
	FD_CLOSE(g_hUart[0]);
	if (g_hUart[1] != INVALID_HANDLE_VALUE)
		tcsetattr(g_hUart[0], TCSANOW, (struct termios *)(&g_ttyConsoleStatus[1]));
	FD_CLOSE(g_hUart[1]);

// 	if (bPoweroff)
// 		POWER_OFF();
//	close(g_hPort);
}

static BOOL __CAMERA_DEV_INITED = FALSE;
//////////////////////////////////////////////////////////////////////////
BOOL InitCameraDevice(void)
{
	BOOL bRet = TRUE;

	CloseCameraDevice();

	memset(&g_VideoIn, 0, sizeof(T_VIDEOIN));
	if (sb_init_videoIn(&g_VideoIn, 320, 240, VIDEO_PALETTE_JPEG) != 0)  
	{
		printf("Can't init camera device\r\n");
		CloseCameraDevice();
		ioctl(g_hCammod, IOCTL_CAMMOD_RESET, 0);
		bRet = FALSE;
		goto _lExit;
	}

	sleep(1);

	if(sb_PauseVideo(&g_VideoIn) != 0)
	{
		printf("Can't init camera device\r\n");
		CloseCameraDevice();
		ioctl(g_hCammod, IOCTL_CAMMOD_RESET, 0);
		bRet = FALSE;
		goto _lExit;
	}

	__CAMERA_DEV_INITED = TRUE;

_lExit:
	return bRet;
}

void CloseCameraDevice(void)
{
	sb_close_videoIn(&g_VideoIn);
	memset(&g_VideoIn, 0, sizeof(g_VideoIn));
	__CAMERA_DEV_INITED = FALSE;
}

//
//
//////////////////////////////////////////////////////////////////////////
int GetMainTickCount(void)
{
	static int __start_time = 0; //second
	struct timeval tv;

	gettimeofday(&tv, NULL);

	if (__start_time == 0)
		__start_time = tv.tv_sec;

	return ((tv.tv_sec - __start_time) * 1000 + tv.tv_usec / 1000);//秒数*1000+微秒/1000就全部转换为毫秒
}

//////////////////////////////////////////////////////////////////////////
DWORD GetTickCount(int nType) //unit of microsecond
{
	DWORD dwRet = 0;
	static struct timeval __start_time = {0, 0};
	struct timeval tv;

	gettimeofday(&tv, NULL);

	switch(nType)
	{
	case TICKCOUNT_START:
		__start_time.tv_sec = tv.tv_sec;
		__start_time.tv_usec = tv.tv_usec;
		break;
	case TICKCOUNT_CALC:
	case TICKCOUNT_STOP:
		dwRet = (tv.tv_sec - __start_time.tv_sec) * 1000000 + tv.tv_usec - __start_time.tv_usec;
		break;
	}

	return dwRet;
}

//////////////////////////////////////////////////////////////////////////
void DelayMicroSecond(DWORD dwMicrosecond)
{
	int i;
//	usleep((__useconds_t)dwMicrosecond);
	while (dwMicrosecond--)
	{
		for (i=0; i<65; i++)
		{
			__asm("NOP");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void DelayMiliSecond(DWORD dwMilisecond)
{
// 	int i;
// 	while (dwMilisecond--)
// 	{
// 		for (i=0; i<65000; i++);
// 	}
	usleep((__useconds_t)(dwMilisecond * 1000));
}

//////////////////////////////////////////////////////////////////////////
int GetLastError(void)
{
	return 0;
//	return errno;
}

//////////////////////////////////////////////////////////////////////////
WORD CRC16Checksum(void* p, int blen)
{
	WORD* pw = (WORD*)p;
	WORD cksum = 0;
	
	while( blen )
	{
		cksum += pw[0];
		pw++;
		blen  -= 2;
	}
	
	return ~cksum;
}

//////////////////////////////////////////////////////////////////////////
void free_spaces(DWORD *pdwImageLimit, DWORD *pdwmallocPt, DWORD *pdwHEAPEND, DWORD *pdwfree)
{
	*pdwImageLimit = 0;
	*pdwmallocPt = 0;
	*pdwHEAPEND = 0;
	*pdwfree = 0;
}

DWORD free_spaces1(void)
{
	return 0;
}

DWORD free_spaces2(void)
{
	return 0;
}

DWORD free_spaces3(void)
{
	return 0;
}

DWORD free_spaces4(void)
{
	return 0;
}

int free_space_flash()
{
	return FREE_SPACE(ENROLLDATA_MOUNTPOINT);
}

int total_flash_size()
{
	return 64*1024*1024;
}

int total_ram_size()
{
	struct sysinfo info;
	sysinfo(&info);
	return (int)info.totalram;
}

int free_space_ram()
{
	struct sysinfo info;
	sysinfo(&info);
	return (int)info.freeram;
}

//
//
//////////////////////////////////////////////////////////////////////////
static BUZZER_CTRL __buzzer_on[] = 
{
	{BUZZER_ON,  0xFFFFFFF0, 0, -1, 0},
	{BUZZER_NONE,  0, 0, -1, 0}
};

static BUZZER_CTRL __buzzer_off[] = 
{
	{BUZZER_OFF, 50, 1, -1, 0},
	{BUZZER_NONE, 0, 0, -1, 0}
};

static BUZZER_CTRL __buzzer_ok[] = 
{
	{BUZZER_OFF, 50, 1, 0, 0},
	{BUZZER_ON,  50, 1, 0, 0},
	{BUZZER_OFF, 50, 1, 0, 0},
	{BUZZER_ON,  50, 1, 0, 0},
	{BUZZER_OFF, 50, 1, 0, 0},
	{BUZZER_ON,  50, 1, 0, 0},
	{BUZZER_OFF, 50, 1, 0, 0},
	{BUZZER_NONE,0,  0, 0, 0}
};

static BUZZER_CTRL __buzzer_error[] = 
{
	{BUZZER_OFF, 50,  1, 0, 0},
	{BUZZER_ON,  200, 1, 0, 0},
	{BUZZER_OFF, 50,  1, 0, 0},
	{BUZZER_NONE,0,   0, 0, 0}
};

static BUZZER_CTRL __buzzer_alarm[] = 
{
	{BUZZER_ON,  50, 1, 1, 1},
	{BUZZER_OFF, 50, 1, 1, 1},
	{BUZZER_NONE,0,  0, 1, 1}
};

static BUZZER_CTRL __buzzer_alarm_async[] = 
{
	{BUZZER_ON,  50, 1, 1, 0},
	{BUZZER_OFF, 50, 1, 1, 0},
	{BUZZER_NONE,0,  0, 1, 0}
};

//////////////////////////////////////////////////////////////////////////
void BUZZER_START(void)
{
	if (g_hBuzzer != INVALID_HANDLE_VALUE)
		write(g_hBuzzer, __buzzer_on, sizeof(__buzzer_on));
}

//////////////////////////////////////////////////////////////////////////
void BUZZER_STOP(void)
{
	if (g_hBuzzer != INVALID_HANDLE_VALUE)
		write(g_hBuzzer, __buzzer_off, sizeof(__buzzer_off));
}

//////////////////////////////////////////////////////////////////////////
void BUZZER_OK(void)
{
	if (g_hBuzzer != INVALID_HANDLE_VALUE)
		write(g_hBuzzer, __buzzer_ok, sizeof(__buzzer_ok));
}

//////////////////////////////////////////////////////////////////////////
void BUZZER_ERROR(void)
{
	if (g_hBuzzer != INVALID_HANDLE_VALUE)
		write(g_hBuzzer, __buzzer_error, sizeof(__buzzer_error));
}

//////////////////////////////////////////////////////////////////////////
void BUZZER_ALARM(void)
{
	if (g_hBuzzer != INVALID_HANDLE_VALUE)
		write(g_hBuzzer, __buzzer_alarm, sizeof(__buzzer_alarm));
}

//////////////////////////////////////////////////////////////////////////
void BUZZER_ALARM_ASYNC(void)
{
	if (g_hBuzzer != INVALID_HANDLE_VALUE)
		write(g_hBuzzer, __buzzer_alarm_async, sizeof(__buzzer_alarm_async));
}
//////////////////////////////////////////////////////////////////////////
void BUZZER_BELL(void)
{

}

//
//
struct input_event KB_DATA;
//////////////////////////////////////////////////////////////////////////
BYTE GETKEY(BOOL bLong)//BOOL bLong = FALSE
{
	if (g_hKeyboard == INVALID_HANDLE_VALUE)
		return UIKEY_NONE;
//xprintf("key1\r\n");
	int KEYCODE = bLong ? -1 : UIKEY_NONE;
	if(uiTimeGetTickCount() - g_dwReadKeyTime > 300)
	{
       		g_dwReadKeyTime=uiTimeGetTickCount();
                //read(g_hKeyboard, &KEYCODE, sizeof(KEYCODE));

                //hiway add
                //the next is test!!!
                int flags;
                //设置位无阻塞
                flags = fcntl(g_hKeyboard,F_GETFL,0);
                fcntl(g_hKeyboard,F_SETFL,flags|O_NONBLOCK);
                read(g_hKeyboard,&KB_DATA,sizeof(struct input_event));//阻塞的读取

                fcntl(g_hKeyboard,F_SETFL,flags);

                if(KB_DATA .type == 1)
                {
                    //qDebug() << "xxxxxxxxxxxxxxxxxxxx";
                    if(KB_DATA.code == 13)//13
                    {
                        if(KB_DATA.value == 1 /*|| KB_DATA.value == 2*/)
                        {
                            KEYCODE = UIKEY_OK;
                            return KEYCODE;
                        }
                    }
                    if(KB_DATA.code == 19)//19
                    {
                        if(KB_DATA.value == 1 /*|| KB_DATA.value == 2*/)
                        {
                            KEYCODE = UIKEY_MENU;
                            return KEYCODE;
                        }
                    }
                    if(KB_DATA.code == 14)//14
                    {
                        if(KB_DATA.value == 1 /*|| KB_DATA.value == 2*/)
                        {
                            KEYCODE = UIKEY_UP;
                            return KEYCODE;
                        }
                    }
                    if(KB_DATA.code == 15)//15
                    {
                        if(KB_DATA.value == 1 /*|| KB_DATA.value == 2*/)
                        {
                            KEYCODE = UIKEY_DOWN;
                            return KEYCODE;
                        }
                    }
                    if(KB_DATA.code == 1)//left
                    {
                        if(KB_DATA.value == 1 /*|| KB_DATA.value == 2*/)
                        {
                            KEYCODE = UIKEY_1;
                            return KEYCODE;
                        }
                    }
                    if(KB_DATA.code == 2)//15
                    {
                        if(KB_DATA.value == 1 /*|| KB_DATA.value == 2*/)
                        {
                            KEYCODE = UIKEY_2;
                            return KEYCODE;
                        }
                    }
                }
                else
                {
                    //continue;
                }


	}
	//int count = 5000;
	//while(count--)
	//{
		
		///这里循环检测power-key，实际是模拟的，为web2.0加入修改的
		//add by loveywm 2112.11.06
		//if(POWER_KEY())
			//return (BYTE)UIKEY_POWER;
		///
	//}

	
//xprintf("POWER_KEY==%d\r\n",POWER_KEY());
//xprintf("!POWER_KEY==%d\r\n",!POWER_KEY());
//xprintf("(BYTE)KEYCODE==%d\r\n",(BYTE)KEYCODE);	
	//sleep(0.3);  //延时0.3秒
	return (BYTE)KEYCODE;
}


//////////////////////////////////////////////////////////////////////////
BOOL KEYBOARD_SLEEP(BOOL bStatus, BOOL bPoweroff)
{
	if (g_hKeyboard == INVALID_HANDLE_VALUE)
		return FALSE;
	return (ioctl(g_hKeyboard, bStatus ? IOCTL_KEYBOARD_PAUSE : IOCTL_KEYBOARD_RESUME, bPoweroff) == 0);
}

//
//
//////////////////////////////////////////////////////////////////////////
void RtcGet(int* pnYear, int* pnMonth, int* pnDay, int* pnWeekday, int* pnHour, int* pnMinute, int* pnSecond)
{
	struct rtc_time rtc;

	if (g_hRtcClock == INVALID_HANDLE_VALUE)
		return;

	if (ioctl(g_hRtcClock, RTC_RD_TIME, &rtc))
	{
//		printf("RTC Read Time Error !\n");
	}

	*pnYear		= rtc.tm_year - 100;
	*pnMonth	= rtc.tm_mon + 1;
	*pnDay		= rtc.tm_mday;
	*pnWeekday	= rtc.tm_wday;
	*pnHour		= rtc.tm_hour;
	*pnMinute	= rtc.tm_min;
	*pnSecond	= rtc.tm_sec;

	if ((*pnYear < 0 || *pnYear > 99) ||
		(*pnMonth < 1 || *pnMonth > 12) ||
		(*pnDay < 1 || *pnDay > 31) ||
		(*pnHour < 0 || *pnHour > 23) ||
		(*pnMinute < 0 || *pnMinute > 59) ||
		(*pnSecond < 0 || *pnSecond > 59))
	{
		*pnYear = 0; *pnMonth = 1; *pnDay = 1; *pnHour = 0; *pnMinute = 0; *pnSecond = 0;
		RtcSet(0, 1, 1, 0, 0, 0, 0);
	}
}

//////////////////////////////////////////////////////////////////////////
void RtcSet(int nYear, int nMonth, int nDay, int nWeekday, int nHour, int nMinute, int nSecond)
{
	struct rtc_time rtc;

	if (g_hRtcClock == INVALID_HANDLE_VALUE)
		return;

	memset(&rtc, 0, sizeof(rtc_time));
	nYear %= 100;
	rtc.tm_year	= nYear + 100;
	rtc.tm_mon	= nMonth - 1;
	rtc.tm_mday = nDay;
	rtc.tm_wday = nWeekday;
	rtc.tm_hour = nHour;
	rtc.tm_min	= nMinute;
	rtc.tm_sec	= nSecond;

	if (ioctl(g_hRtcClock, RTC_SET_TIME, &rtc))
	{
//		printf("RTC Set Time Error !\n");
	}
}

//////////////////////////////////////////////////////////////////////////
void Rtc1Get(int* pnYear, int* pnMonth, int* pnDay, int* pnWeekday, int* pnHour, int* pnMinute, int* pnSecond)
{
	static BYTE _year, _month, _day, _hour, _minute, _second;    //sb 091125
	static BOOL _bInitialFlag = TRUE;                            //sb 091125
	struct rtc_time rtc;

	if (g_hRtc1Clock == INVALID_HANDLE_VALUE)
		return;

	if (ioctl(g_hRtc1Clock, OWNRTC_READ, &rtc))
	{
		Rtc1Set(0, 1, 1, 0, 0, 0, 0);
		if (ioctl(g_hRtc1Clock, OWNRTC_READ, &rtc))
		{
//			printf("RTC Read Time Error !\n");
		}
	}

	*pnYear		= rtc.tm_year - 100;
	*pnMonth	= rtc.tm_mon + 1;
	*pnDay		= rtc.tm_mday;
	*pnWeekday	= rtc.tm_wday;
	*pnHour		= rtc.tm_hour;
	*pnMinute	= rtc.tm_min;
	*pnSecond	= rtc.tm_sec;

	if ((*pnYear < 0 || *pnYear > 99) ||
		(*pnMonth < 1 || *pnMonth > 12) ||
		(*pnDay < 1 || *pnDay > 31) ||
		(*pnHour < 0 || *pnHour > 23) ||
		(*pnMinute < 0 || *pnMinute > 59) ||
		(*pnSecond < 0 || *pnSecond > 59))
	{
	/*	*pnYear = 0; *pnMonth = 1; *pnDay = 1; *pnHour = 0; *pnMinute = 0; *pnSecond = 0;
		Rtc1Set(0, 1, 1, 0, 0, 0, 0);
	}   *///sb 091125
	////sb 091125
			if (_bInitialFlag)
		{
			_bInitialFlag = FALSE;
			*pnYear = 0; *pnMonth = 1; *pnDay = 1; *pnHour = 0; *pnMinute = 0; *pnSecond = 0;
			Rtc1Set(0, 1, 1, 0, 0, 0, 0);
		}
		else
		{
			*pnYear = (int)_year; *pnMonth = (int)_month; *pnDay = (int)_day;
			*pnHour = (int)_hour; *pnMinute = (int)_minute; *pnSecond = (int)_second;
		}
	}

	_year = (BYTE)*pnYear; _month = (BYTE)*pnMonth; _day = (BYTE)*pnDay;
	_hour = (BYTE)*pnHour; _minute = (BYTE)*pnMinute; _second = (BYTE)*pnSecond;
	////sb 091125

}

//////////////////////////////////////////////////////////////////////////
void Rtc1Set(int nYear, int nMonth, int nDay, int nWeekday, int nHour, int nMinute, int nSecond)
{
	struct rtc_time rtc;

	if (g_hRtc1Clock == INVALID_HANDLE_VALUE)
		return;

	memset(&rtc, 0, sizeof(rtc_time));
	nYear %= 100;
	rtc.tm_year	= nYear + 100;
	rtc.tm_mon	= nMonth - 1;
	rtc.tm_mday = nDay;
	rtc.tm_wday = nWeekday;
	rtc.tm_hour = nHour;
	rtc.tm_min	= nMinute;
	rtc.tm_sec	= nSecond;

	if (ioctl(g_hRtc1Clock, OWNRTC_WRITE, &rtc))
	{
//		printf("Own RTC Set Time Error !\n");
	}
}

//////////////////////////////////////////////////////////////////////////
void RtcGetAlam(int* pnHour, int* pnMinute, int* pnSecond)
{
	struct rtc_time rtc_alarm;
	
	if (g_hRtcClock == INVALID_HANDLE_VALUE)
		return;

	if (ioctl(g_hRtcClock, RTC_ALM_READ, &rtc_alarm))
	{
//		printf("RTC Alarm Read Time Error !\n");
	}
	
	*pnHour		= rtc_alarm.tm_hour;
	*pnMinute	= rtc_alarm.tm_min;
	*pnSecond	= rtc_alarm.tm_sec;

}

//////////////////////////////////////////////////////////////////////////
void RtcSetAlam(int nHour, int nMinute, int nSecond)
{
	if (g_hRtcClock == INVALID_HANDLE_VALUE)
		return;

	struct rtc_time rtc_alarm;
	memset(&rtc_alarm, 0, sizeof(rtc_time));
	rtc_alarm.tm_hour = nHour;
	rtc_alarm.tm_min = nMinute;
	rtc_alarm.tm_sec = nSecond;

	if (ioctl(g_hRtcClock, RTC_ALM_SET, &rtc_alarm))
	{
//		printf("RTC Alarm Set Time Error !\n");
	}
}

//////////////////////////////////////////////////////////////////////////
void RtcAlarmDisable()
{
	if (g_hRtcClock == INVALID_HANDLE_VALUE)
		return;

	if (ioctl(g_hRtcClock, RTC_AIE_OFF, 0))
	{
//		printf("RTC Alarm Disable Error !\n");
	}
}

//
//
#define SIOCGIFFLAGS	0x8913
#define SIOCSIFFLAGS	0x8914
#define SIOCGIFHWADDR	0x8927
#define SIOCSIFHWADDR	0x8924
#define SIOCGIFADDR		0x8915
#define SIOCSIFADDR		0x8916
#define SIOCGIFNETMASK	0x891b
#define SIOCSIFNETMASK	0x891c

//////////////////////////////////////////////////////////////////////////
BOOL xifconfig(const char *devname, BYTE */*mac_addr*/, DWORD *ip_addr, DWORD *mask_addr, DWORD *gw_addr, BOOL bSet)
{
	int a, b, c, d;
	BOOL bRet = TRUE;

	//ip config
	if (TRUE)
	{
		if (bSet)
		{
			char *szCommand = (char*)malloc(1024);
			
			if (!szCommand)
				return FALSE;

			//SB_EXEC("ifconfig eth0 down");
			sprintf(szCommand, "ifconfig %s ", devname);
			UI_IP_UNMAKE(*ip_addr, a, b, c, d);
			sprintf(&szCommand[strlen(szCommand)], "%d.%d.%d.%d ", a, b, c, d);
			UI_IP_UNMAKE(*mask_addr, a, b, c, d);
			sprintf(&szCommand[strlen(szCommand)], "netmask %d.%d.%d.%d", a, b, c, d);
			SB_EXEC(szCommand);
			FREE(szCommand);
		}
		else
		{
			int s;
			struct ifreq ifr;

			s = socket(AF_INET, SOCK_DGRAM, 0);
			if (s < 0)
			{
//				printf("xifconfig: socket create error \n");
				return FALSE;
			}
			
			memset(ifr.ifr_name, 0, IFNAMSIZ);
			strcpy(ifr.ifr_name, devname);
			
			ioctl(s, SIOCGIFADDR, &ifr);
			*ip_addr = htonl(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr);
			
			ioctl(s, SIOCGIFNETMASK, &ifr);
			*mask_addr = htonl(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr);

			close(s);
		}
	}

	//set route
	if (TRUE)
	{
		FILE *f;
		int  count = 0;
		char devname[64];
		unsigned long dst, g, m;
		int flgs, ref, use, metric, mtu, win, ir;
		char szDest[10][32];
		char *szTemp;
		
		f = fopen("/proc/net/route", "r");
		if (!f)
		{
			bRet = FALSE;
			goto _lExit;
		}

		szTemp = (char*)malloc(1024);
		if (!szTemp)
			goto _lExit0;
		if (fscanf(f, "%*[^\n]\n") < 0)
			goto _lExit0;

		while (count < 10)
		{
			int r;
			r = fscanf( f, "%63s%lx%lx%X%d%d%d%lx%d%d%d\n",
						devname, &dst, &g, &flgs, &ref, &use, &metric, &m,
						&mtu, &win, &ir);
			if (r != 11)
			{
				if ((r < 0) && feof(f))
					break;
				goto _lExit0;
			}
			
			if (g == 0)
				continue;

			if (dst == 0)
			{
				strcpy(szDest[count], "default");
				if (!bSet) *gw_addr = htonl(g);
			}
			else
			{
				UI_IP_UNMAKE(dst, a, b, c, d);
			//	sprintf(szDest[count], "%03d.%03d.%03d.%03d", d, c, b, a);  //sb 091210
				sprintf(szDest[count], "%d.%d.%d.%d", d, c, b, a);  //sb 091210
			}
			count ++;
		}

		if (bSet)
		{
			while (count > 0)
			{
				count--;
				sprintf(szTemp, "route del %s", szDest[count]);
				SB_EXEC(szTemp);
			}
			
			UI_IP_UNMAKE(*gw_addr, a, b, c, d);
		//	sprintf(szTemp, "route add default gw %03d.%03d.%03d.%03d", a, b, c, d);  //sb 091210
			sprintf(szTemp, "route add default gw %d.%d.%d.%d", a, b, c, d);  //sb 091210
			SB_EXEC(szTemp);
		}
_lExit0:
		fclose(f);
		FREE(szTemp);
	}

_lExit:
	return bRet;
}

#define ETHTOOL_GSET		0x00000001
#define ETHTOOL_SSET		0x00000002
#define SIOCETHTOOL		0x8946

struct ethtool_cmd {
	__uint32_t	cmd;
	__uint32_t	supported;
	__uint32_t	advertising;
	__uint16_t	speed;
	__uint8_t	duplex;
	__uint8_t	port;
	__uint8_t	phy_address;
	__uint8_t	transceiver;
	__uint8_t	autoneg;
	__uint32_t	maxtxpkt;
	__uint32_t	maxrxpkt;
	__uint32_t	reserved[4];
};

BOOL xifconfig_speed(const char *devname, int nSpeed)
{
	int speed = 100;
	struct ifreq ifr;
	int fd = INVALID_HANDLE_VALUE, err;
	BOOL bRet = FALSE;

	if (nSpeed == NETSPEED_10MBPS)
		speed = 10;
	else if (nSpeed == NETSPEED_100MBPS)
		speed = 100;
	else
		return bRet;

	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, devname);

	//Create Datagram Socket
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
// 		perror("Cannot get control socket");
// 		return -1;
		goto _lExit;
	}

	struct ethtool_cmd ecmd;

	//Get Ethernet Information
	ecmd.cmd = ETHTOOL_GSET;
	ifr.ifr_data = (caddr_t)&ecmd;
	err = ioctl(fd, SIOCETHTOOL, &ifr);
	if (err < 0) {
// 		perror("Cannot get current device settings");
// 		return -2;
		goto _lExit;
	}
	else {// Get Ethernet Info OK...
		if (ecmd.speed == speed)
		{
			bRet = TRUE;
			goto _lExit;
		}
		ecmd.speed = speed; // Network Speed (Ex: 10, 100, 1000, 2500)
		ecmd.duplex = 1; //Duplex Mode (1: Full, 0: Half)
		ecmd.autoneg = 1; // Network Negotiation (Ex: Enable, Disable)
		ecmd.cmd = ETHTOOL_SSET;
		ifr.ifr_data = (caddr_t)&ecmd;
		err = ioctl(fd, SIOCETHTOOL, &ifr); // Set Ethernet Information
		if (err < 0){
// 			perror("Cannot set new settings");
// 			return -3;
			goto _lExit;
		}
		else if(speed != 100){// Enable Negotiation
			ecmd.cmd = ETHTOOL_GSET;
			ifr.ifr_data = (caddr_t)&ecmd;
			err = ioctl(fd, SIOCETHTOOL, &ifr);
			if (err < 0) {
// 				perror("Cannot get current device settings");
// 				return -2;
				goto _lExit;
			}
			else{
				ecmd.autoneg = 0;
				ecmd.cmd = ETHTOOL_SSET;
				ifr.ifr_data = (caddr_t)&ecmd;
				err = ioctl(fd, SIOCETHTOOL, &ifr);
				if (err < 0){
// 					perror("Cannot set new settings");
// 					return -3;
					goto _lExit;
				}
			}
		}
	}

	bRet = TRUE;

_lExit:
	FD_CLOSE(fd);
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
static volatile pthread_t __DHCP_THREAD_ID = 0;
//////////////////////////////////////////////////////////////////////////
void * xdhcpconfig_thread(void */*arg*/)
{
	int result;
	char szCommand[64];
	dbComm_dhcpSuccess = FALSE;
	sprintf(szCommand, "/sb3000t/pump -h sb3000t_%03d", dbComm_machineID);  
	result = SB_EXEC(szCommand);  
	pthread_detach(pthread_self());
	dbComm_dhcpSuccess = (result == 0);
	__DHCP_THREAD_ID = 0;
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
BOOL xdhcpconfigure(int nTimeout, BOOL bForce)
{
	int nKey;
	DWORD dwSTime, dwCurTime;
	BOOL bRet = TRUE;

	//DWORD			Comm_ipAddress;															//4
	//DWORD			Comm_ipSubnetMask;														//4
	//DWORD			Comm_ipDefaultGateway;	

   if(Net_LinkIsOk()==0)
   	return 0;

/*
	xifconfig("eth0", dbComm_macAddress, &Comm_ipAddress, &Comm_ipSubnetMask, &Comm_ipDefaultGateway, FALSE);
    if(Comm_ipAddress==0 || Comm_ipSubnetMask==0 || Comm_ipDefaultGateway==0)
    {
		Comm_ipAddress = dbSetupTotal.setSystem.ipAddress;
		Comm_ipSubnetMask = dbSetupTotal.setSystem.ipSubnetMask;
		Comm_ipDefaultGateway = dbSetupTotal.setSystem.ipDefaultGateway;
		xifconfig("eth0", dbComm_macAddress, &Comm_ipAddress, &Comm_ipSubnetMask, &Comm_ipDefaultGateway, TRUE);
    }
*/
	if (bForce && __DHCP_THREAD_ID)
	{
		pthread_detach(__DHCP_THREAD_ID);  
		__DHCP_THREAD_ID = 0;
	}
	if (__DHCP_THREAD_ID)
		return FALSE;
	if (pthread_create((pthread_t*)&__DHCP_THREAD_ID, NULL, xdhcpconfig_thread, NULL))
		return FALSE;

	if (!nTimeout || !g_MainWindow)
		return TRUE;

	uiLcdProgressDlgShow(UISTR_STATUS_DHCP_CONFIGURING); g_bProgress = TRUE;
	uiLcdProgressStart(UISTR_STATUS_DHCP_CONFIGURING);

	dwCurTime = dwSTime = uiTimeGetTickCount();

	while (dwCurTime < dwSTime + nTimeout)
	{
		nKey = uiKeyGetKey();
		if (nKey == UIKEY_ESC)
			break;

		if (!__DHCP_THREAD_ID)
			break;
		uiLcdProgress(LCDPROG_PERCENT(dwCurTime - dwSTime, nTimeout));
		dwCurTime = uiTimeGetTickCount();
	}

	uiLcdProgressEnd();
	uiLcdProgressDlgExit(); g_bProgress = FALSE;

	if (!__DHCP_THREAD_ID)
	{
//		uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_DHCP_CONFIGURE_SUCCESS, UI_MSGTIMEOUT);
		g_uiProcStatus.bPrevDhcpConfigStatus = TRUE;
		bRet = TRUE;
	}
	else
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_DHCP_CONFIGURE_FAIL, UI_MSGTIMEOUT);
		pthread_detach(__DHCP_THREAD_ID);
		bRet = FALSE;
	}
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
void xsignal(int sig)
{
	g_nSignal = sig;

	switch(sig)
	{
	case SIGINT:
		(void)signal(sig, xsignal);
		break;
	default:
		(void)fprintf(stdout, "unknown signal ! (%d)\n", sig);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
BOOL xuartconfig(HFILE s_handle, speed_t s_baud, tcflag_t s_data_bits, int s_parity_bit)
{
	int s_index;
	struct termios s_prev_termios, s_new_termios; 
	BOOL bRet = TRUE;

	if ((!s_handle) || (s_handle == INVALID_HANDLE_VALUE))
		return FALSE;

	bRet  = bRet && (tcgetattr(s_handle, (struct termios *)(&s_prev_termios)) == 0);

	(void)memcpy((void *)(&s_new_termios), (void *)(&s_prev_termios), (size_t)sizeof(struct termios));
	
	s_new_termios.c_iflag = IGNBRK | ((s_parity_bit == 0) ? ((tcflag_t)0) : IGNPAR);
	s_new_termios.c_oflag = (tcflag_t)0;
	s_new_termios.c_cflag = s_data_bits | CLOCAL | CREAD;
	s_new_termios.c_lflag = (tcflag_t)0;
	for(s_index = 0;s_index < NCCS;s_index++)s_new_termios.c_cc[s_index] = (cc_t)0;
	s_new_termios.c_cc[VMIN] = (cc_t)1;
	s_new_termios.c_cc[VTIME] = (cc_t)0;

	bRet = bRet && (cfsetispeed((struct termios *)(&s_new_termios), s_baud) == 0);
	bRet = bRet && (cfsetospeed((struct termios *)(&s_new_termios), s_baud) == 0);
	bRet = bRet && (tcsetattr(s_handle, TCSANOW, (struct termios *)(&s_new_termios)) == 0);
	bRet = bRet && (tcflush(s_handle, TCIOFLUSH) == 0);
//_lExit:
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL xuarttxempty(HFILE s_handle)
{
	int lsr; //Line Status Register
	if (s_handle == INVALID_HANDLE_VALUE)
		return TRUE;
	ioctl(s_handle, TIOCSERGETLSR, &lsr);
	return (lsr == 0);
}

//////////////////////////////////////////////////////////////////////////
BOOL xwiegandconfig(WIEGAND_TYPE *wiegand_type)
{
	BOOL bRet = TRUE;

	if (g_hWiegand == INVALID_HANDLE_VALUE || wiegand_type == NULL)
		return FALSE;
	bRet = (ioctl(g_hWiegand, WIEGAND_MODE_SET, wiegand_type) == 0 ? TRUE : FALSE);
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL xrtcalarmconfig(DWORD dwTime)
{
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;

	if (g_hRtcClock == INVALID_HANDLE_VALUE)
		return FALSE;

	if (dwTime)
	{
		uiRtcSeconds2YMDHMS(dwTime, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
		RtcSetAlam(nHour, nMinute, nSecond);
	}
	else
		RtcAlarmDisable();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void fp_setlivecheck(BOOL bCheck)
{
	if (g_hWatchdogP == INVALID_HANDLE_VALUE)
		return;

	if (bCheck)
		ioctl(g_hWatchdogP, WDOG_ENABLE, 0);
	else
		ioctl(g_hWatchdogP, WDOG_DISABLE, 0);
}

//////////////////////////////////////////////////////////////////////////
void wdog_restart(void)
{
	if (g_hWatchdogP == INVALID_HANDLE_VALUE)
	{
		SB_EXEC("reboot");
		return;
	}

	ioctl(g_hWatchdogP, WDOG_RESTART, 0);
}

static  BOOL __SystemReset=0;

void SystemReset(void)
{
  __SystemReset=1;
  while (1) {};
}


//////////////////////////////////////////////////////////////////////////
void wdog_app_alive(void)
{
	if (g_hWatchdogP == INVALID_HANDLE_VALUE)
		return;
	if(__SystemReset==0)
	   ioctl(g_hWatchdogP, WDOG_APP_ALIVE, 0);
}

//
//
//////////////////////////////////////////////////////////////////////////
static __inline void GPIO_SET_VALUE(DWORD dwAddr, int offset, int bits, int val)
{
	int i;
	DWORD dwMask;
	gpio_ctrl gpio;

	if (g_hPort == INVALID_HANDLE_VALUE)
		return;

	dwMask = 0;
	for (i=0; i<bits; i++)
	{
		dwMask <<= 1;
		dwMask += 1;
	}
	dwMask <<= offset;
	dwMask = ~dwMask;

	gpio.dwAddress = dwAddr;
	gpio.len = 4;
	ioctl(g_hPort, GPIO_READ, &gpio);

	gpio.dwAddress = dwAddr;
	gpio.dwValue = (gpio.dwValue & dwMask) | (val << offset);
	gpio.len = 4;
	ioctl(g_hPort, GPIO_WRITE, &gpio);
}

//////////////////////////////////////////////////////////////////////////
static __inline int GPIO_GET_VALUE(DWORD dwAddr, int offset, int bits)
{
	int i;
	DWORD dwMask;
	gpio_ctrl gpio;

	if (g_hPort == INVALID_HANDLE_VALUE)
		return 0;

	dwMask = 0;
	for (i=0; i<bits; i++)
	{
		dwMask <<= 1;
		dwMask += 1;
	}
	dwMask <<= offset;

	gpio.dwAddress = dwAddr;
	gpio.len = 4;
	ioctl(g_hPort, GPIO_READ, &gpio);
	
	return (gpio.dwValue & dwMask) >> offset;
}

//////////////////////////////////////////////////////////////////////////
#define GPIO_POWEROFF	rGPBDAT
#define GPIO_POWERKEY	rGPFDAT
#define GPIO_BELL		rGPHDAT
#define GPIO_DOOR		rGPHDAT
#define GPIO_DOOR_EXIT	rGPBDAT
#define GPIO_DOOR_SEN	rGPBDAT
#define GPIO_RS485EN	rGPADAT
#define GPIO_TAMPER		rGPFDAT
#define GPIO_LED_R		rGPADAT
#define GPIO_LED_G		rGPADAT
#define GPIO_ALARM		rGPHDAT
#define GPIO_LED_K		rGPADAT
#define GPIO_LCD_BG		rGPDDAT
#define GPIO_STG		rGPEDAT

//////////////////////////////////////////////////////////////////////////
void ALARM_ON(void)
{
	GPIO_SET_VALUE(GPIO_ALARM, 0, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void ALARM_OFF(void)
{
	GPIO_SET_VALUE(GPIO_ALARM, 0, 1, 0);
}

//////////////////////////////////////////////////////////////////////////
void POWER_OFF(void)
{
	GPIO_SET_VALUE(GPIO_POWEROFF, 1, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
int POWER_KEY(void)
{
	//xprintf("GPIO_GET_VALUE(GPIO_POWERKEY, 1, 1)==%d\r\n",GPIO_GET_VALUE(GPIO_POWERKEY, 1, 1));
	return (GPIO_GET_VALUE(GPIO_POWERKEY, 1, 1) == 0);
}

//////////////////////////////////////////////////////////////////////////
void BELL_ON(void)
{
	GPIO_SET_VALUE(GPIO_BELL, 10, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void BELL_OFF(void)
{
	GPIO_SET_VALUE(GPIO_BELL, 10, 1, 0);
}

//////////////////////////////////////////////////////////////////////////
void DOOR_OPEN(void)
{
	GPIO_SET_VALUE(GPIO_DOOR, 6, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void DOOR_CLOSE(void)
{
	GPIO_SET_VALUE(GPIO_DOOR, 6, 1, 0);
}

//////////////////////////////////////////////////////////////////////////
int DOOR_ISNOT_EXIT(void)
{
	return GPIO_GET_VALUE(GPIO_DOOR_EXIT, 2, 1);
}

//////////////////////////////////////////////////////////////////////////
int DOOR_IS_OPENED(void)
{
	return GPIO_GET_VALUE(GPIO_DOOR_SEN, 7, 1);
}

//////////////////////////////////////////////////////////////////////////
void RS485_ENABLE(void)
{
	GPIO_SET_VALUE(GPIO_RS485EN, 13, 1, 1); //DelayMicroSecond(4000);
}

//////////////////////////////////////////////////////////////////////////
void RS485_DISABLE(void)
{
	GPIO_SET_VALUE(GPIO_RS485EN, 13, 1, 0); //DelayMicroSecond(4000);
}

//////////////////////////////////////////////////////////////////////////
int TAMPER_IS_OFF(void)
{
	return (GPIO_GET_VALUE(GPIO_TAMPER, 6, 1) == 0);
}

//////////////////////////////////////////////////////////////////////////
void LED_R_ON()
{
//	GPIO_SET_VALUE(GPIO_LED_R, 3, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void LED_R_OFF()
{
//	GPIO_SET_VALUE(GPIO_LED_R, 3, 1, 0);
}

//////////////////////////////////////////////////////////////////////////
void LED_G_ON()
{
	GPIO_SET_VALUE(GPIO_LED_R, 3, 1, 0);
//	GPIO_SET_VALUE(GPIO_LED_G, 4, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void LED_G_OFF()
{
	GPIO_SET_VALUE(GPIO_LED_R, 3, 1, 1);
//	GPIO_SET_VALUE(GPIO_LED_G, 4, 1, 0);
}

//////////////////////////////////////////////////////////////////////////
void LED_K_ON()
{
	GPIO_SET_VALUE(GPIO_LED_K, 5, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void LED_K_OFF()
{
	GPIO_SET_VALUE(GPIO_LED_K, 5, 1, 0);
}

//////////////////////////////////////////////////////////////////////////
void LCD_BG_ON()
{
	GPIO_SET_VALUE(GPIO_LCD_BG, 8, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void LCD_BG_OFF()
{
	GPIO_SET_VALUE(GPIO_LCD_BG, 8, 1, 0);
}

//////////////////////////////////////////////////////////////////////////
#define SOUND_STOP()	{GPIO_SET_VALUE(GPIO_STG, 7, 4, 0);}

//////////////////////////////////////////////////////////////////////////
void APLUS_SOUND_BELL()
{
	SOUND_STOP();
	GPIO_SET_VALUE(GPIO_STG, 7, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void APLUS_SOUND_PRESSNEW()
{
	SOUND_STOP();
	GPIO_SET_VALUE(GPIO_STG, 8, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void APLUS_SOUND_OK()
{
	SOUND_STOP();
	GPIO_SET_VALUE(GPIO_STG, 9, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
void APLUS_SOUND_REVERIFY()
{
	SOUND_STOP();
	GPIO_SET_VALUE(GPIO_STG, 10, 1, 1);
}

//////////////////////////////////////////////////////////////////////////
static int __BLANK_STATUS = 0;
void LCD_BLANK(int nBlankMode)
{
	__BLANK_STATUS = nBlankMode;
        //hiway del
        //ioctl(g_hTftLcd, FBIOBLANK, nBlankMode);
}

int LCD_BLANK_STATUS()
{
	return __BLANK_STATUS;
}

/************************************************************************/
/* bitmap                                                               */
/************************************************************************/
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} PACKED BITMAPFILEHEADER;//12

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;
	long biWidth;
	long biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} PACKED BITMAPINFOHEADER;//40

typedef struct tagRGBQUAD
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBQUAD;//4

typedef struct tagBITMAPINFO
{
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD bmiColors[1];
} BITMAPINFO; 

struct FP_BITMAP
{
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFO bmInfo;
	RGBQUAD bmiColors[255];

	FP_BITMAP(int cx, int cy)
	{
		int i;
		RGBQUAD *pals;

		bmfHdr.bfType = ((WORD) ('M' << 8) | 'B');  // "BM"
		bmfHdr.bfSize = sizeof(FP_BITMAP) + cx*cy;
		bmfHdr.bfReserved1 = 0;
		bmfHdr.bfReserved2 = 0;
		bmfHdr.bfOffBits = sizeof(FP_BITMAP);
		
		bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmInfo.bmiHeader.biWidth = cx;
		bmInfo.bmiHeader.biHeight	= cy;
		bmInfo.bmiHeader.biPlanes	= 1;
		bmInfo.bmiHeader.biBitCount = 8;
		bmInfo.bmiHeader.biCompression = 0;
		bmInfo.bmiHeader.biSizeImage = cx*cy;
		bmInfo.bmiHeader.biXPelsPerMeter = 0;
		bmInfo.bmiHeader.biYPelsPerMeter = 0;
		bmInfo.bmiHeader.biClrUsed = 0;
		bmInfo.bmiHeader.biClrImportant = 0;
		
		pals = bmInfo.bmiColors;
		for (i = 0; i < 256; i++) {
			pals[i].rgbBlue = i;
			pals[i].rgbGreen = i;
			pals[i].rgbRed = i;
			pals[i].rgbReserved = 0;
		}
	}
} PACKED;

const FP_BITMAP fp_bmp256(256,256);
BYTE __IMAGE_DATA[sizeof(fp_bmp256) + 256*256];

void FP_FLIP()
{
	BYTE* p1 = &__IMAGE_DATA[sizeof(fp_bmp256)];
	BYTE* p2 = &((BYTE*)SB_FP__256IMAGE)[65535];
	int i = 65536;
	while(i)
	{
		*p1 = *p2;
		p1 ++;
		p2 --;
		i--;
	}
}

//////////////////////////////////////////////////////////////////////////
void DrawFingerprint(void *pWindow, void *pOrgPixmap)
{
// 	char szFilename[] = "/tmp/img256.bmp";
// 
// 	Save256Image(szFilename, (BYTE*)SB_FP__256IMAGE, 256*256);

	memcpy(&__IMAGE_DATA[0], &fp_bmp256, sizeof(fp_bmp256));
	FP_FLIP();
//	memcpy(&__IMAGE_DATA[sizeof(fp_bmp256)], SB_FP__256IMAGE, 256*256);
	QLabel *pLabel = (QLabel*)pWindow;
	QPixmap pmap_fp;
	pmap_fp.loadFromData(__IMAGE_DATA, sizeof(__IMAGE_DATA));
// 	int w = pLabel->width();
// 	int h = pLabel->height();
	int w = ((QPixmap*)pOrgPixmap)->width();
	int h = ((QPixmap*)pOrgPixmap)->height();
// 	QRegion r(32, 16, 192, 224, QRegion::Ellipse);
	QRegion r(4, 4, 244, 244, QRegion::Ellipse);
	QPixmap pmap(w, h);

	if (pOrgPixmap)
		pmap = *(QPixmap*)pOrgPixmap;

	QPainter painter(&pmap);

	painter.save();
	painter.scale(w/256.0, h/256.0);
	painter.setClipRegion(r);
	painter.drawPixmap(0, 0, 256.0, 256.0, pmap_fp, 32.0, 16.0, 192.0, 224.0);
//	painter.rotate(180.0);
	painter.restore();
	painter.drawPixmap(0, 0, *(QPixmap*)pOrgPixmap);

	pLabel->setPixmap(pmap);
}

//////////////////////////////////////////////////////////////////////////
void DrawCamera(void *pWindow, void *pOrgPixmap, void *pNewPixmap)
{
	QLabel *pLabel = (QLabel*)pWindow;
	QPixmap pmap = *((QPixmap*)pOrgPixmap);
	int w = ((QPixmap*)pOrgPixmap)->width();
	int h = ((QPixmap*)pOrgPixmap)->height();
//	int x, y;
// 
// 	if (w > h)
// 	{
// 		x = (w - h) / 2;
// 		y = 0;
// 		w = h;
// 	}
// 	else
// 	{
// 		x = 0;
// 		y = (h - w) / 2;
// 		h = w;
// 	}

	QPainter painter(&pmap);

	painter.save();
	painter.scale(w/240.0, h/240.0);
	painter.drawPixmap(0, 0, 240, 240, *(QPixmap*)pNewPixmap, 40, 0, 240, 240);
	painter.restore();

	pLabel->setPixmap(pmap);
}

//////////////////////////////////////////////////////////////////////////
UINT64 STRING2ID(char* strID)
{
	int nLength, i;
	UINT64 nID = 0;
	BYTE number;

	if ((nLength = strlen(strID)) > IDNUMBER_LENGTH)
		return 0;

	for (i=0; i<nLength; i++)
	{
		nID *= 10;

		if (strID[i] >= '0' && strID[i] <= '9')
			number = strID[i] - '0';
// 		else if (strID[i] >= 'A' && strID[i] <= 'Z')
// 			number = 10 + strID[i] - 'A';
// 		else if (strID[i] >= 'a' && strID[i] <= 'z')
// 			number = 10 + strID[i] -'a';
		else
			number = 0;
		nID += number;
	}

	return nID;
}

//////////////////////////////////////////////////////////////////////////
char* ID2STRING(UINT64 nID)
{
	static char szID[IDNUMBER_LENGTH];
	int i;
	BYTE number;

	memset(szID, 0, sizeof(szID));

	for (i=IDNUMBER_LENGTH-1; i>=0; i--)
	{
		number = (BYTE)(nID % 10);
		szID[i] = '0' + number;
		nID /= 10;
	}

//_lExit:
	return szID;
}

//////////////////////////////////////////////////////////////////////////
DWORD STRING2PWD(char* strPassword)
{
	int nLength, i;
	DWORD dwPassword = 0;
	BYTE number;

	if ((nLength = strlen(strPassword)) > 8)
		return 0;

	for (i=0; i<nLength; i++)
	{
		dwPassword <<= 4;
		if (strPassword[i] >= '1' && strPassword[i] <= '9')
			number = strPassword[i] - '0';
		else if (strPassword[i] == '0')
			number = 10;
		else
			return 0;
		dwPassword += number;
	}

	return dwPassword;
}

//////////////////////////////////////////////////////////////////////////
char* PWD2STRING(DWORD dwPassword)
{
	static char szPWD[8];
	int i;
	BYTE number;

	memset(szPWD, 0, sizeof(szPWD));

	if (!dwPassword)
		return szPWD;

	i = 7;
	while (!(dwPassword & (0xF << i * 4))) i--;

	for (; i>=0; i--)
	{
		number = (BYTE)(dwPassword & 0x0F);
		if (number >= 1 && number <= 9)
			szPWD[i] = '0' + number;
		else if (number == 10)
			szPWD[i] = '0';
		dwPassword >>= 4;
	}

	return szPWD;
}

BOOL PWD2STRING(DWORD dwPassword, char *szPWD,int len)
{
	//static char szPWD[8];
	int i;
	BYTE number;

	memset(szPWD, 0, len);

	
	if (!dwPassword)
		return 0;

	i = 7;
	while (!(dwPassword & (0xF << i * 4))) i--;
	

	for (; i>=0; i--)
	{
		number = (BYTE)(dwPassword & 0x0F);
		if (number >= 1 && number <= 9)
			szPWD[i] = '0' + number;
		else if (number == 10)
			szPWD[i] = '0';
		dwPassword >>= 4;
	}

	return 1;
}


//////////////////////////////////////////////////////////////////////////
QString UNICODE2STRING(WORD* szUnicodeStr, int nSize)
{
	QString szRet;
	for (int i=0; szUnicodeStr[i] && i < nSize; i++)
	{
		szRet += QChar(szUnicodeStr[i]);
	}
	return szRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL STRING2UNICODE(QString str, WORD* szUnicodeBuffer, int nBufferSize)
{
	int i;

	if (str.length() >= nBufferSize)
		return FALSE;

	for (i=0; i<str.length(); i++)
		szUnicodeBuffer[i] = str[i].unicode();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
int LOCKGROUP2NUMBER(int nLockGroup)
{
	int nNumber = 0;

	for (int i=0; i<ACCESS_USER_GROUP_COUNT; i++)
	{
		if (nLockGroup & (1 << i))
		{
			nNumber *= 10;
			nNumber += (i + 1);
		}
	}
	return nNumber;
}

//////////////////////////////////////////////////////////////////////////
char* LOCKGROUP2STRING(int nLockGroup)
{
	memset(__TEMP_BUF, 0, sizeof(__TEMP_BUF));

	for (int i=0; i<ACCESS_USER_GROUP_COUNT; i++)
	{
		if (nLockGroup & (1 << i))
			sprintf(&__TEMP_BUF[strlen(__TEMP_BUF)], ":%d", i + 1);
	}

	return &__TEMP_BUF[1];
}

//////////////////////////////////////////////////////////////////////////
int NUMBER2LOCKGROUP(int nNumber)
{
	int nLockGroup = 0;
	int nDigit;

	while (nNumber)
	{
		nDigit = nNumber % 10;
		if (nDigit && nDigit <= ACCESS_USER_GROUP_COUNT)
			nLockGroup |= (1 << (nDigit - 1));
		nNumber /= 10;
	}
	return nLockGroup;
}

//////////////////////////////////////////////////////////////////////////
BOOL LOCKGROUP_VALIDCHECK(BYTE *pLockGroupList, BYTE byLockGroup)
{
	int i;
	BYTE byTemp;

	if (!byLockGroup)
		return TRUE;

	for (i=0; i<MULTI_IDENT_SET_COUNT; i++)
	{
		if (!pLockGroupList[i])
			continue;

		byTemp = pLockGroupList[i] & byLockGroup;
		if ((byTemp == pLockGroupList[i]) || (byTemp == byLockGroup))
			return FALSE;
	}
	return TRUE;
}

#if (SB3000_USERVERIFY_LEVEL == 1)
static int VM_LIST[] = {VM_NONE, VM_ANY, VM_FP, VM_RFFP, VM_RF, VM_IDFP, VM_IDPW};
#elif (SB3000_USERVERIFY_LEVEL == 2)
static int VM_LIST[] = {VM_NONE, VM_ANY, VM_RFFP, VM_RFPW, VM_FPRFPW, VM_FP, VM_RF, VM_IDPW};
#endif /*SB3000_USERVERIFY_LEVEL*/
//////////////////////////////////////////////////////////////////////////
int VERIFYMODE2INDEX(int nVerifyMode)
{
	for (int i=0; i<(int)ITEM_CNT(VM_LIST); i++)
	{
		if (nVerifyMode == VM_LIST[i])
			return i;
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////
int INDEX2VERIFYMODE(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)ITEM_CNT(VM_LIST))
		return -1;
	return VM_LIST[nIndex];
}

//////////////////////////////////////////////////////////////////////////
DWORD VERIFYMODE2MASK(int nVerifyMode)
{
	DWORD dwMask = 0;

	switch (nVerifyMode)
	{
	case VM_ANY:
		dwMask = 0xFFFFFFFF;
		break;
	case VM_FP:
		dwMask = /*(1 << UI_VERIFY_ID) | */(1 << UI_VERIFY_FP);
		break;
	case VM_RFFP:
		dwMask = /*(1 << UI_VERIFY_ID) | */(1 << UI_VERIFY_RF) | (1 << UI_VERIFY_FP);
		break;
	case VM_RF:
		dwMask = /*(1 << UI_VERIFY_ID) | */(1 << UI_VERIFY_RF);
		break;
	case VM_IDFP:
		dwMask = (1 << UI_VERIFY_ID) | (1 << UI_VERIFY_FP);
		break;
	case VM_IDPW:
		dwMask = (1 << UI_VERIFY_ID) | (1 << UI_VERIFY_PW);
		break;
	case VM_RFPW:
		dwMask = (1 << UI_VERIFY_ID) | (1 << UI_VERIFY_RF) | (1 << UI_VERIFY_PW);
		break;
	case VM_FPPW:
		dwMask = (1 << UI_VERIFY_ID) | (1 << UI_VERIFY_FP) | (1 << UI_VERIFY_PW);
		break;
	case VM_FPRFPW:
		dwMask = (1 << UI_VERIFY_ID) | (1 << UI_VERIFY_FP) | (1 << UI_VERIFY_RF) | (1 << UI_VERIFY_PW);
		break;
	}

	return dwMask;
}

//////////////////////////////////////////////////////////////////////////
void EDITBOX_2_T9InputBox(QWidget* w)
{
	QString szObjectName = w->objectName();
	szObjectName += "useT9";
	w->setObjectName(szObjectName);
}

//////////////////////////////////////////////////////////////////////////
void CLEAR_ALL(QWidget *w)
{
	int i;
	QList<QLineEdit*> editList = w->findChildren<QLineEdit*>();
	QList<QComboBox*> comboList = w->findChildren<QComboBox*>();

	for (i=0; i<editList.size(); i++)
		editList[i]->setText("");
	for (i=0; i<comboList.size(); i++)
		comboList[i]->setCurrentIndex(0);
}

//////////////////////////////////////////////////////////////////////////
void SET_DLG_ITEM_COLOR(QWidget *w, int colorFlag /* = 0*/)
{
	int i;
	
	QPalette pal_title = w->palette();
	GUI_DLG_SET_FORE_COLOR(&pal_title, TITLECOLOR);

	QLabel* pTilte = w->findChild<QLabel*>("lblTitleText");
	QList<QLabel*> labelList = w->findChildren<QLabel*>();
	QList<QLineEdit*> editList = w->findChildren<QLineEdit*>();
	QList<QComboBox*> comboList = w->findChildren<QComboBox*>();
	
	QPalette pal = w->palette();
	if(colorFlag == 0)
		GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR1);
	if(colorFlag == 1)
		GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR);
	
	for (i=0; i<labelList.size(); i++)
		labelList[i]->setPalette(pal);
	for (i=0; i<editList.size(); i++)
		editList[i]->setPalette(pal);
	for (i=0; i<comboList.size(); i++)
		comboList[i]->setPalette(pal);

	if(pTilte != 0)
	{
		pTilte->setPalette(pal_title);
		pTilte->setFont(SB_FONT_2());
	}	 
}

//////////////////////////////////////////////////////////////////////////
int FILEOPEN(const char *szFilename, int flags)
{
	int fd = open(szFilename, flags & O_CUSTOMMASK);

	if (fd != INVALID_HANDLE_VALUE)
	{
		DWORD dwMark;
		int nSize = 0;

		if (flags & O_UNICODE)
		{
			dwMark = MAGIC_UNICODE; nSize = 2;
		}
		else if (flags & O_UNICODEBIG)
		{
			dwMark = MAGIC_UNICODEBIG; nSize = 2;
		}
		else if (flags & O_UTF8)
		{
			dwMark = MAGIC_UTF8; nSize = 3;
		}

		if (write(fd, &dwMark, nSize) != nSize)
		{
			close(fd);
			fd = INVALID_HANDLE_VALUE;
		}
	}

	return fd;
}

char* MAKE_FULLPATH(const char *szDir, const char *szFile, const char *szExtension)
{
	char last_char = '0';

	bzero(__TEMP_BUF, sizeof(__TEMP_BUF));
	if (szDir && szDir[0])
	{
		last_char = szDir[strlen(szDir) - 1];
		strcpy(__TEMP_BUF, szDir);
	}
	if (last_char != '/')
		strcat(__TEMP_BUF, "/");
	if (szFile)
		strcat(__TEMP_BUF, szFile);
	if (szExtension)
	{
		strcat(__TEMP_BUF, ".");
		strcat(__TEMP_BUF, szExtension);
	}
	return __TEMP_BUF;
}

BOOL FILE_EXIST(const char *szFile)
{
	struct stat buf;
	return (stat(szFile, &buf) == 0);
}

int FILE_SIZE(const char *szFile)
{
	struct stat buf;
	if (stat(szFile, &buf))
		return 0;
	return (int)buf.st_size;
}

BOOL MKDIR(const char *szDirName)
{
	return (mkdir(szDirName, 777) == 0);
}

BOOL DIR_CHECK_AND_MAKE(const char *szFullPath)
{
	char *dup_str = strdup(szFullPath);
	int k = strlen(szFullPath) - 1;
	BOOL bRet = FALSE;

	if (!dup_str)
		return FALSE;

	while (k > 0)
	{
		if (dup_str[k] == '/')
			break;
		k--;
	}

//	free(dup_str);

	if (k <= 0)
		goto _lExit;

	dup_str[k] = 0;
	if (QString(dup_str).contains(SDCARD_MOUNTPOINT) == TRUE)
	{
		if (!SDCARD_MOUNT())
			goto _lExit;
	}

	if (!FILE_EXIST((const char*)dup_str))
	{
		if (!MKDIR((const char*)dup_str))
			goto _lExit;
	}

//	szFullPath[k] = '/';
	bRet = TRUE;

_lExit:
// 	if (k > 0)
// 		szFullPath[k] = '/';
	FREE(dup_str);
	return bRet;
}

BOOL RMDIR(const char *szDirName)
{
	char szBuffer[64];

	if (QString(szDirName).contains(SDCARD_MOUNTPOINT) == TRUE)
	{
		if (!SDCARD_MOUNT())
			return FALSE;
	}

	sprintf(szBuffer, "rm -rf %s", szDirName);
	SB_EXEC(szBuffer);
	return TRUE;
}

BOOL COPYDIR(const char *szSrc, const char *szDst)
{
	char* szBuffer = (char*)malloc(256);

	if (szBuffer)
		return FALSE;
	sprintf(szBuffer, "cp -rf %s %s", szSrc, szDst);
	SB_EXEC(szBuffer);
	FREE(szBuffer);
	return TRUE;
}

BOOL SAVE_FILE(const char *szFullPath, BYTE *pData, int nSize)
{
	BOOL bRet = FALSE;
	HFILE fd = INVALID_HANDLE_VALUE;

	DIR_CHECK_AND_MAKE(szFullPath);

	if (QString(szFullPath).contains(SDCARD_MOUNTPOINT) == TRUE)
	{
		if (!SDCARD_MOUNT())
			return FALSE;
		if (FREE_SPACE(SDCARD_MOUNTPOINT) < nSize && !SDCARD_MAKESPACE(nSize))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SDCARD_ISFULL, UI_MSGTIMEOUT);
			return FALSE;
		}
	}

	fd = open(szFullPath, O_RDWR | O_CREAT | O_SYNC | O_TRUNC);//
	if (fd == INVALID_HANDLE_VALUE)
		goto _lExit;
	bRet = (write(fd, pData, nSize) == nSize);
// 	if (bRet)
// 		sync();

_lExit:
	FD_CLOSE(fd);
	return bRet;
}

BOOL COPY_FILE(const char *szFilename, const char *szNewFilename)
{
	DIR_CHECK_AND_MAKE(szNewFilename);

	if (QString(szFilename).contains(SDCARD_MOUNTPOINT) || QString(szNewFilename).contains(SDCARD_MOUNTPOINT))
	{
		if (!SDCARD_MOUNT())
			return FALSE;
	}

	if (QString(szNewFilename).contains(SDCARD_MOUNTPOINT))
	{
		int nSize = FILE_SIZE(szFilename);

		if (FREE_SPACE(SDCARD_MOUNTPOINT) < nSize && !SDCARD_MAKESPACE(nSize))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SDCARD_ISFULL, UI_MSGTIMEOUT);
			return FALSE;
		}
	}

	QFile::remove(szNewFilename);
	return QFile::copy(szFilename, szNewFilename);
}

BOOL DELETE_FILE(const char *szFullPath)
{
	return (unlink(szFullPath) == 0);
}

BOOL RENAME_FILE(const char *oldpath, const char *newpath)
{
	return (rename(oldpath, newpath) == 0);
}

int FREE_SPACE(const char *szFilesystem)
{
	struct statfs fs;
	statfs(szFilesystem, &fs);
	return fs.f_bsize * fs.f_bfree;
}

//////////////////////////////////////////////////////////////////////////
typedef struct
{
	BYTE byDirection;
	BYTE res[3];
	DWORD dwLength;
}T_IPC_DATA;
//////////////////////////////////////////////////////////////////////////
int SB_EXEC(const char *command, DWORD dwTimeout)
{
	HFILE hSock;
	struct sockaddr_in server_addr;
	socklen_t server_len;
	T_IPC_DATA hdr;
	int ret;
	int result = -1;
	DWORD dwETime = GetMainTickCount() + dwTimeout;

	if (dwTimeout == -1UL)
		dwETime = -1UL;

	hSock = socket(AF_INET, SOCK_STREAM, 0);
	if (hSock < 0)
		return -1;

	server_len = sizeof(server_addr);
	bzero(&server_addr, server_len);

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(6000);
	if (connect(hSock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		return -1;

	bzero(&hdr, sizeof(hdr));
	hdr.byDirection = 1;
	hdr.dwLength = strlen(command) + 1;
	write(hSock, &hdr, sizeof(hdr));
	write(hSock, command, hdr.dwLength);

	while ((DWORD)GetMainTickCount() < dwETime)
	{
		DelayMiliSecond(10);
		ret = recv(hSock, &hdr, sizeof(hdr), 0);
		if (ret < 0)
		{
			if (errno == EWOULDBLOCK)
				continue;
		}

		if (ret == sizeof(hdr) && hdr.dwLength == sizeof(result))
		{
			DelayMiliSecond(10);
			ret = recv(hSock, &result, hdr.dwLength, 0);
		}
		break;
	}
    close(hSock);
	return result;
}

static QTranslator *__TRANSLATOR = NULL;
BOOL SET_LANGUAGE(int nLanguage)
{
	const char* __sz_language[] = {"lang_en", "lang_sc", "lang_tc", "lang_kr", "lang_jp"};

	if (nLanguage >= UILANG_CNT)
		return FALSE;

	if (!__TRANSLATOR)
		__TRANSLATOR = new QTranslator;

	if (!__TRANSLATOR->load(__sz_language[nLanguage]))
		return FALSE;
	qApp->installTranslator(__TRANSLATOR);
	FONTDATABASE_INIT();
	return TRUE;
}

void SET_GUITHEME(int nTheme)
{
	g_nCurrentTheme = nTheme;

	switch (nTheme)
	{
	case THEME_1:
	case THEME_3:
		g_rgbForeColor = qRgb(255, 255, 214);
		g_rgbForeColor1 = qRgb(0, 0, 0);
		g_rgbBackgroundColor = qRgb(0, 0, 0);
		g_bgImageFilename = (char*)(GUI_RESOURCE_PATH "bg-main.png");
		g_titleImageFilename = (char*)(GUI_RESOURCE_PATH "title-1.png");
		g_inputboxImageFilename =(char*)(GUI_RESOURCE_PATH "bg-inputbox.png");
		g_bottomImageFilename =(char*)(GUI_RESOURCE_PATH "bottom.png");
		g_clockImageFilename = (char*)(GUI_RESOURCE_PATH "clock.png");
		break;
	case THEME_2:
		g_rgbForeColor = qRgb(255, 255, 255);
		g_rgbForeColor1 = qRgb(255, 255, 255);
		g_rgbBackgroundColor = qRgb(255, 255, 255);
		g_bgImageFilename =(char*)(GUI_RESOURCE_PATH "bg-main1.png");
		g_titleImageFilename =(char*)(GUI_RESOURCE_PATH "title-2.png");
		g_inputboxImageFilename =(char*)(GUI_RESOURCE_PATH "bg-inputbox1.png");
		g_bottomImageFilename =(char*)(GUI_RESOURCE_PATH "bottom1.png");
		g_clockImageFilename =(char*)(GUI_RESOURCE_PATH "clock1.png");
		break;
	}
}

BOOL STRING2HM(QString szTime, BYTE & bHour, BYTE & bMinute)
{
	QStringList szList = szTime.split(":");
	bHour = bMinute = 0;
	if (szList.count() != 2)
		return FALSE;
	bHour = (BYTE)szList[0].toInt();
	bMinute = (BYTE)szList[1].toInt();
	return TRUE;
}

BOOL WEBSERVER_START()
{
	if (WEBSERVER_ISALIVE())
		return TRUE;
	return (SB_EXEC("/sb3000t/webserver/webs&") == 0);
}

BOOL WEBSERVER_STOP()
{
	int pid = WEBSERVER_GETPID();
	char szCommand[64];
	if (pid == -1)
		return FALSE;
	sprintf(szCommand, "kill -9 %d", pid);
	SB_EXEC(szCommand);
	return TRUE;
}

int WEBSERVER_GETPID()
{
	HFILE fd = open("/tmp/webs.pid", O_RDONLY);
	int pid = 0;
	if (fd == INVALID_HANDLE_VALUE)
		return -1;
	if (read(fd, &pid, sizeof(int)) != sizeof(int))
		pid = -1;
	FD_CLOSE(fd);
	return pid;
}

BOOL WEBSERVER_ISALIVE()
{
	int pid = WEBSERVER_GETPID();
	char szPath[64];
	if (pid == -1)
		return FALSE;
	sprintf(szPath, "/proc/%d", pid);
	return FILE_EXIST(szPath);
}

BOOL TCPIP_ON()
{
	int fd = INVALID_HANDLE_VALUE;
	char szBuff[16];

	fd = open("/sys/class/net/eth0/operstate", O_RDONLY);
	if (fd != INVALID_HANDLE_VALUE)
	{
		memset(szBuff, 0, sizeof(szBuff));
		read(fd, szBuff, sizeof(szBuff));
		FD_CLOSE(fd);
		if (strncmp(szBuff, "down", 4))
			return TRUE;
	}
	return FALSE;
}

BOOL UDISK_ON()
{
	QDir dir("/sys/class/scsi_disk");
	return (dir.count() > 2);
}

BOOL CAMERA_ON()
{
	static BOOL __prev_status = FALSE;
	BOOL bStatus;

	if(ioctl(g_hCammod, IOCTL_CAMMOD_CHANGED, 0))
	{
		bStatus = ioctl(g_hCammod, IOCTL_CAMMOD_PRESENT, 0);
		if (bStatus)
		{
			wdog_app_alive();
			bStatus = InitCameraDevice();
			wdog_app_alive();
		}
		else
			CloseCameraDevice();
		__prev_status = bStatus;
	}
	return __prev_status;
}

BOOL CAMERA_CAPTURE()
{
	if(!CAMERA_ON())
		return FALSE;
	if(sb_ResumeVideo(&g_VideoIn) != 0)
	{
		CloseCameraDevice();
		return FALSE;
	}

	if(sb_grab(&g_VideoIn) != 0)
	{
		CloseCameraDevice();
		return FALSE;
	}
	if(sb_PauseVideo(&g_VideoIn) != 0)
	{
		CloseCameraDevice();
		return FALSE;
	}
	return TRUE;
}

BOOL SDCARD_ISMOUNT(void)
{
	QDir dir(SDCARD_MOUNTPOINT, "__smackbio-specific");
	return (dir.count() != 1);
}

BOOL SDCARD_DETECT(void)
{
// 	if(ioctl(g_hSdmod, IOCTL_SD_CARD_CHANGED, 0))
// 	{
		if(SDCARD_ISMOUNT())
			umount(SDCARD_MOUNTPOINT);

// 		ioctl(g_hSdmod, IOCTL_SD_DETECT_CARD, 0);
// 		ioctl(g_hSdmod, IOCTL_SD_DETECT_CARD, 0);
// 	}

	return (QDir("/sys/class/mmc_host/mmc0", "mmc*").count() > 0);
}

BOOL SDCARD_MOUNT(void)
{
	int i;
	int nRet;
	QDir dir;
	QDir dirMMCDevice;
	QStringList files;
	QString str,str1;
	char* pszMountDir;
	char szMountDir[256];
	const char* szFileSystems[] = {"vfat", "msdos"};

	if (SDCARD_ISMOUNT())
		umount(SDCARD_MOUNTPOINT);

// 	if (ioctl(g_hSdmod, IOCTL_SD_CARD_CHANGED, 0))
// 	{
// 		ioctl(g_hSdmod, IOCTL_SD_DETECT_CARD, 0);
// 		ioctl(g_hSdmod, IOCTL_SD_DETECT_CARD, 0);
// 	}
	
	dirMMCDevice = QDir("/sys/class/mmc_host/mmc0", "mmc*");
	if(dirMMCDevice.count() == 0)
		return FALSE;
// 	if(ioctl(g_hSdmod, IOCTL_SD_CARD_PRESENT, 0) == 0)
// 		return FALSE;
	
	for (i=0; i<(int)dirMMCDevice.count(); i++)
	{
		dir = QDir(QString("/sys/class/mmc_host/mmc0/") + dirMMCDevice[i], "block:mmcblk*");
		if(dir.count() > 0)
			break;
	}
	files = dir.entryList();
	str = files[0];
	str = str.right(1);

	dir = QDir(QString("/sys/block/mmcblk")+str, "mmcblk*");
	files = dir.entryList();
	if(dir.count() > 0)
	{
//		printf("kjc_debug_1\n");
		str = QString("/dev/")+files[0];
	}
	else
	{
//		printf("kjc_debug_2\n");
		str = QString("/dev/mmcblk")+str;
	}

	pszMountDir = STR2ASCII(str);
	memcpy(szMountDir, pszMountDir, str.count());
	szMountDir[str.count()] = 0;

//	printf("\nSDCARD_MOUNT = %s\n\n", szMountDir);

// 	if(ioctl(g_hSdmod, IOCTL_SD_CARD_PRESENT, 0) == 0)
// 		return FALSE;

	for (i=0; i<(int)ITEM_CNT(szFileSystems); i++)
	{
		nRet = mount(szMountDir, SDCARD_MOUNTPOINT, szFileSystems[i], 0, NULL);
		if (nRet != 0)
		{
			if (errno == 30) //Read-only file system
				nRet = mount(szMountDir, SDCARD_MOUNTPOINT, szFileSystems[i], MS_RDONLY, NULL);
		}
		if (nRet == 0)
			break;
	}
	if(nRet != 0)
	{
//		printf("sdcard mount fail: errno=%d,%s\n", errno, strerror(errno));
		return FALSE;
	}
	
//	printf("mount kkkkkkkkkkkkkkk\n");
	return TRUE;
}

BOOL SDCARD_LOCKED(void)
{
	if (g_hSdmod == INVALID_HANDLE_VALUE)
		return FALSE;

	int nRet = ioctl(g_hSdmod, IOCTL_SD_CARD_LOCKED, 0);
	return (nRet == 1);
}

BOOL SDCARD_RESET(void)
{
	if (g_hSdmod == INVALID_HANDLE_VALUE)
		return FALSE;

	ioctl(g_hSdmod, IOCTL_SD_CARD_RESET, 0);
	ioctl(g_hSdmod, IOCTL_SD_DETECT_CARD, 0);
	ioctl(g_hSdmod, IOCTL_SD_DETECT_CARD, 0);
	return TRUE;
}

// Assume that SDCard is already mounted.
//////////////////////////////////////////////////////////////////////////
BOOL SDCARD_MAKESPACE(int nSize)
{
	BOOL bRet = FALSE;
	QDir dir(SDCARD_MOUNTPOINT PATH_PHOTO_LOG, "", QDir::NoSort, QDir::Files);
	QStringList files= dir.entryList();
	char strFile[64];

	for (int i = files.count() - 1; i >= 0; i--)
	{
		sprintf(strFile, SDCARD_MOUNTPOINT PATH_PHOTO_LOG "/%s", STR2ASCII(files[i]));
		DELETE_FILE(strFile);
		if (FREE_SPACE(SDCARD_MOUNTPOINT) > nSize)
		{
			bRet = TRUE;
			break;
		}
	}

	return bRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define IOCTL_POWER_SUSPEND	0x5001
#define IOCTL_POWER_RESUME	0x5002

BOOL SBUM_SUSPEND()
{
	if (!g_hUSBDevice)
		return FALSE;
	FD_CLOSE(g_hUSBDevice);
	SB_EXEC("rmmod sbum");
	return TRUE;
//	return (ioctl(g_hUSBDevice, IOCTL_POWER_SUSPEND, 0) == 0);
}

BOOL SBUM_RESUME()
{
	SB_EXEC("insmod /usr/modules/sbum.ko");
	return InitSBUM();
//	return (ioctl(g_hUSBDevice, IOCTL_POWER_RESUME, 0) == 0);
}

