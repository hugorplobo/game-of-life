cmake_minimum_required(VERSION 3.15)
project(game-of-life)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)

include_directories(${CMAKE_SOURCE_DIR}/include)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libraylib.a msvcrt opengl32 gdi32 winmm kernel32 shell32 user32)
endif (WIN32)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} raylib m GL pthread dl rt X11)
endif (UNIX)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
