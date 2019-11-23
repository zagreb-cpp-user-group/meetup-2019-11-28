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

set( SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/../src )

set( SOURCES
    ${SRC_ROOT}/main.cpp
    ${SRC_ROOT}/FaceDetector.cpp
    ${SRC_ROOT}/CameraFeed.cpp
)

if ( APPLE )
    list( APPEND SOURCES ${SRC_ROOT}/AppleCameraPermission.mm )
endif()

add_executable( conan_demo ${SOURCES} )
target_link_libraries( conan_demo PRIVATE CONAN_PKG::opencv CONAN_PKG::boost )
