cmake_minimum_required(VERSION 3.16)

project(cnh-treeview VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core Gui)

qt_standard_project_setup()


set(SOURCES
    src/main.cpp
    src/TreeItem.cpp
    src/TreeItemData.cpp
    src/Model.cpp
)

set(HEADERS
    inc/TreeItem.h
    inc/TreeItemData.h
    inc/Model.h
)

qt_add_executable(appcnh-treeview
    ${SOURCES}
    ${HEADERS}
)

qt_add_qml_module(appcnh-treeview
    URI cnh-treeview
    VERSION 1.0
    QML_FILES views/main.qml
)

set_target_properties(appcnh-treeview PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcnh-treeview
    PRIVATE Qt6::Quick
    Qt6::Core
    Qt6::Gui
)

#### Resources
set(cnh-treeview_resource_files
    "database.txt"
)

qt_add_resources(appcnh-treeview "cnh-treeview"
    PREFIX
        "/"
    FILES
        ${cnh-treeview_resource_files}
)

qt_add_resources(appcnh-treeview imageresources
    PREFIX
        "/"
    FILES
        "assets/farmer.png" "assets/plus.png" "assets/minus.png"
        "assets/barn.png" "assets/field.png" "assets/tasks.png"
        "assets/products.png" "assets/seeds.png" "assets/roots.png"
        "assets/fertilizer.png"
)

install(TARGETS appcnh-treeview
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
