cmake_minimum_required(VERSION 3.14)
project(terminalGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(game_lib STATIC
    src/core/Game.cpp
    src/entities/Hero.cpp
    src/entities/Monster.cpp
    src/actions/Action.cpp
    src/rooms/Room.cpp
    src/utils/Input.cpp
)

target_include_directories(game_lib PUBLIC src)

target_compile_options(game_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(game src/main.cpp)
target_link_libraries(game PRIVATE game_lib)
target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic)

option(BUILD_TESTING "Build unit tests" ON)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()