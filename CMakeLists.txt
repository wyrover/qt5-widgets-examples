cmake_minimum_required(VERSION 3.8.2)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


include(cotire)

project(all)



include(cmake/qt571.cmake)

if (POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

# PROJECT_BINARY_DIR  build 目录
# PROJECT_SOURCE_DIR  顶层 CMakefiles.txt 目录


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


include_directories(${PROJECT_SOURCE_DIR}/3rdparty)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/CuteLogger/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/libuv/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/cef2623)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/botan-2)
link_directories(${LIBRARY_OUTPUT_PATH})
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/libuv/lib/Debug)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/cef2623/lib)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/botan-2/lib)

add_subdirectory(3rdparty/CuteLogger)
add_subdirectory(src/cmake01)
add_subdirectory(src/toolbar01)
add_subdirectory(src/layout01)
add_subdirectory(src/qss-test)
add_subdirectory(src/QTableWidget01)
add_subdirectory(src/QTableWidget02)


message(STATUS "CMakefiles.txt path: ${PROJECT_SOURCE_DIR}")
message(STATUS "build path: ${PROJECT_BINARY_DIR}")
message(STATUS "lib oupt path: ${LIBRARY_OUTPUT_PATH}")
message(STATUS "exe oupt path: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "QT_LIB_DIR: ${QT_LIB_DIR}")