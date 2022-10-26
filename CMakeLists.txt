cmake_minimum_required(VERSION 3.2)

project(LRUCache11)


if(PROJECT_IS_TOP_LEVEL)
    SET(${PROJECT_NAME}_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/lrucache11/LRUCache11.hpp
    )

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
    SET(CMAKE_CXX_STANDARD 20)

    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    file(GLOB x_files 
        "tests/*.cpp")

    foreach(filename ${x_files})
        STRING(REGEX REPLACE
        "([/\\][A-Za-z0-9_]+)+[/\\]([A-Za-z0-9_]+)\.c(pp)?"
        "\\2" exec_name ${filename}) # get exec output name

        add_executable(${exec_name} ${filename})
        target_include_directories(${exec_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
        target_compile_features(${exec_name} INTERFACE cxx_nonstatic_member_init cxx_auto_type)
    endforeach()
endif()

