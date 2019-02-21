/****************************************************************************
** Meta object code from reading C++ file 'Detect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Detect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Detect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Detect_t {
    QByteArrayData data[16];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Detect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Detect_t qt_meta_stringdata_Detect = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Detect"
QT_MOC_LITERAL(1, 7, 12), // "selectSingle"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "selectDoub1"
QT_MOC_LITERAL(4, 33, 11), // "selectDoub2"
QT_MOC_LITERAL(5, 45, 11), // "selectTrip1"
QT_MOC_LITERAL(6, 57, 11), // "selectTrip2"
QT_MOC_LITERAL(7, 69, 11), // "selectTrip3"
QT_MOC_LITERAL(8, 81, 11), // "selectQuad1"
QT_MOC_LITERAL(9, 93, 11), // "selectQuad2"
QT_MOC_LITERAL(10, 105, 11), // "selectQuad3"
QT_MOC_LITERAL(11, 117, 11), // "selectQuad4"
QT_MOC_LITERAL(12, 129, 13), // "ComputeCorner"
QT_MOC_LITERAL(13, 143, 15), // "DoubMatchPoints"
QT_MOC_LITERAL(14, 159, 15), // "TripMatchPoints"
QT_MOC_LITERAL(15, 175, 15) // "QuadMatchPoints"

    },
    "Detect\0selectSingle\0\0selectDoub1\0"
    "selectDoub2\0selectTrip1\0selectTrip2\0"
    "selectTrip3\0selectQuad1\0selectQuad2\0"
    "selectQuad3\0selectQuad4\0ComputeCorner\0"
    "DoubMatchPoints\0TripMatchPoints\0"
    "QuadMatchPoints"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Detect[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    0,   91,    2, 0x0a /* Public */,
      10,    0,   92,    2, 0x0a /* Public */,
      11,    0,   93,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Detect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Detect *_t = static_cast<Detect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectSingle(); break;
        case 1: _t->selectDoub1(); break;
        case 2: _t->selectDoub2(); break;
        case 3: _t->selectTrip1(); break;
        case 4: _t->selectTrip2(); break;
        case 5: _t->selectTrip3(); break;
        case 6: _t->selectQuad1(); break;
        case 7: _t->selectQuad2(); break;
        case 8: _t->selectQuad3(); break;
        case 9: _t->selectQuad4(); break;
        case 10: _t->ComputeCorner(); break;
        case 11: _t->DoubMatchPoints(); break;
        case 12: _t->TripMatchPoints(); break;
        case 13: _t->QuadMatchPoints(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Detect::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Detect.data,
      qt_meta_data_Detect,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Detect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Detect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Detect.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Detect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
