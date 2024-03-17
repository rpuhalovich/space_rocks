cmake_minimum_required(VERSION 3.28.3)
project(SpaceRocks C CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER Predefined)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE")

# --- src ---
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE src ${SRC_DIR}/*.c ${SRC_DIR}/*.h)

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src})

set(tgt_inc
    ${SRC_DIR}/board
    ${SRC_DIR}/events
    ${SRC_DIR}/gfx
    ${SRC_DIR}/gfx/util
)

# --- lib ---
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)
set(lib ${lib} raylib)

include_directories(${inc})
set_target_properties(${lib} uninstall PROPERTIES FOLDER "Libraries")

# --- exe ---
add_executable(${PROJECT_NAME} ${src})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${tgt_inc})
target_compile_definitions(${PROJECT_NAME} PUBLIC
    SHADER_DIR="${SHADER_DIR}"
    RES_DIR="${RES_DIR}"
    PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
    MACOSX_DEPLOYMENT_TARGET=10.9
)

target_link_libraries(${PROJECT_NAME} ${lib} "-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL")
