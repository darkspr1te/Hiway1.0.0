/****************************************************************************
** Meta object code from reading C++ file 'UserManage.h'
**
** Created: Fri Dec 27 16:46:37 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "source/gui/UserManage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UserManage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CEnrollStep1[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      22,   14,   13,   13, 0x0a,
      61,   56,   13,   13, 0x0a,
      92,   81,   13,   13, 0x0a,
     123,   13,  118,   13, 0x0a,
     133,   13,  118,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnrollStep1[] = {
    "CEnrollStep1\0\0from,to\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
    "szID\0OnIDChange(QString)\0szPassword\0"
    "OnPasswordChange(QString)\0BOOL\0OnBtnOK()\0"
    "OnBtnESC()\0"
};

const QMetaObject CEnrollStep1::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEnrollStep1,
      qt_meta_data_CEnrollStep1, 0 }
};

const QMetaObject *CEnrollStep1::metaObject() const
{
    return &staticMetaObject;
}

void *CEnrollStep1::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnrollStep1))
        return static_cast<void*>(const_cast< CEnrollStep1*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEnrollStep1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: OnIDChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: OnPasswordChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: { BOOL _r = OnBtnOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 4: { BOOL _r = OnBtnESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_CEnrollStep2[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   13,   14,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnrollStep2[] = {
    "CEnrollStep2\0\0BOOL\0OnKeyPressOK()\0"
};

const QMetaObject CEnrollStep2::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEnrollStep2,
      qt_meta_data_CEnrollStep2, 0 }
};

const QMetaObject *CEnrollStep2::metaObject() const
{
    return &staticMetaObject;
}

void *CEnrollStep2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnrollStep2))
        return static_cast<void*>(const_cast< CEnrollStep2*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEnrollStep2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { BOOL _r = OnKeyPressOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_CEnrollFP[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   10,   11,   10, 0x0a,
      31,   10,   11,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnrollFP[] = {
    "CEnrollFP\0\0BOOL\0OnKeyPressOK()\0"
    "OnKeyPressESC()\0"
};

const QMetaObject CEnrollFP::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEnrollFP,
      qt_meta_data_CEnrollFP, 0 }
};

const QMetaObject *CEnrollFP::metaObject() const
{
    return &staticMetaObject;
}

void *CEnrollFP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnrollFP))
        return static_cast<void*>(const_cast< CEnrollFP*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEnrollFP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { BOOL _r = OnKeyPressOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 1: { BOOL _r = OnKeyPressESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_CEnrollCard[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      18,   12,   13,   12, 0x0a,
      33,   12,   13,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnrollCard[] = {
    "CEnrollCard\0\0BOOL\0OnKeyPressOK()\0"
    "OnKeyPressESC()\0"
};

const QMetaObject CEnrollCard::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEnrollCard,
      qt_meta_data_CEnrollCard, 0 }
};

const QMetaObject *CEnrollCard::metaObject() const
{
    return &staticMetaObject;
}

void *CEnrollCard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnrollCard))
        return static_cast<void*>(const_cast< CEnrollCard*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEnrollCard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { BOOL _r = OnKeyPressOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 1: { BOOL _r = OnKeyPressESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_CEnrollVoice[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   13,   14,   13, 0x0a,
      34,   13,   14,   13, 0x0a,
      65,   54,   50,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnrollVoice[] = {
    "CEnrollVoice\0\0BOOL\0OnKeyPressOK()\0"
    "OnKeyPressESC()\0int\0szFilename\0"
    "OnVoiceRecord(char*)\0"
};

const QMetaObject CEnrollVoice::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEnrollVoice,
      qt_meta_data_CEnrollVoice, 0 }
};

const QMetaObject *CEnrollVoice::metaObject() const
{
    return &staticMetaObject;
}

void *CEnrollVoice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnrollVoice))
        return static_cast<void*>(const_cast< CEnrollVoice*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEnrollVoice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { BOOL _r = OnKeyPressOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 1: { BOOL _r = OnKeyPressESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 2: { int _r = OnVoiceRecord((*reinterpret_cast< char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_CEnrollPhoto[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   13,   14,   13, 0x0a,
      34,   13,   14,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnrollPhoto[] = {
    "CEnrollPhoto\0\0BOOL\0OnKeyPressOK()\0"
    "OnKeyPressESC()\0"
};

const QMetaObject CEnrollPhoto::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEnrollPhoto,
      qt_meta_data_CEnrollPhoto, 0 }
};

const QMetaObject *CEnrollPhoto::metaObject() const
{
    return &staticMetaObject;
}

void *CEnrollPhoto::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnrollPhoto))
        return static_cast<void*>(const_cast< CEnrollPhoto*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEnrollPhoto::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { BOOL _r = OnKeyPressOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 1: { BOOL _r = OnKeyPressESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_CEnrollDelete[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   14,   15,   14, 0x0a,
      35,   14,   15,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnrollDelete[] = {
    "CEnrollDelete\0\0BOOL\0OnKeyPressOK()\0"
    "OnKeyPressESC()\0"
};

const QMetaObject CEnrollDelete::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEnrollDelete,
      qt_meta_data_CEnrollDelete, 0 }
};

const QMetaObject *CEnrollDelete::metaObject() const
{
    return &staticMetaObject;
}

void *CEnrollDelete::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnrollDelete))
        return static_cast<void*>(const_cast< CEnrollDelete*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEnrollDelete::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { BOOL _r = OnKeyPressOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 1: { BOOL _r = OnKeyPressESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_CDuressFP[] = {

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

static const char qt_meta_stringdata_CDuressFP[] = {
    "CDuressFP\0"
};

const QMetaObject CDuressFP::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CDuressFP,
      qt_meta_data_CDuressFP, 0 }
};

const QMetaObject *CDuressFP::metaObject() const
{
    return &staticMetaObject;
}

void *CDuressFP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CDuressFP))
        return static_cast<void*>(const_cast< CDuressFP*>(this));
    return QDialog::qt_metacast(_clname);
}

int CDuressFP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CInputUserID[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      27,   13,   13,   13, 0x0a,
      41,   13,   13,   13, 0x0a,
      60,   52,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CInputUserID[] = {
    "CInputUserID\0\0OnBtnOK_ID()\0OnBtnOK_PWD()\0"
    "OnBtnESC()\0strText\0OnTextChange(QString)\0"
};

const QMetaObject CInputUserID::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CInputUserID,
      qt_meta_data_CInputUserID, 0 }
};

const QMetaObject *CInputUserID::metaObject() const
{
    return &staticMetaObject;
}

void *CInputUserID::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CInputUserID))
        return static_cast<void*>(const_cast< CInputUserID*>(this));
    return QDialog::qt_metacast(_clname);
}

int CInputUserID::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnOK_ID(); break;
        case 1: OnBtnOK_PWD(); break;
        case 2: OnBtnESC(); break;
        case 3: OnTextChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_CInputUserID2[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      25,   14,   14,   14, 0x0a,
      44,   36,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CInputUserID2[] = {
    "CInputUserID2\0\0OnBtnOK()\0OnBtnESC()\0"
    "strText\0OnTextChange(QString)\0"
};

const QMetaObject CInputUserID2::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CInputUserID2,
      qt_meta_data_CInputUserID2, 0 }
};

const QMetaObject *CInputUserID2::metaObject() const
{
    return &staticMetaObject;
}

void *CInputUserID2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CInputUserID2))
        return static_cast<void*>(const_cast< CInputUserID2*>(this));
    return QDialog::qt_metacast(_clname);
}

int CInputUserID2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnOK(); break;
        case 1: OnBtnESC(); break;
        case 2: OnTextChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_CInputUserIDName[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      26,   18,   17,   17, 0x0a,
      65,   60,   17,   17, 0x0a,
      90,   17,   85,   17, 0x0a,
     100,   17,   85,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CInputUserIDName[] = {
    "CInputUserIDName\0\0from,to\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
    "szID\0OnIDChange(QString)\0BOOL\0OnBtnOK()\0"
    "OnBtnESC()\0"
};

const QMetaObject CInputUserIDName::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CInputUserIDName,
      qt_meta_data_CInputUserIDName, 0 }
};

const QMetaObject *CInputUserIDName::metaObject() const
{
    return &staticMetaObject;
}

void *CInputUserIDName::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CInputUserIDName))
        return static_cast<void*>(const_cast< CInputUserIDName*>(this));
    return QDialog::qt_metacast(_clname);
}

int CInputUserIDName::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: OnIDChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { BOOL _r = OnBtnOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 3: { BOOL _r = OnBtnESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_CInputPWD[] = {

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
      43,   32,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CInputPWD[] = {
    "CInputPWD\0\0OnBtnOK()\0OnBtnESC()\0"
    "szPassword\0OnPasswordChange(QString)\0"
};

const QMetaObject CInputPWD::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CInputPWD,
      qt_meta_data_CInputPWD, 0 }
};

const QMetaObject *CInputPWD::metaObject() const
{
    return &staticMetaObject;
}

void *CInputPWD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CInputPWD))
        return static_cast<void*>(const_cast< CInputPWD*>(this));
    return QDialog::qt_metacast(_clname);
}

int CInputPWD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnOK(); break;
        case 1: OnBtnESC(); break;
        case 2: OnPasswordChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_CSearchUser[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      21,   13,   12,   12, 0x0a,
      55,   12,   12,   12, 0x0a,
      65,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSearchUser[] = {
    "CSearchUser\0\0from,to\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
    "OnBtnOK()\0OnBtnESC()\0"
};

const QMetaObject CSearchUser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSearchUser,
      qt_meta_data_CSearchUser, 0 }
};

const QMetaObject *CSearchUser::metaObject() const
{
    return &staticMetaObject;
}

void *CSearchUser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSearchUser))
        return static_cast<void*>(const_cast< CSearchUser*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSearchUser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: OnBtnOK(); break;
        case 2: OnBtnESC(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_CUserList[] = {

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

static const char qt_meta_stringdata_CUserList[] = {
    "CUserList\0"
};

const QMetaObject CUserList::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CUserList,
      qt_meta_data_CUserList, 0 }
};

const QMetaObject *CUserList::metaObject() const
{
    return &staticMetaObject;
}

void *CUserList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CUserList))
        return static_cast<void*>(const_cast< CUserList*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CUserList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CSearchLog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      22,   11,   11,   11, 0x0a,
      40,   33,   11,   11, 0x0a,
      67,   59,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSearchLog[] = {
    "CSearchLog\0\0OnBtnOK()\0OnBtnESC()\0"
    "nIndex\0OnDateChanged(int)\0from,to\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
};

const QMetaObject CSearchLog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSearchLog,
      qt_meta_data_CSearchLog, 0 }
};

const QMetaObject *CSearchLog::metaObject() const
{
    return &staticMetaObject;
}

void *CSearchLog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSearchLog))
        return static_cast<void*>(const_cast< CSearchLog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSearchLog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnOK(); break;
        case 1: OnBtnESC(); break;
        case 2: OnDateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_CSLogList[] = {

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

static const char qt_meta_stringdata_CSLogList[] = {
    "CSLogList\0"
};

const QMetaObject CSLogList::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CSLogList,
      qt_meta_data_CSLogList, 0 }
};

const QMetaObject *CSLogList::metaObject() const
{
    return &staticMetaObject;
}

void *CSLogList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSLogList))
        return static_cast<void*>(const_cast< CSLogList*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CSLogList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CGLogList[] = {

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

static const char qt_meta_stringdata_CGLogList[] = {
    "CGLogList\0"
};

const QMetaObject CGLogList::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CGLogList,
      qt_meta_data_CGLogList, 0 }
};

const QMetaObject *CGLogList::metaObject() const
{
    return &staticMetaObject;
}

void *CGLogList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CGLogList))
        return static_cast<void*>(const_cast< CGLogList*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CGLogList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CUserManage[] = {

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

static const char qt_meta_stringdata_CUserManage[] = {
    "CUserManage\0"
};

const QMetaObject CUserManage::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CUserManage,
      qt_meta_data_CUserManage, 0 }
};

const QMetaObject *CUserManage::metaObject() const
{
    return &staticMetaObject;
}

void *CUserManage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CUserManage))
        return static_cast<void*>(const_cast< CUserManage*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CUserManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CMsgManage[] = {

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

static const char qt_meta_stringdata_CMsgManage[] = {
    "CMsgManage\0"
};

const QMetaObject CMsgManage::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CMsgManage,
      qt_meta_data_CMsgManage, 0 }
};

const QMetaObject *CMsgManage::metaObject() const
{
    return &staticMetaObject;
}

void *CMsgManage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMsgManage))
        return static_cast<void*>(const_cast< CMsgManage*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CMsgManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CMsgEdit[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      20,    9,    9,    9, 0x0a,
      39,   31,    9,    9, 0x0a,
      79,   73,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CMsgEdit[] = {
    "CMsgEdit\0\0OnBtnOK()\0OnBtnESC()\0from,to\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
    "index\0OnCurrentIndexChanged(int)\0"
};

const QMetaObject CMsgEdit::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CMsgEdit,
      qt_meta_data_CMsgEdit, 0 }
};

const QMetaObject *CMsgEdit::metaObject() const
{
    return &staticMetaObject;
}

void *CMsgEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMsgEdit))
        return static_cast<void*>(const_cast< CMsgEdit*>(this));
    return QDialog::qt_metacast(_clname);
}

int CMsgEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnOK(); break;
        case 1: OnBtnESC(); break;
        case 2: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 3: OnCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_CUserEdit[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x0a,
      58,   53,   10,   10, 0x0a,
      89,   78,   10,   10, 0x0a,
     120,   10,  115,   10, 0x0a,
     130,   10,  115,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CUserEdit[] = {
    "CUserEdit\0\0from,to\0OnFocusChanged(QWidget*,QWidget*)\0"
    "szID\0OnIDChange(QString)\0szPassword\0"
    "OnPasswordChange(QString)\0BOOL\0OnBtnOK()\0"
    "OnBtnESC()\0"
};

const QMetaObject CUserEdit::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CUserEdit,
      qt_meta_data_CUserEdit, 0 }
};

const QMetaObject *CUserEdit::metaObject() const
{
    return &staticMetaObject;
}

void *CUserEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CUserEdit))
        return static_cast<void*>(const_cast< CUserEdit*>(this));
    return QDialog::qt_metacast(_clname);
}

int CUserEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: OnIDChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: OnPasswordChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: { BOOL _r = OnBtnOK();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        case 4: { BOOL _r = OnBtnESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_CUserDel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      20,    9,    9,    9, 0x0a,
      39,   31,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CUserDel[] = {
    "CUserDel\0\0OnBtnOK()\0OnBtnESC()\0from,to\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
};

const QMetaObject CUserDel::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CUserDel,
      qt_meta_data_CUserDel, 0 }
};

const QMetaObject *CUserDel::metaObject() const
{
    return &staticMetaObject;
}

void *CUserDel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CUserDel))
        return static_cast<void*>(const_cast< CUserDel*>(this));
    return QDialog::qt_metacast(_clname);
}

int CUserDel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_CDepartmentManage[] = {

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

static const char qt_meta_stringdata_CDepartmentManage[] = {
    "CDepartmentManage\0"
};

const QMetaObject CDepartmentManage::staticMetaObject = {
    { &CMainFrame::staticMetaObject, qt_meta_stringdata_CDepartmentManage,
      qt_meta_data_CDepartmentManage, 0 }
};

const QMetaObject *CDepartmentManage::metaObject() const
{
    return &staticMetaObject;
}

void *CDepartmentManage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CDepartmentManage))
        return static_cast<void*>(const_cast< CDepartmentManage*>(this));
    return CMainFrame::qt_metacast(_clname);
}

int CDepartmentManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMainFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
