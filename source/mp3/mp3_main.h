#ifndef __MP3_MAIN_H__
#define __MP3_MAIN_H__

enum mad_flow {
	MAD_FLOW_CONTINUE = 0x0000,	/* continue normally */
	MAD_FLOW_STOP     = 0x0010,	/* stop decoding normally */
	MAD_FLOW_BREAK    = 0x0011,	/* stop decoding and signal an error */
	MAD_FLOW_IGNORE   = 0x0020	/* ignore the current frame */
};

BOOL MP3_PLAY(const char *szFilename, DWORD dwTimeout = 60000);
int  MP3_STATUS();
BOOL MP3_FILECHECK(char *szFilename);
char* MP3_GetFileName(int nLang, int nSoundNumber);
int Wave_Rec_Start(char* Filename);
int Wave_Rec_End(void);

#endif /*__MP3_MAIN_H__*/
