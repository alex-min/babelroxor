/****************************************************************************
** Meta object code from reading C++ file 'Account.h'
**
** Created: Wed 30. Nov 10:38:40 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../babelClient/Account.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Account.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Graphic__Account[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      52,   45,   17,   17, 0x0a,
      74,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Graphic__Account[] = {
    "Graphic::Account\0\0createFormAccount(QString)\0"
    "status\0validFormAccount(int)\0logIn()\0"
};

const QMetaObject Graphic::Account::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Graphic__Account,
      qt_meta_data_Graphic__Account, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Graphic::Account::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Graphic::Account::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Graphic::Account::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Graphic__Account))
        return static_cast<void*>(const_cast< Account*>(this));
    if (!strcmp(_clname, "InterfaceAccount"))
        return static_cast< InterfaceAccount*>(const_cast< Account*>(this));
    return QWidget::qt_metacast(_clname);
}

int Graphic::Account::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createFormAccount((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: validFormAccount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: logIn(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
