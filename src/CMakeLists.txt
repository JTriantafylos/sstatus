# add the executable
add_executable(sstatus)

target_sources(sstatus
    PRIVATE main.cpp
    PRIVATE Control.cpp
    PRIVATE ConfigParser.cpp
    PRIVATE ShellInterpreter.cpp
    PRIVATE StatusItem.cpp
    PRIVATE StreamWriter.cpp)

set_property(TARGET sstatus PROPERTY CXX_STANDARD 17)
set_property(TARGET sstatus PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

target_include_directories(sstatus
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/tomlplusplus/include)
