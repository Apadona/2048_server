cmake_minimum_required(VERSION 3.5)

project(2048 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RELEASE_COMPILE_FLAGS "-O2 -Wall -Wextra -s")
set(DEBUG_COMPILE_FLAGS "-g3 -Wall -Wextra")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file( GLOB SOURCE_FILES
      src/*.cpp src/*.hpp)

set(PROJECT_SOURCES
        ${SOURCE_FILES}
        #${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(2048
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
else()
    if(ANDROID)
        add_library(2048 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(2048
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(2048 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(2048 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_options( 2048 PRIVATE
                        ${RELEASE_COMPILE_OPTIONS}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(2048)
endif()
