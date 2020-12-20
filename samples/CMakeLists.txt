find_package(OpenCV COMPONENTS imgcodecs REQUIRED)

add_executable(GetArea GetArea.cpp)
target_link_libraries(GetArea PRIVATE Mine::MyLib opencv_imgcodecs)
