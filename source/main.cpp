
//主程序

#include "precomp.h"
#include "gui/MainWindow.h"
#include <QtCore/QTextCodec>
#include "style/customstyle.h"
#include <QtPlugin>
#include "dbug.c"


void   uiProcMain(BOOL bFirst);
void*  DAEMON_THREAD(void* arg);
BOOL   SB3500A_LOAD();

//Q_IMPORT_PLUGIN(qjpeg)

/////////////////////////////主函数/////////////////////////////////////////////
int main(int argc, char ** argv)
{
        BOOL bFirst = TRUE;


        Q_INIT_RESOURCE(sb3000);

        QApplication app(argc, argv);

        app.setFont(SB_FONT_3());
        app.setFont(SB_FONT_4(), "QLineEdit");

        app.setStyle(new CustomStyle);
        QTextCodec::setCodecForTr(QTextCodec::codecForName(TEXTCODEC));

        if (!SB3500A_LOAD())
        {
                printf("Database Load fail\n");
                comm_sendtime();
                return 0;
        }
        printf("%s", "Database Load Succeed\n");

        while (1)
        {
                CMainWindow *w = new CMainWindow();
                if (w)
                {
                    printf("hiway5\n");
                    uiProcMain(bFirst);
                    delete w;
                }
                bFirst = FALSE;
        }
        return 0;
}

BOOL InitFpLibrary(void);
//////////////////////////////////////////////////////////////////////////
BOOL SB3500A_LOAD()
{
        //BOOL bFpLibraryLoad = InitFpLibrary();

        if (SB3000DEV_INIT1() != DEVERR_SUCCESS)
        {
                //uiLcdMessageBox(UI_MSG_ERROR, UISTR_DEVICE_ERROR, UITIME_OUT);
                /*while (1)
                {
                        BUZZER_START(); LED_G_ON(); LED_R_ON(); DelayMiliSecond(500);
                        BUZZER_STOP();  LED_G_OFF();LED_R_OFF();DelayMiliSecond(500);
                }*/
        }
        printf("After SB3000DEV_INIT1()\n");
        //if (!bFpLibraryLoad)
        //{
                //BUZZER_START(); LED_G_ON(); LED_R_ON();
                //while (1) {};
        //}

        BOOL bRet = DbSetupTotalRead();

        printf("After DbSetupTotalRead()\n");

        if (SB3000DEV_INIT2() != DEVERR_SUCCESS)
        {
                //uiLcdMessageBox(UI_MSG_ERROR, UISTR_DEVICE_ERROR, UITIME_OUT);
                /*while (1)
                {
                        BUZZER_START(); LED_G_ON(); LED_R_ON(); DelayMiliSecond(500);
                        BUZZER_STOP();  LED_G_OFF();LED_R_OFF();DelayMiliSecond(500);
                }*/
        }
        //取消服务端
        //comm_tcpserver_init();
        printf("After SB3000DEV_INIT2()\n");

        LCD_BLANK(FBINFO_BLANK_PAUSE);

        gbIsCMOS = TRUE;
        gCMOSType = dbLicense.nCMOS;
        //gCMOSType = CMOSTYPE_HV7131R;

//下面是只读卡模式
        gbIsCMOS = FALSE;
#if(USE_FP == 1)
        if (SB_FP_OPEN(gCMOSType, NULL, NULL) != FP_ERR_SUCCESS)
        {
                uiLcdMessageBox(UI_MSG_ERROR, UISTR_DEVICE_ERROR, UITIME_OUT);
                //printf("FP Engine Open Error !\n");
                gbIsCMOS = FALSE;
        }
        uiCMOSCheck();
#endif
        printf("hiway1\n");
        LCD_BLANK(FBINFO_BLANK_RESUME);
        printf("bRet == %d\n",bRet);
        if (!Db_LoadAllData(bRet))
        {
                LCD_BLANK(FBINFO_BLANK_PAUSE);
                printf("hiway2\n");
                return FALSE;
        }
        LCD_BLANK(FBINFO_BLANK_PAUSE);
        printf("hiway3\n");
        fp_setlivecheck(TRUE);
        printf("hiway4\n");
        return TRUE;
}
