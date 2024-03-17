add_library(ram ram.cpp)
target_link_libraries(ram PUBLIC cpu project_options project_warnings)

target_include_directories(ram PUBLIC includes)
