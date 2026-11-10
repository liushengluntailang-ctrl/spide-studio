/****************************************************************************
** Meta object code from reading C++ file 'ExplorerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/modules/explorer/ExplorerWidget.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExplorerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_Spide__Modules__Explorer__ExplorerWidget_t {
    uint offsetsAndSizes[22];
    char stringdata0[41];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[20];
    char stringdata5[12];
    char stringdata6[6];
    char stringdata7[14];
    char stringdata8[16];
    char stringdata9[19];
    char stringdata10[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Spide__Modules__Explorer__ExplorerWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Spide__Modules__Explorer__ExplorerWidget_t qt_meta_stringdata_Spide__Modules__Explorer__ExplorerWidget = {
    {
        QT_MOC_LITERAL(0, 40),  // "Spide::Modules::Explorer::Exp..."
        QT_MOC_LITERAL(41, 12),  // "fileSelected"
        QT_MOC_LITERAL(54, 0),  // ""
        QT_MOC_LITERAL(55, 8),  // "filePath"
        QT_MOC_LITERAL(64, 19),  // "onItemDoubleClicked"
        QT_MOC_LITERAL(84, 11),  // "QModelIndex"
        QT_MOC_LITERAL(96, 5),  // "index"
        QT_MOC_LITERAL(102, 13),  // "createNewFile"
        QT_MOC_LITERAL(116, 15),  // "createNewFolder"
        QT_MOC_LITERAL(132, 18),  // "renameSelectedItem"
        QT_MOC_LITERAL(151, 18)   // "deleteSelectedItem"
    },
    "Spide::Modules::Explorer::ExplorerWidget",
    "fileSelected",
    "",
    "filePath",
    "onItemDoubleClicked",
    "QModelIndex",
    "index",
    "createNewFile",
    "createNewFolder",
    "renameSelectedItem",
    "deleteSelectedItem"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Spide__Modules__Explorer__ExplorerWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   53,    2, 0x08,    3 /* Private */,
       7,    0,   56,    2, 0x08,    5 /* Private */,
       8,    0,   57,    2, 0x08,    6 /* Private */,
       9,    0,   58,    2, 0x08,    7 /* Private */,
      10,    0,   59,    2, 0x08,    8 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Spide::Modules::Explorer::ExplorerWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Spide__Modules__Explorer__ExplorerWidget.offsetsAndSizes,
    qt_meta_data_Spide__Modules__Explorer__ExplorerWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Spide__Modules__Explorer__ExplorerWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ExplorerWidget, std::true_type>,
        // method 'fileSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onItemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'createNewFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createNewFolder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'renameSelectedItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteSelectedItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Spide::Modules::Explorer::ExplorerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExplorerWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fileSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->onItemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 2: _t->createNewFile(); break;
        case 3: _t->createNewFolder(); break;
        case 4: _t->renameSelectedItem(); break;
        case 5: _t->deleteSelectedItem(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExplorerWidget::*)(const QString & );
            if (_t _q_method = &ExplorerWidget::fileSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *Spide::Modules::Explorer::ExplorerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Spide::Modules::Explorer::ExplorerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Spide__Modules__Explorer__ExplorerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Spide::Modules::Explorer::ExplorerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Spide::Modules::Explorer::ExplorerWidget::fileSelected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
