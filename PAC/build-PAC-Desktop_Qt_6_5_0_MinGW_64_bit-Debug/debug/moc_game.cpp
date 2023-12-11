/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PAC/game.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGameENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGameENDCLASS = QtMocHelpers::stringData(
    "Game",
    "chasePacman",
    "",
    "Gh0st*",
    "Gho",
    "xcor",
    "ycor",
    "escapefromPacman",
    "backToCage",
    "endPanicMode",
    "endRunMode",
    "movePacman",
    "collision"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGameENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[5];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[4];
    char stringdata5[5];
    char stringdata6[5];
    char stringdata7[17];
    char stringdata8[11];
    char stringdata9[13];
    char stringdata10[11];
    char stringdata11[11];
    char stringdata12[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGameENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGameENDCLASS_t qt_meta_stringdata_CLASSGameENDCLASS = {
    {
        QT_MOC_LITERAL(0, 4),  // "Game"
        QT_MOC_LITERAL(5, 11),  // "chasePacman"
        QT_MOC_LITERAL(17, 0),  // ""
        QT_MOC_LITERAL(18, 6),  // "Gh0st*"
        QT_MOC_LITERAL(25, 3),  // "Gho"
        QT_MOC_LITERAL(29, 4),  // "xcor"
        QT_MOC_LITERAL(34, 4),  // "ycor"
        QT_MOC_LITERAL(39, 16),  // "escapefromPacman"
        QT_MOC_LITERAL(56, 10),  // "backToCage"
        QT_MOC_LITERAL(67, 12),  // "endPanicMode"
        QT_MOC_LITERAL(80, 10),  // "endRunMode"
        QT_MOC_LITERAL(91, 10),  // "movePacman"
        QT_MOC_LITERAL(102, 9)   // "collision"
    },
    "Game",
    "chasePacman",
    "",
    "Gh0st*",
    "Gho",
    "xcor",
    "ycor",
    "escapefromPacman",
    "backToCage",
    "endPanicMode",
    "endRunMode",
    "movePacman",
    "collision"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGameENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   56,    2, 0x08,    1 /* Private */,
       7,    1,   63,    2, 0x08,    5 /* Private */,
       8,    1,   66,    2, 0x08,    7 /* Private */,
       9,    1,   69,    2, 0x08,    9 /* Private */,
      10,    1,   72,    2, 0x08,   11 /* Private */,
      11,    0,   75,    2, 0x08,   13 /* Private */,
      12,    0,   76,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Game::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_CLASSGameENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGameENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGameENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Game, std::true_type>,
        // method 'chasePacman'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Gh0st *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'escapefromPacman'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Gh0st *, std::false_type>,
        // method 'backToCage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Gh0st *, std::false_type>,
        // method 'endPanicMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Gh0st *, std::false_type>,
        // method 'endRunMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Gh0st *, std::false_type>,
        // method 'movePacman'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'collision'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Game *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->chasePacman((*reinterpret_cast< std::add_pointer_t<Gh0st*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 1: _t->escapefromPacman((*reinterpret_cast< std::add_pointer_t<Gh0st*>>(_a[1]))); break;
        case 2: _t->backToCage((*reinterpret_cast< std::add_pointer_t<Gh0st*>>(_a[1]))); break;
        case 3: _t->endPanicMode((*reinterpret_cast< std::add_pointer_t<Gh0st*>>(_a[1]))); break;
        case 4: _t->endRunMode((*reinterpret_cast< std::add_pointer_t<Gh0st*>>(_a[1]))); break;
        case 5: _t->movePacman(); break;
        case 6: _t->collision(); break;
        default: ;
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
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGameENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
