cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL LANGUAGES C CXX)

# Output directory magic
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/out")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/archive")

# Compiler things
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 ")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options("-Wall" "-Wextra" "-pedantic")

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

include_directories(include)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# ---------------------------------------------------------------------------
# Glad
# ---------------------------------------------------------------------------
function(add_c_library NAME)
    file(GLOB LIB_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${NAME}/*.c")
    add_library(${NAME} STATIC ${LIB_SOURCES})
    target_include_directories(${NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
endfunction()

add_c_library(glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# ---------------------------------------------------------------------------
# GLFW
# ---------------------------------------------------------------------------
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
