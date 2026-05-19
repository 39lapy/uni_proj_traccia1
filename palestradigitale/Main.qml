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
        }
    }

    Component {
        id: clientDashboard
        ClientDashboard {
            stackView: stack
            onLogout: {
                db.logout()
                stack.pop(null) // pop all the way back to login
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
}