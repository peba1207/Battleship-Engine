cmake_minimum_required(VERSION 3.16)

project(battleship VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appbattleship
    main.cpp
    gamegridcontroller.h gamegridcontroller.cpp
)

qt_add_qml_module(appbattleship
    URI battleship
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES Tile.qml
    SOURCES gamegridcontroller.h gamegridcontroller.cpp
    SOURCES BoardState.cpp
    SOURCES BoardState.h
    QML_FILES ControlButton.qml
    SOURCES statecontroller.h statecontroller.cpp

    RESOURCES
    images/explosion.png
    images/x.png
    QML_FILES HeatmapTile.qml
    SOURCES heatmapcontroller.h heatmapcontroller.cpp
    SOURCES BoardCalculations.cpp BoardCalculations.h
    SOURCES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appbattleship PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appbattleship
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appbattleship
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appbattleship
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(CMAKE_CXX_FLAGS "-Ofast")
