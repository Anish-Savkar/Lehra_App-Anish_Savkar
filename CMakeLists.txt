cmake_minimum_required(VERSION 3.16)

project(LehraApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia)

qt_standard_project_setup(REQUIRES 6.10)

# Content imported from Qt Design Studio (if present)
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(importedcontent)
endif()

qt_add_executable(LehraApp
    main.cpp
)

qt_add_qml_module(LehraApp
    URI LehraApp
    QML_FILES
        Main.qml
    SOURCES
        audioengine.h
        audioengine.cpp
        taalmanager.h
        taalmanager.cpp
)

set_target_properties(LehraApp PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING
        ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    OUTPUT_NAME "Lehra_App-Anish_Savkar"
)

target_link_libraries(LehraApp
    PRIVATE
        Qt6::Quick
        Qt6::Multimedia
)

add_custom_command(
    TARGET LehraApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Audio"
            "$<TARGET_FILE_DIR:LehraApp>/Audio"
)

install(TARGETS LehraApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)