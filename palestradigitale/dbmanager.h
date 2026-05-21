#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class DbManager : public QObject {
    Q_OBJECT
public:
    explicit DbManager(QObject *parent = nullptr);

    bool init();
    void seedTestData();
    void closeLog();

    Q_INVOKABLE bool login(const QString &email, const QString &password);
    Q_INVOKABLE bool registerUser(const QString &firstName, const QString &lastName,
                                  const QString &email, const QString &password,
                                  const QString &userType);
    Q_INVOKABLE void logout();

    Q_INVOKABLE QString currentUserType() const;
    Q_INVOKABLE int currentUserId() const;
    Q_INVOKABLE QString currentUserName() const;

    Q_INVOKABLE QVariantList getWorkoutPrograms();
    Q_INVOKABLE QVariantList getWorkoutProgramsByDifficulty(const QString &difficulty);
    Q_INVOKABLE QVariantList getWorkoutProgramsByGoal(const QString &goal);

    Q_INVOKABLE QVariantList getSessions(int userId);
    Q_INVOKABLE bool logSession(int userId, int programId, const QString &dateTime, int durationMinutes);

    Q_INVOKABLE QVariantList getNutritionPlans();
    Q_INVOKABLE QVariantList getNutritionTips(int userId);

    Q_INVOKABLE QVariantList getAllUsers();
    Q_INVOKABLE bool deleteUser(int userId);
    Q_INVOKABLE QVariantList getClients();
    Q_INVOKABLE QVariantList getTrainers();
    Q_INVOKABLE bool assignTrainer(int trainerId, int clientId, const QString &startDate);
    Q_INVOKABLE QVariantList getAssignments();

    Q_INVOKABLE bool addWorkoutProgram(const QString &title, const QString &goal,
                                       const QString &difficulty, int durationWeeks,
                                       const QString &description);
    Q_INVOKABLE bool deleteWorkoutProgram(int programId);
    Q_INVOKABLE bool updateWorkoutProgram(int programId, const QString &title, const QString &goal,
                                          const QString &difficulty, int durationWeeks,
                                          const QString &description);

    Q_INVOKABLE bool addNutritionPlan(const QString &title, const QString &description);
    Q_INVOKABLE bool deleteNutritionPlan(int planId);
    Q_INVOKABLE bool addNutritionTip(int planId, int userId, const QString &date, const QString &content);
    Q_INVOKABLE bool deleteNutritionTip(int tipId);

    Q_INVOKABLE QVariantList getUserProgress(int userId);
    Q_INVOKABLE QVariantList getFeedbackByUser(int userId);

    Q_INVOKABLE QString generateRegistrationCode(const QString &role);
    Q_INVOKABLE bool validateRegistrationCode(const QString &code, const QString &role);
    Q_INVOKABLE bool markCodeAsUsed(const QString &code);
    Q_INVOKABLE QVariantList getRegistrationCodes();

    Q_INVOKABLE bool addFeedback(int userId, int programId, int planId, int rating, const QString &comment);

private:
    int m_currentUserId = -1;
    QString m_currentUserType;
    QString m_currentUserName;
    QFile m_logFile;

    void logDbChange(const QString &operation, const QString &table, const QString &details);
};

#endif // DBMANAGER_H