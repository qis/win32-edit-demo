cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(win32-edit-demo DESCRIPTION "Win32 Edit Demo" VERSION 0.1.0 LANGUAGES CXX)

# Set resource compiler flags.
set(CMAKE_RC_FLAGS "/nologo -c65001 /DWIN32" CACHE STRING "" FORCE)

# Version
set(PROJECT_VENDOR "Company")
configure_file(res/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/version.h LF)

# Sources
file(GLOB_RECURSE sources src/*.[hc]pp)

# Executable
add_executable(${PROJECT_NAME} WIN32 ${sources} src/main.manifest src/main.rc src/resource.rc)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/main.hpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Dependencies
target_include_directories(${PROJECT_NAME} PRIVATE third_party/wtl/include)

# Install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
