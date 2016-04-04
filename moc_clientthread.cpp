/****************************************************************************
** Meta object code from reading C++ file 'clientthread.h'
**
** Created: Sat Jun 25 13:33:34 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "clientthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      25,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   13,   13,   13, 0x0a,
      52,   13,   13,   13, 0x0a,
      73,   13,   13,   13, 0x0a,
      95,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClientThread[] = {
    "ClientThread\0\0error(int)\0status(int)\0"
    "transmitData()\0setFilePath(QString)\0"
    "getSignalFromClient()\0cancelTransmission()\0"
};

const QMetaObject ClientThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ClientThread,
      qt_meta_data_ClientThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClientThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClientThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClientThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientThread))
        return static_cast<void*>(const_cast< ClientThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ClientThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: status((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: transmitData(); break;
        case 3: setFilePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: getSignalFromClient(); break;
        case 5: cancelTransmission(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ClientThread::error(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientThread::status(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
