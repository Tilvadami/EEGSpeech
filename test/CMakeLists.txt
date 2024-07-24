cmake_minimum_required(VERSION 3.5)
project(EEG_Speech_test)

find_package(Qt5 COMPONENTS Widgets network REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${res})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Network EEG_Speech)

message(${INPOUT32_DLL_DIR}/inpoutx64.dll)
