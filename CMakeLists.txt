cmake_minimum_required(VERSION 3.10)
project(sfb2)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)
find_package(Box2D REQUIRED)

#elegant af
# file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
set(SOURCE_FILES
    src/main.cpp
    src/Game.cpp
    src/Entity.cpp
    src/Wall.cpp
    src/Ball.cpp
)
add_executable(sfb2 ${SOURCE_FILES})

target_include_directories(sfb2 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(sfb2 PRIVATE sfml-system sfml-window sfml-graphics Box2D)
