cmake_minimum_required(VERSION 2.8)

project(molyjam)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

find_package(SFML 2.0 REQUIRED system window graphics audio)

include_directories(${SFML_INCLUDE_DIR})

list(APPEND CMAKE_CXX_FLAGS "--std=c++0x")

add_executable(Game
    src/Game.cpp
    src/Common.h
    src/Renderable.h
    src/Entity.h
    src/World.h
    src/World.cpp
    src/Word.h
    src/Thought.h
)

target_link_libraries(Game ${SFML_LIBRARIES})
