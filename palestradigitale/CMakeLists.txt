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
        qml/RegisterPage.qml
        qml/ClientDashboard.qml
        qml/AdminDashboard.qml
        qml/WorkoutProgramsPage.qml
        qml/WorkoutProgramDetailPage.qml
        qml/SessionsPage.qml
        qml/SessionDetailPage.qml
        qml/NutritionPage.qml
        qml/NutritionPlanDetailPage.qml
        qml/ManageUsersPage.qml
        qml/ManageWorkoutProgramsPage.qml
        qml/ManageNutritionPlansPage.qml
        qml/ManageCodesPage.qml
        qml/UserProgressPage.qml
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
    LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)