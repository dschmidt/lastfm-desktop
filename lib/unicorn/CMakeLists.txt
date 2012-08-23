# CONFIG += dll lastfm sparkle growl logger
# QT = core gui xml network
# include( ../../admin/include.qmake )

add_definitions( -D_UNICORN_DLLEXPORT -DLASTFM_COLLAPSE_NAMESPACE )
add_definitions( -DAPI_KEY=\"${LASTFM_API_KEY}\" )
add_definitions( -DAPI_SECRET=\"${LASTFM_API_SECRET}\" )

# UniqueApplication
# win32:LIBS += user32.lib shell32.lib ole32.lib

# macx:LIBS += -framework Cocoa

set(unicorn_INCLUDES
    ${LIBLASTFM_INCLUDE_DIRS}
)

set(unicorn_SOURCES
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
    qtsingleapplication/qtlockedfile_unix.cpp
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
# HEADERS += \
#     widgets/UserToolButton.h \
#     widgets/UserMenu.h \
#     widgets/UserManagerWidget.h \
#     widgets/UserComboSelector.h \
#     widgets/UnicornTabWidget.h \
#     widgets/TrackWidget.h \
#     widgets/TagListWidget.h \
#     widgets/TagBuckets.h \
#     widgets/StatusLight.h \
#     widgets/SpinnerLabel.h \
#     widgets/Seed.h \
#     widgets/SearchBox.h \
#      \
#     widgets/MessageBar.h \
#     widgets/LfmListViewWidget.h \
#     widgets/Label.h \
#     widgets/ItemSelectorWidget.h \
#     widgets/ImageButton.h \
#     widgets/HttpImageWidget.h \
#     widgets/GhostWidget.h \
#     widgets/FriendsPicker.h \
#     widgets/DataListWidget.h \
#     widgets/DataBox.h \
#     widgets/BannerWidget.h \
#     widgets/ActionButton.h \
#     UpdateInfoFetcher.h \
#     UnicornSettings.h \
#     UnicornSession.h \
#     UnicornMainWindow.h \
#     UnicornCoreApplication.h \
#     UnicornApplication.h \
#     TrackImageFetcher.h \
#     SignalBlocker.h \
#     ScrobblesModel.h \
#     qtwin.h \
#     qtsingleapplication/qtsinglecoreapplication.h \
#     qtsingleapplication/qtsingleapplication.h \
#     qtsingleapplication/qtlockedfile.h \
#     qtsingleapplication/qtlocalpeer.h \
#     QMessageBoxBuilder.h \
#     PlayBus.h \
#     LoginProcess.h \
#     layouts/SlideOverLayout.h \
#     layouts/SideBySideLayout.h \
#     layouts/AnimatedListLayout.h \
#     dialogs/UserManagerDialog.h \
#     dialogs/UpdateDialog.h \
#     dialogs/UnicornDialog.h \
#     dialogs/TagDialog.h \
#     dialogs/LoginDialog.h \
#     dialogs/LoginContinueDialog.h \
#     dialogs/AboutDialog.h \
#     dialogs/ScrobbleConfirmationDialog.h \
#     AnimatedStatusBar.h \
#     AnimatedPushButton.h \
#     dialogs/ShareDialog.h \
#     widgets/AvatarWidget.h \
#     layouts/FlowLayout.h \
#     widgets/SlidingStackedWidget.h \
#     Updater/Updater.h \
#     DesktopServices.h \
#     widgets/StackedWidget.h

#FIXME: move to own target
#win32:SOURCES += qtsingleapplication/qtlockedfile_win.cpp

if(APPLE)
    list(APPEND unicorn_SOURCES
    # cpp
    mac/AppleScript.cpp

    # obj-c
    UnicornApplication_mac.mm
    notify/Notify.mm
    Updater/Updater_mac.mm
    UnicornApplicationDelegate.mm
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

qt4_add_resources(unicorn_RESOURCES qrc/unicorn.qrc)

include_directories(${unicorn_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_library(unicorn SHARED
    ${unicorn_SOURCES}
    ${unicorn_UI_SOURCES}
    ${unicorn_RESOURCES}
)
set_target_properties(unicorn PROPERTIES AUTOMOC TRUE)
target_link_libraries(unicorn ${unicorn_TARGETS})
