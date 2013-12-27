HEADERS			= source/precomp.h \
				  source/_fp.h \
				  source/SB3000LIB.h \
				  source/md5_hash.h \
				  source/Database.h \
				  source/COM.h \
				  source/uiFont.h \
				  source/uiLcd.h \
				  source/uiWrap.h \
				  source/Wiegand.h \
				  source/Lock.h \
				  source/gui/Mainframe.h \
				  source/gui/MainWindow.h \
				  source/gui/MessageBox.h \
				  source/gui/Menu.h \
				  source/gui/UserManage.h \
				  source/gui/ProgressDlg.h \
				  source/gui/SystemManage.h \
				  source/gui/SBTable.h \
				  source/gui/SBLabel.h \
				  source/t9/t9_main.h \
				  source/t9/t9_china.h \
				  source/t9/t9_english.h \
				  source/t9/t9_symbol.h \
				  source/style/customstyle.h \
				  source/camera/spcav4l.h \
    source/http_client/http_main.h \
    source/http_client/CSocket.h

SOURCES			= source/main.cpp \
				  source/_fp.cpp \
				  source/_global.cpp \
				  source/SB3000LIB.cpp \
				  source/md5_hash.cpp \
				  source/Database.cpp \
				  source/COM.cpp \
				  source/uiFont.cpp \
				  source/uiLcd.cpp \
				  source/uiWrap.cpp \
				  source/Wiegand.cpp \
				  source/Lock.cpp \
				  source/gui/Mainframe.cpp \
				  source/gui/MainWindow.cpp \
				  source/gui/MessageBox.cpp \
				  source/gui/Menu.cpp \
				  source/gui/UserManage.cpp \
				  source/gui/ProgressDlg.cpp \
				  source/gui/SystemManage.cpp \
				  source/gui/SBTable.cpp \
				  source/gui/SBLabel.cpp \
				  source/t9/t9_main.cpp \
				  source/t9/t9_china.cpp \
				  source/t9/t9_english.cpp \
				  source/t9/t9_symbol.cpp \
				  source/style/customstyle.cpp \
				  source/camera/spcav4l.cpp

FORMS			= ui/bell-dlg.ui \
				  ui/enroll-card.ui \
				  ui/enroll-fp.ui \
				  ui/enroll-photo.ui \
				  ui/enroll-1.ui\
				  ui/enroll-2.ui\
				  ui/enroll-delete.ui\
				  ui/enroll-voice.ui \
				  ui/input-pwd.ui \
				  ui/input-userid.ui \
				  ui/input-userid-name.ui \
				  ui/duress-set.ui \
				  ui/main.ui \
				  ui/mainframe.ui \
				  ui/msgbox-dlg.ui \
				  ui/progress-dlg.ui \
				  ui/selftest-keyboard.ui \
				  ui/selftest-memory.ui \
				  ui/selftest-rtc.ui \
				  ui/selftest-sensor.ui \
				  ui/selftest-sound.ui \
				  ui/set-bellone.ui \
				  ui/set-trone.ui \
				  ui/t9-input.ui \
				  ui/search-user.ui \
				  ui/search-log.ui \
				  ui/verify.ui \
				  ui/user-edit.ui \
				  ui/user-del.ui \
				  ui/msg-edit.ui \
				  ui/input-userid2.ui
TRANSLATIONS		= lang_en.ts \
			  lang_sc.ts \
			  lang_tc.ts \
			  lang_kr.ts \
			  lang_jp.ts

CODECFORTR		= UTF-8
RESOURCES		= sb3000.qrc
#DEFINES		= 
#INCLUDEPATH	= 
#hiway del
#LIBS			+= -Lsource/mp3 -lmadplay
CONFIGS			= release warn_on
#QT			= 
QTPLUGIN		+= qjpeg
VERSION			= 
TARGET			= sb3000
DESTDIR			= 
#DLLDESTDIR		= 
#hiawy del
#QMAKE_CFLAGS_DEBUG	= -isystem/qtopia-arm/mkspecs/qws/linux-arm-g++ -isystem/qtopia-arm/include/QtCore -isystem/qtopia-arm/include/QtNetwork -isystem/qtopia-arm/include/QtGui -isystem/qtopia-arm/include
#QMAKE_CFLAGS_RELEASE	= -isystem/qtopia-arm/mkspecs/qws/linux-arm-g++ -isystem/qtopia-arm/include/QtCore -isystem/qtopia-arm/include/QtNetwork -isystem/qtopia-arm/include/QtGui -isystem/qtopia-arm/include
#QMAKE_CXXFLAGS		= -isystem/qtopia-arm/mkspecs/qws/linux-arm-g++ -isystem/qtopia-arm/include/QtCore -isystem/qtopia-arm/include/QtNetwork -isystem/qtopia-arm/include/QtGui -isystem/qtopia-arm/include
