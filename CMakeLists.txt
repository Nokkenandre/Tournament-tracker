cmake_minimum_required(VERSION 3.20)

project(Tournament_tracker_proj)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/frontend/resources)

qt_standard_project_setup()
set(QT_LIBRARIES Qt6::Core Qt6::Widgets Qt6::Gui)
set(CPR_LIBRARY cpr::cpr)
set(NLOHMANN_JSON nlohmann_json::nlohmann_json)

file(GLOB SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/frontend/*.cpp
    ${CMAKE_SOURCE_DIR}/frontend/*.h
    ${RESOURCES_DIR}/resources.qrc
)

add_executable(Tournament_tracker ${SOURCE_FILES})
target_link_libraries(Tournament_tracker ${QT_LIBRARIES} ${CPR_LIBRARY} ${NLOHMANN_JSON})