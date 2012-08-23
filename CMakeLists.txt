cmake_minimum_required(VERSION 2.8.8)
project(LastFM)


IF( NOT APPLE )
    # Make linking as strict on linux as it is on osx. Then we don't break linking on mac so often
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-undefined" )
ENDIF( NOT APPLE )

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules)

find_package(Qt4 REQUIRED COMPONENTS QtCore QtXml QtGui QtNetwork QtSql)
include(${QT_USE_FILE})

find_package(LibLastFm REQUIRED)

set(LASTFM_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}")

# hack?! resolve this maybe
include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(lib)
add_subdirectory(app)