import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    width: 400
    height: 700
    visible: true
    title: "Palestra Digitale"

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: loginPage
    }

    Component {
        id: loginPage
        LoginPage {
            onLoginSuccess: function(userType) {
                if (userType === "client") {
                    stack.push(clientDashboard)
                } else {
                    stack.push(adminDashboard)
                }
            }
            onGoToRegister: stack.push(registerPage)
        }
    }

    Component {
        id: clientDashboard
        ClientDashboard {
            stackView: stack
            onLogout: {
                db.logout()
                stack.pop(null) // TORNA A LOGIN
            }
        }
    }

    Component {
        id: adminDashboard
        AdminDashboard {
            stackView: stack
            onLogout: {
                db.logout()
                stack.pop(null)
            }
        }
    }


    Component {
        id: workoutProgramsPage
        WorkoutProgramsPage {
            stackView: stack
        }
    }

    Component {
        id: sessionsPage
        SessionsPage {
            stackView: stack
        }
    }

    Component {
        id: nutritionPage
        NutritionPage {
            stackView: stack
        }
    }


    Component {
        id: workoutProgramDetailPage
        WorkoutProgramDetailPage {
            stackView: stack
        }
    }

    Component {
        id: manageUsersPage
        ManageUsersPage { stackView: stack }
    }

    Component {
        id: manageWorkoutProgramsPage
        ManageWorkoutProgramsPage { stackView: stack }
    }

    Component {
        id: manageNutritionPlansPage
        ManageNutritionPlansPage { stackView: stack }
    }

    Component {
        id: userProgressPage
        UserProgressPage { stackView: stack }
    }

    Component {
        id: registerPage
        RegisterPage { stackView: stack }
    }

    Component {
        id: nutritionPlanDetailPage
        NutritionPlanDetailPage { stackView: stack }
    }

    Component {
        id: manageCodesPage
        ManageCodesPage { stackView: stack }
    }

    Component {
        id: sessionDetailPage
        SessionDetailPage { stackView: stack }
    }
}