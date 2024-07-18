cmake_minimum_required(VERSION 3.5)

project(EEG_Speech LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB src "src/*")
file(GLOB res "res/*.qrc")
add_subdirectory(test)

add_library(${PROJECT_NAME} ${src} ${res})

target_link_libraries(EEG_Speech PRIVATE Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PUBLIC "src")
enable_testing(true)
