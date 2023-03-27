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

set( CMAKE_PREFIX_PATH "/opt/Qt/5.15.2/gcc_64/lib/cmake" )

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

file( GLOB_RECURSE UTILIY_SOURCE_FILES
      src/utils/*.cpp src/utils/*.hpp
    )

file( GLOB_RECURSE SHARED_SOURCE_FILES
      src/shared/*.cpp src/shared/*.hpp
    )

file( GLOB_RECURSE CLIENT_SOURCE_FILES
      src/client/*.cpp src/client/*.hpp
      ${UTILIY_SOURCE_FILES}
      ${SHARED_SOURCE_FILES}
    )

file( GLOB_RECURSE SERVER_SOURCE_FILES
      src/server/*.cpp src/server/*.hpp
      ${UTILIY_SOURCE_FILES}
      ${SHARED_SOURCE_FILES}
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(2048_client
        MANUAL_FINALIZATION
        ${CLIENT_SOURCE_FILES}
    )
    qt_add_executable(2048_server
        MANUAL_FINALIZATION
        ${SERVER_SOURCE_FILES}
    )
else()
        add_executable(2048_client
            ${CLIENT_SOURCE_FILES}
        )
        add_executable(2048_server
            ${SERVER_SOURCE_FILES}
        )
endif()

                ############ building client ############
target_link_libraries(2048_client PRIVATE
                      Qt${QT_VERSION_MAJOR}::Widgets
                      Qt${QT_VERSION_MAJOR}::Network
                      )

target_include_directories(2048_client PRIVATE "src")

set_target_properties(2048_client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if( CMAKE_BUILD_TYPE STREQUAL "Release" )
    target_compile_options( 2048_client PRIVATE
                            ${RELEASE_COMPILE_OPTIONS}
)
else()
    target_compile_options( 2048_client PRIVATE
                            ${DEBUG_COMPILE_OPTIONS})
endif()

                ############ building server ############
target_link_libraries(2048_server PRIVATE
                      Qt${QT_VERSION_MAJOR}::Widgets
                      Qt${QT_VERSION_MAJOR}::Network
                      pq
                      )


target_include_directories(2048_server PRIVATE "src")

set_target_properties(2048_server PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if( CMAKE_BUILD_TYPE STREQUAL "Release" )
    target_compile_options( 2048_server PRIVATE
                            ${RELEASE_COMPILE_OPTIONS}
)
else()
    target_compile_options( 2048_server PRIVATE
                            ${DEBUG_COMPILE_OPTIONS})
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(2048_client)
    qt_finalize_executable(2048_server)
endif()
