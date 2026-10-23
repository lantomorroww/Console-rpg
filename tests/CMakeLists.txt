include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(unit_tests
    test_hero.cpp
    test_monster.cpp
    test_room.cpp
    test_action.cpp
)

target_link_libraries(unit_tests PRIVATE
    game_lib
    GTest::gtest_main
)

target_compile_options(unit_tests PRIVATE -Wall -Wextra -Wpedantic)

gtest_discover_tests(unit_tests)
