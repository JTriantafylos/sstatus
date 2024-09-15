include(FetchContent)

if(NOT DEFINED WITH_FORMAT_TUI)
    set(WITH_FORMAT_TUI ON)
endif()

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
target_link_libraries(sstatus pthread)

FetchContent_Declare(tomlplusplus
                     GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
                     GIT_TAG v3.4.0)
FetchContent_MakeAvailable(tomlplusplus)
target_link_libraries(sstatus tomlplusplus::tomlplusplus)

if(WITH_FORMAT_TUI)
    target_sources(sstatus PRIVATE streamwriters/TuiStreamWriter.cpp)

    FetchContent_Declare(ftxui
                         GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
                         GIT_TAG v5.0.0)
    FetchContent_MakeAvailable(ftxui)
    target_link_libraries(sstatus ftxui::screen)
    target_link_libraries(sstatus ftxui::dom)

    add_definitions(-DSSTATUS_FORMAT_TUI)
endif()

install(TARGETS sstatus
        RUNTIME DESTINATION bin)
