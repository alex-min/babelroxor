/****************************************************************************
** Meta object code from reading C++ file 'RegisterAccount.h'
**
** Created: Sun Nov 27 14:02:23 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../trunk/babelClient/RegisterAccount.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RegisterAccount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Graphic__RegisterAccount[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Graphic__RegisterAccount[] = {
    "Graphic::RegisterAccount\0\0checkStatus()\0"
};

const QMetaObject Graphic::RegisterAccount::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Graphic__RegisterAccount,
      qt_meta_data_Graphic__RegisterAccount, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Graphic::RegisterAccount::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Graphic::RegisterAccount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Graphic::RegisterAccount::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Graphic__RegisterAccount))
        return static_cast<void*>(const_cast< RegisterAccount*>(this));
    if (!strcmp(_clname, "InterfaceRegisterAccount"))
        return static_cast< InterfaceRegisterAccount*>(const_cast< RegisterAccount*>(this));
    return QDialog::qt_metacast(_clname);
}

int Graphic::RegisterAccount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkStatus(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
