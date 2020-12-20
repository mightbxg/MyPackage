cmake_minimum_required(VERSION 3.11)

# project configuration
project(MyPackage
    LANGUAGES CXX
    VERSION 1.0.0)
message(STATUS "MyPackage (CMake project sample)")
message(STATUS "Version: ${PROJECT_VERSION}")

configure_file(Version.cmake.in MyPackage/Version.h)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "release" CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
option(BUILD_SHARED_LIBS "Build using shared libs" ON)
message(STATUS "Build shared libs: ${BUILD_SHARED_LIBS}")

# packages
find_package(OpenCV COMPONENTS core REQUIRED)
find_package(Eigen3 REQUIRED)

# main library
set(PROJECT_MAIN_LIB "MyLib")
file(GLOB_RECURSE HEADERS_FOR_IDE
    "${CMAKE_SOURCE_DIR}/include/*.h"
    "${CMAKE_SOURCE_DIR}/include/*.hpp")
add_library(${PROJECT_MAIN_LIB}
    ${HEADERS_FOR_IDE}
    src/MyFuncs.cpp)
add_library(Mine::MyLib ALIAS ${PROJECT_MAIN_LIB})

target_compile_features(${PROJECT_MAIN_LIB} PRIVATE cxx_std_11)
target_compile_options(${PROJECT_MAIN_LIB} PRIVATE
    "-Wall;-Wextra;-Wformat=2;-Wunused;-Wshadow")
target_include_directories(${PROJECT_MAIN_LIB} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include;${PROJECT_BINARY_DIR}>"
    "$<INSTALL_INTERFACE:include>")
target_link_libraries(${PROJECT_MAIN_LIB} PUBLIC
    opencv_core
    Eigen3::Eigen)

# samples
option(BUILD_SAMPLES "Build sample executables" ON)
if(BUILD_SAMPLES)
    add_subdirectory(samples)
endif()

# tests
include(CTest)
if(BUILD_TESTING)
    option(INSTALL_GTEST "" OFF)
    # fetch GoogleTest from gitee
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY  https://gitee.com/york_chen/googletest.git
        GIT_TAG         release-1.10.0)
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    endif()

    include(GoogleTest)
    add_subdirectory(tests)
endif()

# installation
# install headers
install(DIRECTORY include
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp")
# install version info header
install(FILES "${PROJECT_BINARY_DIR}/MyPackage/Version.h"
    DESTINATION include/MyPackage)
# install and export target
install(TARGETS ${PROJECT_MAIN_LIB}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
# generate and install Targets.cmake
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE Mine::
    DESTINATION lib/cmake/${PROJECT_NAME})
# generate and install Config.cmake & ConfigVersion.cmake
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_SOURCE_DIR}/Config.cmake.in
    ${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "lib/cmake/${PROJECT_NAME}")
# export Targets.cmake to build directory
export(TARGETS ${PROJECT_MAIN_LIB}
    NAMESPACE Mine::
    FILE ${PROJECT_NAME}Targets.cmake)
