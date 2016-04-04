/****************************************************************************
** Meta object code from reading C++ file 'inkpresetingserver.h'
**
** Created: Sat Jun 25 13:33:35 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inkpresetingserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inkpresetingserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InkPresetingServer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      34,   19,   19,   19, 0x05,
      55,   19,   19,   19, 0x05,
      69,   19,   19,   19, 0x05,
      87,   19,   19,   19, 0x05,
     106,   19,   19,   19, 0x05,
     119,  117,   19,   19, 0x05,
     146,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     164,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InkPresetingServer[] = {
    "InkPresetingServer\0\0startToSend()\0"
    "cancelTransmission()\0path(QString)\0"
    "bytesSent(qint64)\0currentStatus(int)\0"
    "error(int)\0,\0ipAddress(QString,quint16)\0"
    "fileSize(quint64)\0setFilePath(QString)\0"
};

const QMetaObject InkPresetingServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_InkPresetingServer,
      qt_meta_data_InkPresetingServer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InkPresetingServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InkPresetingServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InkPresetingServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InkPresetingServer))
        return static_cast<void*>(const_cast< InkPresetingServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int InkPresetingServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startToSend(); break;
        case 1: cancelTransmission(); break;
        case 2: path((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: bytesSent((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: currentStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: ipAddress((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 7: fileSize((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 8: setFilePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void InkPresetingServer::startToSend()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void InkPresetingServer::cancelTransmission()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void InkPresetingServer::path(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void InkPresetingServer::bytesSent(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void InkPresetingServer::currentStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void InkPresetingServer::error(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void InkPresetingServer::ipAddress(QString _t1, quint16 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void InkPresetingServer::fileSize(quint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
