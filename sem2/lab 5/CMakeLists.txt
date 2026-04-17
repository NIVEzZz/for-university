cmake_minimum_required(VERSION 3.16)
project(NPSCardCraft VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt6_standard_project_setup()

set(SOURCES
    main.cpp
    MainWindow.cpp
    CardDialog.cpp
    Person.cpp
)

set(HEADERS
    MainWindow.h
    CardDialog.h
    Person.h
)

set(FORMS
    MainWindow.ui
    CardDialogMag.ui
    CardDialogVrag.ui
)

set(RESOURCES
    resources/images.qrc
)
set(FORMS
    MainWindow.ui
    CardDialogMag.ui
    CardDialogVrag.ui
)

qt6_add_executable(NPSCardCraft ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
target_link_libraries(NPSCardCraft PRIVATE Qt6::Widgets)
