/****************************************************************************
** Meta object code from reading C++ file 'appearance.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../almost done/appearance.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appearance.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Appearance_t {
    QByteArrayData data[15];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Appearance_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Appearance_t qt_meta_stringdata_Appearance = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Appearance"
QT_MOC_LITERAL(1, 11, 14), // "circlePenColor"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "circleWidth"
QT_MOC_LITERAL(4, 39, 16), // "circleBrushColor"
QT_MOC_LITERAL(5, 56, 13), // "arrowPenColor"
QT_MOC_LITERAL(6, 70, 10), // "arrowWidth"
QT_MOC_LITERAL(7, 81, 14), // "textArrowColor"
QT_MOC_LITERAL(8, 96, 15), // "textCircleColor"
QT_MOC_LITERAL(9, 112, 9), // "maybeSave"
QT_MOC_LITERAL(10, 122, 10), // "closeEvent"
QT_MOC_LITERAL(11, 133, 12), // "QCloseEvent*"
QT_MOC_LITERAL(12, 146, 5), // "event"
QT_MOC_LITERAL(13, 152, 20), // "clickedSetTextButton"
QT_MOC_LITERAL(14, 173, 8) // "saveFile"

    },
    "Appearance\0circlePenColor\0\0circleWidth\0"
    "circleBrushColor\0arrowPenColor\0"
    "arrowWidth\0textArrowColor\0textCircleColor\0"
    "maybeSave\0closeEvent\0QCloseEvent*\0"
    "event\0clickedSetTextButton\0saveFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Appearance[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Bool,

       0        // eod
};

void Appearance::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Appearance *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->circlePenColor(); break;
        case 1: _t->circleWidth(); break;
        case 2: _t->circleBrushColor(); break;
        case 3: _t->arrowPenColor(); break;
        case 4: _t->arrowWidth(); break;
        case 5: _t->textArrowColor(); break;
        case 6: _t->textCircleColor(); break;
        case 7: { bool _r = _t->maybeSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 9: _t->clickedSetTextButton(); break;
        case 10: { bool _r = _t->saveFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Appearance::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Appearance.data,
    qt_meta_data_Appearance,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Appearance::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Appearance::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Appearance.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Appearance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
