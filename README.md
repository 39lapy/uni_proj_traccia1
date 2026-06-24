# Palestra Digitale — Documentazione

> Progetto universitario — Qt6 Quick / SQLite  
> Autori: Gabriele Lapalombella + Angelo Mottola  
> Versione: 1.0

---

## Indice

1. [Manuale Tecnico](#manuale-tecnico)
   - [1. Introduzione](#1-introduzione)
   - [2. Requisiti](#2-requisiti)
   - [3. Architettura del sistema](#3-architettura-del-sistema)
   - [4. Schema del database](#4-schema-del-database)
   - [5. Modulo DbManager](#5-modulo-dbmanager)
   - [6. Navigazione e struttura QML](#6-navigazione-e-struttura-qml)
   - [7. Funzionalità implementate](#7-funzionalità-implementate)
   - [8. Sicurezza](#8-sicurezza)
   - [9. Logging](#9-logging)
   - [10. Dati di test](#10-dati-di-test)
   - [11. Testing](#11-testing)
2. [Manuale Utente](#manuale-utente)
   - [1. Avvio dell'applicazione](#1-avvio-dellapplicazione)
   - [2. Registrazione](#2-registrazione)
   - [3. Login](#3-login)
   - [4. Area Cliente](#4-area-cliente)
   - [5. Area Admin / Trainer / Nutrizionista](#5-area-admin--trainer--nutrizionista)
   - [6. Logout](#6-logout)

---

# Manuale Tecnico

## 1. Introduzione

**Palestra Digitale** è un'applicazione desktop/mobile sviluppata con **Qt6 Quick (QML)** e **C++**, che consente la gestione di una palestra digitale. Il sistema supporta quattro tipologie di utenti: clienti, trainer, nutrizionisti e amministratori, ciascuno con funzionalità dedicate.

Il progetto è stato sviluppato come caso di studio universitario e utilizza:

| Tecnologia | Versione | Scopo |
|---|---|---|
| Qt Quick (QML) | 6.10+ | Interfaccia utente |
| C++ | C++17 | Backend e logica applicativa |
| SQLite (QSQLITE) | 3.x | Persistenza dei dati |
| CMake | 3.16+ | Sistema di build |

---

## 2. Requisiti

### 2.1 Requisiti funzionali

| ID | Requisito | Tipo utente |
|---|---|---|
| RF01 | Registrazione con email e password | Tutti |
| RF02 | Login tramite credenziali | Tutti |
| RF03 | Visualizzazione programmi di allenamento con filtri | Cliente |
| RF04 | Registrazione sessioni di allenamento con dettaglio esercizi | Cliente |
| RF05 | Visualizzazione piani nutrizionali e consigli giornalieri | Cliente |
| RF06 | Rilascio feedback con valutazione a stelle | Cliente |
| RF07 | Creazione e gestione programmi di allenamento | Trainer / Admin |
| RF08 | Creazione e gestione piani nutrizionali e consigli | Nutrizionista / Admin |
| RF09 | Gestione utenti e assegnazione trainer a clienti | Admin |
| RF10 | Monitoraggio progressi dei clienti | Admin / Trainer |
| RF11 | Generazione codici OTP per registrazione ruoli protetti | Solo Admin |
| RF12 | Logout | Tutti |

### 2.2 Requisiti non funzionali

| ID | Requisito |
|---|---|
| RNF01 | Le password devono essere memorizzate come hash SHA-256 |
| RNF02 | Trainer e nutrizionisti possono registrarsi solo con un codice OTP valido |
| RNF03 | Tutte le operazioni sul database devono essere loggate su file |
| RNF04 | Le operazioni multi-step sul database devono essere atomiche (transazioni) |
| RNF05 | L'interfaccia deve funzionare su desktop Windows e Linux |

### 2.3 Requisiti di sistema

- Qt 6.10 o superiore con moduli `Quick` e `Sql`
- CMake 3.16 o superiore
- Compilatore compatibile C++17 (MinGW 64-bit su Windows, GCC su Linux)

---

## 3. Architettura del sistema

Il progetto segue un'architettura **C++ backend / QML frontend** con separazione netta tra logica e presentazione.

```
palestradigitale/
├── main.cpp                  # Entry point: inizializza app, DB, engine QML
├── dbmanager.h               # Interfaccia del backend C++
├── dbmanager.cpp             # Implementazione del backend C++
├── CMakeLists.txt            # Configurazione build
├── Main.qml                  # Root QML: StackView + componenti
└── qml/
    ├── LoginPage.qml
    ├── RegisterPage.qml
    ├── ClientDashboard.qml
    ├── AdminDashboard.qml
    ├── WorkoutProgramsPage.qml
    ├── WorkoutProgramDetailPage.qml
    ├── SessionsPage.qml
    ├── SessionDetailPage.qml
    ├── NutritionPage.qml
    ├── NutritionPlanDetailPage.qml
    ├── ManageUsersPage.qml
    ├── ManageWorkoutProgramsPage.qml
    ├── ManageNutritionPlansPage.qml
    ├── ManageCodesPage.qml
    └── UserProgressPage.qml
```

### Flusso dati

```
QML (UI) 
  └─► db.metodo()          [Q_INVOKABLE via setContextProperty]
        └─► DbManager      [C++ — logica e accesso al DB]
              └─► SQLite   [QSQLITE driver — file locale]
```

`DbManager` è esposto a QML tramite `engine.rootContext()->setContextProperty("db", &dbManager)`, rendendo l'oggetto accessibile globalmente in tutti i file QML come `db`.

---

## 4. Schema del database

Il database SQLite (`palestradigitale.db`) contiene le seguenti tabelle:

### `users`
| Campo | Tipo | Note |
|---|---|---|
| user_id | INTEGER PK | Autoincrement |
| first_name | TEXT | |
| last_name | TEXT | |
| email | TEXT UNIQUE | |
| password_hash | TEXT | SHA-256 |
| user_type | TEXT | `client`, `trainer`, `nutritionist`, `administrator` |
| registration_date | TEXT | Default: data corrente |

### `workout_programs`
| Campo | Tipo | Note |
|---|---|---|
| program_id | INTEGER PK | |
| trainer_id | INTEGER FK | → users |
| title | TEXT | |
| goal | TEXT | es. `weight loss`, `muscle gain` |
| difficulty | TEXT | `beginner`, `intermediate`, `advanced` |
| duration_weeks | INTEGER | |
| description | TEXT | |

### `exercises`
| Campo | Tipo | Note |
|---|---|---|
| exercise_id | INTEGER PK | |
| name | TEXT | |
| description | TEXT | |
| category | TEXT | es. `Chest`, `Back`, `Legs` |

### `program_exercises`
| Campo | Tipo | Note |
|---|---|---|
| id | INTEGER PK | |
| program_id | INTEGER FK | → workout_programs (CASCADE DELETE) |
| exercise_id | INTEGER FK | → exercises |
| sets | INTEGER | |
| reps | INTEGER | |
| rest_seconds | INTEGER | |
| order_index | INTEGER | Ordine dell'esercizio nel programma |

### `sessions`
| Campo | Tipo | Note |
|---|---|---|
| session_id | INTEGER PK | |
| user_id | INTEGER FK | → users |
| program_id | INTEGER FK | → workout_programs |
| session_datetime | TEXT | ISO 8601 |
| duration_minutes | INTEGER | |
| completed | INTEGER | 0 = no, 1 = sì |

### `session_results`
| Campo | Tipo | Note |
|---|---|---|
| id | INTEGER PK | |
| session_id | INTEGER FK | → sessions (CASCADE DELETE) |
| program_exercise_id | INTEGER FK | → program_exercises |
| set_number | INTEGER | |
| weight | REAL | kg |
| reps_performed | INTEGER | |

### `assignments`
| Campo | Tipo | Note |
|---|---|---|
| assignment_id | INTEGER PK | |
| trainer_id | INTEGER FK | → users |
| client_id | INTEGER FK | → users |
| start_date | TEXT | |
| end_date | TEXT | Nullable |

### `nutrition_plans`
| Campo | Tipo | Note |
|---|---|---|
| plan_id | INTEGER PK | |
| nutritionist_id | INTEGER FK | → users |
| title | TEXT | |
| description | TEXT | |
| created_at | TEXT | Default: data corrente |

### `nutrition_tips`
| Campo | Tipo | Note |
|---|---|---|
| tip_id | INTEGER PK | |
| plan_id | INTEGER FK | → nutrition_plans |
| user_id | INTEGER FK | → users |
| tip_date | TEXT | |
| content | TEXT | |

### `feedback`
| Campo | Tipo | Note |
|---|---|---|
| feedback_id | INTEGER PK | |
| user_id | INTEGER FK | → users |
| program_id | INTEGER FK | Nullable → workout_programs |
| plan_id | INTEGER FK | Nullable → nutrition_plans |
| rating | INTEGER | 1–5 |
| comment | TEXT | |
| feedback_date | TEXT | Default: data corrente |

### `registration_codes`
| Campo | Tipo | Note |
|---|---|---|
| code | TEXT PK | 6 cifre, univoco |
| role | TEXT | `trainer` o `nutritionist` |
| used | INTEGER | 0 = disponibile, 1 = usato |
| created_at | TEXT | Default: data corrente |

---

## 5. Modulo DbManager

`DbManager` è la classe C++ centrale del progetto. Eredita da `QObject` ed è esposta a QML tramite il contesto del motore.

### 5.1 Metodi pubblici principali

#### Autenticazione

```cpp
bool login(const QString &email, const QString &password)
```
- **Cosa fa:** verifica le credenziali dell'utente confrontando la password con l'hash SHA-256 memorizzato; se valide, aggiorna lo stato interno dell'utente corrente.
- **Pre-condizioni:** email non vuota, password non vuota.
- **Post-condizioni:** se restituisce `true`, `currentUserId()`, `currentUserType()` e `currentUserName()` riflettono l'utente autenticato.
- **Valore di ritorno:** `true` se le credenziali sono corrette, `false` altrimenti.

```cpp
bool registerUser(const QString &firstName, const QString &lastName,
                  const QString &email, const QString &password,
                  const QString &userType)
```
- **Cosa fa:** inserisce un nuovo utente nel database con la password hashata.
- **Pre-condizioni:** email non già presente nel database; `userType` deve essere uno tra `client`, `trainer`, `nutritionist`, `administrator`.
- **Post-condizioni:** se restituisce `true`, l'utente è persistito nel database.
- **Valore di ritorno:** `true` se l'inserimento è riuscito.

```cpp
void logout()
```
- **Cosa fa:** azzera lo stato dell'utente corrente (id, tipo, nome).
- **Post-condizioni:** `currentUserId()` restituisce `-1`.

#### Programmi di allenamento

```cpp
QVariantList getWorkoutPrograms()
QVariantList getWorkoutProgramsByDifficulty(const QString &difficulty)
QVariantList getWorkoutProgramsByGoal(const QString &goal)
QStringList getGoals()
```
- Restituiscono liste di mappe `QVariantMap` con i campi: `program_id`, `title`, `goal`, `difficulty`, `duration_weeks`, `description`, `trainer`.

```cpp
bool addWorkoutProgramWithExercises(const QString &title, const QString &goal,
                                    const QString &difficulty, int durationWeeks,
                                    const QString &description,
                                    const QVariantList &exercises)
```
- **Cosa fa:** inserisce un programma e i suoi esercizi in modo atomico tramite transazione SQLite.
- **Pre-condizioni:** l'utente corrente deve essere autenticato come trainer o administrator.
- **Post-condizioni:** se restituisce `true`, sia il programma che gli esercizi associati sono persistiti; in caso di errore, il rollback garantisce la consistenza del database.

```cpp
bool deleteWorkoutProgram(int programId)
bool updateWorkoutProgram(int programId, ...)
QVariantList getProgramExercises(int programId)
```

#### Sessioni

```cpp
bool logDetailedSession(int userId, int programId, const QString &dateTime,
                        int durationMinutes, const QVariantList &results)
```
- **Cosa fa:** inserisce una sessione completa con i risultati per ogni serie di ogni esercizio, usando una transazione atomica.
- **Pre-condizioni:** `programId` deve corrispondere a un programma esistente con esercizi associati.
- **Post-condizioni:** se restituisce `true`, sessione e tutti i `session_results` sono persistiti.

```cpp
QVariantList getSessions(int userId)
QVariantList getSessionResults(int sessionId)
```

#### Nutrizione

```cpp
QVariantList getNutritionPlans()
QVariantList getNutritionTips(int userId)
QVariantList getNutritionTipsByPlan(int planId, int userId)
bool addNutritionPlan(const QString &title, const QString &description)
bool deleteNutritionPlan(int planId)
bool addNutritionTip(int planId, int userId, const QString &date, const QString &content)
```
- `deleteNutritionPlan` usa una transazione per eliminare prima i feedback e i consigli associati, poi il piano.

#### Utenti e assegnazioni

```cpp
QVariantList getAllUsers()
bool deleteUser(int userId)
QVariantList getClients()
QVariantList getTrainers()
bool assignTrainer(int trainerId, int clientId, const QString &startDate)
QVariantList getAssignments()
```
- `deleteUser` usa una transazione per eliminare prima tutti i record dipendenti (feedback, sessioni, tips, assegnazioni) e poi l'utente.

#### Progressi e feedback

```cpp
QVariantList getUserProgress(int userId)
QVariantList getFeedbackByUser(int userId)
bool addFeedback(int userId, int programId, int planId, int rating, const QString &comment)
```
- `programId` o `planId` possono essere `-1` (equivalente a NULL) se il feedback riguarda solo uno dei due.

#### Codici OTP

```cpp
QString generateRegistrationCode(const QString &role)
bool validateRegistrationCode(const QString &code, const QString &role)
bool markCodeAsUsed(const QString &code)
QVariantList getRegistrationCodes()
```
- `generateRegistrationCode` tenta fino a 10 volte di generare un codice a 6 cifre univoco prima di restituire stringa vuota in caso di fallimento.

### 5.2 Metodi privati

```cpp
QString hashPassword(const QString &password)
```
- Calcola l'hash SHA-256 della password usando `QCryptographicHash`.

```cpp
void logDbChange(const QString &operation, const QString &table, const QString &details)
```
- Scrive un messaggio formattato su console (`qDebug`) e su file di log.

### 5.3 Stato interno

| Campo | Tipo | Descrizione |
|---|---|---|
| `m_currentUserId` | `int` | ID utente autenticato, `-1` se nessuno |
| `m_currentUserType` | `QString` | Tipo ruolo utente corrente |
| `m_currentUserName` | `QString` | Nome utente corrente |
| `m_logFile` | `QFile` | File di log aperto in append |

---

## 6. Navigazione e struttura QML

### 6.1 Struttura di navigazione

La navigazione è gestita da un `StackView` definito in `Main.qml`. Ogni pagina è definita come `Component` e riceve `stackView: stack` come proprietà, permettendo il push/pop programmatico.

```
StackView
└── LoginPage
    ├── RegisterPage
    └── [dopo login]
        ├── ClientDashboard
        │   ├── WorkoutProgramsPage
        │   │   └── WorkoutProgramDetailPage
        │   │       └── SessionDetailPage (logging)
        │   ├── SessionsPage
        │   │   └── SessionDetailPage (view)
        │   └── NutritionPage
        │       └── NutritionPlanDetailPage
        └── AdminDashboard
            ├── ManageUsersPage
            ├── ManageWorkoutProgramsPage
            ├── ManageNutritionPlansPage
            ├── UserProgressPage
            │   └── SessionDetailPage (view)
            └── ManageCodesPage  [solo administrator]
```

### 6.2 Pattern di routing

Il routing post-login avviene in `Main.qml`:

```qml
onLoginSuccess: function(userType) {
    if (userType === "client") {
        stack.push(clientDashboard)
    } else if (userType === "administrator" || userType === "trainer" || userType === "nutritionist") {
        stack.push(adminDashboard)
    }
}
```

Il pulsante "Codici Registrazione" nell'`AdminDashboard` è visibile solo per gli amministratori tramite `visible: db.currentUserType() === "administrator"`.

### 6.3 Convenzioni QML

- Tutte le pagine dichiarano `property StackView stackView` per ricevere il riferimento allo stack.
- Il pulsante "Indietro" nelle toolbar chiama `stackView.pop()`.
- I dettagli vengono passati alle pagine tramite il secondo argomento di `push`: `stackView.push(detailPage, { program: modelData })`.

---

## 7. Funzionalità implementate

### 7.1 Sistema di autenticazione e registrazione

- Login con email e password (hash SHA-256).
- Registrazione libera solo per il ruolo `client`.
- Registrazione per `trainer` e `nutritionist` richiede un codice OTP a 6 cifre generato dall'amministratore.
- I codici OTP sono monouso: vengono marcati come `used = 1` dopo la registrazione.
- Validazione lato client: campi obbligatori, password minimo 8 caratteri, conferma password.

### 7.2 Programmi di allenamento (cliente)

- Lista con filtri per difficoltà e obiettivo (dinamico dal DB).
- Apertura pagina dettaglio con lista esercizi e avvio allenamento.
- Feedback inline con valutazione a stelle (1–5) e commento opzionale.

### 7.3 Sessioni di allenamento

- Logging dettagliato: per ogni esercizio del programma, il cliente inserisce peso e ripetizioni effettive per ogni serie.
- I risultati sono salvati in `session_results` con transazione atomica.
- Storico sessioni con navigazione alla pagina dettaglio.

### 7.4 Nutrizione (cliente)

- Visualizzazione piani nutrizionali con tap per dettaglio.
- Nella pagina dettaglio: consigli filtrati per piano e utente, feedback inline.
- Sezione "Consigli Giornalieri" in dashboard nutrizione con tutti i consigli dell'utente.

### 7.5 Gestione programmi (admin/trainer)

- Lista con eliminazione.
- Creazione nuovo programma con selezione esercizi da catalogo (dialog), sets, reps e recupero per ogni esercizio.

### 7.6 Gestione piani nutrizionali (admin/nutrizionista)

- Lista con eliminazione (cascade su tips e feedback).
- Creazione nuovo piano.
- Aggiunta consigli a un piano per un cliente specifico.

### 7.7 Gestione utenti (admin)

- Lista di tutti gli utenti con eliminazione (cascade su dipendenze).
- Assegnazione trainer a cliente con data inizio.
- Lista assegnazioni attive.

### 7.8 Progressi utenti (admin/trainer)

- Selezione cliente da dropdown.
- Tab sessioni: lista con tap per dettaglio.
- Tab feedback: lista con stelle e commenti.
- Tab statistiche: totale sessioni, sessioni completate, minuti totali, feedback ricevuti, valutazione media.

### 7.9 Codici OTP (solo administrator)

- Generazione codice a 6 cifre per ruolo `trainer` o `nutritionist`.
- Lista codici generati con stato (attivo/usato).

---

## 8. Sicurezza

| Misura | Dettaglio |
|---|---|
| Hashing password | SHA-256 via `QCryptographicHash` |
| Codici OTP | Monouso, 6 cifre, con retry su collisione |
| Ruoli protetti | Trainer e nutrizionisti richiedono codice OTP valido |
| Transazioni DB | Operazioni multi-step usano `transaction()` / `commit()` / `rollback()` |
| Foreign keys | `PRAGMA foreign_keys = ON` attivato all'apertura del DB |

> **Nota:** L'hashing SHA-256 senza salt è adeguato per un prototipo universitario. In un sistema in produzione si raccomanda l'uso di bcrypt o Argon2 con salt casuale per ogni utente.

---

## 9. Logging

Ogni operazione che modifica il database viene registrata su:
- **Console** (`qDebug`)
- **File** `palestradigitale.log` (nella cartella di esecuzione, apertura in append)

Formato del log:
```
[2026-06-08 14:32:01] INSERT -> sessions | user_id: 1 | program_id: 2 | duration: 45
[2026-06-08 14:32:45] INSERT -> feedback | user_id: 1 | rating: 4
[2026-06-08 14:35:00] LOGOUT -> users | user_id: 1
```

Il file viene chiuso correttamente alla chiusura dell'applicazione tramite il segnale `QGuiApplication::aboutToQuit`.

---

## 10. Dati di test

Al primo avvio, `seedTestData()` popola il database con dati di test se le tabelle sono vuote:

| Email | Password | Ruolo |
|---|---|---|
| mario@test.com | 1234 | client |
| luigi@test.com | 1234 | trainer |
| anna@test.com | 1234 | nutritionist |
| admin | admin | administrator |

Vengono anche inseriti 3 programmi di allenamento, 2 piani nutrizionali, 2 consigli nutrizionali per Mario, e un catalogo di 30 esercizi suddivisi per categoria.

---

## 11. Testing
 
Il progetto non utilizza un framework di test automatizzato dedicato (es. Qt Test), ma adotta una strategia di **test manuale strutturato** basata sugli account di seed (`seedTestData()`) e sul sistema di logging su file. Di seguito sono documentati i casi di test ritenuti più rilevanti, organizzati per area funzionale.
 
---
 
### 11.1 Ambiente di test
 
| Parametro | Valore |
|---|---|
| Sistema operativo | Windows 11 / Ubuntu 24.04 |
| Qt | 6.10+ |
| Compiler | MinGW 64-bit (Windows) / GCC (Linux) |
| Database | `palestradigitale.db` — SQLite locale |
| Account seed | Vedi tabella §10 |
| Log | `palestradigitale.log` (nella cartella di esecuzione) |
 
Per ogni test, il log di esecuzione (`palestradigitale.log`) costituisce la traccia persistente dell'esito. Prima di ogni sessione di test si raccomanda di eliminare il file `.db` e ripartire da un database fresco, oppure di usare un `.db` di backup separato.
 
---
 
### 11.2 Test di autenticazione
 
#### TC-AUTH-01 — Login con credenziali valide (client)
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Database seedato, utente `mario@test.com` presente |
| **Input** | email: `mario@test.com`, password: `1234` |
| **Azione** | Compilare i campi e premere "Login" |
| **Risultato atteso** | Redirect a `ClientDashboard`; `db.currentUserType()` restituisce `"client"` |
| **Verifica log** | Nessuna entry INSERT (login non scrive sul DB), nessun errore in console |
 
#### TC-AUTH-02 — Login con password errata
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Database seedato |
| **Input** | email: `mario@test.com`, password: `sbagliata` |
| **Azione** | Compilare i campi e premere "Login" |
| **Risultato atteso** | Messaggio di errore visibile in UI; nessun redirect |
| **Verifica log** | Nessuna entry; `login()` restituisce `false` |
 
#### TC-AUTH-03 — Registrazione nuovo client
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Email non già presente nel database |
| **Input** | Nome: `Test`, Cognome: `User`, email: `test@user.com`, password: `12345678`, conferma: `12345678`, ruolo: `client` |
| **Azione** | Compilare il form di registrazione e premere "Registrati" |
| **Risultato atteso** | Utente inserito nel DB; ritorno al login senza errori |
| **Verifica log** | Entry `INSERT -> users | email: test@user.com` presente nel log |
 
#### TC-AUTH-04 — Registrazione trainer con codice OTP valido
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Effettuare login come `admin`/`admin`; generare un codice OTP per `trainer` dalla sezione "Codici Registrazione"; annotare il codice generato |
| **Input** | Ruolo: `trainer`, OTP: codice annotato |
| **Azione** | Effettuare logout; registrarsi con il codice OTP |
| **Risultato atteso** | Registrazione completata; il codice risulta `used = 1` nella tabella `registration_codes` |
| **Verifica log** | Entry `INSERT -> users` + entry `UPDATE -> registration_codes` |
 
#### TC-AUTH-05 — Registrazione trainer con codice OTP già usato
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | TC-AUTH-04 completato; stesso codice OTP già consumato |
| **Input** | Stesso codice OTP del test precedente |
| **Risultato atteso** | Messaggio di errore "Codice non valido"; registrazione bloccata |
 
#### TC-AUTH-06 — Logout
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Utente autenticato |
| **Azione** | Premere "Logout" |
| **Risultato atteso** | Redirect a `LoginPage`; `db.currentUserId()` restituisce `-1` |
| **Verifica log** | Entry `LOGOUT -> users | user_id: X` |
 
---
 
### 11.3 Test programmi di allenamento
 
#### TC-WK-01 — Visualizzazione lista programmi (client)
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Login come `mario@test.com` |
| **Azione** | Navigare su "Programmi di Allenamento" |
| **Risultato atteso** | Lista popolata con i 3 programmi di seed; filtri "Difficoltà" e "Obiettivo" funzionanti |
 
#### TC-WK-02 — Filtro per difficoltà
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | TC-WK-01 superato |
| **Input** | Selezionare `beginner` dal filtro difficoltà |
| **Risultato atteso** | Lista ristretta ai soli programmi con `difficulty = 'beginner'` |
 
#### TC-WK-03 — Apertura dettaglio programma e visualizzazione esercizi
 
| Campo | Valore |
|---|---|
| **Azione** | Toccare un programma nella lista |
| **Risultato atteso** | `WorkoutProgramDetailPage` aperta; lista esercizi con nome, serie × reps e recupero corretti rispetto al DB |
 
#### TC-WK-04 — Logging sessione dettagliata
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Programma con almeno un esercizio; login come client |
| **Azione** | Dal dettaglio programma, premere "🚀 Inizia Allenamento"; compilare peso e reps per ogni serie; premere "💾 Salva Allenamento" |
| **Risultato atteso** | Entry in `sessions` + entry in `session_results` per ogni serie; sessione visibile in "Le mie Sessioni" |
| **Verifica log** | Entry `INSERT -> sessions` + `INSERT -> session_results` |
 
#### TC-WK-05 — Logging sessione su programma senza esercizi
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Creare un programma vuoto (senza esercizi) come admin/trainer |
| **Azione** | Tentare di avviare l'allenamento su quel programma come client |
| **Risultato atteso** | Messaggio "Il programma non ha esercizi assegnati" oppure pulsante non disponibile; nessuna entry in DB |
 
#### TC-WK-06 — Creazione programma con esercizi (trainer/admin)
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Login come `luigi@test.com` (trainer) o `admin` |
| **Input** | Titolo: `Programma Test`, obiettivo: `weight loss`, difficoltà: `intermediate`, durata: `4`, almeno 1 esercizio dal catalogo |
| **Azione** | Compilare il form e premere "Crea Programma" |
| **Risultato atteso** | Programma visibile nella lista; esercizi presenti nel dettaglio |
| **Verifica log** | Entry `INSERT -> workout_programs` + `INSERT -> program_exercises` (transazione atomica) |
 
#### TC-WK-07 — Eliminazione programma
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Login come admin/trainer; programma esistente |
| **Azione** | Premere il pulsante di eliminazione su un programma |
| **Risultato atteso** | Programma rimosso dalla lista; record rimosso da `workout_programs` e `program_exercises` (cascade) |
 
---
 
### 11.4 Test nutrizione
 
#### TC-NUT-01 — Visualizzazione piani nutrizionali (client)
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Login come `mario@test.com`; piani di seed presenti |
| **Azione** | Navigare su "Nutrizione" |
| **Risultato atteso** | Lista piani nutrizionali visibile; sezione "Consigli Giornalieri" con i 2 consigli di seed per Mario |
 
#### TC-NUT-02 — Consigli filtrati per piano
 
| Campo | Valore |
|---|---|
| **Azione** | Toccare un piano nutrizionale; aprire `NutritionPlanDetailPage` |
| **Risultato atteso** | Solo i consigli associati a quel piano e all'utente corrente sono visibili |
 
#### TC-NUT-03 — Aggiunta consiglio nutrizionale (nutrizionista/admin)
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Login come `anna@test.com` (nutritionist) |
| **Input** | Piano: (selezionare dalla lista), Cliente: `Mario`, data: oggi, contenuto: `Aumentare l'apporto proteico` |
| **Azione** | Premere "Aggiungi Consiglio" |
| **Risultato atteso** | Consiglio visibile per Mario in "Consigli Giornalieri" |
| **Verifica log** | Entry `INSERT -> nutrition_tips` |
 
---
 
### 11.5 Test feedback
 
#### TC-FB-01 — Rilascio feedback su programma
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Login come client; programma visibile |
| **Input** | Rating: 4 stelle, commento: `Ottimo programma` |
| **Azione** | Compilare il form feedback nel dettaglio programma e inviare |
| **Risultato atteso** | Feedback salvato in `feedback`; record visibile in "Progressi Utenti" dall'admin |
| **Verifica log** | Entry `INSERT -> feedback | user_id: X | rating: 4` |
 
#### TC-FB-02 — Feedback con solo rating (commento opzionale)
 
| Campo | Valore |
|---|---|
| **Input** | Rating: 5 stelle, commento: (vuoto) |
| **Risultato atteso** | Feedback salvato correttamente con `comment = NULL` o stringa vuota |
 
---
 
### 11.6 Test gestione utenti (admin)
 
#### TC-ADM-01 — Visualizzazione lista utenti
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Login come `admin`/`admin` |
| **Azione** | Navigare su "👥 Gestione Utenti" > Tab "Utenti" |
| **Risultato atteso** | Lista di tutti gli utenti registrati |
 
#### TC-ADM-02 — Assegnazione trainer a cliente
 
| Campo | Valore |
|---|---|
| **Input** | Trainer: `Luigi`, Cliente: `Mario`, data inizio: oggi |
| **Azione** | Selezionare e premere "Assegna" |
| **Risultato atteso** | Record inserito in `assignments`; assegnazione visibile nel Tab "Assegnazioni" |
| **Verifica log** | Entry `INSERT -> assignments` |
 
#### TC-ADM-03 — Eliminazione utente con cascade
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Utente con sessioni, feedback e assegnazioni collegate |
| **Azione** | Premere eliminazione su un utente |
| **Risultato atteso** | Utente e tutti i record dipendenti eliminati in modo atomico; nessun record orfano in `sessions`, `feedback`, `assignments` |
| **Verifica log** | Entry `DELETE -> users | user_id: X` con conferma transazione |
 
---
 
### 11.7 Test progressi utenti
 
#### TC-PRG-01 — Statistiche cliente
 
| Campo | Valore |
|---|---|
| **Pre-condizione** | Login come admin; `mario@test.com` ha almeno 1 sessione completata e 1 feedback |
| **Azione** | Navigare su "📊 Progressi Utenti"; selezionare `Mario`; premere "Carica" |
| **Risultato atteso** | Tab "Statistiche" mostra valori coerenti con i record presenti nel DB (sessioni totali, completate, minuti, media feedback ≥ 1) |
 
---
 
### 11.8 Test di integrità e casi limite
 
#### TC-INT-01 — Transazione atomica su sessione (rollback simulato)
 
| Campo | Valore |
|---|---|
| **Descrizione** | Verificare che `logDetailedSession()` non lasci dati parziali in caso di errore durante il salvataggio dei `session_results` |
| **Metodo** | Inserire manualmente un `program_exercise_id` inesistente e osservare che né la sessione né i risultati parziali vengono persistiti |
| **Risultato atteso** | Nessun record in `sessions` né in `session_results`; log mostra `ROLLBACK` |
 
#### TC-INT-02 — Email duplicata in registrazione
 
| Campo | Valore |
|---|---|
| **Input** | Tentare di registrare `mario@test.com` una seconda volta |
| **Risultato atteso** | `registerUser()` restituisce `false`; messaggio di errore in UI; nessun inserimento duplicato |
 
#### TC-INT-03 — Foreign key enforcement
 
| Campo | Valore |
|---|---|
| **Descrizione** | SQLite ha `PRAGMA foreign_keys = ON`; tentare di inserire una sessione con `program_id` inesistente |
| **Risultato atteso** | Query fallisce con errore di vincolo; log mostra l'errore; nessun record corrotto |
 
#### TC-INT-04 — Feedback con `program_id` e `plan_id` entrambi NULL
 
| Campo | Valore |
|---|---|
| **Descrizione** | `addFeedback()` accetta `-1` per entrambi; verificare che non venga generato un record logicamente inconsistente |
| **Risultato atteso** | Record inserito con entrambi i campi NULL; visible nei progressi dell'utente |
 
---
 
### 11.9 Copertura funzionale — riepilogo
 
| Area | Test case | Esito atteso |
|---|---|---|
| Autenticazione | TC-AUTH-01…06 | Login, registrazione, OTP, logout |
| Programmi | TC-WK-01…07 | CRUD, filtri, logging sessione |
| Nutrizione | TC-NUT-01…03 | Visualizzazione, consigli |
| Feedback | TC-FB-01…02 | Inserimento con e senza commento |
| Gestione utenti | TC-ADM-01…03 | Lista, assegnazione, cascade delete |
| Progressi | TC-PRG-01 | Statistiche aggregate |
| Integrità | TC-INT-01…04 | Transazioni, FK, duplicati |
 
> **Nota:** tutti i test manuali sopra descritti sono stati eseguiti su un database fresco (generato da `seedTestData()`)

# Manuale Utente

## 1. Avvio dell'applicazione

All'avvio, viene mostrata la schermata di **login**. Se è il primo avvio, usare uno degli account di test indicati nella sezione 10 del manuale tecnico.

---

## 2. Registrazione

1. Dalla schermata di login, toccare **"Non hai un account? Registrati"**.
2. Compilare tutti i campi: nome, cognome, email, password (minimo 8 caratteri), conferma password.
3. Selezionare il **tipo di account**:
   - **Client** — nessun codice richiesto.
   - **Trainer** o **Nutritionist** — inserire il codice OTP fornito dall'amministratore.
4. Toccare **"Registrati"**.
5. In caso di successo, tornare al login e accedere con le credenziali appena create.

> **Nota:** I codici OTP sono monouso. Una volta usato, non è più valido.

---

## 3. Login

1. Inserire email e password.
2. Toccare **"Login"**.
3. In base al proprio ruolo, si verrà indirizzati alla dashboard cliente o alla dashboard amministrativa.

---

## 4. Area Cliente

### 4.1 Programmi di allenamento

1. Dalla dashboard, toccare **"Programmi di Allenamento"**.
2. Usare i filtri in alto per filtrare per **difficoltà** o **obiettivo**.
3. Toccare un programma per aprire il dettaglio.
4. Nel dettaglio è possibile:
   - Vedere la lista degli esercizi inclusi (nome, serie × ripetizioni, recupero).
   - Toccare **"🚀 Inizia Allenamento"** per avviare il logging della sessione.
   - Lasciare un **feedback** con valutazione a stelle e commento.

### 4.2 Registrazione sessione

1. Avviare l'allenamento dalla pagina dettaglio del programma oppure dalla pagina **"Le mie Sessioni"** tramite il pulsante "Registra (Dettagliato)".
2. Per ogni esercizio e ogni serie, inserire:
   - **kg** — il peso utilizzato.
   - **reps** — le ripetizioni effettivamente eseguite.
3. Toccare **"💾 Salva Allenamento"** per salvare la sessione.

> **Nota:** Se un programma non ha esercizi assegnati, non è possibile avviare il logging dettagliato.

### 4.3 Storico sessioni

1. Dalla dashboard, toccare **"Le mie Sessioni"**.
2. Le sessioni completate appaiono in verde, quelle in corso in grigio.
3. Toccare una sessione per vedere i risultati dettagliati (peso e reps per ogni serie).

### 4.4 Nutrizione

1. Dalla dashboard, toccare **"Nutrizione"**.
2. Nella sezione **"Piani Nutrizionali"** sono visibili i piani disponibili; toccare un piano per vedere:
   - Descrizione del piano.
   - Consigli associati a quel piano per il proprio profilo.
   - Sezione per lasciare un feedback.
3. Nella sezione **"Consigli Giornalieri"** sono visibili tutti i consigli ricevuti.

---

## 5. Area Admin / Trainer / Nutrizionista

### 5.1 Gestione utenti *(solo administrator)*

1. Toccare **"👥 Gestione Utenti"**.
2. **Tab "Utenti":** lista di tutti gli utenti registrati con possibilità di eliminazione.
3. **Tab "Assegnazioni":** selezionare un trainer e un cliente, poi toccare **"Assegna"** per creare l'assegnazione.

### 5.2 Gestione programmi di allenamento

1. Toccare **"🏋️ Programmi di Allenamento"**.
2. **Tab "Programmi":** lista dei programmi con eliminazione.
3. **Tab "Nuovo":** compilare titolo, obiettivo, difficoltà, durata e descrizione. Aggiungere esercizi tramite il pulsante **"+ Aggiungi Esercizio"** che apre un dialog per selezionare l'esercizio e specificare serie, ripetizioni e recupero.
4. Toccare **"Crea Programma"** per salvare.

### 5.3 Gestione piani nutrizionali

1. Toccare **"🥗 Piani Nutrizionali"**.
2. **Tab "Piani":** lista con eliminazione.
3. **Tab "Nuovo Piano":** inserire titolo e descrizione.
4. **Tab "Nuovo Consiglio":** selezionare piano e cliente, inserire data e contenuto del consiglio.

### 5.4 Progressi utenti

1. Toccare **"📊 Progressi Utenti"**.
2. Selezionare un cliente dal menu a tendina e toccare **"Carica"**.
3. Navigare tra i tab:
   - **Sessioni** — storico completo con dettaglio toccabile.
   - **Feedback** — valutazioni e commenti lasciati dal cliente.
   - **Statistiche** — riepilogo numerico (sessioni totali, completate, minuti, media feedback).

### 5.5 Codici registrazione *(solo administrator)*

1. Toccare **"🔑 Codici Registrazione"**.
2. Selezionare il ruolo (`trainer` o `nutritionist`) e toccare **"Genera"**.
3. Il codice generato appare in verde. Comunicarlo al futuro trainer/nutrizionista.
4. La lista mostra tutti i codici con stato (attivo/usato).

---

## 6. Logout

Toccare il pulsante **"Logout"** in fondo alla dashboard. Si verrà riportati alla schermata di login.
