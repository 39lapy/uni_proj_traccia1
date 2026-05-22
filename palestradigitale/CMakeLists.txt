cmake_minimum_required(VERSION 3.16)
project(palestradigitale VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Quick Sql)
qt_standard_project_setup(REQUIRES 6.10)
qt_add_executable(apppalestradigitale
    main.cpp
    dbmanager.h
    dbmanager.cpp
)
qt_add_qml_module(apppalestradigitale
    URI palestradigitale
    QML_FILES
        Main.qml
        qml/LoginPage.qml
        QML_FILES qml/ClientDashboard.qml
        QML_FILES qml/AdminDashboard.qml
        QML_FILES qml/WorkoutProgramsPage.qml
        QML_FILES qml/SessionsPage.qml
        QML_FILES
        QML_FILES qml/NutritionPage.qml
        QML_FILES qml/WorkoutProgramDetailPage.qml
        QML_FILES qml/ManageUsersPage.qml
        QML_FILES qml/ManageWorkoutProgramsPage.qml
        QML_FILES qml/ManageNutritionPlansPage.qml
        QML_FILES qml/UserProgressPage.qml
        QML_FILES qml/RegisterPage.qml
        QML_FILES qml/NutritionPlanDetailPage.qml
        QML_FILES qml/ManageCodesPage.qml
        QML_FILES qml/SessionDetailPage.qml
)
target_link_libraries(apppalestradigitale PRIVATE Qt6::Quick Qt6::Sql)

set_target_properties(apppalestradigitale PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
install(TARGETS apppalestradigitale
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)