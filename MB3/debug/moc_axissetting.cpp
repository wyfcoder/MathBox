/****************************************************************************
** Meta object code from reading C++ file 'axissetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../axissetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'axissetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AxisSetting_t {
    QByteArrayData data[5];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AxisSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AxisSetting_t qt_meta_stringdata_AxisSetting = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AxisSetting"
QT_MOC_LITERAL(1, 12, 8), // "sendAxis"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "ShowOk"
QT_MOC_LITERAL(4, 29, 10) // "ShowCancel"

    },
    "AxisSetting\0sendAxis\0\0ShowOk\0ShowCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AxisSetting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,   12,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   54,    2, 0x0a /* Public */,
       4,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int, QMetaType::QColor, QMetaType::QFont, QMetaType::QColor, QMetaType::QFont, QMetaType::Double, QMetaType::Double, QMetaType::QColor, QMetaType::QFont, QMetaType::Double, QMetaType::Double, QMetaType::QColor, QMetaType::QFont,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AxisSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AxisSetting *_t = static_cast<AxisSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->sendAxis((*reinterpret_cast< QColor(*)>(_a[1])),(*reinterpret_cast< QFont(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3])),(*reinterpret_cast< QFont(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< QColor(*)>(_a[7])),(*reinterpret_cast< QFont(*)>(_a[8])),(*reinterpret_cast< double(*)>(_a[9])),(*reinterpret_cast< double(*)>(_a[10])),(*reinterpret_cast< QColor(*)>(_a[11])),(*reinterpret_cast< QFont(*)>(_a[12])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->ShowOk(); break;
        case 2: _t->ShowCancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef int (AxisSetting::*_t)(QColor , QFont , QColor , QFont , double , double , QColor , QFont , double , double , QColor , QFont );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AxisSetting::sendAxis)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AxisSetting::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_AxisSetting.data,
      qt_meta_data_AxisSetting,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AxisSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AxisSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AxisSetting.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int AxisSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
int AxisSetting::sendAxis(QColor _t1, QFont _t2, QColor _t3, QFont _t4, double _t5, double _t6, QColor _t7, QFont _t8, double _t9, double _t10, QColor _t11, QFont _t12)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)), const_cast<void*>(reinterpret_cast<const void*>(&_t11)), const_cast<void*>(reinterpret_cast<const void*>(&_t12)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
