project(Tutorial)
cmake_minimum_required(VERSION 3.0)

set(TAICHI_C_API_INSTALL_DIR $ENV{TAICHI_C_API_INSTALL_DIR})

# Find built taichi C-API library in `TAICHI_C_API_INSTALL_DIR`.
find_library(taichi_c_api taichi_c_api HINTS ${TAICHI_C_API_INSTALL_DIR}/lib NO_CMAKE_FIND_ROOT_PATH)
if (NOT EXISTS ${taichi_c_api})
    message(FATAL_ERROR "Couldn't find C-API library in ${TAICHI_C_API_INSTALL_DIR}")
endif()

# Make sure your target is properly linked!
set(TAICHI_TUTORIAL_DEMO_NAME "0_tutorial_kernel")
message("-- Building ${TAICHI_TUTORIAL_DEMO_NAME}")
add_executable(${TAICHI_TUTORIAL_DEMO_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp)
target_include_directories(${TAICHI_TUTORIAL_DEMO_NAME} PUBLIC ${TAICHI_C_API_INSTALL_DIR}/include)
target_link_libraries(${TAICHI_TUTORIAL_DEMO_NAME} ${taichi_c_api})
