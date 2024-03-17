add_executable(models_test cpu_test.cpp)

target_link_libraries(models_test PRIVATE
    cpu ram project_options project_warnings)

add_test(NAME models_test COMMAND models_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testdata)
