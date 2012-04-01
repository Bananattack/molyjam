cmake_minimum_required(VERSION 2.8)

project(molyjam)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

find_package(SFML 2.0 REQUIRED system window graphics audio)

include_directories(${SFML_INCLUDE_DIR})

list(APPEND CMAKE_CXX_FLAGS "--std=c++0x")

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Game
    src/Game.cpp
    src/Common.h
    src/Renderable.h
    src/Dude.h
    src/Dude.cpp
    src/Entity.h
    src/World.h
    src/World.cpp
    src/Word.h
    src/Word.cpp
    src/Thought.h
    src/Background.h
    src/Background.cpp
    src/Citizen.h
    src/Citizen.cpp
    src/Wall.h
    src/Wall.cpp
)

target_link_libraries(Game ${SFML_LIBRARIES})
