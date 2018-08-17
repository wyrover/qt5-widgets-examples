cmake_minimum_required(VERSION 3.8.2)
PROJECT(CuteLogger)

set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH $ENV{QTDIR571})
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# include
set(SRC_DIR "./src")
set(INCLUDE_DIR "./include")
include_directories(${INCLUDE_DIR})


# source
aux_source_directory(${SRC_DIR} SRC_FILES)
list(REMOVE_ITEM SRC_FILES ${SRC_DIR}/AndroidAppender.cpp)

# target
add_library(CuteLogger STATIC ${SRC_FILES})
target_link_libraries(CuteLogger 
    Qt5::Core     
)

