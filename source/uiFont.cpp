#include "uiFont.h"
#include <QtCore/QStringList>



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////Menu Structure
#define uistr_MENU_MAINMENU				QObject::tr("1.MainMenu")
#define uistr_MENU_USERMANAGE			QObject::tr("2.UserManage")
#define uistr_MENU_SYSTEMSETTING		QObject::tr("3.Setting")
#define uistr_MENU_USBMANAGE			QObject::tr("4.U-DiskManage")
#define uistr_MENU_SYSINFOVIEW			QObject::tr("5.SysInfoView")
#define uistr_MENU_DATAVIEW				QObject::tr("6.DataView")
#define uistr_MENU_ALARMREMOVE			QObject::tr("7.AlarmRemove")

//>>uistr_MENU_USERMANAGE-----------------------------------------------------<<		1
#define uistr_MENU_ENROLLNEW			QObject::tr("1.1.Enroll")
#define uistr_MENU_ENROLLBACKUP			QObject::tr("1.2.Backup")
#define uistr_MENU_ENROLLDELETE			QObject::tr("1.3.Delete")
#define uistr_MENU_ENROLLEDIT			QObject::tr("1.4.Edit")
#define uistr_MENU_ENROLLDEL 			QObject::tr("1.5.Del")       
#define uistr_MENU_MESSINFO				QObject::tr("MENU_MESSINFO")

//>>>>uistr_MENU_ENROLLNEW, uistr_MENU_ENROLLBACKUP---------------------------<<<<		1.1, 1.2
#define uistr_MENU_ENROLL_FP			QObject::tr("1.1.1.EnrollFP")
#define uistr_MENU_ENROLL_RFCARD		QObject::tr("1.1.2.EnrollRF")
#define uistr_MENU_ENROLL_PWD			QObject::tr("MENU_ENROLL_PWD")
#define uistr_MENU_ENROLL_VOICE			QObject::tr("1.1.3.Voice")
#define uistr_MENU_ENROLL_PHOTO			QObject::tr("1.1.4.Photo")
//>>>>uistr_MENU_ENROLLDELETE-------------------------------------------------<<<<		1.3
#define uistr_MENU_DELETE_ALL			QObject::tr("1.3.1.DeleteAll")
#define uistr_MENU_DELETE_FP			QObject::tr("1.3.2.DeleteFP")
#define uistr_MENU_DELETE_RFCARD		QObject::tr("1.3.3.DeleteRF")
#define uistr_MENU_REMOVE_PWD			QObject::tr("1.3.4.RemovePWD")
#define uistr_MENU_DELETE_VOICE			QObject::tr("1.3.5.DeleteVocie")
#define uistr_MENU_DELETE_PHOTO			QObject::tr("1.3.6.DeletePhoto")

//>>uistr_MENU_SYSTEMSETTING--------------------------------------------------<<		2
#define uistr_MENU_MAINSETTING			QObject::tr("2.1.MainSetting")
#define uistr_MENU_ADVANCEDSETTING		QObject::tr("2.2.Advanced")
#define uistr_MENU_POWERMANAGE			QObject::tr("2.3.Power")
#define uistr_MENU_COMMSETTING			QObject::tr("2.4.CommSetting")
#define uistr_MENU_LOGSETTING			QObject::tr("2.5.LogSetting")
#define uistr_MENU_ACSETTING			QObject::tr("2.6.AC Setting")
#define uistr_MENU_SELFTEST				QObject::tr("2.7.SelfTest")

//>>>>uistr_MENU_MAINSETTING--------------------------------------------------<<<<		2.1
#define uistr_MENU_MAINSETTING_TIME		QObject::tr("2.1.1.TimeSet")


#define uistr_MENU_MAINSETTING_LANGUAGE	QObject::tr("2.1.2.Language")
#define uistr_MENU_MAINSETTING_SOUND	QObject::tr("2.1.3.Sound")
#define uistr_MENU_MAINSETTING_VOLUME	QObject::tr("2.1.4.Volume")
#define uistr_MENU_MAINSETTING_KEYALARM	QObject::tr("2.1.5.KeyTones")
#define uistr_MENU_MAINSETTING_BACKGROUP     QObject::tr("2.1.6.Backgroup")    
//>>>>>>uistr_MENU_MAINSETTING_TIME-------------------------------------------<<<<<<	2.1.1
#define uistr_MENU_MAINSETTING_TIME_FORMAT	QObject::tr("2.1.1.1.TimeFormat")
#define uistr_MENU_MAINSETTING_DATE_FORMAT	QObject::tr("2.1.1.2.DateFormat")
#define uistr_MENU_MAINSETTING_TIME_DATE	QObject::tr("2.1.1.3.Date")
#define uistr_MENU_MAINSETTING_TIME_TIME	QObject::tr("2.1.1.4.Time")
//>>>>uistr_MENU_ADVANCEDSETTING----------------------------------------------<<<<		2.2
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF			QObject::tr("2.2.1.VerifyInterface")
#define uistr_MENU_ADVANCEDSETTING_LOGDELETEALL		QObject::tr("2.2.2.AllLog Delete")
#define uistr_MENU_ADVANCEDSETTING_ENROLLDELETEALL	QObject::tr("2.2.3.Enroll Delete")
#define uistr_MENU_ADVANCEDSETTING_DEFAULT			QObject::tr("2.2.4.Default")
#define uistr_MENU_ADVANCEDSETTING_FWUPGRADE		QObject::tr("2.2.5.F/W Upgrade")
#define uistr_MENU_ADVANCEDSETTING_THEME			QObject::tr("MENU_ADVANCEDSETTING_THEME")
#define uistr_MENU_ADVANCEDSETTING_DAYLIGHT			QObject::tr("2.2.6.Daylight")

#define uistr_MENU_UPDATA_FIRMWARE			QObject::tr("HTTPUP_FIRMWARE")//add by loveywm 2012.10.22

#define uistr_MENU_ADVANCEDSETTING_FUNCKEY			QObject::tr("2.2.7.FuncKey")
#define uistr_MENU_ADVANCEDSETTING_MANAGER_COUNT	QObject::tr("2.2.8.ManagerCount")
#define uistr_MENU_ADVANCEDSETTING_DEFAULT_VERIFYMODE QObject::tr("2.2.9.Default Verify Mode")
#define uistr_MENU_ADVANCEDSETTING_SMANAGER_PWD		QObject::tr("2.2.10.SManagerPwd")
#define uistr_MENU_ADVANCEDSETTING_BRIGHT_ADJUST	QObject::tr("2.2.11.BrightAdjust")
//>>>>>>uistr_MENU_ADVANCEDSETTING_VERIFYIF-----------------------------------<<<<<<	2.2.1
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA	QObject::tr("2.2.1.1.Camera")
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF_PHOTOSHOW	QObject::tr("2.2.1.2.PhotoShow")
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERASHOW	QObject::tr("MENU_ADVANCEDSETTING_VERIFYIF_CAMERASHOW")
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF_FPSHOW		QObject::tr("2.2.1.3.FPShow")
//>>>>>>>>uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA--------------------------<<<<<<<<	2.2.1.1
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_SAVE QObject::tr("2.2.1.1.1.CameraSave")
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_FP	QObject::tr("2.2.1.1.2.Fingerprint")
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_CARD	QObject::tr("2.2.1.1.3.RF Card")
#define uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_PWD	QObject::tr("2.2.1.1.4.Password")
//>>>>>>uistr_MENU_ADVANCEDSETTING_DAYLIGHT-----------------------------------<<<<<<	2.2.6
#define uistr_MENU_ADVANCEDSETTING_DAYLIGHT_OFFSET	QObject::tr("2.2.6.1.Offset")
#define uistr_MENU_ADVANCEDSETTING_DAYLIGHT_CHANGE	QObject::tr("2.2.6.2.Change")
#define uistr_MENU_ADVANCEDSETTING_DAYLIGHT_RESTORE	QObject::tr("2.2.6.3.Restore")
//>>>>>>uistr_MENU_ADVANCEDSETTING_FUNCKEY------------------------------------<<<<<<	2.2.7
#define uistr_MENU_ADVANCEDSETTING_FUNCKEY_F1		QObject::tr("2.2.7.1.F1")
#define uistr_MENU_ADVANCEDSETTING_FUNCKEY_F2		QObject::tr("2.2.7.2.F2")
#define uistr_MENU_ADVANCEDSETTING_FUNCKEY_F3		QObject::tr("2.2.7.3.F3")
#define uistr_MENU_ADVANCEDSETTING_FUNCKEY_F4		QObject::tr("2.2.7.4.F4")
//>>>>uistr_MENU_POWERMANAGE--------------------------------------------------<<<<		2.3
#define uistr_MENU_POWERMANAGE_BELL			QObject::tr("2.3.1.Bell")
#define uistr_MENU_POWERMANAGE_IDLE			QObject::tr("2.3.2.Idle")
#define uistr_MENU_POWERMANAGE_POWEROFF		QObject::tr("2.3.3.Poweroff")
#define uistr_MENU_POWERMANAGE_POWERON		QObject::tr("2.3.4.Poweron")
#define uistr_MENU_POWERMANAGE_SLEEP		QObject::tr("2.3.5.Sleep")
#define uistr_MENU_POWERMANAGE_POWERKEYUSE	QObject::tr("2.3.6.PowerkeyUse")
#define uistr_MENU_POWERMANAGE_TRSWITCH		QObject::tr("2.3.7.TR Switch")
//>>>>>>uistr_MENU_POWERMANAGE_IDLE-------------------------------------------<<<<		2.3.2
#define uistr_MENU_POWERMANAGE_IDLE_POWEROFF	QObject::tr("2.3.2.1.Poweroff")
#define uistr_MENU_POWERMANAGE_IDLE_SLEEP		QObject::tr("2.3.2.2.Sleep")
#define uistr_MENU_POWERMANAGE_IDLE_LCDSWITCH	QObject::tr("2.3.2.3.LCD Switch")
//>>>>uistr_MENU_COMMSETTING--------------------------------------------------<<<<		2.4
#define uistr_MENU_COMMSETTING_DEVICEID		QObject::tr("2.4.1.DeviceID")
#define uistr_MENU_COMMSETTING_BAUDRATE		QObject::tr("2.4.2.Baudrate")
#define uistr_MENU_COMMSETTING_ETHERNETUSE	QObject::tr("2.4.3.EthernetUse")
#define uistr_MENU_COMMSETTING_IPADDRESS	QObject::tr("2.4.4.IP Address")
#define uistr_MENU_COMMSETTING_MASKADDRESS	QObject::tr("2.4.5.MaskAddress")
#define uistr_MENU_COMMSETTING_GWADDRESS	QObject::tr("2.4.6.DefGateway")
#define uistr_MENU_COMMSETTING_RS232USE		QObject::tr("2.4.7.RS232Use")
#define uistr_MENU_COMMSETTING_RS485USE		QObject::tr("2.4.8.RS485Use")
#define uistr_MENU_COMMSETTING_COMMPWD		QObject::tr("2.4.9.CommPassword")
#define uistr_MENU_COMMSETTING_DHCPUSE		QObject::tr("2.4.10.DHCP Use")
#define uistr_MENU_COMMSETTING_PCBACKGROUND	QObject::tr("2.4.11.PCBackground")
#define uistr_MENU_COMMSETTING_TCPIP		QObject::tr("2.4.12.TCPIP")
#define uistr_MENU_COMMSETTING_PORTBACKGROUND	QObject::tr("2.4.13.PORTBackground")    
//#define uistr_MENU_COMMSETTING_HTTPUPDATE                      QObject::tr("HTTPUP_TIME")//add by loveywm 2012.10.22
//#define uistr_MENU_UPDATA_FIRMWARE			QObject::tr("HTTPUP_FIRMWARE")//add by loveywm 2012.10.22
//#define uistr_UISTR_MENU_CHESHI			QObject::tr("MENU_CHESHI")
//#define uistr_MENU_COMMSETTING_CLIENT_CONNECT                      QObject::tr("2.4.15.CLIENT_CONNECT")

//>>>>uistr_MENU_LOGSETTING---------------------------------------------------<<<<		2.5
#define uistr_MENU_LOGSETTING_MLOGWARNING	QObject::tr("2.5.1.MLog Warn")
#define uistr_MENU_LOGSETTING_GLOGWARNING	QObject::tr("2.5.2.GLog Warn")
#define uistr_MENU_LOGSETTING_REVERIFYTIME	QObject::tr("2.5.3.ReverifyTime")
//>>>>uistr_MENU_ACSETTING----------------------------------------------------<<<<		2.6
#define uistr_MENU_ACSETTING_TIMEZONE				QObject::tr("2.6.1.Timezone")
#define uistr_MENU_ACSETTING_GROUP					QObject::tr("2.6.2.Group")
#define uistr_MENU_ACSETTING_USERTIMEZONE			QObject::tr("2.6.3.UserTimezone")
#define uistr_MENU_ACSETTING_LOCKGROUP_MAIN			QObject::tr("2.6.4.LockGroupMain")
#define uistr_MENU_ACSETTING_LOCKGROUP				QObject::tr("2.6.5.LockGroup")
#define uistr_MENU_ACSETTING_LOCKTIME				QObject::tr("2.6.6.LockTime")
#define uistr_MENU_ACSETTING_OPENTIME				QObject::tr("2.6.7.DoorOpenTime")
#define uistr_MENU_ACSETTING_DOORSENSOR				QObject::tr("2.6.8.DoorSensor")
#define uistr_MENU_ACSETTING_DURESS					QObject::tr("2.6.9.DuressFP")
#define uistr_MENU_ACSETTING_ILLEGALVERIFYWARNING	QObject::tr("2.6.10.IllegalVerify")
#define uistr_MENU_ACSETTING_GROUPVERIFYMODE		QObject::tr("2.6.11.GroupVerifyMode")
#define uistr_MENU_ACSETTING_ANTIPASS				QObject::tr("2.6.12.Antipass")
#define uistr_MENU_ACSETTING_ACCONTROLLERUSE		QObject::tr("2.6.13.AcControllerUse")
#define uistr_MENU_ACSETTING_GROUP_SET				QObject::tr("2.6.14.GroupSet")
#define uistr_MENU_ACSETTING_GROUP_DEFAULT_VM		QObject::tr("2.6.15.GroupDefaultVM")
#define uistr_MENU_ACSETTING_LOCKGROUP_SET			QObject::tr("2.6.16.LockGroupSet")
//>>>>>>UISTR_MENU_ACSETTING_GROUP--------------------------------------------<<<<<<	2.6.2
#define uistr_MENU_ACSETTING_GROUP_1					QObject::tr("2.6.2.1.G1")
#define uistr_MENU_ACSETTING_GROUP_2					QObject::tr("2.6.2.2.G2")
#define uistr_MENU_ACSETTING_GROUP_3					QObject::tr("2.6.2.3.G3")
#define uistr_MENU_ACSETTING_GROUP_4					QObject::tr("2.6.2.4.G4")
#define uistr_MENU_ACSETTING_GROUP_5					QObject::tr("2.6.2.5.G5")
//>>>>>>UISTR_MENU_ACSETTING_USERTIMEZONE-------------------------------------<<<<<<	2.6.3
#define uistr_MENU_ACSETTING_USERTIMEZONE_GROUP			QObject::tr("2.6.3.1.Group")
#define uistr_MENU_ACSETTING_USERTIMEZONE_GTZUSE		QObject::tr("2.6.3.2.GTzUse")
#define uistr_MENU_ACSETTING_USERTIMEZONE_TZ1			QObject::tr("2.6.3.3.TZ1")
#define uistr_MENU_ACSETTING_USERTIMEZONE_TZ2			QObject::tr("2.6.3.4.TZ2")
#define uistr_MENU_ACSETTING_USERTIMEZONE_TZ3			QObject::tr("2.6.3.5.TZ3")
#define uistr_MENU_ACSETTING_USERTIMEZONE_GVMUSE		QObject::tr("2.6.3.6.GVMUSE")
#define uistr_MENU_ACSETTING_USERTIMEZONE_VERIFYMODE	QObject::tr("2.6.3.7.VERIFYMODE")
//>>>>>>UISTR_MENU_ACSETTING_LOCKGROUP----------------------------------------<<<<<<	2.6.4
#define uistr_MENU_ACSETTING_LOCKGROUP_1				QObject::tr("2.6.4.1.G1")
#define uistr_MENU_ACSETTING_LOCKGROUP_2				QObject::tr("2.6.4.2.G2")
#define uistr_MENU_ACSETTING_LOCKGROUP_3				QObject::tr("2.6.4.3.G3")
#define uistr_MENU_ACSETTING_LOCKGROUP_4				QObject::tr("2.6.4.4.G4")
#define uistr_MENU_ACSETTING_LOCKGROUP_5				QObject::tr("2.6.4.5.G5")
#define uistr_MENU_ACSETTING_LOCKGROUP_6				QObject::tr("2.6.4.6.G6")
#define uistr_MENU_ACSETTING_LOCKGROUP_7				QObject::tr("2.6.4.7.G7")
#define uistr_MENU_ACSETTING_LOCKGROUP_8				QObject::tr("2.6.4.8.G8")
#define uistr_MENU_ACSETTING_LOCKGROUP_9				QObject::tr("2.6.4.9.G9")
#define uistr_MENU_ACSETTING_LOCKGROUP_10				QObject::tr("2.6.4.10.G10")
//>>>>>>UISTR_MENU_ACSETTING_DURESS---------------------------------------<<<<<<	2.6.8
#define uistr_MENU_ACSETTING_DURESS_MANAGE			QObject::tr("2.6.8.1.Manage")
#define uistr_MENU_ACSETTING_DURESS_PWD				QObject::tr("2.6.8.2.Password")
#define uistr_MENU_ACSETTING_DURESS_SOSKEY			QObject::tr("2.6.8.3.SOSKey")
#define uistr_MENU_ACSETTING_DURESS_ALARMDELAY		QObject::tr("2.6.8.4.AlarmDelay")
//>>>>>>>>UISTR_MENU_ACSETTING_DURESS_MANAGE------------------------------<<<<<<<<	2.6.8.1
#define uistr_MENU_ACSETTING_DURESS_MANAGE_ENROLL	QObject::tr("2.6.8.1.1.Enroll")
#define uistr_MENU_ACSETTING_DURESS_MANAGE_SET		QObject::tr("2.6.8.1.2.Set")
#define uistr_MENU_ACSETTING_DURESS_MANAGE_REMOVE	QObject::tr("2.6.8.1.3.Remove")
#define uistr_MENU_ACSETTING_DURESS_MANAGE_REMOVEALL QObject::tr("2.6.8.1.4.RemoveAll")
//>>>>>>UISTR_MENU_ACSETTING_GROUPVERIFYMODE----------------------------------<<<<<<	2.6.10
#define uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP1		QObject::tr("2.6.10.1.G1")
#define uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP2		QObject::tr("2.6.10.2.G2")
#define uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP3		QObject::tr("2.6.10.3.G3")
#define uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP4		QObject::tr("2.6.10.4.G4")
#define uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP5		QObject::tr("2.6.10.5.G5")
//>>>>uistr_MENU_SELFTEST-----------------------------------------------------<<<<		2.7
#define uistr_MENU_SELFTEST_ALL			QObject::tr("2.7.1.Test All")
#define uistr_MENU_SELFTEST_MEMORY		QObject::tr("2.7.2.Memory")
#define uistr_MENU_SELFTEST_LCD			QObject::tr("2.7.3.LCD")
#define uistr_MENU_SELFTEST_SOUND		QObject::tr("2.7.4.Sound")
#define uistr_MENU_SELFTEST_SENSOR		QObject::tr("2.7.5.Sensor")
#define uistr_MENU_SELFTEST_KEYBOARD	QObject::tr("2.7.6.Keyboard")
#define uistr_MENU_SELFTEST_RTC			QObject::tr("2.7.7.RTC")
#define uistr_MENU_SELFTEST_MP3			QObject::tr("2.7.8.MP3")

//>>uistr_MENU_USBMANAGE------------------------------------------------------<<		3
#define uistr_MENU_GLOGDOWNLOAD			QObject::tr("3.1.GLogDownload")
#define uistr_MENU_ALLGLOGDOWNLOAD		QObject::tr("3.2.AllGLogDownload")     
#define uistr_MENU_MLOGDOWNLOAD			QObject::tr("3.3.MLogDownload")
#define uistr_MENU_ALLMLOGDOWNLOAD		QObject::tr("3.4.ALLMLogDownload")     
#define uistr_MENU_USERINFODOWNLOAD		QObject::tr("3.5.UserInfoDownload")
#define uistr_MENU_USERINFOUPLOAD		QObject::tr("3.6.UserInfoUpload")
#define uistr_MENU_MSGUPLOAD			QObject::tr("3.7.MessageUpload")
#define uistr_MENU_MP3UPLOAD			QObject::tr("3.8.MP3Upload")

//>>uistr_MENU_SYSINFOVIEW----------------------------------------------------<<		4
#define uistr_MENU_USERENROLLCOUNT		QObject::tr("4.1.EnrollCount")
#define uistr_MENU_FPENROLLCOUNT		QObject::tr("4.2.FP Count")
#define uistr_MENU_PWDENROLLCOUNT		QObject::tr("MENU_PWDENROLLCOUNT")
#define uistr_MENU_CARDENROLLCOUNT		QObject::tr("MENU_CARDENROLLCOUNT")
#define uistr_MENU_GLOGCOUNT			QObject::tr("4.3.GLog Count")
#define uistr_MENU_MLOGCOUNT			QObject::tr("4.4.MLog Count")
#define uistr_MENU_USEDMEMORY			QObject::tr("4.5.UsedMemory")
#define uistr_MENU_FREESPACES			QObject::tr("4.6.FreeSpaces")
#define uistr_MENU_DEVICEINFO			QObject::tr("4.7.DeviceInfo")
#define uistr_MENU_USEDSPACES			QObject::tr("4.8.UsedSpaces")

//>>>>UISTR_MENU_FREESPACES---------------------------------------------------<<<<		4.6
#define uistr_MENU_FREE_USERENROLLCOUNT		QObject::tr("4.6.1.EnrollCount")
#define uistr_MENU_FREE_FPENROLLCOUNT		QObject::tr("4.6.2.FP Count")
#define uistr_MENU_FREE_PWDENROLLCOUNT		QObject::tr("MENU_FREE_PWDENROLLCOUNT")
#define uistr_MENU_FREE_CARDENROLLCOUNT		QObject::tr("MENU_FREE_CARDENROLLCOUNT")
#define uistr_MENU_FREE_GLOGCOUNT			QObject::tr("4.6.3.GLog Count")
#define uistr_MENU_FREE_MLOGCOUNT			QObject::tr("4.6.4.MLog Count")
#define uistr_MENU_FREE_FREEMEMORY			QObject::tr("4.6.5.FreeMemory")
//>>>>UISTR_MENU_DEVICEINFO---------------------------------------------------<<<<		4.7
#define uistr_MENU_DEVINFO_FP				QObject::tr("4.7.1.FP")
#define uistr_MENU_DEVINFO_GLOG				QObject::tr("4.7.2.GLOG")
#define uistr_MENU_DEVINFO_SLOG				QObject::tr("4.7.3.SLOG")
#define uistr_MENU_DEVINFO_MEMORY			QObject::tr("4.7.4.Memory")
#define uistr_MENU_DEVINFO_FIRSTDATE		QObject::tr("4.7.5.Firstdate")
#define uistr_MENU_DEVINFO_SN				QObject::tr("4.7.6.SN")
#define uistr_MENU_DEVINFO_TRADEMARK		QObject::tr("4.7.7.Trademark")
#define uistr_MENU_DEVINFO_PRODUCTNAME		QObject::tr("4.7.8.ProductName")
#define uistr_MENU_DEVINFO_PRODUCTTYPE		QObject::tr("4.7.9.ProductType")
#define uistr_MENU_DEVINFO_ENGINEVERSION	QObject::tr("4.7.10.EngineVersion")
#define uistr_MENU_DEVINFO_FIRMWAREVERSION	QObject::tr("4.7.11.FirmwareVersion")
#define uistr_MENU_DEVINFO_HARDWAREVERSION	QObject::tr("MENU_DEVINFO_HARDWAREVERSION")

//>>uistr_MENU_DATAVIEW-------------------------------------------------------<<		5
#define uistr_MENU_GLOGVIEW				QObject::tr("5.1.GLogView")
#define uistr_MENU_MLOGVIEW				QObject::tr("5.2.MLogView")
#define uistr_MENU_ENROLLVIEW			QObject::tr("5.3.EnrollView")
//////////////////////////////

////////////////Menu Structure
#define uistr_HELP_MAINMENU				QObject::tr("Help-1.MainMENU")
#define uistr_HELP_USERMANAGE			QObject::tr("Help-2.UserManage")
#define uistr_HELP_SYSTEMSETTING		QObject::tr("Help-3.Setting")
#define uistr_HELP_USBMANAGE			QObject::tr("Help-4.U-DiskManage")
#define uistr_HELP_SYSINFOVIEW			QObject::tr("Help-5.SysInfoView")
#define uistr_HELP_DATAVIEW				QObject::tr("Help-6.DataView")
#define uistr_HELP_ALARMREMOVE			QObject::tr("Help-7.AlarmRemove")

//>>uistr_HELP_USERMANAGE-----------------------------------------------------<<		1
#define uistr_HELP_ENROLLNEW			QObject::tr("Help-1.1.Enroll")
#define uistr_HELP_ENROLLBACKUP			QObject::tr("Help-1.2.Backup")
#define uistr_HELP_ENROLLDELETE			QObject::tr("Help-1.3.Delete")

//>>>>uistr_HELP_ENROLLNEW, uistr_HELP_ENROLLBACKUP---------------------------<<<<		1.1, 1.2
#define uistr_HELP_ENROLL_FP			QObject::tr("Help-1.1.1.EnrollFP")
#define uistr_HELP_ENROLL_RFCARD		QObject::tr("Help-1.1.2.EnrollRF")
#define uistr_HELP_ENROLL_VOICE			QObject::tr("Help-1.1.3.Voice")
#define uistr_HELP_ENROLL_PHOTO			QObject::tr("Help-1.1.4.Photo")
//>>>>uistr_HELP_ENROLLDELETE-------------------------------------------------<<<<		1.3
#define uistr_HELP_DELETE_ALL			QObject::tr("Help-1.3.1.DeleteAll")
#define uistr_HELP_DELETE_FP			QObject::tr("Help-1.3.2.DeleteFP")
#define uistr_HELP_DELETE_RFCARD		QObject::tr("Help-1.3.3.DeleteRF")
#define uistr_HELP_REMOVE_PWD			QObject::tr("Help-1.3.4.RemovePWD")
#define uistr_HELP_DELETE_VOICE			QObject::tr("Help-1.3.5.DeleteVocie")
#define uistr_HELP_DELETE_PHOTO			QObject::tr("Help-1.3.6.DeletePhoto")

//>>uistr_HELP_SYSTEMSETTING--------------------------------------------------<<		2
#define uistr_HELP_MAINSETTING			QObject::tr("Help-2.1.MainSetting")
#define uistr_HELP_ADVANCEDSETTING		QObject::tr("Help-2.2.Advanced")
#define uistr_HELP_POWERMANAGE			QObject::tr("Help-2.3.Power")
#define uistr_HELP_COMMSETTING			QObject::tr("Help-2.4.CommSetting")
#define uistr_HELP_LOGSETTING			QObject::tr("Help-2.5.LogSetting")
#define uistr_HELP_ACSETTING			QObject::tr("Help-2.6.AC Setting")
#define uistr_HELP_SELFTEST				QObject::tr("Help-2.7.SelfTest")

//>>>>uistr_HELP_MAINSETTING--------------------------------------------------<<<<		2.1
#define uistr_HELP_MAINSETTING_TIME		QObject::tr("Help-2.1.1.TimeSet")
#define uistr_HELP_MAINSETTING_LANGUAGE	QObject::tr("Help-2.1.2.Language")
#define uistr_HELP_MAINSETTING_SOUND	QObject::tr("Help-2.1.3.Sound")
#define uistr_HELP_MAINSETTING_VOLUME	QObject::tr("Help-2.1.4.Volume")
#define uistr_HELP_MAINSETTING_KEYALARM	QObject::tr("Help-2.1.5.KeyTones")
//>>>>>>uistr_HELP_MAINSETTING_TIME-------------------------------------------<<<<<<	2.1.1
#define uistr_HELP_MAINSETTING_TIME_FORMAT	QObject::tr("Help-2.1.1.1.TimeFormat")
#define uistr_HELP_MAINSETTING_DATE_FORMAT	QObject::tr("Help-2.1.1.2.DateFormat")
#define uistr_HELP_MAINSETTING_TIME_DATE	QObject::tr("Help-2.1.1.3.Date")
#define uistr_HELP_MAINSETTING_TIME_TIME	QObject::tr("Help-2.1.1.4.Time")
//>>>>uistr_HELP_ADVANCEDSETTING----------------------------------------------<<<<		2.2
#define uistr_HELP_ADVANCEDSETTING_VERIFYIF			QObject::tr("Help-2.2.1.VerifyInterface")
#define uistr_HELP_ADVANCEDSETTING_LOGDELETEALL		QObject::tr("Help-2.2.2.AllLog Delete")
#define uistr_HELP_ADVANCEDSETTING_ENROLLDELETEALL	QObject::tr("Help-2.2.3.Enroll Delete")
#define uistr_HELP_ADVANCEDSETTING_DEFAULT			QObject::tr("Help-2.2.4.Default")
#define uistr_HELP_ADVANCEDSETTING_FWUPGRADE		QObject::tr("Help-2.2.5.F/W Upgrade")
#define uistr_HELP_ADVANCEDSETTING_DAYLIGHT			QObject::tr("Help-2.2.6.Daylight")
#define uistr_HELP_ADVANCEDSETTING_FUNCKEY			QObject::tr("Help-2.2.7.FuncKey")
#define uistr_HELP_ADVANCEDSETTING_MANAGER_COUNT	QObject::tr("Help-2.2.8.ManagerCount")
#define uistr_HELP_ADVANCEDSETTING_DEFAULT_VERIFYMODE QObject::tr("Help-2.2.9.Default Verify Mode")
#define uistr_HELP_ADVANCEDSETTING_SMANAGER_PWD		QObject::tr("Help-2.2.10.SManagerPwd")
#define uistr_HELP_ADVANCEDSETTING_BRIGHT_ADJUST	QObject::tr("Help-2.2.11.BrightAdjust")
//>>>>>>uistr_HELP_ADVANCEDSETTING_VERIFYIF-----------------------------------<<<<<<	2.2.1
#define uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA	QObject::tr("Help-2.2.1.1.Camera")
#define uistr_HELP_ADVANCEDSETTING_VERIFYIF_PHOTO	QObject::tr("Help-2.2.1.2.PhotoShow")
#define uistr_HELP_ADVANCEDSETTING_VERIFYIF_FP		QObject::tr("Help-2.2.1.3.FPShow")
//>>>>>>>>uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA--------------------------<<<<<<<<	2.2.1.1
#define uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA_SAVE QObject::tr("Help-2.2.1.1.1.CameraSave")
#define uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA_FP	QObject::tr("Help-2.2.1.1.2.Fingerprint")
#define uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA_CARD	QObject::tr("Help-2.2.1.1.3.RF Card")
#define uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA_PWD	QObject::tr("Help-2.2.1.1.4.Password")
//>>>>>>uistr_HELP_ADVANCEDSETTING_DAYLIGHT-----------------------------------<<<<<<	2.2.6
#define uistr_HELP_ADVANCEDSETTING_DAYLIGHT_OFFSET	QObject::tr("Help-2.2.6.1.Offset")
#define uistr_HELP_ADVANCEDSETTING_DAYLIGHT_CHANGE	QObject::tr("Help-2.2.6.2.Change")
#define uistr_HELP_ADVANCEDSETTING_DAYLIGHT_RESTORE	QObject::tr("Help-2.2.6.3.Restore")
//>>>>>>uistr_HELP_ADVANCEDSETTING_FUNCKEY------------------------------------<<<<<<	2.2.7
#define uistr_HELP_ADVANCEDSETTING_FUNCKEY_F1		QObject::tr("Help-2.2.7.1.F1")
#define uistr_HELP_ADVANCEDSETTING_FUNCKEY_F2		QObject::tr("Help-2.2.7.2.F2")
#define uistr_HELP_ADVANCEDSETTING_FUNCKEY_F3		QObject::tr("Help-2.2.7.3.F3")
#define uistr_HELP_ADVANCEDSETTING_FUNCKEY_F4		QObject::tr("Help-2.2.7.4.F4")
//>>>>uistr_HELP_POWERMANAGE--------------------------------------------------<<<<		2.3
#define uistr_HELP_POWERMANAGE_BELL			QObject::tr("Help-2.3.1.Bell")
#define uistr_HELP_POWERMANAGE_IDLE			QObject::tr("Help-2.3.2.Idle")
#define uistr_HELP_POWERMANAGE_POWEROFF		QObject::tr("Help-2.3.3.Poweroff")
#define uistr_HELP_POWERMANAGE_POWERON		QObject::tr("Help-2.3.4.Poweron")
#define uistr_HELP_POWERMANAGE_SLEEP		QObject::tr("Help-2.3.5.Sleep")
#define uistr_HELP_POWERMANAGE_POWERKEYUSE	QObject::tr("Help-2.3.6.PowerkeyUse")
#define uistr_HELP_POWERMANAGE_TRSWITCH		QObject::tr("Help-2.3.7.TR Switch")
//>>>>>>uistr_HELP_POWERMANAGE_IDLE-------------------------------------------<<<<		2.3.2
#define uistr_HELP_POWERMANAGE_IDLE_POWEROFF	QObject::tr("Help-2.3.2.1.Poweroff")
#define uistr_HELP_POWERMANAGE_IDLE_SLEEP		QObject::tr("Help-2.3.2.2.Sleep")
#define uistr_HELP_POWERMANAGE_IDLE_LCDSWITCH	QObject::tr("Help-2.3.2.3.LCD Switch")
//>>>>uistr_HELP_COMMSETTING--------------------------------------------------<<<<		2.4
#define uistr_HELP_COMMSETTING_DEVICEID		QObject::tr("Help-2.4.1.DeviceID")
#define uistr_HELP_COMMSETTING_BAUDRATE		QObject::tr("Help-2.4.2.Baudrate")
#define uistr_HELP_COMMSETTING_ETHERNETUSE	QObject::tr("Help-2.4.3.EthernetUse")
#define uistr_HELP_COMMSETTING_IPADDRESS	QObject::tr("Help-2.4.4.IP Address")
#define uistr_HELP_COMMSETTING_MASKADDRESS	QObject::tr("Help-2.4.5.MaskAddress")
#define uistr_HELP_COMMSETTING_GWADDRESS	QObject::tr("Help-2.4.6.DefGateway")
#define uistr_HELP_COMMSETTING_RS232USE		QObject::tr("Help-2.4.7.RS232Use")
#define uistr_HELP_COMMSETTING_RS485USE		QObject::tr("Help-2.4.8.RS485Use")
#define uistr_HELP_COMMSETTING_COMMPWD		QObject::tr("Help-2.4.9.CommPassword")
#define uistr_HELP_COMMSETTING_DHCPUSE		QObject::tr("Help-2.4.10.DHCP Use")
#define uistr_HELP_COMMSETTING_PCBACKGROUND	QObject::tr("Help-2.4.11.PCBackground")
//>>>>uistr_HELP_LOGSETTING---------------------------------------------------<<<<		2.5
#define uistr_HELP_LOGSETTING_MLOGWARNING	QObject::tr("Help-2.5.1.MLog Warn")
#define uistr_HELP_LOGSETTING_GLOGWARNING	QObject::tr("Help-2.5.2.GLog Warn")
#define uistr_HELP_LOGSETTING_REVERIFYTIME	QObject::tr("Help-2.5.3.ReverifyTime")
//>>>>uistr_HELP_ACSETTING----------------------------------------------------<<<<		2.6
#define uistr_HELP_ACSETTING_TIMEZONE				QObject::tr("Help-2.6.1.Timezone")
#define uistr_HELP_ACSETTING_GROUP					QObject::tr("Help-2.6.2.Group")
#define uistr_HELP_ACSETTING_USERTIMEZONE			QObject::tr("Help-2.6.3.UserTimezone")
#define uistr_HELP_ACSETTING_LOCKGROUP_MAIN			QObject::tr("Help-2.6.4.LockGroupMain")
#define uistr_HELP_ACSETTING_LOCKGROUP				QObject::tr("Help-2.6.5.LockGroup")
#define uistr_HELP_ACSETTING_LOCKTIME				QObject::tr("Help-2.6.6.LockTime")
#define uistr_HELP_ACSETTING_OPENTIME				QObject::tr("Help-2.6.7.DoorOpenTime")
#define uistr_HELP_ACSETTING_DOORSENSOR				QObject::tr("Help-2.6.8.DoorSensor")
#define uistr_HELP_ACSETTING_DURESS					QObject::tr("Help-2.6.9.DuressFP")
#define uistr_HELP_ACSETTING_ILLEGALVERIFYWARNING	QObject::tr("Help-2.6.10.IllegalVerify")
#define uistr_HELP_ACSETTING_GROUPVERIFYMODE		QObject::tr("Help-2.6.11.GroupVerifyMode")
#define uistr_HELP_ACSETTING_ANTIPASS				QObject::tr("Help-2.6.12.Antipass")
#define uistr_HELP_ACSETTING_ACCONTROLLERUSE		QObject::tr("Help-2.6.13.AcControllerUse")
//>>>>>>UISTR_HELP_ACSETTING_GROUP--------------------------------------------<<<<<<	2.6.2
#define uistr_HELP_ACSETTING_GROUP_1					QObject::tr("Help-2.6.2.1.G1")
#define uistr_HELP_ACSETTING_GROUP_2					QObject::tr("Help-2.6.2.2.G2")
#define uistr_HELP_ACSETTING_GROUP_3					QObject::tr("Help-2.6.2.3.G3")
#define uistr_HELP_ACSETTING_GROUP_4					QObject::tr("Help-2.6.2.4.G4")
#define uistr_HELP_ACSETTING_GROUP_5					QObject::tr("Help-2.6.2.5.G5")
//>>>>>>UISTR_HELP_ACSETTING_USERTIMEZONE-------------------------------------<<<<<<	2.6.3
#define uistr_HELP_ACSETTING_USERTIMEZONE_GROUP			QObject::tr("Help-2.6.3.1.Group")
#define uistr_HELP_ACSETTING_USERTIMEZONE_GTZUSE		QObject::tr("Help-2.6.3.2.GTzUse")
#define uistr_HELP_ACSETTING_USERTIMEZONE_TZ1			QObject::tr("Help-2.6.3.3.TZ1")
#define uistr_HELP_ACSETTING_USERTIMEZONE_TZ2			QObject::tr("Help-2.6.3.4.TZ2")
#define uistr_HELP_ACSETTING_USERTIMEZONE_TZ3			QObject::tr("Help-2.6.3.5.TZ3")
#define uistr_HELP_ACSETTING_USERTIMEZONE_GVMUSE		QObject::tr("Help-2.6.3.6.GVMUSE")
#define uistr_HELP_ACSETTING_USERTIMEZONE_VERIFYMODE	QObject::tr("Help-2.6.3.7.VERIFYMODE")
//>>>>>>UISTR_HELP_ACSETTING_LOCKGROUP----------------------------------------<<<<<<	2.6.4
#define uistr_HELP_ACSETTING_LOCKGROUP_1				QObject::tr("Help-2.6.4.1.G1")
#define uistr_HELP_ACSETTING_LOCKGROUP_2				QObject::tr("Help-2.6.4.2.G2")
#define uistr_HELP_ACSETTING_LOCKGROUP_3				QObject::tr("Help-2.6.4.3.G3")
#define uistr_HELP_ACSETTING_LOCKGROUP_4				QObject::tr("Help-2.6.4.4.G4")
#define uistr_HELP_ACSETTING_LOCKGROUP_5				QObject::tr("Help-2.6.4.5.G5")
#define uistr_HELP_ACSETTING_LOCKGROUP_6				QObject::tr("Help-2.6.4.6.G6")
#define uistr_HELP_ACSETTING_LOCKGROUP_7				QObject::tr("Help-2.6.4.7.G7")
#define uistr_HELP_ACSETTING_LOCKGROUP_8				QObject::tr("Help-2.6.4.8.G8")
#define uistr_HELP_ACSETTING_LOCKGROUP_9				QObject::tr("Help-2.6.4.9.G9")
#define uistr_HELP_ACSETTING_LOCKGROUP_10				QObject::tr("Help-2.6.4.10.G10")
//>>>>>>UISTR_HELP_ACSETTING_DURESS---------------------------------------<<<<<<	2.6.8
#define uistr_HELP_ACSETTING_DURESS_MANAGE			QObject::tr("Help-2.6.8.1.Manage")
#define uistr_HELP_ACSETTING_DURESS_PWD				QObject::tr("Help-2.6.8.2.Password")
#define uistr_HELP_ACSETTING_DURESS_SOSKEY			QObject::tr("Help-2.6.8.3.SOSKey")
#define uistr_HELP_ACSETTING_DURESS_ALARMDELAY		QObject::tr("Help-2.6.8.4.AlarmDelay")
//>>>>>>>>UISTR_HELP_ACSETTING_DURESS_MANAGE------------------------------<<<<<<<<	2.6.8.1
#define uistr_HELP_ACSETTING_DURESS_MANAGE_ENROLL	QObject::tr("Help-2.6.8.1.1.Enroll")
#define uistr_HELP_ACSETTING_DURESS_MANAGE_SET		QObject::tr("Help-2.6.8.1.2.Set")
#define uistr_HELP_ACSETTING_DURESS_MANAGE_REMOVE	QObject::tr("Help-2.6.8.1.3.Remove")
#define uistr_HELP_ACSETTING_DURESS_MANAGE_REMOVEALL QObject::tr("Help-2.6.8.1.4.RemoveAll")
//>>>>>>UISTR_HELP_ACSETTING_GROUPVERIFYMODE----------------------------------<<<<<<	2.6.10
#define uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP1		QObject::tr("Help-2.6.10.1.G1")
#define uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP2		QObject::tr("Help-2.6.10.2.G2")
#define uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP3		QObject::tr("Help-2.6.10.3.G3")
#define uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP4		QObject::tr("Help-2.6.10.4.G4")
#define uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP5		QObject::tr("Help-2.6.10.5.G5")
//>>>>uistr_HELP_SELFTEST-----------------------------------------------------<<<<		2.7
#define uistr_HELP_SELFTEST_ALL			QObject::tr("Help-2.7.1.Test All")
#define uistr_HELP_SELFTEST_MEMORY		QObject::tr("Help-2.7.2.Memory")
#define uistr_HELP_SELFTEST_LCD			QObject::tr("Help-2.7.3.LCD")
#define uistr_HELP_SELFTEST_SOUND		QObject::tr("Help-2.7.4.Sound")
#define uistr_HELP_SELFTEST_SENSOR		QObject::tr("Help-2.7.5.Sensor")
#define uistr_HELP_SELFTEST_KEYBOARD	QObject::tr("Help-2.7.6.Keyboard")
#define uistr_HELP_SELFTEST_RTC			QObject::tr("Help-2.7.7.RTC")
#define uistr_HELP_SELFTEST_MP3			QObject::tr("Help-2.7.8.MP3")

//>>uistr_HELP_USBMANAGE------------------------------------------------------<<		3
#define uistr_HELP_GLOGDOWNLOAD			QObject::tr("Help-3.1.GLogDownload")
#define uistr_HELP_MLOGDOWNLOAD			QObject::tr("Help-3.2.MLogDownload")
#define uistr_HELP_USERINFODOWNLOAD		QObject::tr("Help-3.3.UserInfoDownload")
#define uistr_HELP_USERINFOUPLOAD		QObject::tr("Help-3.4.UserInfoUpload")
#define uistr_HELP_MSGUPLOAD			QObject::tr("Help-3.5.MessageUpload")
#define uistr_HELP_MP3UPLOAD			QObject::tr("Help-3.6.MP3Upload")

//>>uistr_HELP_SYSINFOVIEW----------------------------------------------------<<		4
#define uistr_HELP_USERENROLLCOUNT		QObject::tr("Help-4.1.EnrollCount")
#define uistr_HELP_FPENROLLCOUNT		QObject::tr("Help-4.2.FP Count")
#define uistr_HELP_GLOGCOUNT			QObject::tr("Help-4.3.GLog Count")
#define uistr_HELP_MLOGCOUNT			QObject::tr("Help-4.4.MLog Count")
#define uistr_HELP_USEDMEMORY			QObject::tr("Help-4.5.UsedMemory")
#define uistr_HELP_FREESPACES			QObject::tr("Help-4.6.FreeSpaces")
#define uistr_HELP_DEVICEINFO			QObject::tr("Help-4.7.DeviceInfo")

//>>>>UISTR_HELP_FREESPACES---------------------------------------------------<<<<		4.6
#define uistr_HELP_FREE_USERENROLLCOUNT		QObject::tr("Help-4.6.1.EnrollCount")
#define uistr_HELP_FREE_FPENROLLCOUNT		QObject::tr("Help-4.6.2.FP Count")
#define uistr_HELP_FREE_GLOGCOUNT			QObject::tr("Help-4.6.3.GLog Count")
#define uistr_HELP_FREE_MLOGCOUNT			QObject::tr("Help-4.6.4.MLog Count")
#define uistr_HELP_FREE_FREEMEMORY			QObject::tr("Help-4.6.5.FreeMemory")
//>>>>UISTR_HELP_DEVICEINFO---------------------------------------------------<<<<		4.7
#define uistr_HELP_DEVINFO_FP				QObject::tr("Help-4.7.1.FP")
#define uistr_HELP_DEVINFO_GLOG				QObject::tr("Help-4.7.2.GLOG")
#define uistr_HELP_DEVINFO_SLOG				QObject::tr("Help-4.7.3.SLOG")
#define uistr_HELP_DEVINFO_MEMORY			QObject::tr("Help-4.7.4.Memory")
#define uistr_HELP_DEVINFO_FIRSTDATE		QObject::tr("Help-4.7.5.Firstdate")
#define uistr_HELP_DEVINFO_SN				QObject::tr("Help-4.7.6.SN")
#define uistr_HELP_DEVINFO_TRADEMARK		QObject::tr("Help-4.7.7.Trademark")
#define uistr_HELP_DEVINFO_PRODUCTNAME		QObject::tr("Help-4.7.8.ProductName")
#define uistr_HELP_DEVINFO_PRODUCTTYPE		QObject::tr("Help-4.7.9.ProductType")
#define uistr_HELP_DEVINFO_ENGINEVERSION	QObject::tr("Help-4.7.10.EngineVersion")
#define uistr_HELP_DEVINFO_FIRMWAREVERSION	QObject::tr("Help-4.7.11.FirmwareVersion")

//>>uistr_HELP_DATAVIEW-------------------------------------------------------<<		5
#define uistr_HELP_GLOGVIEW				QObject::tr("Help-5.1.GLogView")
#define uistr_HELP_MLOGVIEW				QObject::tr("Help-5.2.MLogView")
#define uistr_HELP_ENROLLVIEW			QObject::tr("Help-5.3.EnrollView")
//////////////////////////////

///////////////Enroll
#define uistr_ENROLL_OVERFLOW			QObject::tr("EnrollOverflow")
#define uistr_ENROLL_MANAGER_OVERFLOW	QObject::tr("EnrollManagerOverflow")
#define uistr_ENROLL_NOUSER				QObject::tr("EnrollNoUser")
#define uistr_ENROLL_INVALID_ID			QObject::tr("EnrollInvalidID")
#define uistr_ENROLL_USED_ID			QObject::tr("EnrollUsedID")
#define uistr_ENROLL_INCORRECT_PWD		QObject::tr("EnrollIncorrectPwd")
#define uistr_ENROLL_SAVEOK				QObject::tr("EnrollSaveSuccess")
#define uistr_ENROLL_SAVEFAIL			QObject::tr("EnrollSaveFail")
#define uistr_ENROLL_CURRENT_USER		QObject::tr("EnrollCurrentUser")
#define uistr_ENROLL_NAME				QObject::tr("EnrollName")
#define uistr_ENROLLFP_FPFULL			QObject::tr("EnrollFpFPFULL")
#define uistr_ENROLLFP_FPNO				QObject::tr("EnrollFpFPNO")
#define uistr_ENROLLFP_PRESSFP1			QObject::tr("EnrollFpPress1")
#define uistr_ENROLLFP_PRESSFP2			QObject::tr("EnrollFpPress2")
#define uistr_ENROLLFP_PRESSFP3			QObject::tr("EnrollFpPress3")
#define uistr_ENROLLFP_TAKEOFF			QObject::tr("EnrollFpTakeoff")
#define uistr_ENROLLFP_PRESAGAIN		QObject::tr("EnrollFpPressAgain")
#define uistr_ENROLLFP_ENROLLSUCCESS	QObject::tr("EnrollFpEnrollSuccess")
#define uistr_ENROLLFP_FPDOUBLED		QObject::tr("EnrollFpFPDOUBLED")
#define uistr_ENROLLFP_ESCAPE			QObject::tr("EnrollFpEscape")
#define uistr_ENROLLFP_NOT_ENROLLED		QObject::tr("EnrollFpNotEnrolled")
#define uistr_ENROLLPWD_PWDEXIST		QObject::tr("ENROLLPWD_PWDEXIST")
#define uistr_ENROLLPWD_FAIL			QObject::tr("ENROLLPWD_FAIL")
#define uistr_ENROLLCARD_RFEXIST		QObject::tr("EnrollCardRFExist")
#define uistr_ENROLLCARD_INPUTRF		QObject::tr("EnrollCardInputRF")
#define uistr_ENROLLCARD_ENROLLSUCCESS	QObject::tr("EnrollCardEnrollSuccess")
#define uistr_ENROLLCARD_RFDOUBLED_REINPUT QObject::tr("EnrollCardDoubledReinput")
#define uistr_ENROLLVOICE_VOICEEXIST	QObject::tr("EnrollVoiceExist")
#define uistr_ENROLLVOICE_SPEAKNAME		QObject::tr("EnrollVoiceSpeakName")
#define uistr_ENROLLVOICE_ENROLLSUCCESS	QObject::tr("EnrollVoiceEnrollSuccess")
#define uistr_ENROLLVOICE_RETRY			QObject::tr("EnrollVoiceRetry")
#define uistr_ENROLLVOICE_START			QObject::tr("EnrollVoiceStart")
#define uistr_ENROLLVOICE_STOP			QObject::tr("EnrollVoiceStop")
#define usitr_ENROLLVOICE_PLAYBACK		QObject::tr("EnrollVoicePlayback")
#define uistr_ENROLLPHOTO_PHOTOEXIST	QObject::tr("EnrollPhotoExist")
#define uistr_ENROLLPHOTO_PREPARE		QObject::tr("EnrollPhotoPrepare")
#define uistr_ENROLLPHOTO_SUCCESS		QObject::tr("EnrollPhotoSuccess")
#define uistr_ENROLLPHOTO_RETRY			QObject::tr("EnrollPhotoRetry")
#define uistr_ENROLLDELETE_DELETECONFIRM	QObject::tr("EnrollDeleteConfirm")
#define uistr_ENROLLDELETE_DELETESUCCESS	QObject::tr("EnrollDeleteSuccess")
#define uistr_ENROLLDELETE_NOFP				QObject::tr("EnrollDeleteNoFP")
#define uistr_ENROLLDELETE_NOCARD			QObject::tr("EnrollDeleteNoCard")
#define uistr_ENROLLDELETE_NOPWD			QObject::tr("EnrollDeleteNoPwd")
#define uistr_ENROLLDELETE_NOVOICE			QObject::tr("EnrollDeleteNoVoice")
#define uistr_ENROLLDELETE_NOPHOTO			QObject::tr("EnrollDeleteNoPhoto")
#define uistr_ENROLLDELETE_NODATA			QObject::tr("EnrollDeleteNoData")
#define uistr_DURESS_PRESS_ENROLLEDFP		QObject::tr("DuressPressEnrolledFP")
#define uistr_DURESS_ALREADYSET				QObject::tr("DuressAlreadySet")
#define uistr_DURESS_NOT					QObject::tr("DuressNot")
#define uistr_DURESS_SET_CONFIRM			QObject::tr("DuressSetConfirm")
#define uistr_DURESS_REMOVE_CONFIRM			QObject::tr("DuressRemoveConfirm")
#define uistr_DURESS_NOEXIST				QObject::tr("DuressNoExist")
//////////////////////////////

/////////////Verify
#define uistr_VERIFY_DATE				QObject::tr("VerifyDate")
#define uistr_VERIFY_TIME				QObject::tr("VerifyTime")
#define uistr_VERIFY_TRSTATE			QObject::tr("VerifyTRState")
#define uistr_VERIFY_ID					QObject::tr("VerifyID")
#define uistr_VERIFY_NAME				QObject::tr("VerifyName")
#define uistr_VERIFY_PRIV				QObject::tr("VerifyPriv")
#define uistr_VERIFY_PART				QObject::tr("VerifyPart")
#define uistr_VERIFY_TAKEOFF			QObject::tr("VerifyTakeoff")
#define uistr_VERIFY_DISABLED			QObject::tr("VerifyDisabled")
#define uistr_VERIFY_ILLEGAL			QObject::tr("VerifyIllegal")
#define uistr_VERIFY_SUCCESS			QObject::tr("VerifySuccess")
#define uistr_VERIFY_REVERIFY			QObject::tr("VerifyReverify")
#define uistr_VERIFY_FAIL				QObject::tr("VerifyFailure")
#define uistr_VERIFY_REINPUT			QObject::tr("VerifyReinput")
#define uistr_VERIFY_INPUT_ID			QObject::tr("VerifyInputID")
#define uistr_VERIFY_PRESS_FINGER		QObject::tr("VerifyPressFP")
#define uistr_VERIFY_INPUT_CARD			QObject::tr("VerifyInputCD")
#define uistr_VERIFY_INPUT_PWD			QObject::tr("VerifyInputPW")
#define uistr_VERIFY_INVALID_TZ			QObject::tr("VerifyInvalidTZ")
#define uistr_VERIFY_INVALID_GROUP		QObject::tr("VerifyInvalidGroup")
#define uistr_VERIFY_ANTIPASS_NOT		QObject::tr("VerifyAntipassNot")
#define usitr_VERIFY_MASTER_CONNECT_ERROR QObject::tr("VerifyMasterConnectError")
//////////////////////////////

/////////////Search
#define uistr_SEARCH_INVALIDPARAM		QObject::tr("SearchInvalidParam")
#define uistr_SEARCH_NODATA				QObject::tr("SearchNoData")
#define uistr_SEARCH_MUST_VERIFY		QObject::tr("SearchVerify")
//////////////////////////////

#define uistr_LANG_ENG					QObject::tr("LangEnglish")
#define uistr_LANG_SCHN					QObject::tr("LangS-Chinese")
#define uistr_LANG_TCHN					QObject::tr("LangT-Chinese")
#define uistr_LANG_KOR					QObject::tr("LangKorean")
#define uistr_LANG_JPN					QObject::tr("LangJapanese")

#define uistr_BK_1					    QObject::tr("Backgroup1")
#define uistr_BK_2					    QObject::tr("Backgroup2")
#define uistr_BK_3					    QObject::tr("Backgroup3")
#define uistr_BK_4					    QObject::tr("Backgroup4")
#define uistr_BK_5					    QObject::tr("Backgroup5")
#define uistr_BK_6					    QObject::tr("Backgroup6")

#define uistr_FUNC_DUTYNO				QObject::tr("sbfont1_FuncDutyNo")     
#define uistr_FUNC_DUTYON				QObject::tr("sbfont1_FuncDutyOn")
#define uistr_FUNC_DUTYOFF				QObject::tr("sbfont1_FuncDutyOff")
#define uistr_FUNC_OVERTIMEON			QObject::tr("sbfont1_FuncOvertimeOn")
#define uistr_FUNC_OVERTIMEOFF			QObject::tr("sbfont1_FuncOvertimeOff")
#define uistr_FUNC_GOOUTON				QObject::tr("sbfont1_FuncGooutOn")
#define uistr_FUNC_GOOUTOFF				QObject::tr("sbfont1_FuncGooutOff")
#define uistr_FUNC_IN					QObject::tr("sbfont1_FuncIn")
#define uistr_FUNC_OUT					QObject::tr("sbfont1_FuncOut")
#define uistr_FUNC_LOGVIEW				QObject::tr("FuncLogView")
#define uistr_FUNC_BELL					QObject::tr("FuncBell")
#define uistr_FUNC_ALARM				QObject::tr("FuncAlarm")
#define uistr_FUNC_SYSINFO				QObject::tr("FuncSysInfo")

#define uistr_TIMEFMT_12				QObject::tr("TimeFormat-12")
#define uistr_TIMEFMT_24				QObject::tr("TimeFormat-24")

#define uistr_DATEFMT_1					QObject::tr("YY-MM-DD")
#define uistr_DATEFMT_2					QObject::tr("YY/MM/DD")
#define uistr_DATEFMT_3					QObject::tr("YY.MM.DD")
#define uistr_DATEFMT_4					QObject::tr("MM-DD-YY")
#define uistr_DATEFMT_5					QObject::tr("MM/DD/YY")
#define uistr_DATEFMT_6					QObject::tr("MM.DD.YY")
#define uistr_DATEFMT_7					QObject::tr("DD-MM-YY")
#define uistr_DATEFMT_8					QObject::tr("DD/MM/YY")
#define uistr_DATEFMT_9					QObject::tr("DD.MM.YY")
#define uistr_DATEFMT_10				QObject::tr("YYYYMMDD")

#define uistr_BPS_9600					QObject::tr("9600bps")
#define uistr_BPS_19200					QObject::tr("19200bps")
#define uistr_BPS_38400					QObject::tr("38400bps")
#define uistr_BPS_57600					QObject::tr("57600bps")
#define uistr_BPS_115200				QObject::tr("115200bps")

#define uistr_THEME_1					QObject::tr("TMEME_1")
#define uistr_THEME_2					QObject::tr("TMEME_2")

#define uistr_VERIFYMODE_NONE			QObject::tr("VM_NONE")
#define uistr_VERIFYMODE_ANY			QObject::tr("VM_ANY")
#define uistr_VERIFYMODE_FP				QObject::tr("VM_FP")
#define uistr_VERIFYMODE_RFFP			QObject::tr("VM_RF+FP")
#define uistr_VERIFYMODE_RF				QObject::tr("VM_RF")
#define uistr_VERIFYMODE_IDFP			QObject::tr("VM_ID+FP")
#define uistr_VERIFYMODE_IDPW			QObject::tr("VM_ID+PW")

#define uistr_DOORSENSOR_NO				QObject::tr("NoDoorSensor")
#define uistr_DOORSENSOR_OPEN			QObject::tr("AlwaysOpen")
#define uistr_DOORSENSOR_CLOSE			QObject::tr("AlwaysClose")

#define uistr_ANTIPASS_NO				QObject::tr("AntipassNo")
#define uistr_ANTIPASS_MASTER			QObject::tr("AntipassMaster")
#define uistr_ANTIPASS_SLAVE			QObject::tr("AntipassSlave")

#define uistr_YESNO_NO					QObject::tr("NO")
#define uistr_YESNO_YES					QObject::tr("YES")

#define uistr_ACTION_CONFIRM			QObject::tr("ActionConfirm")
#define uistr_ACTION_SUCCESS			QObject::tr("ActionSuccess")
#define uistr_ACTION_FAIL				QObject::tr("ActionFail")

#define uistr_BELL_NO					QObject::tr("BellNo")
#define uistr_BELL_STIME				QObject::tr("BellSTime")
#define uistr_BELL_LENGTH				QObject::tr("BellLength")
#define uistr_BELL_TYPE					QObject::tr("BellType")

#define uistr_TR_NO						QObject::tr("TRNo")
#define uistr_TR_STIME					QObject::tr("TRSTime")
#define uistr_TR_ETIME					QObject::tr("TRETime")
#define uistr_TR_STATUS					QObject::tr("TRStatus")

#define uistr_ULHDR_ID					QObject::tr("ID")
#define uistr_ULHDR_NAME				QObject::tr("Name")
#define uistr_ULHDR_TZ					QObject::tr("TZ")
#define uistr_ULHDR_FP					QObject::tr("FP")
#define uistr_ULHDR_PWD					QObject::tr("PWD")
#define uistr_ULHDR_CARD				QObject::tr("CD")
#define uistr_UM_SEARCH					QObject::tr("Search")
#define uistr_UM_LOGVIEW				QObject::tr("Log View")
#define uistr_UM_EDIT					QObject::tr("Edit")
#define uistr_UM_DELETE					QObject::tr("Delete")
#define uistr_LOGHDR_TIMESTAMP			QObject::tr("LogTime")
#define uistr_LOGHDR_ID					QObject::tr("ID")
#define uistr_LOGHDR_NAME				QObject::tr("Name")
#define uistr_LOGHDR_CONTENT			QObject::tr("Content")

#define uistr_DB_LOAD					QObject::tr("DB Load")
#define uistr_FINGERPRINT_LOAD			QObject::tr("Fingerprint Load")
#define uistr_FILEREAD					QObject::tr("File Reading...")
#define uistr_FILEWRITE					QObject::tr("File Writing...")
#define uistr_FLASHREAD					QObject::tr("Flash Reading...")
#define uistr_FLASHWRITE				QObject::tr("Flash Writing...")
#define uistr_COMMUNICATING				QObject::tr("Communicating...")
#define uistr_WAIT_FOR_COMMUNICATING	QObject::tr("Wait for moment...")
#define uistr_WARNING					QObject::tr("Warning")
#define uistr_USER_SEARCH_WARNING		QObject::tr("Please input ID or UserName !")
#define uistr_USER_LOG_WARNING			QObject::tr("There is no log data !")
#define uistr_DELETE_CONFIRM			QObject::tr("Are you sure delete?")
#define uistr_UDISK_NOTFOUND			QObject::tr("Can't find USB Disk")
#define uistr_SDCARD_NOTFOUND			QObject::tr("Can't find SDCARD")
#define uistr_NO_FILES					QObject::tr("There is no files")
#define uistr_CAMERA_NOTFOUND			QObject::tr("Camera not found")
#define uistr_USB_ISFULL				QObject::tr("USB disk is full")
#define uistr_SDCARD_ISFULL				QObject::tr("SD card is full")

#define uistr_TZHDR_NO					QObject::tr("TzhdrNo")
#define uistr_TZHDR_NAME				QObject::tr("Name")
#define uistr_TZHDR_FROMTIME			QObject::tr("From")
#define uistr_TZHDR_TOTIME				QObject::tr("To")
#define uistr_TZHDR_CONTENT				QObject::tr("TzhdrTimezone")
#define uistr_TZHDR_TIME				QObject::tr("Time")
#define uistr_TZHDR_TYPE				QObject::tr("Type")
#define uistr_TZHDR_STATUS				QObject::tr("Status")

#define uistr_WEEKDAY_SUN				QObject::tr("SUN")
#define uistr_WEEKDAY_MON				QObject::tr("MON")
#define uistr_WEEKDAY_TUE				QObject::tr("TUE")
#define uistr_WEEKDAY_WED				QObject::tr("WED")
#define uistr_WEEKDAY_THU				QObject::tr("THU")
#define uistr_WEEKDAY_FRI				QObject::tr("FRI")
#define uistr_WEEKDAY_SAT				QObject::tr("SAT")

#define uistr_MONTH_JAN					QObject::tr("January")
#define uistr_MONTH_FEB					QObject::tr("February")
#define uistr_MONTH_MAR					QObject::tr("March")
#define uistr_MONTH_APR					QObject::tr("April")
#define uistr_MONTH_MAY					QObject::tr("May")
#define uistr_MONTH_JUN					QObject::tr("June")
#define uistr_MONTH_JUL					QObject::tr("July")
#define uistr_MONTH_AUG					QObject::tr("August")
#define uistr_MONTH_SEP					QObject::tr("September")
#define uistr_MONTH_OCT					QObject::tr("October")
#define uistr_MONTH_NOV					QObject::tr("November")
#define uistr_MONTH_DEC					QObject::tr("December")

#define uistr_SLOG_TURNON				QObject::tr("SLogTurnOn")
#define uistr_SLOG_TURNOFF				QObject::tr("SLogTurnOff")
#define uistr_SLOG_ILLEGALVERIFY_ALARM	QObject::tr("SLogIlgAlarm")
#define uistr_SLOG_TAMPER_ALARM			QObject::tr("SLogTamper")
#define uistr_SLOG_ENTERMENU			QObject::tr("SLogEnterMenu")
#define uistr_SLOG_SETTINGCHANGED		QObject::tr("SLogSettingChanged")
#define uistr_SLOG_BACKUPENROLL_FP		QObject::tr("SLogBackupFP")
#define uistr_SLOG_SETPASSWORD			QObject::tr("SLogSetPWD")
#define uistr_SLOG_ENROLL_CARD			QObject::tr("SLogEnrollCard")
#define uistr_SLOG_DELETE_USER			QObject::tr("SLogDeleteUser")
#define uistr_SLOG_DELETE_FP			QObject::tr("SLogDeleteFP")
#define uistr_SLOG_DELETE_PASSWORD		QObject::tr("SLogDeletePWD")
#define uistr_SLOG_DELETE_CARD			QObject::tr("SLogDeleteCard")
#define uistr_SLOG_DELETE_ALL			QObject::tr("SLogDeleteAll")
#define uistr_SLOG_CREATE_MFCARD		QObject::tr("SLogCreateMFCard")
#define uistr_SLOG_ENROLL_MFCARD		QObject::tr("SLogEnrollMFCard")
#define uistr_SLOG_REGISTER_MFCARD		QObject::tr("SLogRegisterMFCard")
#define uistr_SLOG_DELETE_MF_REGIST		QObject::tr("SLogDelMFRegist")
#define uistr_SLOG_CLEAR_MF				QObject::tr("SLogClearMF")
#define uistr_SLOG_ENROLLDATA2CARD		QObject::tr("SLogEnroll2Card")
#define uistr_SLOG_CARD2MACHINE			QObject::tr("SLogCard2Machine")
#define uistr_SLOG_SETTIME				QObject::tr("SLogSetTime")
#define uistr_SLOG_RESTORE				QObject::tr("SLogRestore")
#define uistr_SLOG_DELETE_ALL_GLOG		QObject::tr("SLogDelAllLog")
#define uistr_SLOG_REMOVE_MANAGERPRIV	QObject::tr("SLogRemovePriv")
#define uistr_SLOG_TIMEGROUP_SET		QObject::tr("SLogTGSet")
#define uistr_SLOG_USERTZ_SET			QObject::tr("SLogUserTZSet")
#define uistr_SLOG_TIMEZONE_SET			QObject::tr("SLogTZSet")
#define uistr_SLOG_LOCKGROUP_SET		QObject::tr("SLogLockGroupSet")
#define uistr_SLOG_DOOROPEN				QObject::tr("SLogDoorOpen")
#define uistr_SLOG_ENROLL_USER			QObject::tr("SLogEnrollUser")
#define uistr_SLOG_OPENTIMEOUT_ALARM	QObject::tr("SLogDoorOpenTimeoutAlarm")
#define uistr_SLOG_ILGOPEN_ALARM		QObject::tr("SLogIlgOpenAlarm")
#define uistr_SLOG_DURESS_ALARM			QObject::tr("SLogDuressALarm")

#define uistr_SOUND_DIGIT0				QObject::tr("SoundD0")
#define uistr_SOUND_DIGIT1				QObject::tr("SoundD1")
#define uistr_SOUND_DIGIT2				QObject::tr("SoundD2")
#define uistr_SOUND_DIGIT3				QObject::tr("SoundD3")
#define uistr_SOUND_DIGIT4				QObject::tr("SoundD4")
#define uistr_SOUND_DIGIT5				QObject::tr("SoundD5")
#define uistr_SOUND_DIGIT6				QObject::tr("SoundD6")
#define uistr_SOUND_DIGIT7				QObject::tr("SoundD7")
#define uistr_SOUND_DIGIT8				QObject::tr("SoundD8")
#define uistr_SOUND_DIGIT9				QObject::tr("SoundD9")
#define uistr_SOUND_TURNON				QObject::tr("SoundTurnon")
#define uistr_SOUND_TURNOFF				QObject::tr("SoundTurnoff")
#define uistr_SOUND_PRESSFINGER_1		QObject::tr("SoundPressFP1")
#define uistr_SOUND_PRESSFINGER_2		QObject::tr("SoundPressFP2")
#define uistr_SOUND_PRESSFINGER_3		QObject::tr("SoundPressFP3")
#define uistr_SOUND_TAKEOFF_FP			QObject::tr("SoundTakeoffFP")
#define uistr_SOUND_PRESSFP_RETRY		QObject::tr("SoundRepressFP")
#define uistr_SOUND_FPENROLL_SUCCESS	QObject::tr("SoundFPEnrollSuccess")
#define uistr_SOUND_FPENROLL_FAIL		QObject::tr("SoundFPEnrollFail")
#define uistr_SOUND_FPDOUBLED			QObject::tr("SoundFPDoubled")
#define uistr_SOUND_INPUT_PWD			QObject::tr("SoundInputPWD")
#define uistr_SOUND_PWD_ERROR			QObject::tr("SoundPwdError")
#define uistr_SOUND_INPUT_CARD			QObject::tr("SoundInputCard")
#define uistr_SOUND_CARDDOUBLED_RETRY	QObject::tr("SoundCardDoubledRetry")
#define uistr_SOUND_CARDENROLL_SUCCESS	QObject::tr("SoundCardEnrollSuccess")
#define uistr_SOUND_TALK_YOURNAME		QObject::tr("SoundTalkYourName")
#define uistr_SOUND_VOICERECORD_SUCCESS	QObject::tr("SoundRecordSuccess")
#define uistr_SOUND_VOICERECORD_RETRY	QObject::tr("SoundRe-record")
#define uistr_SOUND_PREPARE_FOR_PHOTO	QObject::tr("SoundPrepareForPhoto")
#define uistr_SOUND_PHOTO_SUCCESS		QObject::tr("SoundPhotoSuccess")
#define uistr_SOUND_CAMERA_TONE			QObject::tr("SoundCameraTone")
#define uistr_SOUND_KEYTONES			QObject::tr("SoundKeyTones")
#define uistr_SOUND_MENUSELECT			QObject::tr("SoundMenuSelect")
#define uistr_SOUND_ENTERMENU			QObject::tr("SoundEnterMenu")
#define uistr_SOUND_VERIFY_SUCCESS		QObject::tr("SoundVerifySuccess")
#define uistr_SOUND_VERIFY_FAIL			QObject::tr("SoundVerfiyFail")
#define uistr_SOUND_ERROR				QObject::tr("SoundError")
#define uistr_SOUND_QUESTION			QObject::tr("SoundQuestion")
#define uistr_SOUND_OK					QObject::tr("SoundOk")
#define uistr_SOUND_BELL1				QObject::tr("SoundBell1")
#define uistr_SOUND_BELL2				QObject::tr("SoundBell2")
#define uistr_SOUND_BELL3				QObject::tr("SoundBell3")
#define uistr_SOUND_BELL4				QObject::tr("SoundBell4")
#define uistr_SOUND_BELL5				QObject::tr("SoundBell5")

#define uistr_MP3UPLOAD_DESC			QObject::tr("MP3UpDesc")
#define uistr_MP3UPLOAD_CONFIRM			QObject::tr("MP3UpConfirm")

#define uistr_MANAGER_CONFIRM			QObject::tr("Manager Confirm")
#define uistr_WORKING					QObject::tr("Working...")
#define uistr_DEVICE_ERROR				QObject::tr("Device Error !")
#define uistr_CHECK_SENSOR				QObject::tr("Check Sensor !")
#define uistr_SLOG_OVERFLOW				QObject::tr("SLog Overflow !")
#define uistr_GLOG_OVERFLOW				QObject::tr("GLog Overflow !")

#define uistr_PRIV_USER					QObject::tr("User")
#define uistr_PRIV_MANAGER				QObject::tr("Manager")
#define uistr_PRIV_SMANAGER				QObject::tr("SManager")

#define uistr_UNIT_YEAR					QObject::tr("UnitYear")
#define uistr_UNIT_MONTH				QObject::tr("UnitMonth")
#define uistr_UNIT_DAY					QObject::tr("UnitDay")
#define uistr_UNIT_HOUR					QObject::tr("UnitHour")
#define uistr_UNIT_MINUTE				QObject::tr("UnitMinute")
#define uistr_UNIT_SECOND				QObject::tr("UnitSecond")
#define uistr_UNIT_TIMES				QObject::tr("UnitTimes")
#define uistr_UNIT_LOG					QObject::tr("UnitLog")
#define uistr_UNIT_FP					QObject::tr("UnitFP")
#define uistr_UNIT_PERCENT				QObject::tr("UnitPercent")
#define uistr_UNIT_PEOPLE				QObject::tr("UnitPeople")

#define uistr_T9_CHN					QObject::tr("T9_CHN")
#define uistr_T9_ENG					QObject::tr("T9_ENG")
#define uistr_T9_SYM					QObject::tr("T9_SYM")
#define uistr_T9_NUM					QObject::tr("T9_NUM")

#define uistr_STATUS_MENU				QObject::tr("StatusMenu")
#define uistr_STATUS_MENU1				QObject::tr("StatusMenu1")
#define uistr_STATUS_LCDTEST			QObject::tr("StatusLCDTest")
#define uistr_STATUS_BELL				QObject::tr("StatusBell")
#define uistr_STATUS_SAVE_QUESTION		QObject::tr("Do you save?")
#define uistr_STATUS_POWEROFF			QObject::tr("StatusPoweroff")
#define uistr_STATUS_RESTART			QObject::tr("StatusRestart")
#define uistr_STATUS_NOLOG				QObject::tr("StatusNoLog")
#define uistr_STATUS_CONTROLLER_CONNECT_ERROR QObject::tr("Can not connect to controller")
#define usitr_STATUS_HELP				QObject::tr("StatusHelp")
#define uistr_STATUS_BRIGHT_ADJUST_SUCCESS	QObject::tr("StatusBrightAdjustSuccess")
#define uistr_STATUS_BRIGHT_ADJUST_FAIL		QObject::tr("StatusBrightAdjustFail")
#define uistr_STATUS_DHCP_CONFIGURING		QObject::tr("DHCP Configuring...")
#define uistr_STATUS_DHCP_CONFIGURE_SUCCESS	QObject::tr("DHCP configure success")
#define uistr_STATUS_DHCP_CONFIGURE_FAIL	QObject::tr("DHCP configure fail")
#define uistr_STATUS_VOICE_DOWNLOAD		QObject::tr("User voice download...")
#define uistr_STATUS_VOICE_UPLOAD		QObject::tr("User voice upload...")
#define uistr_STATUS_PHOTO_DOWNLOAD		QObject::tr("User photo download...")
#define uistr_STATUS_PHOTO_UPLOAD		QObject::tr("User photo upload...")
#define uistr_STATUS_AM					QObject::tr("StatusAM")
#define uistr_STATUS_PM					QObject::tr("StatusPM")
#define uistr_STATUS_INVALID_WAVFORMAT	QObject::tr("StatusInvalidWavFormat")
#define uistr_STATUS_OK_SELECT			QObject::tr("STATUS_OK_SELECT")
#define uistr_STATUS_OK_SEARCH			QObject::tr("STATUS_OK_SEARCH")
#define uistr_STATUS_ESC_BACK			QObject::tr("STATUS_ESC_BACK")
#define uistr_STATUS_MENU_CLEAR			QObject::tr("STATUS_MENU_CLEAR")
#define uistr_STATUS_OK_T9				QObject::tr("STATUS_OK_T9")

#define uistr_SYMBOL_BRACKET_ON			QObject::tr("SymbolBracketOn")
#define uistr_SYMBOL_BRACKET_OFF		QObject::tr("SymbolBracketOff")
#define uistr_SYMBOL_MINUS				QObject::tr("SymbolMinus")
#define uistr_SYMBOL_LEFT				QObject::tr("SymbolLeft")
#define uistr_SYMBOL_RIGHT				QObject::tr("SymbolRight")
#define uistr_SYMBOL_UP					QObject::tr("SymbolUp")
#define uistr_SYMBOL_DOWN				QObject::tr("SymbolDown")
#define uistr_SYMBOL_WAVE				QObject::tr("SymbolWave")
#define uistr_SYMBOL_STAR				QObject::tr("SymbolStar")
#define uistr_SYMBOLS_SBFONT0			QObject::tr("sbfont0_0123456789: ")
#define uistr_SYMBOLS_SBFONT1			QObject::tr("sbfont1_0123456789-:")
#define uistr_SYMBOLS_SBFONT2			QObject::tr("sbfont2_0123456789:")

#define uistr_HELP_ENROLLSTEP1			QObject::tr("HelpEnrollStep1")
#define uistr_HELP_ENROLLSTEP2			QObject::tr("HelpEnrollStep2")
#define uistr_HELP_ENROLLFP				QObject::tr("HelpEnrollFP")
#define uistr_HELP_ENROLLDURESS			QObject::tr("HelpEnrollDuress")
#define uistr_HELP_ENROLLCARD			QObject::tr("HelpEnrollCard")
#define uistr_HELP_ENROLLVOICE			QObject::tr("HelpEnrollVoice")
#define uistr_HELP_ENROLLPHOTO			QObject::tr("HelpEnrollPhoto")
#define uistr_HELP_ENROLLDELETE1		QObject::tr("HelpEnrollDelete")
#define uistr_HELP_DURESSFPSET			QObject::tr("HelpDuressFPSet")
#define uistr_HELP_DURESSFPREMOVE		QObject::tr("HelpDuressFPRemove")
#define uistr_HELP_INPUTID				QObject::tr("HelpInputID")
#define uistr_HELP_INPUTPWD				QObject::tr("HelpInputPWD")
#define uistr_HELP_SEARCHUSER			QObject::tr("HelpSearchUser")
#define uistr_HELP_MENU					QObject::tr("HelpMenu")
#define uistr_HELP_BELLSETUP			QObject::tr("HelpBellSetup")
#define uistr_HELP_BELLSETONE			QObject::tr("HelpBellSetOne")
#define uistr_HELP_TRSETUP				QObject::tr("HelpTrSetup")
#define uistr_HELP_TRSETONE				QObject::tr("HelpTrSetOne")
#define uistr_HELP_TIMEZONESETUP		QObject::tr("HelpTimezoneSetup")
#define uistr_HELP_MP3UPLOAD1			QObject::tr("HelpMp3Upload")
#define uistr_HELP_SYSTEMUPGRADE		QObject::tr("HelpSystemUpgrade")
#define uistr_HELP_SELFTESTKEYBOARD		QObject::tr("HelpSelftestKeyboard")
#define uistr_HELP_SELFTESTMEMORY		QObject::tr("HelpSelftestMemory")
#define uistr_HELP_SELFTESTRTC			QObject::tr("HelpSelftestRtc")
#define uistr_HELP_SELFTESTSENSOR		QObject::tr("HelpSelftestSensor")
#define uistr_HELP_SELFTESTSOUND		QObject::tr("HelpSelftestSound")
#define uistr_HELP_SELFTESTALL			QObject::tr("HelpSelftestAll")
#define uistr_HELP_USERLIST				QObject::tr("HelpUserList")
#define uistr_HELP_SEARCHLOG			QObject::tr("HelpSearchLog")
#define uistr_HELP_SLOGLIST				QObject::tr("HelpSLogList")
#define uistr_HELP_GLOGLIST				QObject::tr("HelpGLogList")

#define uistr_MSG_ID                    QObject::tr("MSG_ID")
#define uistr_MSG_STARTTIME				QObject::tr("MSG_STARTTIME")
#define uistr_MSG_INTERVAL				QObject::tr("MSG_INTERVAL")
#define uistr_MSG_TYPE					QObject::tr("MSG_TYPE")
#define uistr_MSG_TEXT					QObject::tr("MSG_TEXT")
#define uistr_STATUS_MSG_INPUT_ERROR	QObject::tr("STATUS_MSG_INPUT_ERROR")
#define uistr_STATUS_MSG_DEL_ALARM		QObject::tr("STATUS_MSG_DEL_ALARM")
#define uistr_MSG_EDIT					QObject::tr("MSG_EDIT")
#define uistr_MSG_NEW					QObject::tr("MSG_NEW")
#define uistr_MSG_TEXTMARK				QObject::tr("MSG_TEXTMARK")
#define uistr_MSG_TYPE_USER				QObject::tr("MSG_TYPE_USER")
#define uistr_MSG_TYPE_GENERAL			QObject::tr("MSG_TYPE_GENERAL")
#define uistr_USER_MANAGE				QObject::tr("USER_MANAGE")
#define uistr_MSG_MANAGE				QObject::tr("MSG_MANAGE")
#define uistr_USER_STATUS				QObject::tr("USER_STATUS")
#define uistr_MSG_STATUS				QObject::tr("MSG_STATUS")
#define uistr_MSG_UNIT					QObject::tr("MSG_UNIT")
#define uistr_STATUS_LOG				QObject::tr("STATUS_LOG")  
#define uistr_STATUS_USER				QObject::tr("STATUS_USER")  
#define uistr_USER_NEW					QObject::tr("USER_NEW")
#define uistr_USER_EDIT					QObject::tr("USER_EDIT")
#define uistr_STATUS_MSG_ALLDEL_ALARM	QObject::tr("STATUS_MSG_ALLDEL_ALARM")
#define uistr_UNIT_MAN					QObject::tr("UINT_MAN")
#define uistr_UNIT_CNT					QObject::tr("UINT_CNT")
#define uistr_UNIT_GE					QObject::tr("UINT_GE")  
#define uistr_UNIT_TOTAL				QObject::tr("UNIT_TOTAL")
#define uistr_UNIT_USED					QObject::tr("UNIT_USED")
#define uistr_ALARM_REMOVE_CONFIRM		QObject::tr("ALARM_REMOVE_CONFIRM")

#define uistr_PRESS_VERIFY_GET_DATA	QObject::tr("PRESS_VERIFY_GET_DATA")  
#define uistr_VERIFY_GET_DATA_SUCCESS	QObject::tr("VERIFY_GET_DATA_SUCCESS")
#define uistr_VERIFY_GET_DATA_FAIL		QObject::tr("VERIFY_GET_DATA_FAIL")
#define uistr_ENROLL_GET_NAME_FAIL		QObject::tr("ENROLL_GET_NAME_FAIL")
#define uistr_ENROLL_FAIL               QObject::tr("ENROLL_FAIL")
#define uistr_ENROLL_DATA_SAVE_TIME     QObject::tr("ENROLL_DATA_SAVE_TIME")
#define uistr_SERVER_NO_ENROLL_ID     QObject::tr("SERVER_NO_ENROLL_ID")
#define uistr_SERVER_NO_ENROLL_FP     QObject::tr("SERVER_NO_ENROLL_FP")
#define uistr_MENU_TCIPIP_MODE               QObject::tr("MENU_TCIPIP_MODE")
#define uistr_MENU_DBUGLOGDOWNLOAD           QObject::tr("MENU_DBUGLOGDOWNLOAD")
#define uistr_MENU_DBUGLOGDELET            QObject::tr("MENU_DBUGLOGDELETD")

#define uistr_MENU_WIEGANDFORMAT            QObject::tr("MENU_WIEGANDFORMAT")
#define uistr_WIEGAND_26            QObject::tr("WIEGAND_26")
#define uistr_WIEGAND_34            QObject::tr("WIEGAND_34")

#define uistr_MENU_DNSSERVERIP            QObject::tr("MENU_DNSSERVERIP")

#define uistr_UPDATE_TIME            QObject::tr("UPDATE_TIME")
#define uistr_UPDATE_FIRMWARE            QObject::tr("UPDATE_FIRMWARE")
#define uistr_GET_NAME_FAIL            QObject::tr("get-name-fail")


static QStringList *__STRINGTABLE = NULL;
void FONTDATABASE_INIT()
{
	if (!__STRINGTABLE)
		__STRINGTABLE = new QStringList;
	else
		__STRINGTABLE->clear();

	////////////////Menu Structure
	__STRINGTABLE->append(uistr_MENU_MAINMENU);
	__STRINGTABLE->append(uistr_MENU_USERMANAGE);
	__STRINGTABLE->append(uistr_MENU_SYSTEMSETTING);
	__STRINGTABLE->append(uistr_MENU_USBMANAGE);
	__STRINGTABLE->append(uistr_MENU_SYSINFOVIEW);
	__STRINGTABLE->append(uistr_MENU_DATAVIEW);
	__STRINGTABLE->append(uistr_MENU_ALARMREMOVE);

	//>>uistr_MENU_USERMANAGE-----------------------------------------------------<<		1
	__STRINGTABLE->append(uistr_MENU_ENROLLNEW);
	__STRINGTABLE->append(uistr_MENU_ENROLLBACKUP);
	__STRINGTABLE->append(uistr_MENU_ENROLLDELETE);
	__STRINGTABLE->append(uistr_MENU_ENROLLEDIT);
	__STRINGTABLE->append(uistr_MENU_ENROLLDEL);   
	__STRINGTABLE->append(uistr_MENU_MESSINFO);

	//>>>>uistr_MENU_ENROLLNEW, uistr_MENU_ENROLLBACKUP---------------------------<<<<		1.1, 1.2
	__STRINGTABLE->append(uistr_MENU_ENROLL_FP);
	__STRINGTABLE->append(uistr_MENU_ENROLL_RFCARD);
	__STRINGTABLE->append(uistr_MENU_ENROLL_PWD);
	__STRINGTABLE->append(uistr_MENU_ENROLL_VOICE);
	__STRINGTABLE->append(uistr_MENU_ENROLL_PHOTO);
	//>>>>uistr_MENU_ENROLLDELETE-------------------------------------------------<<<<		1.3
	__STRINGTABLE->append(uistr_MENU_DELETE_ALL);
	__STRINGTABLE->append(uistr_MENU_DELETE_FP);
	__STRINGTABLE->append(uistr_MENU_DELETE_RFCARD);
	__STRINGTABLE->append(uistr_MENU_REMOVE_PWD);
	__STRINGTABLE->append(uistr_MENU_DELETE_VOICE);
	__STRINGTABLE->append(uistr_MENU_DELETE_PHOTO);

	//>>uistr_MENU_SYSTEMSETTING--------------------------------------------------<<		2
	__STRINGTABLE->append(uistr_MENU_MAINSETTING);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING);
	__STRINGTABLE->append(uistr_MENU_LOGSETTING);
	__STRINGTABLE->append(uistr_MENU_ACSETTING);
	__STRINGTABLE->append(uistr_MENU_SELFTEST);

	//>>>>uistr_MENU_MAINSETTING--------------------------------------------------<<<<		2.1
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_TIME);
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_LANGUAGE);
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_SOUND);
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_VOLUME);
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_KEYALARM);
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_BACKGROUP);   
	//>>>>>>uistr_MENU_MAINSETTING_TIME-------------------------------------------<<<<<<	2.1.1
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_TIME_FORMAT);
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_DATE_FORMAT);
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_TIME_DATE);
	__STRINGTABLE->append(uistr_MENU_MAINSETTING_TIME_TIME);
	//>>>>uistr_MENU_ADVANCEDSETTING----------------------------------------------<<<<		2.2
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_LOGDELETEALL);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_ENROLLDELETEALL);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_DEFAULT);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_FWUPGRADE);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_THEME);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_DAYLIGHT);

	__STRINGTABLE->append(uistr_MENU_UPDATA_FIRMWARE);	//add by loveywm 2012.10.22
	
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_FUNCKEY);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_MANAGER_COUNT);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_DEFAULT_VERIFYMODE);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_SMANAGER_PWD);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_BRIGHT_ADJUST);
	//>>>>>>uistr_MENU_ADVANCEDSETTING_VERIFYIF-----------------------------------<<<<<<	2.2.1
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF_PHOTOSHOW);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERASHOW);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF_FPSHOW);
	//>>>>>>>>uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA--------------------------<<<<<<<<	2.2.1.1
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_SAVE);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_FP);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_CARD);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_PWD);
	//>>>>>>uistr_MENU_ADVANCEDSETTING_DAYLIGHT-----------------------------------<<<<<<	2.2.6
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_DAYLIGHT_OFFSET);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_DAYLIGHT_CHANGE);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_DAYLIGHT_RESTORE);
	//>>>>>>uistr_MENU_ADVANCEDSETTING_FUNCKEY------------------------------------<<<<<<	2.2.7
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_FUNCKEY_F1);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_FUNCKEY_F2);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_FUNCKEY_F3);
	__STRINGTABLE->append(uistr_MENU_ADVANCEDSETTING_FUNCKEY_F4);
	//>>>>uistr_MENU_POWERMANAGE--------------------------------------------------<<<<		2.3
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_BELL);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_IDLE);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_POWEROFF);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_POWERON);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_SLEEP);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_POWERKEYUSE);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_TRSWITCH);
	//>>>>>>uistr_MENU_POWERMANAGE_IDLE-------------------------------------------<<<<		2.3.2
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_IDLE_POWEROFF);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_IDLE_SLEEP);
	__STRINGTABLE->append(uistr_MENU_POWERMANAGE_IDLE_LCDSWITCH);
	//>>>>uistr_MENU_COMMSETTING--------------------------------------------------<<<<		2.4
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_DEVICEID);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_BAUDRATE);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_ETHERNETUSE);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_IPADDRESS);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_MASKADDRESS);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_GWADDRESS);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_RS232USE);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_RS485USE);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_COMMPWD);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_DHCPUSE);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_PCBACKGROUND);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_TCPIP);
	__STRINGTABLE->append(uistr_MENU_COMMSETTING_PORTBACKGROUND);   

	//__STRINGTABLE->append(uistr_MENU_COMMSETTING_HTTPUPDATE);//add by loveywm
	//__STRINGTABLE->append(uistr_MENU_UPDATA_FIRMWARE);
	//__STRINGTABLE->append(uistr_UISTR_MENU_CHESHI);
	//__STRINGTABLE->append(uistr_MENU_COMMSETTING_CLIENT_CONNECT);
	
	//>>>>uistr_MENU_LOGSETTING---------------------------------------------------<<<<		2.5
	__STRINGTABLE->append(uistr_MENU_LOGSETTING_MLOGWARNING);
	__STRINGTABLE->append(uistr_MENU_LOGSETTING_GLOGWARNING);
	__STRINGTABLE->append(uistr_MENU_LOGSETTING_REVERIFYTIME);
	//>>>>uistr_MENU_ACSETTING----------------------------------------------------<<<<		2.6
	__STRINGTABLE->append(uistr_MENU_ACSETTING_TIMEZONE);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUP);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_USERTIMEZONE);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_MAIN);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKTIME);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_OPENTIME);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DOORSENSOR);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_ILLEGALVERIFYWARNING);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUPVERIFYMODE);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_ANTIPASS);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_ACCONTROLLERUSE);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUP_SET);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUP_DEFAULT_VM);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_SET);
	//>>>>>>UISTR_MENU_ACSETTING_GROUP--------------------------------------------<<<<<<	2.6.2
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUP_1);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUP_2);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUP_3);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUP_4);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUP_5);
	//>>>>>>UISTR_MENU_ACSETTING_USERTIMEZONE-------------------------------------<<<<<<	2.6.3
	__STRINGTABLE->append(uistr_MENU_ACSETTING_USERTIMEZONE_GROUP);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_USERTIMEZONE_GTZUSE);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_USERTIMEZONE_TZ1);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_USERTIMEZONE_TZ2);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_USERTIMEZONE_TZ3);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_USERTIMEZONE_GVMUSE);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_USERTIMEZONE_VERIFYMODE);
	//>>>>>>UISTR_MENU_ACSETTING_LOCKGROUP----------------------------------------<<<<<<	2.6.4
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_1);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_2);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_3);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_4);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_5);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_6);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_7);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_8);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_9);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_LOCKGROUP_10);
	//>>>>>>UISTR_MENU_ACSETTING_DURESS---------------------------------------<<<<<<	2.6.8
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS_MANAGE);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS_PWD);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS_SOSKEY);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS_ALARMDELAY);
	//>>>>>>>>UISTR_MENU_ACSETTING_DURESS_MANAGE------------------------------<<<<<<<<	2.6.8.1
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS_MANAGE_ENROLL);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS_MANAGE_SET);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS_MANAGE_REMOVE);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_DURESS_MANAGE_REMOVEALL);
	//>>>>>>UISTR_MENU_ACSETTING_GROUPVERIFYMODE----------------------------------<<<<<<	2.6.10
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP1);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP2);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP3);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP4);
	__STRINGTABLE->append(uistr_MENU_ACSETTING_GROUPVERIFYMODE_GROUP5);
	//>>>>uistr_MENU_SELFTEST-----------------------------------------------------<<<<		2.7
	__STRINGTABLE->append(uistr_MENU_SELFTEST_ALL);
	__STRINGTABLE->append(uistr_MENU_SELFTEST_MEMORY);
	__STRINGTABLE->append(uistr_MENU_SELFTEST_LCD);
	__STRINGTABLE->append(uistr_MENU_SELFTEST_SOUND);
	__STRINGTABLE->append(uistr_MENU_SELFTEST_SENSOR);
	__STRINGTABLE->append(uistr_MENU_SELFTEST_KEYBOARD);
	__STRINGTABLE->append(uistr_MENU_SELFTEST_RTC);
	__STRINGTABLE->append(uistr_MENU_SELFTEST_MP3);

	//>>uistr_MENU_USBMANAGE------------------------------------------------------<<		3
	__STRINGTABLE->append(uistr_MENU_GLOGDOWNLOAD);
	__STRINGTABLE->append(uistr_MENU_ALLGLOGDOWNLOAD);   
	__STRINGTABLE->append(uistr_MENU_MLOGDOWNLOAD);
	__STRINGTABLE->append(uistr_MENU_ALLMLOGDOWNLOAD);   
	__STRINGTABLE->append(uistr_MENU_USERINFODOWNLOAD);
	__STRINGTABLE->append(uistr_MENU_USERINFOUPLOAD);
	__STRINGTABLE->append(uistr_MENU_MSGUPLOAD);
	__STRINGTABLE->append(uistr_MENU_MP3UPLOAD);

	//>>uistr_MENU_SYSINFOVIEW----------------------------------------------------<<		4
	__STRINGTABLE->append(uistr_MENU_USERENROLLCOUNT);
	__STRINGTABLE->append(uistr_MENU_FPENROLLCOUNT);
	__STRINGTABLE->append(uistr_MENU_PWDENROLLCOUNT);
	__STRINGTABLE->append(uistr_MENU_CARDENROLLCOUNT);
	__STRINGTABLE->append(uistr_MENU_GLOGCOUNT);
	__STRINGTABLE->append(uistr_MENU_MLOGCOUNT);
	__STRINGTABLE->append(uistr_MENU_USEDMEMORY);
	__STRINGTABLE->append(uistr_MENU_FREESPACES);
	__STRINGTABLE->append(uistr_MENU_DEVICEINFO);
	__STRINGTABLE->append(uistr_MENU_USEDSPACES);

	//>>>>UISTR_MENU_FREESPACES---------------------------------------------------<<<<		4.6
	__STRINGTABLE->append(uistr_MENU_FREE_USERENROLLCOUNT);
	__STRINGTABLE->append(uistr_MENU_FREE_FPENROLLCOUNT);
	__STRINGTABLE->append(uistr_MENU_FREE_PWDENROLLCOUNT);
	__STRINGTABLE->append(uistr_MENU_FREE_CARDENROLLCOUNT);
	__STRINGTABLE->append(uistr_MENU_FREE_GLOGCOUNT);
	__STRINGTABLE->append(uistr_MENU_FREE_MLOGCOUNT);
	__STRINGTABLE->append(uistr_MENU_FREE_FREEMEMORY);
	//>>>>UISTR_MENU_DEVICEINFO---------------------------------------------------<<<<		4.7
	__STRINGTABLE->append(uistr_MENU_DEVINFO_FP);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_GLOG);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_SLOG);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_MEMORY);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_FIRSTDATE);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_SN);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_TRADEMARK);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_PRODUCTNAME);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_PRODUCTTYPE);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_ENGINEVERSION);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_FIRMWAREVERSION);
	__STRINGTABLE->append(uistr_MENU_DEVINFO_HARDWAREVERSION);

	//>>uistr_MENU_DATAVIEW-------------------------------------------------------<<		5
	__STRINGTABLE->append(uistr_MENU_GLOGVIEW);
	__STRINGTABLE->append(uistr_MENU_MLOGVIEW);
	__STRINGTABLE->append(uistr_MENU_ENROLLVIEW);
	//////////////////////////////

	////////////////Help Structure
	__STRINGTABLE->append(uistr_HELP_MAINMENU);
	__STRINGTABLE->append(uistr_HELP_USERMANAGE);
	__STRINGTABLE->append(uistr_HELP_SYSTEMSETTING);
	__STRINGTABLE->append(uistr_HELP_USBMANAGE);
	__STRINGTABLE->append(uistr_HELP_SYSINFOVIEW);
	__STRINGTABLE->append(uistr_HELP_DATAVIEW);
	__STRINGTABLE->append(uistr_HELP_ALARMREMOVE);

	//>>uistr_HELP_USERMANAGE-----------------------------------------------------<<		1
	__STRINGTABLE->append(uistr_HELP_ENROLLNEW);
	__STRINGTABLE->append(uistr_HELP_ENROLLBACKUP);
	__STRINGTABLE->append(uistr_HELP_ENROLLDELETE);

	//>>>>uistr_HELP_ENROLLNEW, uistr_HELP_ENROLLBACKUP---------------------------<<<<		1.1, 1.2
	__STRINGTABLE->append(uistr_HELP_ENROLL_FP);
	__STRINGTABLE->append(uistr_HELP_ENROLL_RFCARD);
	__STRINGTABLE->append(uistr_HELP_ENROLL_VOICE);
	__STRINGTABLE->append(uistr_HELP_ENROLL_PHOTO);
	//>>>>uistr_HELP_ENROLLDELETE-------------------------------------------------<<<<		1.3
	__STRINGTABLE->append(uistr_HELP_DELETE_ALL);
	__STRINGTABLE->append(uistr_HELP_DELETE_FP);
	__STRINGTABLE->append(uistr_HELP_DELETE_RFCARD);
	__STRINGTABLE->append(uistr_HELP_REMOVE_PWD);
	__STRINGTABLE->append(uistr_HELP_DELETE_VOICE);
	__STRINGTABLE->append(uistr_HELP_DELETE_PHOTO);

	//>>uistr_HELP_SYSTEMSETTING--------------------------------------------------<<		2
	__STRINGTABLE->append(uistr_HELP_MAINSETTING);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING);
	__STRINGTABLE->append(uistr_HELP_LOGSETTING);
	__STRINGTABLE->append(uistr_HELP_ACSETTING);
	__STRINGTABLE->append(uistr_HELP_SELFTEST);

	//>>>>uistr_HELP_MAINSETTING--------------------------------------------------<<<<		2.1
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_TIME);
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_LANGUAGE);
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_SOUND);
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_VOLUME);
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_KEYALARM);
	//>>>>>>uistr_HELP_MAINSETTING_TIME-------------------------------------------<<<<<<	2.1.1
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_TIME_FORMAT);
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_DATE_FORMAT);
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_TIME_DATE);
	__STRINGTABLE->append(uistr_HELP_MAINSETTING_TIME_TIME);
	//>>>>uistr_HELP_ADVANCEDSETTING----------------------------------------------<<<<		2.2
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_VERIFYIF);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_LOGDELETEALL);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_ENROLLDELETEALL);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_DEFAULT);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_FWUPGRADE);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_DAYLIGHT);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_FUNCKEY);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_MANAGER_COUNT);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_DEFAULT_VERIFYMODE);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_SMANAGER_PWD);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_BRIGHT_ADJUST);
	//>>>>>>uistr_HELP_ADVANCEDSETTING_VERIFYIF-----------------------------------<<<<<<	2.2.1
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_VERIFYIF_PHOTO);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_VERIFYIF_FP);
	//>>>>>>>>uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA--------------------------<<<<<<<<	2.2.1.1
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA_SAVE);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA_FP);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA_CARD);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_VERIFYIF_CAMERA_PWD);
	//>>>>>>uistr_HELP_ADVANCEDSETTING_DAYLIGHT-----------------------------------<<<<<<	2.2.6
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_DAYLIGHT_OFFSET);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_DAYLIGHT_CHANGE);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_DAYLIGHT_RESTORE);
	//>>>>>>uistr_HELP_ADVANCEDSETTING_FUNCKEY------------------------------------<<<<<<	2.2.7
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_FUNCKEY_F1);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_FUNCKEY_F2);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_FUNCKEY_F3);
	__STRINGTABLE->append(uistr_HELP_ADVANCEDSETTING_FUNCKEY_F4);
	//>>>>uistr_HELP_POWERMANAGE--------------------------------------------------<<<<		2.3
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_BELL);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_IDLE);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_POWEROFF);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_POWERON);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_SLEEP);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_POWERKEYUSE);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_TRSWITCH);
	//>>>>>>uistr_HELP_POWERMANAGE_IDLE-------------------------------------------<<<<		2.3.2
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_IDLE_POWEROFF);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_IDLE_SLEEP);
	__STRINGTABLE->append(uistr_HELP_POWERMANAGE_IDLE_LCDSWITCH);
	//>>>>uistr_HELP_COMMSETTING--------------------------------------------------<<<<		2.4
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_DEVICEID);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_BAUDRATE);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_ETHERNETUSE);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_IPADDRESS);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_MASKADDRESS);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_GWADDRESS);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_RS232USE);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_RS485USE);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_COMMPWD);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_DHCPUSE);
	__STRINGTABLE->append(uistr_HELP_COMMSETTING_PCBACKGROUND);
	//>>>>uistr_HELP_LOGSETTING---------------------------------------------------<<<<		2.5
	__STRINGTABLE->append(uistr_HELP_LOGSETTING_MLOGWARNING);
	__STRINGTABLE->append(uistr_HELP_LOGSETTING_GLOGWARNING);
	__STRINGTABLE->append(uistr_HELP_LOGSETTING_REVERIFYTIME);
	//>>>>uistr_HELP_ACSETTING----------------------------------------------------<<<<		2.6
	__STRINGTABLE->append(uistr_HELP_ACSETTING_TIMEZONE);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUP);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_USERTIMEZONE);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_MAIN);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKTIME);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_OPENTIME);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DOORSENSOR);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_ILLEGALVERIFYWARNING);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUPVERIFYMODE);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_ANTIPASS);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_ACCONTROLLERUSE);
	//>>>>>>UISTR_HELP_ACSETTING_GROUP--------------------------------------------<<<<<<	2.6.2
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUP_1);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUP_2);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUP_3);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUP_4);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUP_5);
	//>>>>>>UISTR_HELP_ACSETTING_USERTIMEZONE-------------------------------------<<<<<<	2.6.3
	__STRINGTABLE->append(uistr_HELP_ACSETTING_USERTIMEZONE_GROUP);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_USERTIMEZONE_GTZUSE);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_USERTIMEZONE_TZ1);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_USERTIMEZONE_TZ2);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_USERTIMEZONE_TZ3);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_USERTIMEZONE_GVMUSE);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_USERTIMEZONE_VERIFYMODE);
	//>>>>>>UISTR_HELP_ACSETTING_LOCKGROUP----------------------------------------<<<<<<	2.6.4
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_1);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_2);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_3);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_4);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_5);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_6);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_7);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_8);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_9);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_LOCKGROUP_10);
	//>>>>>>UISTR_HELP_ACSETTING_DURESS---------------------------------------<<<<<<	2.6.8
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS_MANAGE);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS_PWD);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS_SOSKEY);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS_ALARMDELAY);
	//>>>>>>>>UISTR_HELP_ACSETTING_DURESS_MANAGE------------------------------<<<<<<<<	2.6.8.1
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS_MANAGE_ENROLL);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS_MANAGE_SET);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS_MANAGE_REMOVE);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_DURESS_MANAGE_REMOVEALL);
	//>>>>>>UISTR_HELP_ACSETTING_GROUPVERIFYMODE----------------------------------<<<<<<	2.6.10
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP1);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP2);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP3);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP4);
	__STRINGTABLE->append(uistr_HELP_ACSETTING_GROUPVERIFYMODE_GROUP5);
	//>>>>uistr_HELP_SELFTEST-----------------------------------------------------<<<<		2.7
	__STRINGTABLE->append(uistr_HELP_SELFTEST_ALL);
	__STRINGTABLE->append(uistr_HELP_SELFTEST_MEMORY);
	__STRINGTABLE->append(uistr_HELP_SELFTEST_LCD);
	__STRINGTABLE->append(uistr_HELP_SELFTEST_SOUND);
	__STRINGTABLE->append(uistr_HELP_SELFTEST_SENSOR);
	__STRINGTABLE->append(uistr_HELP_SELFTEST_KEYBOARD);
	__STRINGTABLE->append(uistr_HELP_SELFTEST_RTC);
	__STRINGTABLE->append(uistr_HELP_SELFTEST_MP3);

	//>>uistr_HELP_USBMANAGE------------------------------------------------------<<		3
	__STRINGTABLE->append(uistr_HELP_GLOGDOWNLOAD);
	__STRINGTABLE->append(uistr_HELP_MLOGDOWNLOAD);
	__STRINGTABLE->append(uistr_HELP_USERINFODOWNLOAD);
	__STRINGTABLE->append(uistr_HELP_USERINFOUPLOAD);
	__STRINGTABLE->append(uistr_HELP_MSGUPLOAD);
	__STRINGTABLE->append(uistr_HELP_MP3UPLOAD);

	//>>uistr_HELP_SYSINFOVIEW----------------------------------------------------<<		4
	__STRINGTABLE->append(uistr_HELP_USERENROLLCOUNT);
	__STRINGTABLE->append(uistr_HELP_FPENROLLCOUNT);
	__STRINGTABLE->append(uistr_HELP_GLOGCOUNT);
	__STRINGTABLE->append(uistr_HELP_MLOGCOUNT);
	__STRINGTABLE->append(uistr_HELP_USEDMEMORY);
	__STRINGTABLE->append(uistr_HELP_FREESPACES);
	__STRINGTABLE->append(uistr_HELP_DEVICEINFO);

	//>>>>UISTR_HELP_FREESPACES---------------------------------------------------<<<<		4.6
	__STRINGTABLE->append(uistr_HELP_FREE_USERENROLLCOUNT);
	__STRINGTABLE->append(uistr_HELP_FREE_FPENROLLCOUNT);
	__STRINGTABLE->append(uistr_HELP_FREE_GLOGCOUNT);
	__STRINGTABLE->append(uistr_HELP_FREE_MLOGCOUNT);
	__STRINGTABLE->append(uistr_HELP_FREE_FREEMEMORY);
	//>>>>UISTR_HELP_DEVICEINFO---------------------------------------------------<<<<		4.7
	__STRINGTABLE->append(uistr_HELP_DEVINFO_FP);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_GLOG);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_SLOG);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_MEMORY);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_FIRSTDATE);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_SN);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_TRADEMARK);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_PRODUCTNAME);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_PRODUCTTYPE);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_ENGINEVERSION);
	__STRINGTABLE->append(uistr_HELP_DEVINFO_FIRMWAREVERSION);

	//>>uistr_HELP_DATAVIEW-------------------------------------------------------<<		5
	__STRINGTABLE->append(uistr_HELP_GLOGVIEW);
	__STRINGTABLE->append(uistr_HELP_MLOGVIEW);
	__STRINGTABLE->append(uistr_HELP_ENROLLVIEW);
	//////////////////////////////

	///////////////Enroll
	__STRINGTABLE->append(uistr_ENROLL_OVERFLOW);
	__STRINGTABLE->append(uistr_ENROLL_MANAGER_OVERFLOW);
	__STRINGTABLE->append(uistr_ENROLL_NOUSER);
	__STRINGTABLE->append(uistr_ENROLL_INVALID_ID);
	__STRINGTABLE->append(uistr_ENROLL_USED_ID);
	__STRINGTABLE->append(uistr_ENROLL_INCORRECT_PWD);
	__STRINGTABLE->append(uistr_ENROLL_SAVEOK);
	__STRINGTABLE->append(uistr_ENROLL_SAVEFAIL);
	__STRINGTABLE->append(uistr_ENROLL_CURRENT_USER);
	__STRINGTABLE->append(uistr_ENROLL_NAME);
	__STRINGTABLE->append(uistr_ENROLLFP_FPFULL);
	__STRINGTABLE->append(uistr_ENROLLFP_FPNO);
	__STRINGTABLE->append(uistr_ENROLLFP_PRESSFP1);
	__STRINGTABLE->append(uistr_ENROLLFP_PRESSFP2);
	__STRINGTABLE->append(uistr_ENROLLFP_PRESSFP3);
	__STRINGTABLE->append(uistr_ENROLLFP_TAKEOFF);
	__STRINGTABLE->append(uistr_ENROLLFP_PRESAGAIN);
	__STRINGTABLE->append(uistr_ENROLLFP_ENROLLSUCCESS);
	__STRINGTABLE->append(uistr_ENROLLFP_FPDOUBLED);
	__STRINGTABLE->append(uistr_ENROLLFP_ESCAPE);
	__STRINGTABLE->append(uistr_ENROLLFP_NOT_ENROLLED);
	__STRINGTABLE->append(uistr_ENROLLPWD_PWDEXIST);
	__STRINGTABLE->append(uistr_ENROLLPWD_FAIL);
	__STRINGTABLE->append(uistr_ENROLLCARD_RFEXIST);
	__STRINGTABLE->append(uistr_ENROLLCARD_INPUTRF);
	__STRINGTABLE->append(uistr_ENROLLCARD_ENROLLSUCCESS);
	__STRINGTABLE->append(uistr_ENROLLCARD_RFDOUBLED_REINPUT);
	__STRINGTABLE->append(uistr_ENROLLVOICE_VOICEEXIST);
	__STRINGTABLE->append(uistr_ENROLLVOICE_SPEAKNAME);
	__STRINGTABLE->append(uistr_ENROLLVOICE_ENROLLSUCCESS);
	__STRINGTABLE->append(uistr_ENROLLVOICE_RETRY);
	__STRINGTABLE->append(uistr_ENROLLVOICE_START);
	__STRINGTABLE->append(uistr_ENROLLVOICE_STOP);
	__STRINGTABLE->append(usitr_ENROLLVOICE_PLAYBACK);
	__STRINGTABLE->append(uistr_ENROLLPHOTO_PHOTOEXIST);
	__STRINGTABLE->append(uistr_ENROLLPHOTO_PREPARE);
	__STRINGTABLE->append(uistr_ENROLLPHOTO_SUCCESS);
	__STRINGTABLE->append(uistr_ENROLLPHOTO_RETRY);
	__STRINGTABLE->append(uistr_ENROLLDELETE_DELETECONFIRM);
	__STRINGTABLE->append(uistr_ENROLLDELETE_DELETESUCCESS);
	__STRINGTABLE->append(uistr_ENROLLDELETE_NOFP);
	__STRINGTABLE->append(uistr_ENROLLDELETE_NOCARD);
	__STRINGTABLE->append(uistr_ENROLLDELETE_NOPWD);
	__STRINGTABLE->append(uistr_ENROLLDELETE_NOVOICE);
	__STRINGTABLE->append(uistr_ENROLLDELETE_NOPHOTO);
	__STRINGTABLE->append(uistr_ENROLLDELETE_NODATA);
	__STRINGTABLE->append(uistr_DURESS_PRESS_ENROLLEDFP);
	__STRINGTABLE->append(uistr_DURESS_ALREADYSET);
	__STRINGTABLE->append(uistr_DURESS_NOT);
	__STRINGTABLE->append(uistr_DURESS_SET_CONFIRM);
	__STRINGTABLE->append(uistr_DURESS_REMOVE_CONFIRM);
	__STRINGTABLE->append(uistr_DURESS_NOEXIST);
	//////////////////////////////

	/////////////Verify
	__STRINGTABLE->append(uistr_VERIFY_DATE);
	__STRINGTABLE->append(uistr_VERIFY_TIME);
	__STRINGTABLE->append(uistr_VERIFY_TRSTATE);
	__STRINGTABLE->append(uistr_VERIFY_ID);
	__STRINGTABLE->append(uistr_VERIFY_NAME);
	__STRINGTABLE->append(uistr_VERIFY_PRIV);
	__STRINGTABLE->append(uistr_VERIFY_PART);
	__STRINGTABLE->append(uistr_VERIFY_TAKEOFF);
	__STRINGTABLE->append(uistr_VERIFY_DISABLED);
	__STRINGTABLE->append(uistr_VERIFY_ILLEGAL);
	__STRINGTABLE->append(uistr_VERIFY_SUCCESS);
	__STRINGTABLE->append(uistr_VERIFY_REVERIFY);
	__STRINGTABLE->append(uistr_VERIFY_FAIL);
	__STRINGTABLE->append(uistr_VERIFY_REINPUT);
	__STRINGTABLE->append(uistr_VERIFY_INPUT_ID);
	__STRINGTABLE->append(uistr_VERIFY_PRESS_FINGER);
	__STRINGTABLE->append(uistr_VERIFY_INPUT_CARD);
	__STRINGTABLE->append(uistr_VERIFY_INPUT_PWD);
	__STRINGTABLE->append(uistr_VERIFY_INVALID_TZ);
	__STRINGTABLE->append(uistr_VERIFY_INVALID_GROUP);
	__STRINGTABLE->append(uistr_VERIFY_ANTIPASS_NOT);
	__STRINGTABLE->append(usitr_VERIFY_MASTER_CONNECT_ERROR);
	//////////////////////////////

	/////////////Search
	__STRINGTABLE->append(uistr_SEARCH_INVALIDPARAM);
	__STRINGTABLE->append(uistr_SEARCH_NODATA);
	__STRINGTABLE->append(uistr_SEARCH_MUST_VERIFY);
	//////////////////////////////

	__STRINGTABLE->append(uistr_LANG_ENG);
	__STRINGTABLE->append(uistr_LANG_SCHN);
	__STRINGTABLE->append(uistr_LANG_TCHN);
	__STRINGTABLE->append(uistr_LANG_KOR);
	__STRINGTABLE->append(uistr_LANG_JPN);


	__STRINGTABLE->append(uistr_BK_1);
	__STRINGTABLE->append(uistr_BK_2);
	__STRINGTABLE->append(uistr_BK_3);
	__STRINGTABLE->append(uistr_BK_4);
	__STRINGTABLE->append(uistr_BK_5);
	__STRINGTABLE->append(uistr_BK_6);


	__STRINGTABLE->append(uistr_FUNC_DUTYNO);   
	__STRINGTABLE->append(uistr_FUNC_DUTYON);
	__STRINGTABLE->append(uistr_FUNC_DUTYOFF);
	__STRINGTABLE->append(uistr_FUNC_OVERTIMEON);
	__STRINGTABLE->append(uistr_FUNC_OVERTIMEOFF);
	__STRINGTABLE->append(uistr_FUNC_GOOUTON);
	__STRINGTABLE->append(uistr_FUNC_GOOUTOFF);
	__STRINGTABLE->append(uistr_FUNC_IN);
	__STRINGTABLE->append(uistr_FUNC_OUT);
	__STRINGTABLE->append(uistr_FUNC_LOGVIEW);
	__STRINGTABLE->append(uistr_FUNC_BELL);
	__STRINGTABLE->append(uistr_FUNC_ALARM);
	__STRINGTABLE->append(uistr_FUNC_SYSINFO);

	__STRINGTABLE->append(uistr_TIMEFMT_12);
	__STRINGTABLE->append(uistr_TIMEFMT_24);

	__STRINGTABLE->append(uistr_DATEFMT_1);
	__STRINGTABLE->append(uistr_DATEFMT_2);
	__STRINGTABLE->append(uistr_DATEFMT_3);
	__STRINGTABLE->append(uistr_DATEFMT_4);
	__STRINGTABLE->append(uistr_DATEFMT_5);
	__STRINGTABLE->append(uistr_DATEFMT_6);
	__STRINGTABLE->append(uistr_DATEFMT_7);
	__STRINGTABLE->append(uistr_DATEFMT_8);
	__STRINGTABLE->append(uistr_DATEFMT_9);
	__STRINGTABLE->append(uistr_DATEFMT_10);

	__STRINGTABLE->append(uistr_BPS_9600);
	__STRINGTABLE->append(uistr_BPS_19200);
	__STRINGTABLE->append(uistr_BPS_38400);
	__STRINGTABLE->append(uistr_BPS_57600);
	__STRINGTABLE->append(uistr_BPS_115200);

	__STRINGTABLE->append(uistr_THEME_1);
	__STRINGTABLE->append(uistr_THEME_2);

	__STRINGTABLE->append(uistr_VERIFYMODE_NONE);
	__STRINGTABLE->append(uistr_VERIFYMODE_ANY);
	__STRINGTABLE->append(uistr_VERIFYMODE_FP);
	__STRINGTABLE->append(uistr_VERIFYMODE_RFFP);
	__STRINGTABLE->append(uistr_VERIFYMODE_RF);
	__STRINGTABLE->append(uistr_VERIFYMODE_IDFP);
	__STRINGTABLE->append(uistr_VERIFYMODE_IDPW);

	__STRINGTABLE->append(uistr_DOORSENSOR_NO);
	__STRINGTABLE->append(uistr_DOORSENSOR_OPEN);
	__STRINGTABLE->append(uistr_DOORSENSOR_CLOSE);

	__STRINGTABLE->append(uistr_ANTIPASS_NO);
	__STRINGTABLE->append(uistr_ANTIPASS_MASTER);
	__STRINGTABLE->append(uistr_ANTIPASS_SLAVE);

	__STRINGTABLE->append(uistr_YESNO_NO);
	__STRINGTABLE->append(uistr_YESNO_YES);

	__STRINGTABLE->append(uistr_ACTION_CONFIRM);
	__STRINGTABLE->append(uistr_ACTION_SUCCESS);
	__STRINGTABLE->append(uistr_ACTION_FAIL);
	
	__STRINGTABLE->append(uistr_BELL_NO);
	__STRINGTABLE->append(uistr_BELL_STIME);
	__STRINGTABLE->append(uistr_BELL_LENGTH);
	__STRINGTABLE->append(uistr_BELL_TYPE);

	__STRINGTABLE->append(uistr_TR_NO);
	__STRINGTABLE->append(uistr_TR_STIME);
	__STRINGTABLE->append(uistr_TR_ETIME);
	__STRINGTABLE->append(uistr_TR_STATUS);


	__STRINGTABLE->append(uistr_ULHDR_ID);
	__STRINGTABLE->append(uistr_ULHDR_NAME);
	__STRINGTABLE->append(uistr_ULHDR_TZ);
	__STRINGTABLE->append(uistr_ULHDR_FP);
	__STRINGTABLE->append(uistr_ULHDR_PWD);
	__STRINGTABLE->append(uistr_ULHDR_CARD);
	__STRINGTABLE->append(uistr_UM_SEARCH);
	__STRINGTABLE->append(uistr_UM_LOGVIEW);
	__STRINGTABLE->append(uistr_UM_EDIT);
	__STRINGTABLE->append(uistr_UM_DELETE);
	__STRINGTABLE->append(uistr_LOGHDR_TIMESTAMP);
	__STRINGTABLE->append(uistr_LOGHDR_ID);
	__STRINGTABLE->append(uistr_LOGHDR_NAME);
	__STRINGTABLE->append(uistr_LOGHDR_CONTENT);

	__STRINGTABLE->append(uistr_DB_LOAD);
	__STRINGTABLE->append(uistr_FINGERPRINT_LOAD);
	__STRINGTABLE->append(uistr_FILEREAD);
	__STRINGTABLE->append(uistr_FILEWRITE);
	__STRINGTABLE->append(uistr_FLASHREAD);
	__STRINGTABLE->append(uistr_FLASHWRITE);
	__STRINGTABLE->append(uistr_COMMUNICATING);
	__STRINGTABLE->append(uistr_WAIT_FOR_COMMUNICATING);
	__STRINGTABLE->append(uistr_WARNING);
	__STRINGTABLE->append(uistr_USER_SEARCH_WARNING);
	__STRINGTABLE->append(uistr_USER_LOG_WARNING);
	__STRINGTABLE->append(uistr_DELETE_CONFIRM);
	__STRINGTABLE->append(uistr_UDISK_NOTFOUND);
	__STRINGTABLE->append(uistr_SDCARD_NOTFOUND);
	__STRINGTABLE->append(uistr_NO_FILES);
	__STRINGTABLE->append(uistr_CAMERA_NOTFOUND);
	__STRINGTABLE->append(uistr_USB_ISFULL);
	__STRINGTABLE->append(uistr_SDCARD_ISFULL);

	__STRINGTABLE->append(uistr_TZHDR_NO);
	__STRINGTABLE->append(uistr_TZHDR_NAME);
	__STRINGTABLE->append(uistr_TZHDR_FROMTIME);
	__STRINGTABLE->append(uistr_TZHDR_TOTIME);
	__STRINGTABLE->append(uistr_TZHDR_CONTENT);
	__STRINGTABLE->append(uistr_TZHDR_TIME);
	__STRINGTABLE->append(uistr_TZHDR_TYPE);
	__STRINGTABLE->append(uistr_TZHDR_STATUS);

	__STRINGTABLE->append(uistr_WEEKDAY_SUN);
	__STRINGTABLE->append(uistr_WEEKDAY_MON);
	__STRINGTABLE->append(uistr_WEEKDAY_TUE);
	__STRINGTABLE->append(uistr_WEEKDAY_WED);
	__STRINGTABLE->append(uistr_WEEKDAY_THU);
	__STRINGTABLE->append(uistr_WEEKDAY_FRI);
	__STRINGTABLE->append(uistr_WEEKDAY_SAT);

	__STRINGTABLE->append(uistr_MONTH_JAN);
	__STRINGTABLE->append(uistr_MONTH_FEB);
	__STRINGTABLE->append(uistr_MONTH_MAR);
	__STRINGTABLE->append(uistr_MONTH_APR);
	__STRINGTABLE->append(uistr_MONTH_MAY);
	__STRINGTABLE->append(uistr_MONTH_JUN);
	__STRINGTABLE->append(uistr_MONTH_JUL);
	__STRINGTABLE->append(uistr_MONTH_AUG);
	__STRINGTABLE->append(uistr_MONTH_SEP);
	__STRINGTABLE->append(uistr_MONTH_OCT);
	__STRINGTABLE->append(uistr_MONTH_NOV);
	__STRINGTABLE->append(uistr_MONTH_DEC);

	__STRINGTABLE->append(uistr_SLOG_TURNON);
	__STRINGTABLE->append(uistr_SLOG_TURNOFF);
	__STRINGTABLE->append(uistr_SLOG_ILLEGALVERIFY_ALARM);
	__STRINGTABLE->append(uistr_SLOG_TAMPER_ALARM);
	__STRINGTABLE->append(uistr_SLOG_ENTERMENU);
	__STRINGTABLE->append(uistr_SLOG_SETTINGCHANGED);
	__STRINGTABLE->append(uistr_SLOG_BACKUPENROLL_FP);
	__STRINGTABLE->append(uistr_SLOG_SETPASSWORD);
	__STRINGTABLE->append(uistr_SLOG_ENROLL_CARD);
	__STRINGTABLE->append(uistr_SLOG_DELETE_USER);
	__STRINGTABLE->append(uistr_SLOG_DELETE_FP);
	__STRINGTABLE->append(uistr_SLOG_DELETE_PASSWORD);
	__STRINGTABLE->append(uistr_SLOG_DELETE_CARD);
	__STRINGTABLE->append(uistr_SLOG_DELETE_ALL);
	__STRINGTABLE->append(uistr_SLOG_CREATE_MFCARD);
	__STRINGTABLE->append(uistr_SLOG_ENROLL_MFCARD);
	__STRINGTABLE->append(uistr_SLOG_REGISTER_MFCARD);
	__STRINGTABLE->append(uistr_SLOG_DELETE_MF_REGIST);
	__STRINGTABLE->append(uistr_SLOG_CLEAR_MF);
	__STRINGTABLE->append(uistr_SLOG_ENROLLDATA2CARD);
	__STRINGTABLE->append(uistr_SLOG_CARD2MACHINE);
	__STRINGTABLE->append(uistr_SLOG_SETTIME);
	__STRINGTABLE->append(uistr_SLOG_RESTORE);
	__STRINGTABLE->append(uistr_SLOG_DELETE_ALL_GLOG);
	__STRINGTABLE->append(uistr_SLOG_REMOVE_MANAGERPRIV);
	__STRINGTABLE->append(uistr_SLOG_TIMEGROUP_SET);
	__STRINGTABLE->append(uistr_SLOG_USERTZ_SET);
	__STRINGTABLE->append(uistr_SLOG_TIMEZONE_SET);
	__STRINGTABLE->append(uistr_SLOG_LOCKGROUP_SET);
	__STRINGTABLE->append(uistr_SLOG_DOOROPEN);
	__STRINGTABLE->append(uistr_SLOG_ENROLL_USER);
	__STRINGTABLE->append(uistr_SLOG_OPENTIMEOUT_ALARM);
	__STRINGTABLE->append(uistr_SLOG_ILGOPEN_ALARM);
	__STRINGTABLE->append(uistr_SLOG_DURESS_ALARM);

	__STRINGTABLE->append(uistr_SOUND_DIGIT0);
	__STRINGTABLE->append(uistr_SOUND_DIGIT1);
	__STRINGTABLE->append(uistr_SOUND_DIGIT2);
	__STRINGTABLE->append(uistr_SOUND_DIGIT3);
	__STRINGTABLE->append(uistr_SOUND_DIGIT4);
	__STRINGTABLE->append(uistr_SOUND_DIGIT5);
	__STRINGTABLE->append(uistr_SOUND_DIGIT6);
	__STRINGTABLE->append(uistr_SOUND_DIGIT7);
	__STRINGTABLE->append(uistr_SOUND_DIGIT8);
	__STRINGTABLE->append(uistr_SOUND_DIGIT9);
	__STRINGTABLE->append(uistr_SOUND_TURNON);
	__STRINGTABLE->append(uistr_SOUND_TURNOFF);
	__STRINGTABLE->append(uistr_SOUND_PRESSFINGER_1);
	__STRINGTABLE->append(uistr_SOUND_PRESSFINGER_2);
	__STRINGTABLE->append(uistr_SOUND_PRESSFINGER_3);
	__STRINGTABLE->append(uistr_SOUND_TAKEOFF_FP);
	__STRINGTABLE->append(uistr_SOUND_PRESSFP_RETRY);
	__STRINGTABLE->append(uistr_SOUND_FPENROLL_SUCCESS);
	__STRINGTABLE->append(uistr_SOUND_FPENROLL_FAIL);
	__STRINGTABLE->append(uistr_SOUND_FPDOUBLED);
	__STRINGTABLE->append(uistr_SOUND_INPUT_PWD);
	__STRINGTABLE->append(uistr_SOUND_PWD_ERROR);
	__STRINGTABLE->append(uistr_SOUND_INPUT_CARD);
	__STRINGTABLE->append(uistr_SOUND_CARDDOUBLED_RETRY);
	__STRINGTABLE->append(uistr_SOUND_CARDENROLL_SUCCESS);
	__STRINGTABLE->append(uistr_SOUND_TALK_YOURNAME);
	__STRINGTABLE->append(uistr_SOUND_VOICERECORD_SUCCESS);
	__STRINGTABLE->append(uistr_SOUND_VOICERECORD_RETRY);
	__STRINGTABLE->append(uistr_SOUND_PREPARE_FOR_PHOTO);
	__STRINGTABLE->append(uistr_SOUND_PHOTO_SUCCESS);
	__STRINGTABLE->append(uistr_SOUND_CAMERA_TONE);
	__STRINGTABLE->append(uistr_SOUND_KEYTONES);
	__STRINGTABLE->append(uistr_SOUND_MENUSELECT);
	__STRINGTABLE->append(uistr_SOUND_ENTERMENU);
	__STRINGTABLE->append(uistr_SOUND_VERIFY_SUCCESS);
	__STRINGTABLE->append(uistr_SOUND_VERIFY_FAIL);
	__STRINGTABLE->append(uistr_SOUND_ERROR);
	__STRINGTABLE->append(uistr_SOUND_QUESTION);
	__STRINGTABLE->append(uistr_SOUND_OK);
	__STRINGTABLE->append(uistr_SOUND_BELL1);
	__STRINGTABLE->append(uistr_SOUND_BELL2);
	__STRINGTABLE->append(uistr_SOUND_BELL3);
	__STRINGTABLE->append(uistr_SOUND_BELL4);
	__STRINGTABLE->append(uistr_SOUND_BELL5);


	__STRINGTABLE->append(uistr_MP3UPLOAD_DESC);
	__STRINGTABLE->append(uistr_MP3UPLOAD_CONFIRM);

	__STRINGTABLE->append(uistr_MANAGER_CONFIRM);
	__STRINGTABLE->append(uistr_WORKING);
	__STRINGTABLE->append(uistr_DEVICE_ERROR);
	__STRINGTABLE->append(uistr_CHECK_SENSOR);
	__STRINGTABLE->append(uistr_SLOG_OVERFLOW);
	__STRINGTABLE->append(uistr_GLOG_OVERFLOW);

	__STRINGTABLE->append(uistr_PRIV_USER);
	__STRINGTABLE->append(uistr_PRIV_MANAGER);
	__STRINGTABLE->append(uistr_PRIV_SMANAGER);

	__STRINGTABLE->append(uistr_UNIT_YEAR);
	__STRINGTABLE->append(uistr_UNIT_MONTH);
	__STRINGTABLE->append(uistr_UNIT_DAY);
	__STRINGTABLE->append(uistr_UNIT_HOUR);
	__STRINGTABLE->append(uistr_UNIT_MINUTE);
	__STRINGTABLE->append(uistr_UNIT_SECOND);
	__STRINGTABLE->append(uistr_UNIT_TIMES);
	__STRINGTABLE->append(uistr_UNIT_LOG);
	__STRINGTABLE->append(uistr_UNIT_FP);
	__STRINGTABLE->append(uistr_UNIT_PERCENT);
	__STRINGTABLE->append(uistr_UNIT_PEOPLE);

	__STRINGTABLE->append(uistr_T9_CHN);
	__STRINGTABLE->append(uistr_T9_ENG);
	__STRINGTABLE->append(uistr_T9_SYM);
	__STRINGTABLE->append(uistr_T9_NUM);

	__STRINGTABLE->append(uistr_STATUS_MENU);
	__STRINGTABLE->append(uistr_STATUS_MENU1);
	__STRINGTABLE->append(uistr_STATUS_LCDTEST);
	__STRINGTABLE->append(uistr_STATUS_BELL);
	__STRINGTABLE->append(uistr_STATUS_SAVE_QUESTION);
	__STRINGTABLE->append(uistr_STATUS_POWEROFF);
	__STRINGTABLE->append(uistr_STATUS_RESTART);
	__STRINGTABLE->append(uistr_STATUS_NOLOG);
	__STRINGTABLE->append(uistr_STATUS_CONTROLLER_CONNECT_ERROR);
	__STRINGTABLE->append(usitr_STATUS_HELP);
	__STRINGTABLE->append(uistr_STATUS_BRIGHT_ADJUST_SUCCESS);
	__STRINGTABLE->append(uistr_STATUS_BRIGHT_ADJUST_FAIL);
	__STRINGTABLE->append(uistr_STATUS_DHCP_CONFIGURING);
	__STRINGTABLE->append(uistr_STATUS_DHCP_CONFIGURE_SUCCESS);
	__STRINGTABLE->append(uistr_STATUS_DHCP_CONFIGURE_FAIL);
	__STRINGTABLE->append(uistr_STATUS_VOICE_DOWNLOAD);
	__STRINGTABLE->append(uistr_STATUS_VOICE_UPLOAD);
	__STRINGTABLE->append(uistr_STATUS_PHOTO_DOWNLOAD);
	__STRINGTABLE->append(uistr_STATUS_PHOTO_UPLOAD);
	__STRINGTABLE->append(uistr_STATUS_AM);
	__STRINGTABLE->append(uistr_STATUS_PM);
	__STRINGTABLE->append(uistr_STATUS_INVALID_WAVFORMAT);
	__STRINGTABLE->append(uistr_STATUS_OK_SELECT);
	__STRINGTABLE->append(uistr_STATUS_OK_SEARCH);
	__STRINGTABLE->append(uistr_STATUS_ESC_BACK);
	__STRINGTABLE->append(uistr_STATUS_MENU_CLEAR);
	__STRINGTABLE->append(uistr_STATUS_OK_T9);

	__STRINGTABLE->append(uistr_SYMBOL_BRACKET_ON);
	__STRINGTABLE->append(uistr_SYMBOL_BRACKET_OFF);
	__STRINGTABLE->append(uistr_SYMBOL_MINUS);
	__STRINGTABLE->append(uistr_SYMBOL_LEFT);
	__STRINGTABLE->append(uistr_SYMBOL_RIGHT);
	__STRINGTABLE->append(uistr_SYMBOL_UP);
	__STRINGTABLE->append(uistr_SYMBOL_DOWN);
	__STRINGTABLE->append(uistr_SYMBOL_WAVE);
	__STRINGTABLE->append(uistr_SYMBOL_STAR);
	__STRINGTABLE->append(uistr_SYMBOLS_SBFONT0);
	__STRINGTABLE->append(uistr_SYMBOLS_SBFONT1);
	__STRINGTABLE->append(uistr_SYMBOLS_SBFONT2);

	__STRINGTABLE->append(uistr_HELP_ENROLLSTEP1);
	__STRINGTABLE->append(uistr_HELP_ENROLLSTEP2);
	__STRINGTABLE->append(uistr_HELP_ENROLLFP);
	__STRINGTABLE->append(uistr_HELP_ENROLLDURESS);
	__STRINGTABLE->append(uistr_HELP_ENROLLCARD);
	__STRINGTABLE->append(uistr_HELP_ENROLLVOICE);
	__STRINGTABLE->append(uistr_HELP_ENROLLPHOTO);
	__STRINGTABLE->append(uistr_HELP_ENROLLDELETE1);
	__STRINGTABLE->append(uistr_HELP_DURESSFPSET);
	__STRINGTABLE->append(uistr_HELP_DURESSFPREMOVE);
	__STRINGTABLE->append(uistr_HELP_INPUTID);
	__STRINGTABLE->append(uistr_HELP_INPUTPWD);
	__STRINGTABLE->append(uistr_HELP_SEARCHUSER);
	__STRINGTABLE->append(uistr_HELP_MENU);
	__STRINGTABLE->append(uistr_HELP_BELLSETUP);
	__STRINGTABLE->append(uistr_HELP_BELLSETONE);
	__STRINGTABLE->append(uistr_HELP_TRSETUP);
	__STRINGTABLE->append(uistr_HELP_TRSETONE);
	__STRINGTABLE->append(uistr_HELP_TIMEZONESETUP);
	__STRINGTABLE->append(uistr_HELP_MP3UPLOAD1);
	__STRINGTABLE->append(uistr_HELP_SYSTEMUPGRADE);
	__STRINGTABLE->append(uistr_HELP_SELFTESTKEYBOARD);
	__STRINGTABLE->append(uistr_HELP_SELFTESTMEMORY);
	__STRINGTABLE->append(uistr_HELP_SELFTESTRTC);
	__STRINGTABLE->append(uistr_HELP_SELFTESTSENSOR);
	__STRINGTABLE->append(uistr_HELP_SELFTESTSOUND);
	__STRINGTABLE->append(uistr_HELP_SELFTESTALL);
	__STRINGTABLE->append(uistr_HELP_USERLIST);
	__STRINGTABLE->append(uistr_HELP_SEARCHLOG);
	__STRINGTABLE->append(uistr_HELP_SLOGLIST);
	__STRINGTABLE->append(uistr_HELP_GLOGLIST);

	__STRINGTABLE->append(uistr_MSG_ID);
	__STRINGTABLE->append(uistr_MSG_STARTTIME);
	__STRINGTABLE->append(uistr_MSG_INTERVAL);
	__STRINGTABLE->append(uistr_MSG_TYPE);
	__STRINGTABLE->append(uistr_MSG_TEXT);
	__STRINGTABLE->append(uistr_STATUS_MSG_INPUT_ERROR);
	__STRINGTABLE->append(uistr_STATUS_MSG_DEL_ALARM);
	__STRINGTABLE->append(uistr_MSG_EDIT);
	__STRINGTABLE->append(uistr_MSG_NEW);
	__STRINGTABLE->append(uistr_MSG_TEXTMARK);
	__STRINGTABLE->append(uistr_MSG_TYPE_USER);
	__STRINGTABLE->append(uistr_MSG_TYPE_GENERAL);
	__STRINGTABLE->append(uistr_USER_MANAGE);
	__STRINGTABLE->append(uistr_MSG_MANAGE);
	__STRINGTABLE->append(uistr_USER_STATUS);
	__STRINGTABLE->append(uistr_MSG_STATUS);
	__STRINGTABLE->append(uistr_MSG_UNIT);
	__STRINGTABLE->append(uistr_STATUS_LOG);  
	__STRINGTABLE->append(uistr_STATUS_USER);  
	__STRINGTABLE->append(uistr_USER_NEW);
	__STRINGTABLE->append(uistr_USER_EDIT);
	__STRINGTABLE->append(uistr_STATUS_MSG_ALLDEL_ALARM);
	__STRINGTABLE->append(uistr_UNIT_MAN);
	__STRINGTABLE->append(uistr_UNIT_CNT);
	__STRINGTABLE->append(uistr_UNIT_GE);   
	__STRINGTABLE->append(uistr_UNIT_TOTAL);
	__STRINGTABLE->append(uistr_UNIT_USED);
	__STRINGTABLE->append(uistr_ALARM_REMOVE_CONFIRM);
	
	__STRINGTABLE->append(uistr_PRESS_VERIFY_GET_DATA);          //按“#”键从服务器获取指纹模板到本地
	__STRINGTABLE->append(uistr_VERIFY_GET_DATA_SUCCESS);          //获取成功
	__STRINGTABLE->append(uistr_VERIFY_GET_DATA_FAIL);          //获取失败
	__STRINGTABLE->append(uistr_ENROLL_GET_NAME_FAIL);          //获取姓名失败；系统无此号码，不允许继续注册
    __STRINGTABLE->append(uistr_ENROLL_FAIL);                    //注册失败
    __STRINGTABLE->append(uistr_ENROLL_DATA_SAVE_TIME);                    //网络获取的数据保持时间
    __STRINGTABLE->append(uistr_SERVER_NO_ENROLL_ID);       //服务器无此ID

    __STRINGTABLE->append(uistr_SERVER_NO_ENROLL_FP);       //服务器无此ID
	
    __STRINGTABLE->append(uistr_MENU_TCIPIP_MODE);
    __STRINGTABLE->append(uistr_MENU_DBUGLOGDOWNLOAD);	
    __STRINGTABLE->append(uistr_MENU_DBUGLOGDELET);		

    __STRINGTABLE->append(uistr_MENU_WIEGANDFORMAT);		
    __STRINGTABLE->append(uistr_WIEGAND_26);		
    __STRINGTABLE->append(uistr_WIEGAND_34);	
	
    __STRINGTABLE->append(uistr_MENU_DNSSERVERIP);	
	
	__STRINGTABLE->append(uistr_UPDATE_TIME);
	__STRINGTABLE->append(uistr_UPDATE_FIRMWARE);
	__STRINGTABLE->append(uistr_GET_NAME_FAIL);
	

	
}

//////////////////////////////////////////////////////////////////////////
QString UISTR(int nIndex)
{
	if (nIndex < 0)
		return QString("");
	if (!__STRINGTABLE)
		FONTDATABASE_INIT();

	if (__STRINGTABLE->size() <= nIndex)
		return QString("No Text");

	return __STRINGTABLE->at(nIndex);
};
