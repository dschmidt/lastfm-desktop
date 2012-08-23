set(APP_VERSION 2.1.20)
add_definitions( -DLASTFM_COLLAPSE_NAMESPACE )

#FIXME: port this to cmake
# # TODO: FIX THIS: I think this means that we can only build bundles
# mac {
#     DESTDIR = "../../_bin/Last.fm.app/Contents/Helpers"
#     QMAKE_POST_LINK += ../../admin/dist/mac/bundleFrameworks.sh \"$$DESTDIR/$$TARGET\"
# }

list(APPEND twiddly_INCLUDES
     ${LIBLASTFM_INCLUDE_DIRS}
)

list(APPEND twiddly_SOURCES
    main.cpp
    TwiddlyApplication.cpp
    PlayCountsDatabase.cpp
    IPod.cpp
    Utils.cpp
)

if(APPLE)
    list(APPEND twiddly_SOURCES
        ITunesLibrary_mac.cpp
        Utils_mac.mm
    )
endif()

list(APPEND twiddly_TARGETS
# internal targets
    unicorn

# external libs
    ${LIBLASTFM_LIBRARIES}
    ${QT_QTSQL_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

include_directories(${twiddly_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(twiddly ${twiddly_SOURCES} ${twiddly_UI_SOURCES}  ${twiddly_RESOURCES})
set_target_properties(twiddly PROPERTIES AUTOMOC TRUE)
target_link_libraries(twiddly ${twiddly_TARGETS})