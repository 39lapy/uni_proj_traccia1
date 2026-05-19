/****************************************************************************
** Meta object code from reading C++ file 'dbmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../dbmanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN9DbManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto DbManager::qt_create_metaobjectdata<qt_meta_tag_ZN9DbManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DbManager",
        "login",
        "",
        "email",
        "password",
        "registerUser",
        "firstName",
        "lastName",
        "userType",
        "logout",
        "currentUserType",
        "currentUserId",
        "currentUserName",
        "getWorkoutPrograms",
        "QVariantList",
        "getWorkoutProgramsByDifficulty",
        "difficulty",
        "getWorkoutProgramsByGoal",
        "goal",
        "getSessions",
        "userId",
        "logSession",
        "programId",
        "dateTime",
        "durationMinutes",
        "getNutritionPlans",
        "getNutritionTips",
        "addFeedback",
        "planId",
        "rating",
        "comment"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'login'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
        // Method 'registerUser'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &, const QString &, const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 6 }, { QMetaType::QString, 7 }, { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
            { QMetaType::QString, 8 },
        }}),
        // Method 'logout'
        QtMocHelpers::MethodData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'currentUserType'
        QtMocHelpers::MethodData<QString() const>(10, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'currentUserId'
        QtMocHelpers::MethodData<int() const>(11, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'currentUserName'
        QtMocHelpers::MethodData<QString() const>(12, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'getWorkoutPrograms'
        QtMocHelpers::MethodData<QVariantList()>(13, 2, QMC::AccessPublic, 0x80000000 | 14),
        // Method 'getWorkoutProgramsByDifficulty'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(15, 2, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::QString, 16 },
        }}),
        // Method 'getWorkoutProgramsByGoal'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(17, 2, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'getSessions'
        QtMocHelpers::MethodData<QVariantList(int)>(19, 2, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::Int, 20 },
        }}),
        // Method 'logSession'
        QtMocHelpers::MethodData<bool(int, int, const QString &, int)>(21, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 20 }, { QMetaType::Int, 22 }, { QMetaType::QString, 23 }, { QMetaType::Int, 24 },
        }}),
        // Method 'getNutritionPlans'
        QtMocHelpers::MethodData<QVariantList()>(25, 2, QMC::AccessPublic, 0x80000000 | 14),
        // Method 'getNutritionTips'
        QtMocHelpers::MethodData<QVariantList(int)>(26, 2, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::Int, 20 },
        }}),
        // Method 'addFeedback'
        QtMocHelpers::MethodData<bool(int, int, int, int, const QString &)>(27, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 20 }, { QMetaType::Int, 22 }, { QMetaType::Int, 28 }, { QMetaType::Int, 29 },
            { QMetaType::QString, 30 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DbManager, qt_meta_tag_ZN9DbManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DbManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9DbManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9DbManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9DbManagerE_t>.metaTypes,
    nullptr
} };

void DbManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DbManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = _t->login((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->registerUser((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->logout(); break;
        case 3: { QString _r = _t->currentUserType();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { int _r = _t->currentUserId();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->currentUserName();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 6: { QVariantList _r = _t->getWorkoutPrograms();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantList _r = _t->getWorkoutProgramsByDifficulty((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantList _r = _t->getWorkoutProgramsByGoal((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantList _r = _t->getSessions((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->logSession((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantList _r = _t->getNutritionPlans();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantList _r = _t->getNutritionTips((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->addFeedback((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *DbManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DbManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9DbManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DbManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
