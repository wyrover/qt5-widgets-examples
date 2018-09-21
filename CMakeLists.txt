cmake_minimum_required(VERSION 3.8.2)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


include(cotire)

project(all)



include(cmake/qt571.cmake)
include(cmake/generate_demo.cmake)

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
add_subdirectory(3rdparty/cactus)
add_subdirectory(src/cmake01)
#add_subdirectory(src/toolbar01)
#add_subdirectory(src/layout01)
add_subdirectory(src/qss-test)
#add_subdirectory(src/svg-01)
generate_demo("svg-01")
generate_demo("popup-01")
generate_demo("popup-02")
generate_demo("border-image-01")
generate_demo("tooltip-01")

message(STATUS "CMakefiles.txt path: ${PROJECT_SOURCE_DIR}")
message(STATUS "build path: ${PROJECT_BINARY_DIR}")
message(STATUS "lib oupt path: ${LIBRARY_OUTPUT_PATH}")
message(STATUS "exe oupt path: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "QT_LIB_DIR: ${QT_LIB_DIR}")





# generate_demo("toolbar01")
# generate_demo("HBoxLayout-01")
# generate_demo("HBoxLayout-02")
# generate_demo("HBoxLayout-03")
# generate_demo("HBoxLayout-04")
# generate_demo("HBoxLayout-05")
# generate_demo("HBoxLayout-06")
# generate_demo("HBoxLayout-07")
# generate_demo("HBoxLayout-08")

# generate_demo("FormLayout-01")
# generate_demo("FormLayout-02")

# generate_demo("GridLayout-01")
# generate_demo("GridLayout-02")

# generate_demo("Splitter-01")
# generate_demo("Splitter-02")

# generate_demo("StackedLayout-01")



# generate_demo("QTableWidget01")
# generate_demo("QTableWidget02")

# generate_demo("Event-01")
# generate_demo("Event-02")
# generate_demo("Event-03")
# generate_demo("Event-04")
# generate_demo("Event-05")
 generate_demo("Event-06")

# generate_demo("QDockWidget-01")
# generate_demo("QDockWidget-02")

# generate_demo("QStackedWidget-01")

# generate_demo("QSplitter-01")

# generate_demo("QTabWidget-01")

# generate_demo("animation-01")
# generate_demo("animation-02")
# generate_demo("animation-03")
# generate_demo("animation-04")
generate_demo("animation-05")
generate_demo("animation-06")
generate_demo("animation-07")
generate_demo("animation-08")

# generate_demo("itemanimation-01")


# generate_demo("QComboBox-01")

# generate_demo("addressbook")

# generate_demo("dock-01")

# generate_demo("delegate-01")
# generate_demo("delegate-02")

# generate_demo("model-01")
# generate_demo("model-02")
# generate_demo("treemodel")

# generate_demo("size-01")



# generate_demo("QDockWidgetDemo")

# generate_demo("QStringListModel")

# generate_demo("FontAwesome")
# generate_demo("tagbuttton")

# generate_demo("HTYImageViewer")

# generate_demo("KuWo")
# generate_demo("Qt_QQMusic")
# generate_demo("Qt_StandardPixmap")
# generate_demo("HTYEdit")
# generate_demo("NeteaseMusic")
# generate_demo("HTYFloatBall")
# generate_demo("HTYPaint_Qt")
# generate_demo("deepin-weather")
# generate_demo("HTYStartMenu")
# generate_demo("HTYGIFPlayer")
# generate_demo("HTYDown")
# generate_demo("rili")
# generate_demo("monitor-desktop")
 generate_demo("CusButtonGroup")
# generate_demo("TreeWidget")
# generate_demo("DockDemo")
