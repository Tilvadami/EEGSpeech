cmake_minimum_required(VERSION 3.5)

project(EEG_Speech LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INPOUT32_DLL_DIR ${PROJECT_SOURCE_DIR}/dll)
if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
endif()

find_package(Qt5 COMPONENTS Widgets network gui REQUIRED)
#link_directories(${PROJECT_SOURCE_DIR}/dll)

# 链接动态库
#link_libraries(${PROJECT_SOURCE_DIR}/dll/inpoutx64.dll)
file(GLOB src "src/*")
file(GLOB res "res/*.qrc")
add_subdirectory(test)

add_library(${PROJECT_NAME} ${src} ${res})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Network Qt5::Gui ${PROJECT_SOURCE_DIR}/dll/inpoutx64.dll)

target_include_directories(${PROJECT_NAME} PUBLIC "src")
enable_testing(true)
