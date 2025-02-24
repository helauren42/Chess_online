/****************************************************************************
** Meta object code from reading C++ file 'session.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "session.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'session.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN14SessionManagerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14SessionManagerE = QtMocHelpers::stringData(
    "SessionManager",
    "sigPlayerConnection",
    "",
    "sigUpdateOnlinePlayers",
    "text",
    "sigSignupState",
    "msg",
    "sigMakeLogin",
    "sigFaultyLogin",
    "sigInvite",
    "sigLaunchOnlineGame",
    "sigHandleClick",
    "Pos",
    "clicked_square",
    "sigOpponentDisconnection",
    "onNewPlayerConnection",
    "onConnected",
    "onMessageReceived",
    "message",
    "onDisconnected",
    "onSendChallenge",
    "challenger",
    "challenged",
    "gameConnected",
    "gameMessageReceived",
    "gameDisconnected",
    "onConnectGameSock",
    "onUpdateLogin",
    "std::string",
    "username",
    "password",
    "onLogout",
    "onCreateAccount",
    "dob",
    "closeOnlineGame"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14SessionManagerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  146,    2, 0x06,    1 /* Public */,
       3,    1,  147,    2, 0x06,    2 /* Public */,
       5,    1,  150,    2, 0x06,    4 /* Public */,
       7,    0,  153,    2, 0x06,    6 /* Public */,
       8,    1,  154,    2, 0x06,    7 /* Public */,
       9,    0,  157,    2, 0x06,    9 /* Public */,
      10,    0,  158,    2, 0x06,   10 /* Public */,
      11,    1,  159,    2, 0x06,   11 /* Public */,
      14,    0,  162,    2, 0x06,   13 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      15,    0,  163,    2, 0x0a,   14 /* Public */,
      16,    0,  164,    2, 0x0a,   15 /* Public */,
      17,    1,  165,    2, 0x0a,   16 /* Public */,
      19,    0,  168,    2, 0x10a,   18 /* Public | MethodIsConst  */,
      20,    2,  169,    2, 0x0a,   19 /* Public */,
      23,    0,  174,    2, 0x0a,   22 /* Public */,
      24,    1,  175,    2, 0x0a,   23 /* Public */,
      25,    0,  178,    2, 0x10a,   25 /* Public | MethodIsConst  */,
      26,    0,  179,    2, 0x0a,   26 /* Public */,
      27,    2,  180,    2, 0x0a,   27 /* Public */,
      31,    0,  185,    2, 0x0a,   30 /* Public */,
      32,    3,  186,    2, 0x0a,   31 /* Public */,
      34,    0,  193,    2, 0x0a,   35 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28, 0x80000000 | 28,   29,   30,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28, 0x80000000 | 28, 0x80000000 | 28,   29,   30,   33,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SessionManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN14SessionManagerE.offsetsAndSizes,
    qt_meta_data_ZN14SessionManagerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14SessionManagerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SessionManager, std::true_type>,
        // method 'sigPlayerConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sigUpdateOnlinePlayers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'sigSignupState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sigMakeLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sigFaultyLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'sigInvite'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sigLaunchOnlineGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sigHandleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Pos &, std::false_type>,
        // method 'sigOpponentDisconnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNewPlayerConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMessageReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSendChallenge'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'gameConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gameMessageReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'gameDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onConnectGameSock'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onUpdateLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        // method 'onLogout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCreateAccount'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        // method 'closeOnlineGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SessionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SessionManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sigPlayerConnection(); break;
        case 1: _t->sigUpdateOnlinePlayers((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->sigSignupState((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->sigMakeLogin(); break;
        case 4: _t->sigFaultyLogin((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->sigInvite(); break;
        case 6: _t->sigLaunchOnlineGame(); break;
        case 7: _t->sigHandleClick((*reinterpret_cast< std::add_pointer_t<Pos>>(_a[1]))); break;
        case 8: _t->sigOpponentDisconnection(); break;
        case 9: _t->onNewPlayerConnection(); break;
        case 10: _t->onConnected(); break;
        case 11: _t->onMessageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->onDisconnected(); break;
        case 13: _t->onSendChallenge((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 14: _t->gameConnected(); break;
        case 15: _t->gameMessageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->gameDisconnected(); break;
        case 17: _t->onConnectGameSock(); break;
        case 18: _t->onUpdateLogin((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2]))); break;
        case 19: _t->onLogout(); break;
        case 20: _t->onCreateAccount((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::string>>(_a[3]))); break;
        case 21: _t->closeOnlineGame(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (SessionManager::*)();
            if (_q_method_type _q_method = &SessionManager::sigPlayerConnection; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (SessionManager::*)(const QString & );
            if (_q_method_type _q_method = &SessionManager::sigUpdateOnlinePlayers; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (SessionManager::*)(QString );
            if (_q_method_type _q_method = &SessionManager::sigSignupState; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (SessionManager::*)();
            if (_q_method_type _q_method = &SessionManager::sigMakeLogin; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (SessionManager::*)(const QString & );
            if (_q_method_type _q_method = &SessionManager::sigFaultyLogin; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (SessionManager::*)();
            if (_q_method_type _q_method = &SessionManager::sigInvite; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (SessionManager::*)();
            if (_q_method_type _q_method = &SessionManager::sigLaunchOnlineGame; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (SessionManager::*)(const Pos & );
            if (_q_method_type _q_method = &SessionManager::sigHandleClick; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (SessionManager::*)();
            if (_q_method_type _q_method = &SessionManager::sigOpponentDisconnection; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject *SessionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SessionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14SessionManagerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SessionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void SessionManager::sigPlayerConnection()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SessionManager::sigUpdateOnlinePlayers(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SessionManager::sigSignupState(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SessionManager::sigMakeLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SessionManager::sigFaultyLogin(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SessionManager::sigInvite()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SessionManager::sigLaunchOnlineGame()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void SessionManager::sigHandleClick(const Pos & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SessionManager::sigOpponentDisconnection()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
