cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME imgui_app)

project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "-g -Wall")

set(SOURCE_FILES src/main.cpp src/imgui_impl_sdl_gl3.cpp src/gl3w.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${OPENGL_INCLUDE_DIR}
   ${SDL2_INCLUDE_DIR}
)

add_subdirectory(libs/imgui)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} imgui)
