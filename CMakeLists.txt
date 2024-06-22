cmake_minimum_required(VERSION 3.24)
project(GameTrain)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameTrain main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/sfml/lib/cmake/sfml)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/sfml/include/SFML)
target_link_libraries(GameTrain sfml-system sfml-window sfml-graphics sfml-audio)
