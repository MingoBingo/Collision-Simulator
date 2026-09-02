cmake_minimum_required(VERSION 3.15)
project(CollisionEngine C)

find_library(RAYLIB_LIB raylib)
find_path(RAYLIB_INCLUDE_DIR raylib.h)

add_executable(collision_engine main.c)

target_include_directories(collision_engine PRIVATE ${RAYLIB_INCLUDE_DIR})
target_link_libraries(collision_engine PRIVATE ${RAYLIB_LIB} m pthread dl rt X11 GL)