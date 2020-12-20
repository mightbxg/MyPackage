find_package(OpenCV COMPONENTS imgcodecs REQUIRED)

include(CMakeParseArguments)

function(package_add_test)
    set(options)
    set(oneValueArgs TARGET WORKING_DIRECTORY)
    set(multiValueArgs FILES LIBRARIES)
    cmake_parse_arguments(_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if(NOT _TEST_TARGET)
        message(FATAL_ERROR "Target name not provided!")
    endif(NOT _TEST_TARGET)
    add_executable(${_TEST_TARGET} ${_TEST_FILES})
    target_link_libraries(${_TEST_TARGET} gtest gmock gtest_main ${_TEST_LIBRARIES})
    gtest_discover_tests(${_TEST_TARGET}
        WORKING_DIRECTORY ${_TEST_WORKING_DIRECTORY}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${_TEST_WORKING_DIRECTORY}")
endfunction(package_add_test)

package_add_test(TARGET test_myfuncs
    FILES test_myfuncs.cpp
    LIBRARIES Mine::MyLib opencv_imgcodecs
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
