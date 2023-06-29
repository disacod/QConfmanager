/****************************************************************************
** Meta object code from reading C++ file 'animlayout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "animlayout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'animlayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AnimLayout_t {
    QByteArrayData data[10];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnimLayout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnimLayout_t qt_meta_stringdata_AnimLayout = {
    {
QT_MOC_LITERAL(0, 0, 10), // "AnimLayout"
QT_MOC_LITERAL(1, 11, 12), // "deltaChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "value"
QT_MOC_LITERAL(4, 31, 17), // "widgetRectChanged"
QT_MOC_LITERAL(5, 49, 18), // "deltaActiveChanged"
QT_MOC_LITERAL(6, 68, 6), // "active"
QT_MOC_LITERAL(7, 75, 6), // "testIt"
QT_MOC_LITERAL(8, 82, 5), // "delta"
QT_MOC_LITERAL(9, 88, 10) // "widgetRect"

    },
    "AnimLayout\0deltaChanged\0\0value\0"
    "widgetRectChanged\0deltaActiveChanged\0"
    "active\0testIt\0delta\0widgetRect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnimLayout[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       3,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       5,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, QMetaType::QRect,    3,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::QPoint, 0x00495103,
       9, QMetaType::QRect, 0x00495103,
       6, QMetaType::Bool, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void AnimLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AnimLayout *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deltaChanged((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->widgetRectChanged((*reinterpret_cast< const QRect(*)>(_a[1]))); break;
        case 2: _t->deltaActiveChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->testIt(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AnimLayout::*)(const QPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AnimLayout::deltaChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AnimLayout::*)(const QRect & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AnimLayout::widgetRectChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AnimLayout::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AnimLayout::deltaActiveChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AnimLayout *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPoint*>(_v) = _t->delta(); break;
        case 1: *reinterpret_cast< QRect*>(_v) = _t->widgetRect(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isDeltaActive(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AnimLayout *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDelta(*reinterpret_cast< QPoint*>(_v)); break;
        case 1: _t->setWidgetRect(*reinterpret_cast< QRect*>(_v)); break;
        case 2: _t->setDeltaActive(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AnimLayout::staticMetaObject = { {
    &QLayout::staticMetaObject,
    qt_meta_stringdata_AnimLayout.data,
    qt_meta_data_AnimLayout,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AnimLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnimLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AnimLayout.stringdata0))
        return static_cast<void*>(this);
    return QLayout::qt_metacast(_clname);
}

int AnimLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AnimLayout::deltaChanged(const QPoint & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AnimLayout::widgetRectChanged(const QRect & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AnimLayout::deltaActiveChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
