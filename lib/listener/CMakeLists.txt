
add_definitions( -D_LOGGER_DLLEXPORT -DLASTFM_COLLAPSE_NAMESPACE)


list(APPEND listener_INCLUDES ${LIBLASTFM_INCLUDE_DIRS})

if(WIN32)
    list(APPEND listener_TARGETS advapi32 user32)
endif()

# basically not easy to support on other platforms, but feel free to fork
if(UNIX AND NOT APPLE)
    list(APPEND listener_SOURCES DBusListener.cpp)
endif()

if(APPLE)
    list(APPEND listener_SOURCES
        mac/ITunesListener.cpp
        mac/SpotifyListener.mm
    )

    find_library(APPKIT_FRAMEWORK AppKit)
    list(APPEND listener_TARGETS ${APPKIT_FRAMEWORK})

    list(APPEND listener_TARGETS unicorn)
endif()

list(APPEND listener_SOURCES
    PlayerMediator.cpp
    PlayerListener.cpp
    PlayerConnection.cpp
    PlayerCommandParser.cpp
    legacy/LegacyPlayerListener.cpp
)

# win32 {
#     SOURCES += win/SpotifyListener.cpp \
#                ../../plugins/iTunes/ITunesTrack.cpp \
#                ../../plugins/iTunes/ITunesComWrapper.cpp \
#                $$ROOT_DIR/plugins/scrobsub/EncodingUtils.cpp \
#                $$ROOT_DIR/lib/3rdparty/iTunesCOMAPI/iTunesCOMInterface_i.c
#
#     HEADERS += win/SpotifyListener.h \
#                ../../plugins/iTunes/ITunesTrack.h \
#                ../../plugins/iTunes/ITunesComWrapper.h \
#                ../../plugins/iTunes/ITunesEventInterface.h \
#                ../../plugins/iTunes/ITunesExceptions.h \
#                $$ROOT_DIR/plugins/scrobsub/EncodingUtils.h
#
#     LIBS += -lcomsuppw
#
#     DEFINES += _WIN32_DCOM
# }

include_directories(${listener_INCLUDES})

add_library(listener SHARED
    ${listener_SOURCES}
)

list(APPEND listener_TARGETS
    ${LIBLASTFM_LIBRARIES}
    ${QT_QTNETWORK_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

set_target_properties(listener PROPERTIES AUTOMOC TRUE)
target_link_libraries(listener ${listener_TARGETS})