cmake_minimum_required(VERSION 2.8)
PROJECT(CuteLogger)

set(CMAKE_PREFIX_PATH $ENV{QTDIR571})
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)



set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

aux_source_directory(${SRC_DIR} SRC_FILES)
list(REMOVE_ITEM SRC_FILES ${SRC_DIR}/AndroidAppender.cpp)


include_directories(${INCLUDE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ./bin)
SET(LIBRARY_OUTPUT_PATH ./lib)

set(CMAKE_AUTOMOC ON)

# add_subdirectory(./src/base)


add_library(CuteLogger STATIC ${SRC_FILES})

target_link_libraries(CuteLogger 
    Qt5::Core     
)

