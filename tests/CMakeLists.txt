include(FetchContent)

FetchContent_Declare(
    googletest
    SYSTEM
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(cpu_test cpu_test.cpp)

target_link_libraries(cpu_test PRIVATE
    cpu ram GTest::gtest_main project_options project_warnings)

add_test(NAME cpu_test COMMAND cpu_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(semihosting_test semihosting_test.cpp)

target_link_libraries(semihosting_test PRIVATE
    cpu ram GTest::gtest_main project_options project_warnings)

add_test(NAME semihosting_test COMMAND semihosting_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
