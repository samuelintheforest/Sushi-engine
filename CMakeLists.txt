cmake_minimum_required(VERSION 3.10.0)
project(Sushi-engine VERSION 0.1.0 LANGUAGES C CXX)

# 1. Set the path to third-party libs folders
set(SRC_DIR /home/samu/Documents/coding/games/libs/src)
set(INCLUDE_DIR /home/samu/Documents/coding/games/libs/includes)
set(LIBRARIES_DIR /home/samu/Documents/coding/games/libs/libraries)

# 2. Adding libraries to compilation
# Create a library from GLAD source
add_library(glad ${SRC_DIR}/glad.c)
target_include_directories(glad PUBLIC ${INCLUDE_DIR})

# 3. Adding all source files from the directory
file(GLOB SUSHI_SOURCES "Sushi-engine/Sushi-engine/*.cpp")

add_executable(Sushi-engine ${CMAKE_SOURCE_DIR}/Sushi-engine/Sushi-engine/Main.cpp ${SUSHI_SOURCES})
# Link GLAD to your executable
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES_DIR}/libglfw3.a)


target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Sushi-engine/Sushi-engine/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

