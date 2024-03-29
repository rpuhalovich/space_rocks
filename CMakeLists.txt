cmake_minimum_required(VERSION 3.28.3)
project(SpaceRocks C)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER Predefined)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# --- src ---
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE src ${SRC_DIR}/*.c ${SRC_DIR}/*.h)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src})

# --- lib ---
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "ae50bfa"
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)
set(lib ${lib} raylib)

set_target_properties(${lib} uninstall PROPERTIES FOLDER "Libraries")

# --- exe ---
add_executable(${PROJECT_NAME} ${src})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PUBLIC
    RES_DIR="${CMAKE_SOURCE_DIR}/res/"
    PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
)
target_link_libraries(${PROJECT_NAME} ${lib} "-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL")
