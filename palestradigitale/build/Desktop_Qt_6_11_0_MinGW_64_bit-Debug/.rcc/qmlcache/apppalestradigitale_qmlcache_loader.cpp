#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_palestradigitale_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_palestradigitale_qml_LoginPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_palestradigitale_qml_ClientDashboard_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_palestradigitale_qml_AdminDashboard_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_palestradigitale_qml_WorkoutProgramsPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_palestradigitale_qml_SessionsPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_palestradigitale_qml_NutritionPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_palestradigitale_qml_WorkoutProgramDetailPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/palestradigitale/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_palestradigitale_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/palestradigitale/qml/LoginPage.qml"), &QmlCacheGeneratedCode::_qt_qml_palestradigitale_qml_LoginPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/palestradigitale/qml/ClientDashboard.qml"), &QmlCacheGeneratedCode::_qt_qml_palestradigitale_qml_ClientDashboard_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/palestradigitale/qml/AdminDashboard.qml"), &QmlCacheGeneratedCode::_qt_qml_palestradigitale_qml_AdminDashboard_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/palestradigitale/qml/WorkoutProgramsPage.qml"), &QmlCacheGeneratedCode::_qt_qml_palestradigitale_qml_WorkoutProgramsPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/palestradigitale/qml/SessionsPage.qml"), &QmlCacheGeneratedCode::_qt_qml_palestradigitale_qml_SessionsPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/palestradigitale/qml/NutritionPage.qml"), &QmlCacheGeneratedCode::_qt_qml_palestradigitale_qml_NutritionPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/palestradigitale/qml/WorkoutProgramDetailPage.qml"), &QmlCacheGeneratedCode::_qt_qml_palestradigitale_qml_WorkoutProgramDetailPage_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_apppalestradigitale)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_apppalestradigitale))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_apppalestradigitale)() {
    return 1;
}
