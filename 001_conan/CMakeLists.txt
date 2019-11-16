cmake_minimum_required( VERSION 3.15 )
project(conan_demo CXX)

set( CMAKE_CXX_STANDARD 17 )

# Download automatically, you can also just copy the conan.cmake file
if( NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake" )
   message( STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan" )
   file( DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake" )
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run( CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS BUILD missing )

add_executable( conan_demo
    src/main.cpp
    src/FaceDetector.cpp
    src/CameraFeed.cpp
)
target_link_libraries( conan_demo PRIVATE CONAN_PKG::opencv CONAN_PKG::boost )
