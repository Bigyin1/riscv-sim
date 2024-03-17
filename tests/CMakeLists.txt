include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(models_test cpu_test.cpp)

target_link_libraries(models_test PRIVATE
    cpu ram GTest::gtest_main project_options project_warnings)

add_test(NAME models_test COMMAND models_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testdata)
