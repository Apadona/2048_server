cmake_minimum_required(VERSION 3.5)

project(2048 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if ON, target will be build for 64-bit systems, OFF and target will be build for 32-bit systems.
option( architecture_64 "select build architecture (32 or 64) bit." ON )

set( CMAKE_PREFIX_PATH "/opt/Qt/5.15.2/gcc_64/lib/cmake" )

set( build_directory "${CMAKE_SOURCE_DIR}" )
set( client_include_directory "src" )
set( server_include_directory "src" )

set(RELEASE_COMPILE_FLAGS "-O2 -Wall -Wextra -s")
set(DEBUG_COMPILE_FLAGS "-g3 -Wall -Wextra")

if( WIN32 )
    set( os_title "windows" )

elseif( UNIX )
    if( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
        set( os_title "linux" )

    else()
        message( FATAL_ERROR "UNIX platform other than Linux detected!\n" )
    endif()

else()
    message( FATAL_ERROR "only windows and linux are currently supported!\n" )
endif()

if( architecture_64 )
    set( target_architecture "x64" )
else()
    set( target_architecture "x32" )
endif()

# directories for the executables/libraries that we are building.
set( executable_directory "${build_directory}/bin/${CMAKE_BUILD_TYPE}/${os_title}/${target_architecture}" )

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

target_include_directories(2048_client PRIVATE "${client_include_directory}")

set_target_properties(2048_client PROPERTIES
    WIN32_EXECUTABLE TRUE
    RUNTIME_OUTPUT_DIRECTORY "${executable_directory}"
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


target_include_directories(2048_server PRIVATE "${server_include_directory}")

set_target_properties(2048_server PROPERTIES
    WIN32_EXECUTABLE TRUE
    RUNTIME_OUTPUT_DIRECTORY "${executable_directory}"
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
