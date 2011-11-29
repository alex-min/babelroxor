/****************************************************************************
** Meta object code from reading C++ file 'DockWidgetContent.h'
**
** Created: Tue 29. Nov 12:58:22 2011
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
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x0a,
      41,   27,   27,   27, 0x0a,
      66,   57,   27,   27, 0x0a,
      97,   90,   27,   27, 0x0a,
     115,   27,   27,   27, 0x0a,
     135,  130,   27,   27, 0x0a,
     157,   90,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Graphic__DockWidgetContent[] = {
    "Graphic::DockWidgetContent\0\0addContact()\0"
    "removeContact()\0finished\0"
    "closeContactDialog(int)\0status\0"
    "updateStatus(int)\0chooseAvatar()\0name\0"
    "updateAvatar(QString)\0manageCall(int)\0"
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
        case 0: addContact(); break;
        case 1: removeContact(); break;
        case 2: closeContactDialog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: updateStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: chooseAvatar(); break;
        case 5: updateAvatar((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: manageCall((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
