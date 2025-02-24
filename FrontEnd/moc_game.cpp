/****************************************************************************
** Meta object code from reading C++ file 'game.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "game.hpp"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.hpp' doesn't include <QObject>."
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
struct qt_meta_tag_ZN4GameE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN4GameE = QtMocHelpers::stringData(
    "Game",
    "sigClickedBoard",
    "",
    "sigRedirMenu",
    "onStartGame",
    "onHandleClick",
    "Pos",
    "clicked_square",
    "onOpponentDisconnection",
    "onLeaveGame",
    "on_MenuButton_clicked",
    "emptySquares",
    "setHotseatBoard",
    "setOnlineBoard",
    "on_Restart_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN4GameE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,
       3,    0,   81,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   82,    2, 0x0a,    3 /* Public */,
       5,    1,   83,    2, 0x0a,    4 /* Public */,
       8,    0,   86,    2, 0x0a,    6 /* Public */,
       9,    0,   87,    2, 0x0a,    7 /* Public */,
      10,    0,   88,    2, 0x0a,    8 /* Public */,
      11,    0,   89,    2, 0x0a,    9 /* Public */,
      12,    0,   90,    2, 0x0a,   10 /* Public */,
      13,    0,   91,    2, 0x0a,   11 /* Public */,
      14,    0,   92,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Game::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN4GameE.offsetsAndSizes,
    qt_meta_data_ZN4GameE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN4GameE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Game, std::true_type>,
        // method 'sigClickedBoard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sigRedirMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStartGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onHandleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Pos &, std::false_type>,
        // method 'onOpponentDisconnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLeaveGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_MenuButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'emptySquares'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setHotseatBoard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setOnlineBoard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Restart_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Game *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sigClickedBoard(); break;
        case 1: _t->sigRedirMenu(); break;
        case 2: _t->onStartGame(); break;
        case 3: _t->onHandleClick((*reinterpret_cast< std::add_pointer_t<Pos>>(_a[1]))); break;
        case 4: _t->onOpponentDisconnection(); break;
        case 5: _t->onLeaveGame(); break;
        case 6: _t->on_MenuButton_clicked(); break;
        case 7: _t->emptySquares(); break;
        case 8: _t->setHotseatBoard(); break;
        case 9: _t->setOnlineBoard(); break;
        case 10: _t->on_Restart_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (Game::*)();
            if (_q_method_type _q_method = &Game::sigClickedBoard; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (Game::*)();
            if (_q_method_type _q_method = &Game::sigRedirMenu; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN4GameE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Game::sigClickedBoard()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Game::sigRedirMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
