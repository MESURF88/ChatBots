cmake_minimum_required(VERSION 3.14)

project(ChatBots VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/target)
message("${CMAKE_BINARY_DIR}")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Network REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(PROJECT_INCLUDES
    JsonSchema.hpp
    TcpComm.hpp
    TcpClientComm.hpp
    TcpServerComm.hpp
    DisplayLogic.hpp
)

set(PROJECT_SOURCES
        main.cpp
        TcpClientComm.cpp
        TcpServerComm.cpp
	DisplayLogic.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ChatBots
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ChatBots SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ChatBots
          ${PROJECT_INCLUDES}
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(ChatBots
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(ChatBots
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Network)
  
target_include_directories(ChatBots PRIVATE
 "${CMAKE_CURRENT_SOURCE_DIR}/jsoncons/include"
)


set_target_properties(ChatBots PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

set_target_properties(ChatBots 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(ChatBots)
    qt_finalize_executable(ChatBots)
endif()
