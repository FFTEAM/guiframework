/****************************************************************************
** Meta object code from reading C++ file 'selectioncontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QT_GUI/Controller/selectioncontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectioncontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SelectionController_t {
    QByteArrayData data[7];
    char stringdata[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectionController_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectionController_t qt_meta_stringdata_SelectionController = {
    {
QT_MOC_LITERAL(0, 0, 19), // "SelectionController"
QT_MOC_LITERAL(1, 20, 14), // "selectYearSlot"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 12), // "aCurrentText"
QT_MOC_LITERAL(4, 49, 15), // "selectMonthSlot"
QT_MOC_LITERAL(5, 65, 21), // "newDataFromDeviceSlot"
QT_MOC_LITERAL(6, 87, 5) // "aType"

    },
    "SelectionController\0selectYearSlot\0\0"
    "aCurrentText\0selectMonthSlot\0"
    "newDataFromDeviceSlot\0aType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectionController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::UChar,    6,

       0        // eod
};

void SelectionController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SelectionController *_t = static_cast<SelectionController *>(_o);
        switch (_id) {
        case 0: _t->selectYearSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->selectMonthSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->newDataFromDeviceSlot((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SelectionController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SelectionController.data,
      qt_meta_data_SelectionController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SelectionController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectionController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SelectionController.stringdata))
        return static_cast<void*>(const_cast< SelectionController*>(this));
    return QObject::qt_metacast(_clname);
}

int SelectionController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
