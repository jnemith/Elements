cmake_minimum_required (VERSION 3.11)

project("Elements")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(include)
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR include)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
# set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(GLAD "src/glad.c")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
# find_package(ASSIMP REQUIRED)
set(LIBS GL glfw glm GLAD dl) #vkbootstrap vma glm tinyobjloader imgui stb_image ASSIMP

set(BIN_NAME Elements)
file(GLOB_RECURSE SOURCE "${SRC}/*.cpp")


set(CMAKE_CXX_STANDARD 17)

add_executable(${BIN_NAME} ${SOURCE})

target_link_libraries(${BIN_NAME} ${LIBS})
