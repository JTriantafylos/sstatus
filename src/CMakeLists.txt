# add the executable
add_executable(sstatus)

target_sources(sstatus
        PRIVATE main.cpp
        PRIVATE Control.cpp
        PRIVATE ConfigParser.cpp
        PRIVATE ShellInterpreter.cpp
        PRIVATE StatusItem.cpp
        PRIVATE StatusItemThread.cpp
        PRIVATE streamwriters/SwaybarStreamWriter.cpp)

set_property(TARGET sstatus PROPERTY CXX_STANDARD 23)
set_property(TARGET sstatus PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# TODO: Include tomlplusplus via CMake FetchContent
target_include_directories(sstatus PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(sstatus pthread)

install(TARGETS sstatus
        RUNTIME DESTINATION bin)
