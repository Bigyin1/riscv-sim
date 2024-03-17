add_library(cpu cpu.cpp registers.cpp addrSpace.cpp instructions/handlers.cpp instructions/decoder.cpp)
target_link_libraries(cpu PRIVATE project_options project_warnings)

target_include_directories(cpu PUBLIC includes PUBLIC instructions .)
