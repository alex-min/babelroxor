/****************************************************************************
** Meta object code from reading C++ file 'TalkWindow.h'
**
** Created: Wed 30. Nov 10:38:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../babelClient/TalkWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TalkWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Graphic__TalkWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      34,   20,   20,   20, 0x0a,
      57,   52,   20,   20, 0x0a,
      79,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Graphic__TalkWindow[] = {
    "Graphic::TalkWindow\0\0changeBold()\0"
    "changeUnderline()\0name\0changeFamily(QString)\0"
    "sendTextToServer()\0"
};

const QMetaObject Graphic::TalkWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Graphic__TalkWindow,
      qt_meta_data_Graphic__TalkWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Graphic::TalkWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Graphic::TalkWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Graphic::TalkWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Graphic__TalkWindow))
        return static_cast<void*>(const_cast< TalkWindow*>(this));
    if (!strcmp(_clname, "InterfaceTalkWindow"))
        return static_cast< InterfaceTalkWindow*>(const_cast< TalkWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int Graphic::TalkWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeBold(); break;
        case 1: changeUnderline(); break;
        case 2: changeFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: sendTextToServer(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
