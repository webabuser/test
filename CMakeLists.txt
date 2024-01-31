cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME Chat)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/chat.h 
    src/message.h 
    src/user.h 
    src/dynamic_array.h 
    src/bad_range.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)