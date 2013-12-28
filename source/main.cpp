
/*
        这个版本固件来至于标准版本"SB3300-5K v1.35.1536.00";
        主要改动就是将原先的网路通信方面的协议改动了。
        改动的文件主要是com.cpp和com.h
        增加的具体内容:
        1:将原网路通信1.0改为2.0
        2:增加http方面的三个命令，时间，指纹，更新地址
        3:指纹容量变为2000枚。主要是把自动获取指纹全局变量gFpMaximum
           手动设置为2000 ；把显示的改动下
        //4:添加对power键值的捕捉，主要是照顾硬件平台的不支持

        修改人:姚伟民，date:2012.11.09
*/

//************************************************************************
//loveywm在2013.01.22日修改了com.cpp下的web2_cmd_get_user_reg()
//和web2_cmd_set_user_reg();两个函数

//************************************************************************
//2013.01.30 修复com.cpp下web2_cmd_get_user_reg();函数下的bug，在获取用户信息时
//忘了发送用户信息了。
//版本号升级为"SB3300-5K v1.35.1537.00"

//************************************************************************
//2013.02.01修复com.cpp下u8 web2_cmd_get_log( );函数下的取值错误bug，
//主要是指针指定位置有误。另外将所有获取时间的传值
//的时间累都换为u32，先前的int行最后不要。
//版本号升级为"SB3300-5K v1.35.1538.00"

//************************************************************************
//loveywm在2013.02.21日修复了如下bug:
//a:上传验证信息时间顺序紊乱
//b:存在重复上传记录，但索引却不同
//原因:主要是断网保存的验证信息在连上网络后上传的时间
//内又存在打卡验证动作，从而导致时间错误和重复上传
//解决方法:在验证上传函数中加入对机器是否有没验证记录
//上传的判断，见uiLogGlogAdd()函数的修改
//增加如下bug修复
//a:在函数web2_send_data()修复返回值的正确判断
//b:增加函数u8 web2_recv_data(int timeout)，主要是主动等待pc回复
//他被用于下面三个函数web2_send_finger，web2_send_glog，make_connect
//b修复的好处:先前处理发送后的接受都是在主循环等待接受的
//修改后是发送后就等待一段时间接受，防止接受紊乱
//!!!存在问题:接受时间不好确定，比如网络不稳定造成影响等
//???待改进问题:上传的验证信息中的索引在断电后在次从0开始
//版本号升级为"SB3300-5K v1.35.1539.00"
//???待改进问题已修复，见函数web2_send_glog

//只有返回索引与上传的对应才加1 modify:2013.03.29 web2_realtime_log


//修改数据接受兼容问题modify:2013.04.18.web2_cmd_set_user_reg
//版本号升级为"SB3300-5K v1.35.1539.01"

//修改姓名兼容问题，固件更新的bug! modify2013.04.19  web2_cmd_set_user_reg web2_cmd_get_all_userid http_updata_firmware
//版本号升级为"SB3300-5K v1.35.1540.00"

//2013.05.06增加卡的注册web2_cmd_set_user_reg


#include "precomp.h"
#include "gui/MainWindow.h"
#include <QtCore/QTextCodec>
#include "style/customstyle.h"
#include <QtPlugin>
#include "dbug.c"


void   uiProcMain(BOOL bFirst);
void* DAEMON_THREAD(void* arg);
BOOL SB3500A_LOAD();

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
