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
        "getNutritionTipsByPlan",
        "QVariantList",
        "",
        "planId",
        "userId",
        "login",
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
        "getWorkoutProgramsByDifficulty",
        "difficulty",
        "getWorkoutProgramsByGoal",
        "goal",
        "getSessions",
        "logSession",
        "programId",
        "dateTime",
        "durationMinutes",
        "logDetailedSession",
        "results",
        "getNutritionPlans",
        "getNutritionTips",
        "getAllUsers",
        "deleteUser",
        "getClients",
        "getTrainers",
        "assignTrainer",
        "trainerId",
        "clientId",
        "startDate",
        "getAssignments",
        "addWorkoutProgram",
        "title",
        "durationWeeks",
        "description",
        "addWorkoutProgramWithExercises",
        "exercises",
        "deleteWorkoutProgram",
        "updateWorkoutProgram",
        "getAllExercises",
        "getProgramExercises",
        "getSessionResults",
        "sessionId",
        "addNutritionPlan",
        "deleteNutritionPlan",
        "addNutritionTip",
        "date",
        "content",
        "deleteNutritionTip",
        "tipId",
        "getUserProgress",
        "getFeedbackByUser",
        "generateRegistrationCode",
        "role",
        "validateRegistrationCode",
        "code",
        "markCodeAsUsed",
        "getRegistrationCodes",
        "getGoals",
        "addFeedback",
        "rating",
        "comment"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'getNutritionTipsByPlan'
        QtMocHelpers::MethodData<QVariantList(int, int)>(1, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::Int, 4 }, { QMetaType::Int, 5 },
        }}),
        // Method 'login'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(6, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 8 },
        }}),
        // Method 'registerUser'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &, const QString &, const QString &)>(9, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 10 }, { QMetaType::QString, 11 }, { QMetaType::QString, 7 }, { QMetaType::QString, 8 },
            { QMetaType::QString, 12 },
        }}),
        // Method 'logout'
        QtMocHelpers::MethodData<void()>(13, 3, QMC::AccessPublic, QMetaType::Void),
        // Method 'currentUserType'
        QtMocHelpers::MethodData<QString() const>(14, 3, QMC::AccessPublic, QMetaType::QString),
        // Method 'currentUserId'
        QtMocHelpers::MethodData<int() const>(15, 3, QMC::AccessPublic, QMetaType::Int),
        // Method 'currentUserName'
        QtMocHelpers::MethodData<QString() const>(16, 3, QMC::AccessPublic, QMetaType::QString),
        // Method 'getWorkoutPrograms'
        QtMocHelpers::MethodData<QVariantList()>(17, 3, QMC::AccessPublic, 0x80000000 | 2),
        // Method 'getWorkoutProgramsByDifficulty'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(18, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::QString, 19 },
        }}),
        // Method 'getWorkoutProgramsByGoal'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(20, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::QString, 21 },
        }}),
        // Method 'getSessions'
        QtMocHelpers::MethodData<QVariantList(int)>(22, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'logSession'
        QtMocHelpers::MethodData<bool(int, int, const QString &, int)>(23, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 5 }, { QMetaType::Int, 24 }, { QMetaType::QString, 25 }, { QMetaType::Int, 26 },
        }}),
        // Method 'logDetailedSession'
        QtMocHelpers::MethodData<bool(int, int, const QString &, int, const QVariantList &)>(27, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 5 }, { QMetaType::Int, 24 }, { QMetaType::QString, 25 }, { QMetaType::Int, 26 },
            { 0x80000000 | 2, 28 },
        }}),
        // Method 'getNutritionPlans'
        QtMocHelpers::MethodData<QVariantList()>(29, 3, QMC::AccessPublic, 0x80000000 | 2),
        // Method 'getNutritionTips'
        QtMocHelpers::MethodData<QVariantList(int)>(30, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'getAllUsers'
        QtMocHelpers::MethodData<QVariantList()>(31, 3, QMC::AccessPublic, 0x80000000 | 2),
        // Method 'deleteUser'
        QtMocHelpers::MethodData<bool(int)>(32, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'getClients'
        QtMocHelpers::MethodData<QVariantList()>(33, 3, QMC::AccessPublic, 0x80000000 | 2),
        // Method 'getTrainers'
        QtMocHelpers::MethodData<QVariantList()>(34, 3, QMC::AccessPublic, 0x80000000 | 2),
        // Method 'assignTrainer'
        QtMocHelpers::MethodData<bool(int, int, const QString &)>(35, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 36 }, { QMetaType::Int, 37 }, { QMetaType::QString, 38 },
        }}),
        // Method 'getAssignments'
        QtMocHelpers::MethodData<QVariantList()>(39, 3, QMC::AccessPublic, 0x80000000 | 2),
        // Method 'addWorkoutProgram'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &, int, const QString &)>(40, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 41 }, { QMetaType::QString, 21 }, { QMetaType::QString, 19 }, { QMetaType::Int, 42 },
            { QMetaType::QString, 43 },
        }}),
        // Method 'addWorkoutProgramWithExercises'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &, int, const QString &, const QVariantList &)>(44, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 41 }, { QMetaType::QString, 21 }, { QMetaType::QString, 19 }, { QMetaType::Int, 42 },
            { QMetaType::QString, 43 }, { 0x80000000 | 2, 45 },
        }}),
        // Method 'deleteWorkoutProgram'
        QtMocHelpers::MethodData<bool(int)>(46, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 24 },
        }}),
        // Method 'updateWorkoutProgram'
        QtMocHelpers::MethodData<bool(int, const QString &, const QString &, const QString &, int, const QString &)>(47, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 24 }, { QMetaType::QString, 41 }, { QMetaType::QString, 21 }, { QMetaType::QString, 19 },
            { QMetaType::Int, 42 }, { QMetaType::QString, 43 },
        }}),
        // Method 'getAllExercises'
        QtMocHelpers::MethodData<QVariantList()>(48, 3, QMC::AccessPublic, 0x80000000 | 2),
        // Method 'getProgramExercises'
        QtMocHelpers::MethodData<QVariantList(int)>(49, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::Int, 24 },
        }}),
        // Method 'getSessionResults'
        QtMocHelpers::MethodData<QVariantList(int)>(50, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::Int, 51 },
        }}),
        // Method 'addNutritionPlan'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(52, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 41 }, { QMetaType::QString, 43 },
        }}),
        // Method 'deleteNutritionPlan'
        QtMocHelpers::MethodData<bool(int)>(53, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 4 },
        }}),
        // Method 'addNutritionTip'
        QtMocHelpers::MethodData<bool(int, int, const QString &, const QString &)>(54, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 4 }, { QMetaType::Int, 5 }, { QMetaType::QString, 55 }, { QMetaType::QString, 56 },
        }}),
        // Method 'deleteNutritionTip'
        QtMocHelpers::MethodData<bool(int)>(57, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 58 },
        }}),
        // Method 'getUserProgress'
        QtMocHelpers::MethodData<QVariantList(int)>(59, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'getFeedbackByUser'
        QtMocHelpers::MethodData<QVariantList(int)>(60, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'generateRegistrationCode'
        QtMocHelpers::MethodData<QString(const QString &)>(61, 3, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 62 },
        }}),
        // Method 'validateRegistrationCode'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(63, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 64 }, { QMetaType::QString, 62 },
        }}),
        // Method 'markCodeAsUsed'
        QtMocHelpers::MethodData<bool(const QString &)>(65, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 64 },
        }}),
        // Method 'getRegistrationCodes'
        QtMocHelpers::MethodData<QVariantList()>(66, 3, QMC::AccessPublic, 0x80000000 | 2),
        // Method 'getGoals'
        QtMocHelpers::MethodData<QStringList()>(67, 3, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'addFeedback'
        QtMocHelpers::MethodData<bool(int, int, int, int, const QString &)>(68, 3, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 5 }, { QMetaType::Int, 24 }, { QMetaType::Int, 4 }, { QMetaType::Int, 69 },
            { QMetaType::QString, 70 },
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
        case 0: { QVariantList _r = _t->getNutritionTipsByPlan((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->login((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->registerUser((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->logout(); break;
        case 4: { QString _r = _t->currentUserType();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->currentUserId();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 6: { QString _r = _t->currentUserName();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantList _r = _t->getWorkoutPrograms();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantList _r = _t->getWorkoutProgramsByDifficulty((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantList _r = _t->getWorkoutProgramsByGoal((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->getSessions((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->logSession((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->logDetailedSession((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QVariantList>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { QVariantList _r = _t->getNutritionPlans();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 14: { QVariantList _r = _t->getNutritionTips((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 15: { QVariantList _r = _t->getAllUsers();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->deleteUser((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 17: { QVariantList _r = _t->getClients();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantList _r = _t->getTrainers();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->assignTrainer((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { QVariantList _r = _t->getAssignments();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 21: { bool _r = _t->addWorkoutProgram((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 22: { bool _r = _t->addWorkoutProgramWithExercises((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QVariantList>>(_a[6])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 23: { bool _r = _t->deleteWorkoutProgram((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 24: { bool _r = _t->updateWorkoutProgram((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[6])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 25: { QVariantList _r = _t->getAllExercises();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 26: { QVariantList _r = _t->getProgramExercises((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 27: { QVariantList _r = _t->getSessionResults((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 28: { bool _r = _t->addNutritionPlan((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 29: { bool _r = _t->deleteNutritionPlan((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 30: { bool _r = _t->addNutritionTip((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 31: { bool _r = _t->deleteNutritionTip((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 32: { QVariantList _r = _t->getUserProgress((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 33: { QVariantList _r = _t->getFeedbackByUser((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 34: { QString _r = _t->generateRegistrationCode((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 35: { bool _r = _t->validateRegistrationCode((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 36: { bool _r = _t->markCodeAsUsed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 37: { QVariantList _r = _t->getRegistrationCodes();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 38: { QStringList _r = _t->getGoals();
            if (_a[0]) *reinterpret_cast<QStringList*>(_a[0]) = std::move(_r); }  break;
        case 39: { bool _r = _t->addFeedback((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])));
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
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 40;
    }
    return _id;
}
QT_WARNING_POP
