cmake_minimum_required(VERSION 3.14)
project(calc)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  eval_test
  tests/eval_test.cpp
  source/parse.cpp
  source/queue.cpp
  source/lex.cpp
  source/eval.cpp
)
target_link_libraries(
  eval_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(eval_test)
