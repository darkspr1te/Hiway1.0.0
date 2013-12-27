#include "../precomp.h"
#include <QtGui/QApplication>
#include <QtCore/QString>

//////////////////////////////////////////////////////////////////////////
extern "C"
{
	extern volatile int MADPLAY_CONTROL;
	int play(const char* filename, int vol);
	int wav_rec_start(const char* filename);
	int wav_rec_end(void);

}

//////////////////////////////////////////////////////////////////////////
typedef struct stSoundTh{
	char szFilename[256];
	int nRet;
}T_MP3PLAY_DATA;

pthread_t __MP3_THREAD_ID = 0;
volatile BOOL __RECORDING = FALSE;
T_MP3PLAY_DATA __MP3_DAT, __MP3_DAT_THREAD;

//////////////////////////////////////////////////////////////////////////
void * MP3_THREAD(void */*arg*/)
{
	__MP3_DAT_THREAD = __MP3_DAT;
	__MP3_DAT_THREAD.nRet = play((char*)__MP3_DAT_THREAD.szFilename, dbSetupTotal.setSystem.nVolume);
	if(__MP3_DAT_THREAD.nRet == -1)
		__MP3_DAT.nRet = __MP3_DAT_THREAD.nRet;
	pthread_detach(pthread_self());
	__MP3_THREAD_ID = 0;
	return NULL;
}

BOOL MP3_PLAY(const char *szFilename, DWORD dwTimeout/* = 60000*/)
{
	DWORD dwEndTime;
	void* join_Ret;
	int nErr;

	return FALSE;//zwh 2010.12.2
	if (__RECORDING)
		return FALSE;
	if (__MP3_THREAD_ID)
	{
		MADPLAY_CONTROL = MAD_FLOW_STOP;
//		pthread_detach(__MP3_THREAD_ID);
		pthread_join(__MP3_THREAD_ID, &join_Ret);
		__MP3_THREAD_ID = 0;
	}
// 	while (__MP3_THREAD_ID)
// 	{
// 		MADPLAY_CONTROL = MAD_FLOW_STOP;
// 	}
 	MADPLAY_CONTROL = MAD_FLOW_CONTINUE;

	if (!szFilename)
		return FALSE;

	__MP3_DAT.nRet = 0;
	strcpy(__MP3_DAT.szFilename, szFilename);

	nErr = pthread_create((pthread_t*)&__MP3_THREAD_ID, NULL, MP3_THREAD, NULL);
	if (nErr)
		return FALSE;

	dwEndTime = uiTimeGetTickCount() + dwTimeout;
	WAIT_EVENT((uiTimeGetTickCount() < dwEndTime && __MP3_THREAD_ID));

//	if(__MP3_THREAD_ID)
//		pthread_join(__MP3_THREAD_ID, &join_Ret);

	if(__MP3_DAT.nRet == -1)
		return FALSE;
	else
		return TRUE;
}

int MP3_STATUS()
{
	if (__MP3_THREAD_ID)
		return MAD_FLOW_CONTINUE;
	return MAD_FLOW_STOP;
}

BOOL MP3_FILECHECK(char */*szFilename*/)
{
	return TRUE;
}

static char __TEMP_BUF[32];
char* MP3_GetFileName(int /*nLang*/, int nSoundNumber)
{
// 	if (nLang >= UILANG_CNT)
// 		return NULL;

	memset(__TEMP_BUF, 0, sizeof(__TEMP_BUF));
//	char* dirs[] = {"eng", "schn", "tchn", "kor", "jpn"};
//	sprintf(__TEMP_BUF, "%s/%s/%d.mp3", FLASH_MP3_CURRENT_DIRNAME, dirs[nLang], nStr - UISTR_SOUND_START);
	sprintf(__TEMP_BUF, "%s/%d.mp3", FLASH_MP3_CURRENT_DIRNAME, nSoundNumber);
	return __TEMP_BUF;
}

int Wave_Rec_Start(char* Filename)
{
	void *join_Ret;
	if(__MP3_THREAD_ID){
		pthread_join(__MP3_THREAD_ID, &join_Ret);
		__MP3_THREAD_ID = 0;
	}
	
	__RECORDING = TRUE;
	int nRet = wav_rec_start(Filename);
	if (nRet < 0)
		__RECORDING = FALSE;
	return nRet;
}

int Wave_Rec_End(void)
{
	int nRet = wav_rec_end();
	usleep(500000);
	__RECORDING = FALSE;
	return nRet;
}
