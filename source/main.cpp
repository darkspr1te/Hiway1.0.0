
/*
	����汾�̼������ڱ�׼�汾"SB3300-5K v1.35.1536.00";
	��Ҫ�Ķ����ǽ�ԭ�ȵ���·ͨ�ŷ����Э��Ķ��ˡ�
	�Ķ����ļ���Ҫ��com.cpp��com.h
	���ӵľ�������:
	1:��ԭ��·ͨ��1.0��Ϊ2.0
	2:����http������������ʱ�䣬ָ�ƣ����µ�ַ
	3:ָ��������Ϊ2000ö����Ҫ�ǰ��Զ���ȡָ��ȫ�ֱ���gFpMaximum
	   �ֶ�����Ϊ2000 ������ʾ�ĸĶ���
	//4:��Ӷ�power��ֵ�Ĳ�׽����Ҫ���չ�Ӳ��ƽ̨�Ĳ�֧��

	�޸���:Ҧΰ��date:2012.11.09
*/

//************************************************************************
//loveywm��2013.01.22���޸���com.cpp�µ�web2_cmd_get_user_reg()
//��web2_cmd_set_user_reg();��������

//************************************************************************
//2013.01.30 �޸�com.cpp��web2_cmd_get_user_reg();�����µ�bug���ڻ�ȡ�û���Ϣʱ
//���˷����û���Ϣ�ˡ�
//�汾������Ϊ"SB3300-5K v1.35.1537.00"

//************************************************************************
//2013.02.01�޸�com.cpp��u8 web2_cmd_get_log( );�����µ�ȡֵ����bug��
//��Ҫ��ָ��ָ��λ���������⽫���л�ȡʱ��Ĵ�ֵ
//��ʱ���۶���Ϊu32����ǰ��int�����Ҫ��
//�汾������Ϊ"SB3300-5K v1.35.1538.00"

//************************************************************************
//loveywm��2013.02.21���޸�������bug:
//a:�ϴ���֤��Ϣʱ��˳������
//b:�����ظ��ϴ���¼��������ȴ��ͬ
//ԭ��:��Ҫ�Ƕ����������֤��Ϣ������������ϴ���ʱ��
//���ִ��ڴ���֤�������Ӷ�����ʱ�������ظ��ϴ�
//�������:����֤�ϴ������м���Ի����Ƿ���û��֤��¼
//�ϴ����жϣ���uiLogGlogAdd()�������޸�
//��������bug�޸�
//a:�ں���web2_send_data()�޸�����ֵ����ȷ�ж�
//b:���Ӻ���u8 web2_recv_data(int timeout)����Ҫ�������ȴ�pc�ظ�
//��������������������web2_send_finger��web2_send_glog��make_connect
//b�޸��ĺô�:��ǰ�����ͺ�Ľ��ܶ�������ѭ���ȴ����ܵ�
//�޸ĺ��Ƿ��ͺ�͵ȴ�һ��ʱ����ܣ���ֹ��������
//!!!��������:����ʱ�䲻��ȷ�����������粻�ȶ����Ӱ���
//???���Ľ�����:�ϴ�����֤��Ϣ�е������ڶϵ���ڴδ�0��ʼ
//�汾������Ϊ"SB3300-5K v1.35.1539.00"
//???���Ľ��������޸���������web2_send_glog

//ֻ�з����������ϴ��Ķ�Ӧ�ż�1 modify:2013.03.29 web2_realtime_log


//�޸����ݽ��ܼ�������modify:2013.04.18.web2_cmd_set_user_reg
//�汾������Ϊ"SB3300-5K v1.35.1539.01"

//�޸������������⣬�̼����µ�bug! modify2013.04.19  web2_cmd_set_user_reg web2_cmd_get_all_userid http_updata_firmware
//�汾������Ϊ"SB3300-5K v1.35.1540.00"

//2013.05.06���ӿ���ע��web2_cmd_set_user_reg


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



/////////////////////////////������/////////////////////////////////////////////
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
	//ȡ�������	
	//comm_tcpserver_init();
        printf("After SB3000DEV_INIT2()\n");
	
	LCD_BLANK(FBINFO_BLANK_PAUSE);

	gbIsCMOS = TRUE;
	gCMOSType = dbLicense.nCMOS;
	//gCMOSType = CMOSTYPE_HV7131R;
	
//������ֻ����ģʽ	
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
