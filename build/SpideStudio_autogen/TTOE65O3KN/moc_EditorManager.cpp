/****************************************************************************
** Meta object code from reading C++ file 'EditorManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/modules/editor/EditorManager.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditorManager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_Spide__Modules__Editor__EditorManager_t {
    uint offsetsAndSizes[24];
    char stringdata0[38];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[4];
    char stringdata5[10];
    char stringdata6[9];
    char stringdata7[9];
    char stringdata8[6];
    char stringdata9[20];
    char stringdata10[30];
    char stringdata11[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Spide__Modules__Editor__EditorManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Spide__Modules__Editor__EditorManager_t qt_meta_stringdata_Spide__Modules__Editor__EditorManager = {
    {
        QT_MOC_LITERAL(0, 37),  // "Spide::Modules::Editor::Edito..."
        QT_MOC_LITERAL(38, 13),  // "cursorChanged"
        QT_MOC_LITERAL(52, 0),  // ""
        QT_MOC_LITERAL(53, 4),  // "line"
        QT_MOC_LITERAL(58, 3),  // "col"
        QT_MOC_LITERAL(62, 9),  // "fileSaved"
        QT_MOC_LITERAL(72, 8),  // "filePath"
        QT_MOC_LITERAL(81, 8),  // "closeTab"
        QT_MOC_LITERAL(90, 5),  // "index"
        QT_MOC_LITERAL(96, 19),  // "onCurrentTabChanged"
        QT_MOC_LITERAL(116, 29),  // "onDocumentModificationChanged"
        QT_MOC_LITERAL(146, 8)   // "modified"
    },
    "Spide::Modules::Editor::EditorManager",
    "cursorChanged",
    "",
    "line",
    "col",
    "fileSaved",
    "filePath",
    "closeTab",
    "index",
    "onCurrentTabChanged",
    "onDocumentModificationChanged",
    "modified"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Spide__Modules__Editor__EditorManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   44,    2, 0x06,    1 /* Public */,
       5,    1,   49,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   52,    2, 0x0a,    6 /* Public */,
       9,    1,   55,    2, 0x08,    8 /* Private */,
      10,    1,   58,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Bool,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject Spide::Modules::Editor::EditorManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QTabWidget::staticMetaObject>(),
    qt_meta_stringdata_Spide__Modules__Editor__EditorManager.offsetsAndSizes,
    qt_meta_data_Spide__Modules__Editor__EditorManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Spide__Modules__Editor__EditorManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<EditorManager, std::true_type>,
        // method 'cursorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fileSaved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'closeTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onCurrentTabChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onDocumentModificationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void Spide::Modules::Editor::EditorManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EditorManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->cursorChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->fileSaved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->closeTab((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->onCurrentTabChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->onDocumentModificationChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EditorManager::*)(int , int );
            if (_t _q_method = &EditorManager::cursorChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EditorManager::*)(const QString & );
            if (_t _q_method = &EditorManager::fileSaved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *Spide::Modules::Editor::EditorManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Spide::Modules::Editor::EditorManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Spide__Modules__Editor__EditorManager.stringdata0))
        return static_cast<void*>(this);
    return QTabWidget::qt_metacast(_clname);
}

int Spide::Modules::Editor::EditorManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Spide::Modules::Editor::EditorManager::cursorChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Spide::Modules::Editor::EditorManager::fileSaved(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
