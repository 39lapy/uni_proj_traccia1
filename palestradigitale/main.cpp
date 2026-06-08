#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "dbmanager.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DbManager dbManager;
    if (!dbManager.init()) {
        return -1;
    }

    dbManager.seedTestData();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("db", &dbManager);

    QObject::connect(&app, &QGuiApplication::aboutToQuit, [&dbManager]() {
        dbManager.closeLog();
    });

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("palestradigitale", "Main");
    return QCoreApplication::exec();
}