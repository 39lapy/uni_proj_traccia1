#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlQuery>
#include <QSqlRecord>
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


    dbManager.init();
    dbManager.seedTestData();

    QVariantList programs = dbManager.getWorkoutPrograms();
    qDebug() << "Programs count:" << programs.count();



    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("db", &dbManager); // ← here

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("palestradigitale", "Main");
    return QCoreApplication::exec();

    // Print all tables
    QStringList tables = {"users", "workout_programs", "sessions",
                          "assignments", "nutrition_plans", "nutrition_tips", "feedback"};

    for (const QString &table : tables) {
        qDebug() << "\n=== TABLE:" << table << "===";
        QSqlQuery query("SELECT * FROM " + table);
        QSqlRecord rec = query.record();

        // Print column names
        QStringList cols;
        for (int i = 0; i < rec.count(); i++)
            cols << rec.fieldName(i);
        qDebug() << cols.join(" | ");

        // Print rows
        while (query.next()) {
            QStringList row;
            for (int i = 0; i < rec.count(); i++)
                row << query.value(i).toString();
            qDebug() << row.join(" | ");
        }
    }

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("palestradigitale", "Main");
    return QCoreApplication::exec();

    QObject::connect(&app, &QGuiApplication::aboutToQuit, [&dbManager]() {
        dbManager.closeLog();
    });
}