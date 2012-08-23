# CONFIG += dll lastfm sparkle growl logger
# QT = core gui xml network
# include( ../../admin/include.qmake )

#FIXME: add checks for growl

add_definitions( -D_UNICORN_DLLEXPORT -DLASTFM_COLLAPSE_NAMESPACE )
add_definitions( -DAPI_KEY=\"${LASTFM_API_KEY}\" )
add_definitions( -DAPI_SECRET=\"${LASTFM_API_SECRET}\" )

# UniqueApplication
# win32:LIBS += user32.lib shell32.lib ole32.lib

# macx:LIBS += -framework Cocoa

set(unicorn_INCLUDES
    ${LIBLASTFM_INCLUDE_DIRS}
)

list(APPEND unicorn_SOURCES
    dialogs/ShareDialog.cpp
    widgets/AvatarWidget.cpp
    layouts/FlowLayout.cpp
    widgets/UserMenu.cpp
    widgets/SlidingStackedWidget.cpp
    widgets/UserToolButton.cpp
    widgets/UserManagerWidget.cpp
    widgets/UnicornTabWidget.cpp
    widgets/TrackWidget.cpp
    widgets/TagListWidget.cpp
    widgets/TagBuckets.cpp
    widgets/StatusLight.cpp
    widgets/SearchBox.cpp
    widgets/MessageBar.cpp
    widgets/LfmListViewWidget.cpp
    widgets/Label.cpp
    widgets/ItemSelectorWidget.cpp
    widgets/ImageButton.cpp
    widgets/HttpImageWidget.cpp
    widgets/GhostWidget.cpp
    widgets/FriendsPicker.cpp
    widgets/DataListWidget.cpp
    widgets/BannerWidget.cpp
    widgets/ActionButton.cpp
    UpdateInfoFetcher.cpp
    UnicornSettings.cpp
    UnicornSession.cpp
    UnicornMainWindow.cpp
    UnicornCoreApplication.cpp
    UnicornApplication.cpp
    TrackImageFetcher.cpp
    ScrobblesModel.cpp
    qtwin.cpp

#FIXME: move to 3rdparty and make own target
    qtsingleapplication/qtsinglecoreapplication.cpp
    qtsingleapplication/qtsingleapplication.cpp
    qtsingleapplication/qtlockedfile.cpp
    qtsingleapplication/qtlocalpeer.cpp

    QMessageBoxBuilder.cpp
    LoginProcess.cpp
    layouts/SlideOverLayout.cpp
    layouts/SideBySideLayout.cpp
    layouts/AnimatedListLayout.cpp
    dialogs/UserManagerDialog.cpp
    dialogs/UpdateDialog.cpp
    dialogs/TagDialog.cpp
    dialogs/LoginDialog.cpp
    dialogs/LoginContinueDialog.cpp
    dialogs/AboutDialog.cpp
    dialogs/ScrobbleConfirmationDialog.cpp
    AnimatedStatusBar.cpp
    DesktopServices.cpp
    Updater/Updater.cpp
    widgets/StackedWidget.cpp


    # header only
    dialogs/UnicornDialog.h
    widgets/PlayableMimeData.h
    SignalBlocker.h
    PlayBus.h
)


#FIXME: move to own target
if(UNIX)
    list(APPEND unicorn_SOURCES qtsingleapplication/qtlockedfile_unix.cpp)
elseif(WIN32)
    list(APPEND unicorn_SOURCES qtsingleapplication/qtlockedfile_win.cpp)
endif()

if(APPLE)
    list(APPEND unicorn_SOURCES
    # cpp
    mac/AppleScript.cpp

    # obj-c
    UnicornApplication_mac.mm
    notify/Notify.mm
    Updater/Updater_mac.mm
    UnicornApplicationDelegate.mm

    # headers
#     mac/AppleScript.cpp
#     notify/Notify.h
#     UnicornApplicationDelegate.h
    )
endif()


# macx:HEADERS += mac/AppleScript.h \
#                 notify/Notify.h \
#                 UnicornApplicationDelegate.h

#FIXME: re-enable breakpad
# CONFIG( break ) {
#     HEADERS += CrashReporter/CrashReporter.h
#     SOURCES += CrashReporter/CrashReporter.cpp
#     macx:OBJECTIVE_SOURCES += CrashReporter/CrashReporter_mac.mm
# }

qt4_wrap_ui(unicorn_UI_SOURCES
    dialogs/ShareDialog.ui
    dialogs/LoginDialog.ui
    dialogs/TagDialog.ui
    dialogs/AboutDialog.ui
)

list(APPEND unicorn_TARGETS
    logger
    ${LIBLASTFM_LIBRARIES}
    ${QT_QTXML_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

if(APPLE)
    find_library(GROWL_FRAMEWORK Growl)
    list(APPEND unicorn_TARGETS ${GROWL_FRAMEWORK})

    find_library(SPARKLE_FRAMEWORK Sparkle)
    list(APPEND unicorn_TARGETS ${SPARKLE_FRAMEWORK})

    find_library(CARBON_FRAMEWORK Carbon)
    list(APPEND unicorn_TARGETS ${CARBON_FRAMEWORK})

    find_library(FOUNDATION_FRAMEWORK Foundation)
    list(APPEND unicorn_TARGETS ${FOUNDATION_FRAMEWORK})

    find_library(APPKIT_FRAMEWORK AppKit)
    list(APPEND unicorn_TARGETS ${APPKIT_FRAMEWORK})
endif()

if(WIN32)
    list(APPEND unicorn_TARGETS user32 shell32 ole32)
endif()

qt4_add_resources(unicorn_RESOURCES qrc/unicorn.qrc)

include_directories(${unicorn_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_library(unicorn SHARED
    ${unicorn_SOURCES}
    ${unicorn_UI_SOURCES}
    ${unicorn_RESOURCES}
)
set_target_properties(unicorn PROPERTIES AUTOMOC TRUE)
target_link_libraries(unicorn ${unicorn_TARGETS})
