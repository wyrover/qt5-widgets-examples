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


if(MSVC)
    add_definitions(-DWIN32 -D_WINDOWS -D_CRT_SECURE_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS -D_USE_MATH_DEFINES=1 -DNOMINMAX)
    add_compile_options("/Zc:threadSafeInit-")


    # Force /MT for static VC runtimes if Release...
    foreach(flag_var
        CMAKE_C_FLAGS CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif()
    endforeach()
endif()


# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)




if(WIN32 AND MSVC)
    # For static Windows builds, we also need to pull in the Qt5 Platform
    # support library, which is not exposed to CMake properly, unfortunately
    GET_TARGET_PROPERTY(QT_LIB_DIR "${Qt5Widgets_LIBRARIES}" LOCATION)
    GET_FILENAME_COMPONENT(QT_LIB_DIR "${QT_LIB_DIR}" PATH)

    # Qt5PlatformSupport
    FIND_LIBRARY(Qt5Platform_LIBRARIES_RELEASE Qt5PlatformSupport
        HINTS "${QT_LIB_DIR}"
    )
    FIND_LIBRARY(Qt5Platform_LIBRARIES_DEBUG Qt5PlatformSupportd
        HINTS "${QT_LIB_DIR}"
    )

    # Qt5Svg
    FIND_LIBRARY(Qt5SVG_LIBRARIES_RELEASE Qt5Svg
        HINTS "${QT_LIB_DIR}"
    )
    FIND_LIBRARY(Qt5SVG_LIBRARIES_DEBUG Qt5Svgd
        HINTS "${QT_LIB_DIR}"
    )

    # qwindows
    FIND_LIBRARY(Qt5QWindows_LIBRARIES_RELEASE qwindows
        HINTS "${QT_LIB_DIR}/../plugins/platforms"
    )
    FIND_LIBRARY(Qt5QWindows_LIBRARIES_DEBUG qwindowsd
        HINTS "${QT_LIB_DIR}/../plugins/platforms"
    )


    # qico
    FIND_LIBRARY(Qt5QICO_LIBRARIES_RELEASE qico
        HINTS "${QT_LIB_DIR}/../plugins/imageformats"
    )
    FIND_LIBRARY(Qt5QICO_LIBRARIES_DEBUG qicod
        HINTS "${QT_LIB_DIR}/../plugins/imageformats"
    )


    # qsvg
    FIND_LIBRARY(Qt5QSVG_LIBRARIES_RELEASE qsvg
        HINTS "${QT_LIB_DIR}/../plugins/imageformats"
    )
    FIND_LIBRARY(Qt5QSVG_LIBRARIES_DEBUG qsvgd
        HINTS "${QT_LIB_DIR}/../plugins/imageformats"
    )


    # qsvgicon
    FIND_LIBRARY(Qt5QSVGICON_LIBRARIES_RELEASE qsvgicon
        HINTS "${QT_LIB_DIR}/../plugins/iconengines"
    )
    FIND_LIBRARY(Qt5QSVGICON_LIBRARIES_DEBUG qsvgicond
        HINTS "${QT_LIB_DIR}/../plugins/iconengines"
    )

    # qtharfbuzzng
    FIND_LIBRARY(Qt5HB_LIBRARIES_RELEASE qtharfbuzzng
        HINTS "${QT_LIB_DIR}"
    )
    FIND_LIBRARY(Qt5HB_LIBRARIES_DEBUG qtharfbuzzngd
        HINTS "${QT_LIB_DIR}"
    )

    # qtfreetype
    FIND_LIBRARY(Qt5FT_LIBRARIES_RELEASE qtfreetype
        HINTS "${QT_LIB_DIR}"
    )
    FIND_LIBRARY(Qt5FT_LIBRARIES_DEBUG qtfreetyped
        HINTS "${QT_LIB_DIR}"
    )

    # qtpcre
    FIND_LIBRARY(Qt5PCRE_LIBRARIES_RELEASE qtpcre
        HINTS "${QT_LIB_DIR}"
    )
    FIND_LIBRARY(Qt5PCRE_LIBRARIES_DEBUG qtpcred
        HINTS "${QT_LIB_DIR}"
    )

    # qtpng
    FIND_LIBRARY(Qt5PNG_LIBRARIES_RELEASE qtpng
        HINTS "${QT_LIB_DIR}"
    )
    FIND_LIBRARY(Qt5PNG_LIBRARIES_DEBUG qtpngd
        HINTS "${QT_LIB_DIR}"
    )   


    # qsqlite
    FIND_LIBRARY(Qt5SQLITE_LIBRARIES_RELEASE qsqlite
        HINTS "${QT_LIB_DIR}/../plugins/sqldrivers"
    )
    FIND_LIBRARY(Qt5SQLITE_LIBRARIES_DEBUG qsqlited
        HINTS "${QT_LIB_DIR}/../plugins/sqldrivers"
    )  

   


    SET(Qt5SVG_LIBRARIES optimized ${Qt5SVG_LIBRARIES_RELEASE} debug ${Qt5SVG_LIBRARIES_DEBUG})
    SET(Qt5Platform_LIBRARIES optimized ${Qt5Platform_LIBRARIES_RELEASE} debug ${Qt5Platform_LIBRARIES_DEBUG})
    SET(Qt5QWindows_LIBRARIES optimized ${Qt5QWindows_LIBRARIES_RELEASE} debug ${Qt5QWindows_LIBRARIES_DEBUG})
    SET(Qt5QICO_LIBRARIES optimized ${Qt5QICO_LIBRARIES_RELEASE} debug ${Qt5QICO_LIBRARIES_DEBUG})
    SET(Qt5HB_LIBRARIES optimized ${Qt5HB_LIBRARIES_RELEASE} debug ${Qt5HB_LIBRARIES_DEBUG})
    SET(Qt5FT_LIBRARIES optimized ${Qt5FT_LIBRARIES_RELEASE} debug ${Qt5FT_LIBRARIES_DEBUG})    
    SET(Qt5PCRE_LIBRARIES optimized ${Qt5PCRE_LIBRARIES_RELEASE} debug ${Qt5PCRE_LIBRARIES_DEBUG})
    SET(Qt5PNG_LIBRARIES optimized ${Qt5PNG_LIBRARIES_RELEASE} debug ${Qt5PNG_LIBRARIES_DEBUG})
    SET(Qt5QSVGICON_LIBRARIES optimized ${Qt5QSVGICON_LIBRARIES_RELEASE} debug ${Qt5QSVGICON_LIBRARIES_DEBUG})
    SET(Qt5QSVG_LIBRARIES optimized ${Qt5QSVG_LIBRARIES_RELEASE} debug ${Qt5QSVG_LIBRARIES_DEBUG})
    SET(Qt5SQLITE_LIBRARIES optimized ${Qt5SQLITE_LIBRARIES_RELEASE} debug ${Qt5SQLITE_LIBRARIES_DEBUG})

    
    ADD_DEFINITIONS(-DSTATIC_QT5)
endif()
