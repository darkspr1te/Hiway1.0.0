/****************************************************************************
** Meta object code from reading C++ file 'SystemManage.h'
**
** Created: Fri Dec 27 16:46:38 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "source/gui/SystemManage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SystemManage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CBellSetup[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CBellSetup[] = {
    "CBellSetup\0"
};

const QMetaObject CBellSetup::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CBellSetup,
      qt_meta_data_CBellSetup, 0 }
};

const QMetaObject *CBellSetup::metaObject() const
{
    return &staticMetaObject;
}

void *CBellSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBellSetup))
        return static_cast<void*>(const_cast< CBellSetup*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CBellSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CBellSetOne[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      23,   12,   12,   12, 0x0a,
      42,   34,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CBellSetOne[] = {
    "CBellSetOne\0\0OnBtnOK()\0OnBtnESC()\0"
    "from,to\0OnFocusChanged(QWidget*,QWidget*)\0"
};

const QMetaObject CBellSetOne::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CBellSetOne,
      qt_meta_data_CBellSetOne, 0 }
};

const QMetaObject *CBellSetOne::metaObject() const
{
    return &staticMetaObject;
}

void *CBellSetOne::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBellSetOne))
        return static_cast<void*>(const_cast< CBellSetOne*>(this));
    return QDialog::qt_metacast(_clname);
}

int CBellSetOne::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnOK(); break;
        case 1: OnBtnESC(); break;
        case 2: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_CTrSetup[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CTrSetup[] = {
    "CTrSetup\0"
};

const QMetaObject CTrSetup::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CTrSetup,
      qt_meta_data_CTrSetup, 0 }
};

const QMetaObject *CTrSetup::metaObject() const
{
    return &staticMetaObject;
}

void *CTrSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CTrSetup))
        return static_cast<void*>(const_cast< CTrSetup*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CTrSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CTrSetOne[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      21,   10,   10,   10, 0x0a,
      40,   32,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CTrSetOne[] = {
    "CTrSetOne\0\0OnBtnOK()\0OnBtnESC()\0from,to\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
};

const QMetaObject CTrSetOne::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CTrSetOne,
      qt_meta_data_CTrSetOne, 0 }
};

const QMetaObject *CTrSetOne::metaObject() const
{
    return &staticMetaObject;
}

void *CTrSetOne::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CTrSetOne))
        return static_cast<void*>(const_cast< CTrSetOne*>(this));
    return QDialog::qt_metacast(_clname);
}

int CTrSetOne::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnOK(); break;
        case 1: OnBtnESC(); break;
        case 2: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_CTimezoneSetup[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CTimezoneSetup[] = {
    "CTimezoneSetup\0"
};

const QMetaObject CTimezoneSetup::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CTimezoneSetup,
      qt_meta_data_CTimezoneSetup, 0 }
};

const QMetaObject *CTimezoneSetup::metaObject() const
{
    return &staticMetaObject;
}

void *CTimezoneSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CTimezoneSetup))
        return static_cast<void*>(const_cast< CTimezoneSetup*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CTimezoneSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CMp3Upload[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CMp3Upload[] = {
    "CMp3Upload\0"
};

const QMetaObject CMp3Upload::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CMp3Upload,
      qt_meta_data_CMp3Upload, 0 }
};

const QMetaObject *CMp3Upload::metaObject() const
{
    return &staticMetaObject;
}

void *CMp3Upload::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMp3Upload))
        return static_cast<void*>(const_cast< CMp3Upload*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CMp3Upload::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CSystemUpgrade[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CSystemUpgrade[] = {
    "CSystemUpgrade\0"
};

const QMetaObject CSystemUpgrade::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CSystemUpgrade,
      qt_meta_data_CSystemUpgrade, 0 }
};

const QMetaObject *CSystemUpgrade::metaObject() const
{
    return &staticMetaObject;
}

void *CSystemUpgrade::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSystemUpgrade))
        return static_cast<void*>(const_cast< CSystemUpgrade*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CSystemUpgrade::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CSelftestKeyboard[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CSelftestKeyboard[] = {
    "CSelftestKeyboard\0"
};

const QMetaObject CSelftestKeyboard::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSelftestKeyboard,
      qt_meta_data_CSelftestKeyboard, 0 }
};

const QMetaObject *CSelftestKeyboard::metaObject() const
{
    return &staticMetaObject;
}

void *CSelftestKeyboard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSelftestKeyboard))
        return static_cast<void*>(const_cast< CSelftestKeyboard*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSelftestKeyboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CSelftestMemory[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CSelftestMemory[] = {
    "CSelftestMemory\0"
};

const QMetaObject CSelftestMemory::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSelftestMemory,
      qt_meta_data_CSelftestMemory, 0 }
};

const QMetaObject *CSelftestMemory::metaObject() const
{
    return &staticMetaObject;
}

void *CSelftestMemory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSelftestMemory))
        return static_cast<void*>(const_cast< CSelftestMemory*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSelftestMemory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CSelftestRtc[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSelftestRtc[] = {
    "CSelftestRtc\0\0OnBtnEsc()\0"
};

const QMetaObject CSelftestRtc::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSelftestRtc,
      qt_meta_data_CSelftestRtc, 0 }
};

const QMetaObject *CSelftestRtc::metaObject() const
{
    return &staticMetaObject;
}

void *CSelftestRtc::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSelftestRtc))
        return static_cast<void*>(const_cast< CSelftestRtc*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSelftestRtc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnEsc(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_CSelftestSensor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CSelftestSensor[] = {
    "CSelftestSensor\0"
};

const QMetaObject CSelftestSensor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSelftestSensor,
      qt_meta_data_CSelftestSensor, 0 }
};

const QMetaObject *CSelftestSensor::metaObject() const
{
    return &staticMetaObject;
}

void *CSelftestSensor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSelftestSensor))
        return static_cast<void*>(const_cast< CSelftestSensor*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSelftestSensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CSelftestSound[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      28,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSelftestSound[] = {
    "CSelftestSound\0\0OnBtnPlay()\0OnBtnEsc()\0"
};

const QMetaObject CSelftestSound::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSelftestSound,
      qt_meta_data_CSelftestSound, 0 }
};

const QMetaObject *CSelftestSound::metaObject() const
{
    return &staticMetaObject;
}

void *CSelftestSound::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSelftestSound))
        return static_cast<void*>(const_cast< CSelftestSound*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSelftestSound::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnPlay(); break;
        case 1: OnBtnEsc(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_CSelftestAll[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CSelftestAll[] = {
    "CSelftestAll\0"
};

const QMetaObject CSelftestAll::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CSelftestAll,
      qt_meta_data_CSelftestAll, 0 }
};

const QMetaObject *CSelftestAll::metaObject() const
{
    return &staticMetaObject;
}

void *CSelftestAll::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSelftestAll))
        return static_cast<void*>(const_cast< CSelftestAll*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CSelftestAll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CHelpWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CHelpWindow[] = {
    "CHelpWindow\0"
};

const QMetaObject CHelpWindow::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CHelpWindow,
      qt_meta_data_CHelpWindow, 0 }
};

const QMetaObject *CHelpWindow::metaObject() const
{
    return &staticMetaObject;
}

void *CHelpWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CHelpWindow))
        return static_cast<void*>(const_cast< CHelpWindow*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CHelpWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
