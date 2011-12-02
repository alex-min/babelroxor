/****************************************************************************
** Meta object code from reading C++ file 'DockWidgetContent.h'
**
** Created: Fri 2. Dec 17:01:21 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../babelClient/DockWidgetContent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DockWidgetContent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Graphic__DockWidgetContent[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,
      49,   47,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   27,   27,   27, 0x0a,
      88,   27,   27,   27, 0x0a,
     113,  104,   27,   27, 0x0a,
     144,  137,   27,   27, 0x0a,
     162,   27,   27,   27, 0x0a,
     182,  177,   27,   27, 0x0a,
     204,  137,   27,   27, 0x0a,
     233,  220,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Graphic__DockWidgetContent[] = {
    "Graphic::DockWidgetContent\0\0"
    "newClient(QString)\0,\0clientStatus(QString,int)\0"
    "addContact()\0removeContact()\0finished\0"
    "closeContactDialog(int)\0status\0"
    "updateStatus(int)\0chooseAvatar()\0name\0"
    "updateAvatar(QString)\0manageCall(int)\0"
    "login,status\0updateStatusForContact(QString,int)\0"
};

const QMetaObject Graphic::DockWidgetContent::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Graphic__DockWidgetContent,
      qt_meta_data_Graphic__DockWidgetContent, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Graphic::DockWidgetContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Graphic::DockWidgetContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Graphic::DockWidgetContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Graphic__DockWidgetContent))
        return static_cast<void*>(const_cast< DockWidgetContent*>(this));
    if (!strcmp(_clname, "InterfaceDockWidgetContent"))
        return static_cast< InterfaceDockWidgetContent*>(const_cast< DockWidgetContent*>(this));
    return QWidget::qt_metacast(_clname);
}

int Graphic::DockWidgetContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newClient((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: clientStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: addContact(); break;
        case 3: removeContact(); break;
        case 4: closeContactDialog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: updateStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: chooseAvatar(); break;
        case 7: updateAvatar((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: manageCall((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: updateStatusForContact((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Graphic::DockWidgetContent::newClient(QString const & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Graphic::DockWidgetContent::clientStatus(QString const & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
