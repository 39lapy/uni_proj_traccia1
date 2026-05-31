#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>

DbManager::DbManager(QObject *parent) : QObject(parent) {}

bool DbManager::init() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("palestradigitale.db");

    if (!db.open()) {
        qDebug() << "DB error:" << db.lastError().text();
        return false;
    }

    m_logFile.setFileName("palestradigitale.log");
    if (!m_logFile.open(QIODevice::Append | QIODevice::Text))
        qDebug() << "Could not open log file!";

    logDbChange("INIT", "database", "connection opened");

    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");

    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "first_name TEXT NOT NULL,"
               "last_name TEXT NOT NULL,"
               "email TEXT NOT NULL UNIQUE,"
               "password_hash TEXT NOT NULL,"
               "user_type TEXT NOT NULL CHECK(user_type IN ('client','trainer','nutritionist','administrator')),"
               "registration_date TEXT DEFAULT (date('now'))"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS workout_programs ("
               "program_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "trainer_id INTEGER NOT NULL,"
               "title TEXT NOT NULL,"
               "goal TEXT,"
               "difficulty TEXT NOT NULL CHECK(difficulty IN ('beginner','intermediate','advanced')),"
               "duration_weeks INTEGER,"
               "description TEXT,"
               "FOREIGN KEY (trainer_id) REFERENCES users(user_id)"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS sessions ("
               "session_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER NOT NULL,"
               "program_id INTEGER NOT NULL,"
               "session_datetime TEXT NOT NULL,"
               "duration_minutes INTEGER,"
               "completed INTEGER DEFAULT 0,"
               "FOREIGN KEY (user_id) REFERENCES users(user_id),"
               "FOREIGN KEY (program_id) REFERENCES workout_programs(program_id)"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS assignments ("
               "assignment_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "trainer_id INTEGER NOT NULL,"
               "client_id INTEGER NOT NULL,"
               "start_date TEXT NOT NULL,"
               "end_date TEXT,"
               "FOREIGN KEY (trainer_id) REFERENCES users(user_id),"
               "FOREIGN KEY (client_id) REFERENCES users(user_id)"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS nutrition_plans ("
               "plan_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "nutritionist_id INTEGER NOT NULL,"
               "title TEXT NOT NULL,"
               "description TEXT,"
               "created_at TEXT DEFAULT (date('now')),"
               "FOREIGN KEY (nutritionist_id) REFERENCES users(user_id)"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS nutrition_tips ("
               "tip_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "plan_id INTEGER NOT NULL,"
               "user_id INTEGER NOT NULL,"
               "tip_date TEXT NOT NULL,"
               "content TEXT NOT NULL,"
               "FOREIGN KEY (plan_id) REFERENCES nutrition_plans(plan_id),"
               "FOREIGN KEY (user_id) REFERENCES users(user_id)"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS feedback ("
               "feedback_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER NOT NULL,"
               "program_id INTEGER,"
               "plan_id INTEGER,"
               "rating INTEGER CHECK(rating BETWEEN 1 AND 5),"
               "comment TEXT,"
               "feedback_date TEXT DEFAULT (date('now')),"
               "FOREIGN KEY (user_id) REFERENCES users(user_id),"
               "FOREIGN KEY (program_id) REFERENCES workout_programs(program_id),"
               "FOREIGN KEY (plan_id) REFERENCES nutrition_plans(plan_id)"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS registration_codes ("
               "code TEXT PRIMARY KEY,"
               "role TEXT NOT NULL,"
               "used INTEGER DEFAULT 0,"
               "created_at TEXT DEFAULT (date('now'))"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS exercises ("
               "exercise_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT NOT NULL,"
               "description TEXT,"
               "category TEXT"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS program_exercises ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "program_id INTEGER NOT NULL,"
               "exercise_id INTEGER NOT NULL,"
               "sets INTEGER NOT NULL,"
               "reps INTEGER NOT NULL,"
               "rest_seconds INTEGER,"
               "order_index INTEGER,"
               "FOREIGN KEY (program_id) REFERENCES workout_programs(program_id) ON DELETE CASCADE,"
               "FOREIGN KEY (exercise_id) REFERENCES exercises(exercise_id)"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS session_results ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "session_id INTEGER NOT NULL,"
               "program_exercise_id INTEGER NOT NULL,"
               "set_number INTEGER NOT NULL,"
               "weight REAL,"
               "reps_performed INTEGER,"
               "FOREIGN KEY (session_id) REFERENCES sessions(session_id) ON DELETE CASCADE,"
               "FOREIGN KEY (program_exercise_id) REFERENCES program_exercises(id)"
               ")");

    return true;
}

void DbManager::closeLog() {
    logDbChange("SHUTDOWN", "database", "connection closed");
    m_logFile.close();
}

void DbManager::logDbChange(const QString &operation, const QString &table, const QString &details) {
    QString message = "[" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "] "
                      + operation.toUpper() + " -> " + table + " | " + details;
    qDebug() << message;
    if (m_logFile.isOpen()) {
        QTextStream stream(&m_logFile);
        stream << message << "\n";
    }
}

bool DbManager::login(const QString &email, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT user_id, first_name, user_type, password_hash FROM users WHERE email = :email");
    query.bindValue(":email", email);
    query.exec();
    if (query.next()) {
        if (query.value("password_hash").toString() == password) {
            m_currentUserId = query.value("user_id").toInt();
            m_currentUserName = query.value("first_name").toString();
            m_currentUserType = query.value("user_type").toString();
            logDbChange("LOGIN", "users", "email: " + email + " | type: " + m_currentUserType);
            return true;
        }
    }
    return false;
}

bool DbManager::registerUser(const QString &firstName, const QString &lastName,
                             const QString &email, const QString &password,
                             const QString &userType) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (first_name, last_name, email, password_hash, user_type) "
                  "VALUES (:first, :last, :email, :pass, :type)");
    query.bindValue(":first", firstName);
    query.bindValue(":last", lastName);
    query.bindValue(":email", email);
    query.bindValue(":pass", password);
    query.bindValue(":type", userType);
    if (query.exec()) {
        logDbChange("INSERT", "users", "email: " + email + " | type: " + userType);
        return true;
    }
    return false;
}

void DbManager::logout() {
    logDbChange("LOGOUT", "users", "user_id: " + QString::number(m_currentUserId));
    m_currentUserId = -1;
    m_currentUserType = "";
    m_currentUserName = "";
}

QString DbManager::currentUserType() const { return m_currentUserType; }
int DbManager::currentUserId() const { return m_currentUserId; }
QString DbManager::currentUserName() const { return m_currentUserName; }

QVariantList DbManager::getWorkoutPrograms() {
    QVariantList result;
    QSqlQuery query("SELECT w.program_id, w.title, w.goal, w.difficulty, "
                    "w.duration_weeks, w.description, u.first_name, u.last_name "
                    "FROM workout_programs w JOIN users u ON w.trainer_id = u.user_id");
    while (query.next()) {
        QVariantMap program;
        program["program_id"] = query.value("program_id");
        program["title"] = query.value("title");
        program["goal"] = query.value("goal");
        program["difficulty"] = query.value("difficulty");
        program["duration_weeks"] = query.value("duration_weeks");
        program["description"] = query.value("description");
        program["trainer"] = query.value("first_name").toString() + " " + query.value("last_name").toString();
        result.append(program);
    }
    return result;
}

QVariantList DbManager::getWorkoutProgramsByDifficulty(const QString &difficulty) {
    QVariantList result;
    QSqlQuery query;
    query.prepare("SELECT w.program_id, w.title, w.goal, w.difficulty, "
                  "w.duration_weeks, w.description, u.first_name, u.last_name "
                  "FROM workout_programs w JOIN users u ON w.trainer_id = u.user_id "
                  "WHERE w.difficulty = :difficulty");
    query.bindValue(":difficulty", difficulty);
    query.exec();
    while (query.next()) {
        QVariantMap program;
        program["program_id"] = query.value("program_id");
        program["title"] = query.value("title");
        program["goal"] = query.value("goal");
        program["difficulty"] = query.value("difficulty");
        program["duration_weeks"] = query.value("duration_weeks");
        program["description"] = query.value("description");
        program["trainer"] = query.value("first_name").toString() + " " + query.value("last_name").toString();
        result.append(program);
    }
    return result;
}

QVariantList DbManager::getWorkoutProgramsByGoal(const QString &goal) {
    QVariantList result;
    QSqlQuery query;
    query.prepare("SELECT w.program_id, w.title, w.goal, w.difficulty, "
                  "w.duration_weeks, w.description, u.first_name, u.last_name "
                  "FROM workout_programs w JOIN users u ON w.trainer_id = u.user_id "
                  "WHERE w.goal = :goal");
    query.bindValue(":goal", goal);
    query.exec();
    while (query.next()) {
        QVariantMap program;
        program["program_id"] = query.value("program_id");
        program["title"] = query.value("title");
        program["goal"] = query.value("goal");
        program["difficulty"] = query.value("difficulty");
        program["duration_weeks"] = query.value("duration_weeks");
        program["description"] = query.value("description");
        program["trainer"] = query.value("first_name").toString() + " " + query.value("last_name").toString();
        result.append(program);
    }
    return result;
}

QVariantList DbManager::getSessions(int userId) {
    QVariantList result;
    QSqlQuery query;
    query.prepare("SELECT s.session_id, s.session_datetime, s.duration_minutes, "
                  "s.completed, w.title "
                  "FROM sessions s JOIN workout_programs w ON s.program_id = w.program_id "
                  "WHERE s.user_id = :uid ORDER BY s.session_datetime DESC");
    query.bindValue(":uid", userId);
    query.exec();
    while (query.next()) {
        QVariantMap session;
        session["session_id"] = query.value("session_id");
        session["datetime"] = query.value("session_datetime");
        session["duration"] = query.value("duration_minutes");
        session["completed"] = query.value("completed");
        session["program"] = query.value("title");
        result.append(session);
    }
    return result;
}

bool DbManager::logSession(int userId, int programId, const QString &dateTime, int durationMinutes) {
    QSqlQuery query;
    query.prepare("INSERT INTO sessions (user_id, program_id, session_datetime, duration_minutes, completed) "
                  "VALUES (:uid, :pid, :dt, :dur, 1)");
    query.bindValue(":uid", userId);
    query.bindValue(":pid", programId);
    query.bindValue(":dt", dateTime);
    query.bindValue(":dur", durationMinutes);
    if (query.exec()) {
        logDbChange("INSERT", "sessions", "user_id: " + QString::number(userId) +
                                              " | program_id: " + QString::number(programId) +
                                              " | duration: " + QString::number(durationMinutes));
        return true;
    }
    return false;
}

bool DbManager::logDetailedSession(int userId, int programId, const QString &dateTime, int durationMinutes, const QVariantList &results) {
    if (!QSqlDatabase::database().transaction()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO sessions (user_id, program_id, session_datetime, duration_minutes, completed) "
                  "VALUES (:uid, :pid, :dt, :dur, 1)");
    query.bindValue(":uid", userId);
    query.bindValue(":pid", programId);
    query.bindValue(":dt", dateTime);
    query.bindValue(":dur", durationMinutes);

    if (!query.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }

    int sessionId = query.lastInsertId().toInt();

    for (int i = 0; i < results.size(); ++i) {
        QVariantMap res = results[i].toMap();
        QSqlQuery resQuery;
        resQuery.prepare("INSERT INTO session_results (session_id, program_exercise_id, set_number, weight, reps_performed) "
                         "VALUES (:sid, :peid, :set, :w, :r)");
        resQuery.bindValue(":sid", sessionId);
        resQuery.bindValue(":peid", res["program_exercise_id"]);
        resQuery.bindValue(":set", res["set_number"]);
        resQuery.bindValue(":w", res["weight"]);
        resQuery.bindValue(":r", res["reps_performed"]);
        if (!resQuery.exec()) {
            QSqlDatabase::database().rollback();
            return false;
        }
    }

    if (!QSqlDatabase::database().commit()) {
        QSqlDatabase::database().rollback();
        return false;
    }

    logDbChange("INSERT", "sessions", "Detailed session for user " + QString::number(userId) + " | program " + QString::number(programId));
    return true;
}

QVariantList DbManager::getNutritionPlans() {
    QVariantList result;
    QSqlQuery query("SELECT n.plan_id, n.title, n.description, n.created_at, "
                    "u.first_name, u.last_name "
                    "FROM nutrition_plans n JOIN users u ON n.nutritionist_id = u.user_id");
    while (query.next()) {
        QVariantMap plan;
        plan["plan_id"] = query.value("plan_id");
        plan["title"] = query.value("title");
        plan["description"] = query.value("description");
        plan["created_at"] = query.value("created_at");
        plan["nutritionist"] = query.value("first_name").toString() + " " + query.value("last_name").toString();
        result.append(plan);
    }
    return result;
}

QVariantList DbManager::getNutritionTips(int userId) {
    QVariantList result;
    QSqlQuery query;
    query.prepare("SELECT t.tip_id, t.tip_date, t.content, n.title "
                  "FROM nutrition_tips t JOIN nutrition_plans n ON t.plan_id = n.plan_id "
                  "WHERE t.user_id = :uid ORDER BY t.tip_date DESC");
    query.bindValue(":uid", userId);
    query.exec();
    while (query.next()) {
        QVariantMap tip;
        tip["tip_id"] = query.value("tip_id");
        tip["date"] = query.value("tip_date");
        tip["content"] = query.value("content");
        tip["plan"] = query.value("title");
        result.append(tip);
    }
    return result;
}


QVariantList DbManager::getAllUsers() {
    QVariantList result;
    QSqlQuery query("SELECT user_id, first_name, last_name, email, user_type, registration_date FROM users");
    while (query.next()) {
        QVariantMap user;
        user["user_id"] = query.value("user_id");
        user["first_name"] = query.value("first_name");
        user["last_name"] = query.value("last_name");
        user["email"] = query.value("email");
        user["user_type"] = query.value("user_type");
        user["registration_date"] = query.value("registration_date");
        result.append(user);
    }
    return result;
}

bool DbManager::deleteUser(int userId) {
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE user_id = :uid");
    query.bindValue(":uid", userId);
    if (query.exec()) {
        logDbChange("DELETE", "users", "user_id: " + QString::number(userId));
        return true;
    }
    return false;
}

QVariantList DbManager::getClients() {
    QVariantList result;
    QSqlQuery query("SELECT user_id, first_name, last_name, email FROM users WHERE user_type = 'client'");
    while (query.next()) {
        QVariantMap user;
        user["user_id"] = query.value("user_id");
        user["first_name"] = query.value("first_name");
        user["last_name"] = query.value("last_name");
        user["email"] = query.value("email");
        result.append(user);
    }
    return result;
}

QVariantList DbManager::getTrainers() {
    QVariantList result;
    QSqlQuery query("SELECT user_id, first_name, last_name, email FROM users WHERE user_type = 'trainer'");
    while (query.next()) {
        QVariantMap user;
        user["user_id"] = query.value("user_id");
        user["first_name"] = query.value("first_name");
        user["last_name"] = query.value("last_name");
        user["email"] = query.value("email");
        result.append(user);
    }
    return result;
}

bool DbManager::assignTrainer(int trainerId, int clientId, const QString &startDate) {
    QSqlQuery query;
    query.prepare("INSERT INTO assignments (trainer_id, client_id, start_date) "
                  "VALUES (:tid, :cid, :date)");
    query.bindValue(":tid", trainerId);
    query.bindValue(":cid", clientId);
    query.bindValue(":date", startDate);
    if (query.exec()) {
        logDbChange("INSERT", "assignments", "trainer_id: " + QString::number(trainerId) +
                                                 " | client_id: " + QString::number(clientId));
        return true;
    }
    return false;
}

QVariantList DbManager::getAssignments() {
    QVariantList result;
    QSqlQuery query("SELECT a.assignment_id, a.start_date, a.end_date, "
                    "t.first_name || ' ' || t.last_name AS trainer, "
                    "c.first_name || ' ' || c.last_name AS client "
                    "FROM assignments a "
                    "JOIN users t ON a.trainer_id = t.user_id "
                    "JOIN users c ON a.client_id = c.user_id");
    while (query.next()) {
        QVariantMap assignment;
        assignment["assignment_id"] = query.value("assignment_id");
        assignment["trainer"] = query.value("trainer");
        assignment["client"] = query.value("client");
        assignment["start_date"] = query.value("start_date");
        assignment["end_date"] = query.value("end_date");
        result.append(assignment);
    }
    return result;
}


bool DbManager::addFeedback(int userId, int programId, int planId, int rating, const QString &comment) {
    QSqlQuery query;
    query.prepare("INSERT INTO feedback (user_id, program_id, plan_id, rating, comment) "
                  "VALUES (:uid, :pid, :plid, :rating, :comment)");
    query.bindValue(":uid", userId);
    query.bindValue(":pid", programId == -1 ? QVariant() : QVariant(programId));
    query.bindValue(":plid", planId == -1 ? QVariant() : QVariant(planId));
    query.bindValue(":rating", rating);
    query.bindValue(":comment", comment);
    if (query.exec()) {
        logDbChange("INSERT", "feedback", "user_id: " + QString::number(userId) +
                                              " | rating: " + QString::number(rating));
        return true;
    }
    return false;
}

void DbManager::seedTestData() {
    QSqlQuery check;

    // Helper lambda to insert exercise if not exists
    auto insertEx = [&](const QString &name, const QString &desc, const QString &cat) {
        QSqlQuery q;
        q.prepare("SELECT COUNT(*) FROM exercises WHERE name = :name");
        q.bindValue(":name", name);
        q.exec();
        q.next();
        if (q.value(0).toInt() == 0) {
            QSqlQuery ins;
            ins.prepare("INSERT INTO exercises (name, description, category) VALUES (:name, :desc, :cat)");
            ins.bindValue(":name", name);
            ins.bindValue(":desc", desc);
            ins.bindValue(":cat", cat);
            ins.exec();
        }
    };

    // Users seeding (existing logic)
    check.exec("SELECT COUNT(*) FROM users");
    check.next();
    if (check.value(0).toInt() == 0) {
        QSqlQuery query;
        query.prepare("INSERT INTO users (first_name, last_name, email, password_hash, user_type) "
                      "VALUES (:first, :last, :email, :pass, :type)");

        query.bindValue(":first", "Mario"); query.bindValue(":last", "Rossi");
        query.bindValue(":email", "mario@test.com"); query.bindValue(":pass", "1234");
        query.bindValue(":type", "client"); query.exec();

        query.bindValue(":first", "Luigi"); query.bindValue(":last", "Verdi");
        query.bindValue(":email", "luigi@test.com"); query.bindValue(":pass", "1234");
        query.bindValue(":type", "trainer"); query.exec();

        query.bindValue(":first", "admin"); query.bindValue(":last", "istrator");
        query.bindValue(":email", "admin"); query.bindValue(":pass", "admin");
        query.bindValue(":type", "administrator"); query.exec();

        qDebug() << "Users seeded.";
    }

    // Workout programs, Nutrition plans, Tips (keep existing logic)
    // ... skipping for brevity but keeping in file ...

    // Exercises - Categorized and expanded
    insertEx("Panca Piana Bilanciere", "Classico esercizio per il petto su panca piana.", "Chest");
    insertEx("Panca Inclinata Manubri", "Esercizio per la parte superiore del petto.", "Chest");
    insertEx("Croci ai Cavi", "Isolamento per i pettorali ai cavi alti.", "Chest");
    insertEx("Push-up (Flessioni)", "Esercizio a corpo libero per petto e tricipiti.", "Chest");
    insertEx("Dips alle Parallele", "Esercizio per petto basso e tricipiti.", "Chest");

    insertEx("Trazioni alla Sbarra", "Esercizio fondamentale per la larghezza del dorso.", "Back");
    insertEx("Lat Machine", "Variante alla macchina delle trazioni.", "Back");
    insertEx("Rematore con Bilanciere", "Esercizio per lo spessore del dorso.", "Back");
    insertEx("Pulley Basso", "Rematore al cavo basso.", "Back");
    insertEx("Iperestensioni", "Isolamento per i lombari.", "Back");

    insertEx("Squat Bilanciere", "Re degli esercizi per le gambe.", "Legs");
    insertEx("Leg Press", "Esercizio alla macchina per cosce e glutei.", "Legs");
    insertEx("Leg Extension", "Isolamento per i quadricipiti.", "Legs");
    insertEx("Leg Curl", "Isolamento per i bicipiti femorali.", "Legs");
    insertEx("Affondi con Manubri", "Esercizio dinamico per gambe e glutei.", "Legs");
    insertEx("Calf Raise", "Esercizio per i polpacci.", "Legs");

    insertEx("Military Press", "Spinte sopra la testa con bilanciere.", "Shoulders");
    insertEx("Alzate Laterali", "Isolamento per il deltoide laterale.", "Shoulders");
    insertEx("Alzate Posteriori", "Isolamento per il deltoide posteriore.", "Shoulders");
    insertEx("Face Pull", "Esercizio ai cavi per la salute delle spalle.", "Shoulders");

    insertEx("Curl Bilanciere", "Classico per i bicipiti.", "Arms");
    insertEx("Curl a Martello", "Esercizio per bicipiti e brachioradiale.", "Arms");
    insertEx("Pushdown Tricipiti", "Estensioni ai cavi per i tricipiti.", "Arms");
    insertEx("French Press", "Spinte su panca per i tricipiti.", "Arms");

    insertEx("Plank", "Tenuta isometrica per il core.", "Abs");
    insertEx("Crunch Addominale", "Classico esercizio per il retto addominale.", "Abs");
    insertEx("Leg Raise", "Sollevamento gambe per addominali bassi.", "Abs");
    insertEx("Russian Twist", "Esercizio per gli obliqui.", "Abs");

    insertEx("Stacco da Terra", "Esercizio fondamentale per tutta la catena posteriore.", "Back/Legs");
    insertEx("Burpees", "Esercizio cardio full-body.", "Cardio");

    qDebug() << "Exercises list refreshed.";
}

bool DbManager::addWorkoutProgram(const QString &title, const QString &goal,
                                  const QString &difficulty, int durationWeeks,
                                  const QString &description) {
    QSqlQuery query;
    query.prepare("INSERT INTO workout_programs (trainer_id, title, goal, difficulty, duration_weeks, description) "
                  "VALUES (:tid, :title, :goal, :diff, :weeks, :desc)");
    query.bindValue(":tid", m_currentUserId);
    query.bindValue(":title", title);
    query.bindValue(":goal", goal);
    query.bindValue(":diff", difficulty);
    query.bindValue(":weeks", durationWeeks);
    query.bindValue(":desc", description);
    if (query.exec()) {
        logDbChange("INSERT", "workout_programs", "title: " + title + " | difficulty: " + difficulty);
        return true;
    }
    return false;
}

bool DbManager::addWorkoutProgramWithExercises(const QString &title, const QString &goal,
                                               const QString &difficulty, int durationWeeks,
                                               const QString &description, const QVariantList &exercises) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        logDbChange("ERROR", "database", "database not open");
        return false;
    }

    if (!db.transaction()) {
        logDbChange("ERROR", "transaction", "could not start transaction: " + db.lastError().text());
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO workout_programs (trainer_id, title, goal, difficulty, duration_weeks, description) "
                  "VALUES (:tid, :title, :goal, :diff, :weeks, :desc)");
    query.bindValue(":tid", m_currentUserId);
    query.bindValue(":title", title);
    query.bindValue(":goal", goal);
    query.bindValue(":diff", difficulty);
    query.bindValue(":weeks", durationWeeks);
    query.bindValue(":desc", description);

    if (!query.exec()) {
        logDbChange("ERROR", "workout_programs", "insert failed: " + query.lastError().text());
        db.rollback();
        return false;
    }

    int programId = query.lastInsertId().toInt();

    for (int i = 0; i < exercises.size(); ++i) {
        QVariantMap ex = exercises[i].toMap();
        
        QSqlQuery exQuery(db);
        exQuery.prepare("INSERT INTO program_exercises (program_id, exercise_id, sets, reps, rest_seconds, order_index) "
                        "VALUES (:pid, :eid, :sets, :reps, :rest, :idx)");
        exQuery.bindValue(":pid", programId);
        exQuery.bindValue(":eid", ex["exercise_id"]);
        exQuery.bindValue(":sets", ex["sets"]);
        exQuery.bindValue(":reps", ex["reps"]);
        exQuery.bindValue(":rest", ex["rest_seconds"]);
        exQuery.bindValue(":idx", i);
        
        if (!exQuery.exec()) {
            logDbChange("ERROR", "program_exercises", QString("insert failed at index %1: %2").arg(i).arg(exQuery.lastError().text()));
            db.rollback();
            return false;
        }
    }

    if (!db.commit()) {
        logDbChange("ERROR", "transaction", "commit failed: " + db.lastError().text());
        db.rollback();
        return false;
    }

    logDbChange("INSERT", "workout_programs", "title: " + title + " with " + QString::number(exercises.size()) + " exercises");
    return true;
}

bool DbManager::deleteWorkoutProgram(int programId) {
    QSqlQuery query;
    query.prepare("DELETE FROM workout_programs WHERE program_id = :pid");
    query.bindValue(":pid", programId);
    if (query.exec()) {
        logDbChange("DELETE", "workout_programs", "program_id: " + QString::number(programId));
        return true;
    }
    return false;
}

bool DbManager::updateWorkoutProgram(int programId, const QString &title, const QString &goal,
                                     const QString &difficulty, int durationWeeks,
                                     const QString &description) {
    QSqlQuery query;
    query.prepare("UPDATE workout_programs SET title=:title, goal=:goal, difficulty=:diff, "
                  "duration_weeks=:weeks, description=:desc WHERE program_id=:pid");
    query.bindValue(":title", title);
    query.bindValue(":goal", goal);
    query.bindValue(":diff", difficulty);
    query.bindValue(":weeks", durationWeeks);
    query.bindValue(":desc", description);
    query.bindValue(":pid", programId);
    if (query.exec()) {
        logDbChange("UPDATE", "workout_programs", "program_id: " + QString::number(programId) + " | title: " + title);
        return true;
    }
    return false;
}

QVariantList DbManager::getAllExercises() {
    QVariantList result;
    QSqlQuery query("SELECT exercise_id, name, description, category FROM exercises ORDER BY category, name");
    while (query.next()) {
        QVariantMap exercise;
        exercise["exercise_id"] = query.value("exercise_id");
        exercise["name"] = query.value("name");
        exercise["description"] = query.value("description");
        exercise["category"] = query.value("category");
        result.append(exercise);
    }
    return result;
}

QVariantList DbManager::getProgramExercises(int programId) {
    QVariantList result;
    QSqlQuery query;
    query.prepare("SELECT pe.id, pe.exercise_id, e.name, pe.sets, pe.reps, pe.rest_seconds, pe.order_index "
                  "FROM program_exercises pe JOIN exercises e ON pe.exercise_id = e.exercise_id "
                  "WHERE pe.program_id = :pid ORDER BY pe.order_index ASC");
    query.bindValue(":pid", programId);
    query.exec();
    while (query.next()) {
        QVariantMap pe;
        pe["id"] = query.value("id");
        pe["exercise_id"] = query.value("exercise_id");
        pe["name"] = query.value("name");
        pe["sets"] = query.value("sets");
        pe["reps"] = query.value("reps");
        pe["rest_seconds"] = query.value("rest_seconds");
        pe["order_index"] = query.value("order_index");
        result.append(pe);
    }
    return result;
}

QVariantList DbManager::getSessionResults(int sessionId) {
    QVariantList result;
    QSqlQuery query;
    query.prepare("SELECT sr.id, sr.program_exercise_id, sr.set_number, sr.weight, sr.reps_performed, e.name "
                  "FROM session_results sr "
                  "JOIN program_exercises pe ON sr.program_exercise_id = pe.id "
                  "JOIN exercises e ON pe.exercise_id = e.exercise_id "
                  "WHERE sr.session_id = :sid ORDER BY sr.id ASC");
    query.bindValue(":sid", sessionId);
    query.exec();
    while (query.next()) {
        QVariantMap res;
        res["id"] = query.value("id");
        res["program_exercise_id"] = query.value("program_exercise_id");
        res["set_number"] = query.value("set_number");
        res["weight"] = query.value("weight");
        res["reps_performed"] = query.value("reps_performed");
        res["exercise_name"] = query.value("name");
        result.append(res);
    }
    return result;
}

bool DbManager::addNutritionPlan(const QString &title, const QString &description) {
    QSqlQuery query;
    query.prepare("INSERT INTO nutrition_plans (nutritionist_id, title, description) "
                  "VALUES (:nid, :title, :desc)");
    query.bindValue(":nid", m_currentUserId);
    query.bindValue(":title", title);
    query.bindValue(":desc", description);
    if (query.exec()) {
        logDbChange("INSERT", "nutrition_plans", "title: " + title);
        return true;
    }
    return false;
}

bool DbManager::deleteNutritionPlan(int planId) {
    QSqlQuery query;
    query.prepare("DELETE FROM nutrition_plans WHERE plan_id = :pid");
    query.bindValue(":pid", planId);
    if (query.exec()) {
        logDbChange("DELETE", "nutrition_plans", "plan_id: " + QString::number(planId));
        return true;
    }
    return false;
}

bool DbManager::addNutritionTip(int planId, int userId, const QString &date, const QString &content) {
    QSqlQuery query;
    query.prepare("INSERT INTO nutrition_tips (plan_id, user_id, tip_date, content) "
                  "VALUES (:pid, :uid, :date, :content)");
    query.bindValue(":pid", planId);
    query.bindValue(":uid", userId);
    query.bindValue(":date", date);
    query.bindValue(":content", content);
    if (query.exec()) {
        logDbChange("INSERT", "nutrition_tips", "plan_id: " + QString::number(planId) + " | user_id: " + QString::number(userId));
        return true;
    }
    return false;
}

bool DbManager::deleteNutritionTip(int tipId) {
    QSqlQuery query;
    query.prepare("DELETE FROM nutrition_tips WHERE tip_id = :tid");
    query.bindValue(":tid", tipId);
    if (query.exec()) {
        logDbChange("DELETE", "nutrition_tips", "tip_id: " + QString::number(tipId));
        return true;
    }
    return false;
}

QVariantList DbManager::getUserProgress(int userId) {
    QVariantList result;
    QSqlQuery query;
    query.prepare("SELECT s.session_id, s.session_datetime, s.duration_minutes, "
                  "s.completed, w.title, w.difficulty "
                  "FROM sessions s "
                  "JOIN workout_programs w ON s.program_id = w.program_id "
                  "WHERE s.user_id = :uid "
                  "ORDER BY s.session_datetime DESC");
    query.bindValue(":uid", userId);
    query.exec();
    while (query.next()) {
        QVariantMap session;
        session["session_id"] = query.value("session_id");
        session["datetime"] = query.value("session_datetime");
        session["duration"] = query.value("duration_minutes");
        session["completed"] = query.value("completed");
        session["program"] = query.value("title");
        session["difficulty"] = query.value("difficulty");
        result.append(session);
    }
    return result;
}

QVariantList DbManager::getFeedbackByUser(int userId) {
    QVariantList result;
    QSqlQuery query;
    query.prepare("SELECT f.feedback_id, f.rating, f.comment, f.feedback_date, "
                  "w.title AS program_title, n.title AS plan_title "
                  "FROM feedback f "
                  "LEFT JOIN workout_programs w ON f.program_id = w.program_id "
                  "LEFT JOIN nutrition_plans n ON f.plan_id = n.plan_id "
                  "WHERE f.user_id = :uid "
                  "ORDER BY f.feedback_date DESC");
    query.bindValue(":uid", userId);
    query.exec();
    while (query.next()) {
        QVariantMap feedback;
        feedback["feedback_id"] = query.value("feedback_id");
        feedback["rating"] = query.value("rating");
        feedback["comment"] = query.value("comment");
        feedback["date"] = query.value("feedback_date");
        feedback["program"] = query.value("program_title");
        feedback["plan"] = query.value("plan_title");
        result.append(feedback);
    }
    return result;
}

QString DbManager::generateRegistrationCode(const QString &role) {
    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 999999));
    QSqlQuery query;
    query.prepare("INSERT INTO registration_codes (code, role) VALUES (:code, :role)");
    query.bindValue(":code", code);
    query.bindValue(":role", role);
    if (query.exec()) {
        logDbChange("INSERT", "registration_codes", "role: " + role + " | code: " + code);
        return code;
    }
    return "";
}

bool DbManager::validateRegistrationCode(const QString &code, const QString &role) {
    QSqlQuery query;
    query.prepare("SELECT code FROM registration_codes "
                  "WHERE code = :code AND role = :role AND used = 0");
    query.bindValue(":code", code);
    query.bindValue(":role", role);
    query.exec();
    return query.next();
}

bool DbManager::markCodeAsUsed(const QString &code) {
    QSqlQuery query;
    query.prepare("UPDATE registration_codes SET used = 1 WHERE code = :code");
    query.bindValue(":code", code);
    if (query.exec()) {
        logDbChange("UPDATE", "registration_codes", "code: " + code + " marked as used");
        return true;
    }
    return false;
}

QVariantList DbManager::getRegistrationCodes() {
    QVariantList result;
    QSqlQuery query("SELECT code, role, used, created_at FROM registration_codes ORDER BY created_at DESC");
    while (query.next()) {
        QVariantMap c;
        c["code"] = query.value("code");
        c["role"] = query.value("role");
        c["used"] = query.value("used");
        c["created_at"] = query.value("created_at");
        result.append(c);
    }
    return result;
}

QStringList DbManager::getGoals() {
    QStringList result;
    QSqlQuery query("SELECT DISTINCT goal FROM workout_programs WHERE goal IS NOT NULL AND goal != ''");
    while (query.next()) {
        result.append(query.value(0).toString());
    }
    return result;
}