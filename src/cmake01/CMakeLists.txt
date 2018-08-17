cmake_minimum_required(VERSION 3.8.2)

project(helloworld)


set(CMAKE_PREFIX_PATH $ENV{QTDIR571})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# There may be a way to tell up front if Qt5 is going to be found, but I haven't found
# a foolproof way to do it yet, so settle for the default error message for now.
#if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
#            "environment variable to the install prefix of Qt 5, either on the command line as "
#            "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
#endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

# Add a compiler flag
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
  add_definitions(/D_CRT_SECURE_NO_WARNINGS /D_USING_V110_SDK71_)
endif()



# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)



# Generate rules for building source files from the resources
qt5_add_resources(QRCS resources.qrc)


# Generate code from ui files
set(UI_HEADERS mainwindow.ui)


set(SOURCE_FILES main.cpp mainwindow.cpp)

# Tell CMake to create the helloworld executable
add_executable(helloworld ${SOURCE_FILES} ${UI_HEADERS} ${QRCS})




# Add the Qt5 Widgets for linking
target_link_libraries(helloworld 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets 
    ${Qt5Platform_LIBRARIES} 
    ${Qt5QWindows_LIBRARIES} 
    ${Qt5PNG_LIBRARIES} 
    ${Qt5QICO_LIBRARIES} 
    ${Qt5HB_LIBRARIES} 
    ${Qt5FT_LIBRARIES} 
    ${Qt5PCRE_LIBRARIES} 
    ${Qt5QSVGICON_LIBRARIES} 
    ${Qt5SVG_LIBRARIES} 
    ws2_32 
    Imm32 
    Winmm
    CuteLogger
)

set_target_properties(helloworld PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
