include(FetchContent)

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

target_include_directories(sstatus PRIVATE ${PROJECT_SOURCE_DIR}/include)

FetchContent_Declare(tomlplusplus
                     GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
                     GIT_TAG v3.4.0)
FetchContent_MakeAvailable(tomlplusplus)

target_link_libraries(sstatus
                      pthread
                      tomlplusplus::tomlplusplus)

install(TARGETS sstatus
        RUNTIME DESTINATION bin)
