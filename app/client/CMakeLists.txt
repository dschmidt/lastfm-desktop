set(APP_VERSION 2.1.20)
add_definitions( -DLASTFM_COLLAPSE_NAMESPACE -DAPP_VERSION=\"${APP_VERSION}\")

list(APPEND lastfm_INCLUDES
    ${LIBLASTFM_INCLUDE_DIRS}
)

list(APPEND lastfm_SOURCES
    AudioscrobblerSettings.cpp
    Application.cpp
    StationSearch.cpp
    ScrobSocket.cpp
    MediaDevices/MediaDevice.cpp
    MediaDevices/IpodDevice.cpp
    MediaDevices/DeviceScrobbler.cpp
    MainWindow.cpp
    main.cpp
    Settings/SettingsWidget.cpp
    Settings/ScrobbleSettingsWidget.cpp
    Settings/IpodSettingsWidget.cpp
    Settings/AccountSettingsWidget.cpp
    Settings/PreferencesDialog.cpp
    Settings/AdvancedSettingsWidget.cpp
    Settings/GeneralSettingsWidget.cpp
    Services/ScrobbleService/StopWatch.cpp
    Services/ScrobbleService/ScrobbleService.cpp
    Services/RadioService/RadioService.cpp
    Services/RadioService/RadioConnection.cpp
    Dialogs/ScrobbleSetupDialog.cpp
    Dialogs/DiagnosticsDialog.cpp
    Bootstrapper/PluginBootstrapper.cpp
    Bootstrapper/ITunesDevice/itunesdevice.cpp
    Bootstrapper/iTunesBootstrapper.cpp
    Bootstrapper/AbstractFileBootstrapper.cpp
    Bootstrapper/AbstractBootstrapper.cpp
    Widgets/TitleBar.cpp
    Widgets/TagFilterDialog.cpp
    Widgets/StatusBar.cpp
    Widgets/SideBar.cpp
    Widgets/RadioWidget.cpp
    Widgets/NothingPlayingWidget.cpp
    Widgets/NowPlayingStackedWidget.cpp
    Widgets/ProfileWidget.cpp
    Widgets/FriendListWidget.cpp
    Widgets/FriendWidget.cpp
    Widgets/BioWidget.cpp
    Widgets/MetadataWidget.cpp
    Widgets/TagWidget.cpp
    Widgets/ShortcutEdit.cpp
    Widgets/ProfileArtistWidget.cpp
    Widgets/ScrobbleControls.cpp
    Widgets/ProgressBar.cpp
    Widgets/QuickStartWidget.cpp
    Widgets/PointyArrow.cpp
    Widgets/PlaybackControlsWidget.cpp
    Widgets/PlayableItemWidget.cpp
    Widgets/NowPlayingWidget.cpp
    Widgets/RefreshButton.cpp
    Widgets/WidgetTextObject.cpp
    Wizard/LoginPage.cpp
    Wizard/BootstrapPage.cpp
    Wizard/FirstRunWizard.cpp
    Wizard/AccessPage.cpp
    Wizard/TourMetadataPage.cpp
    Wizard/PluginsPage.cpp
    Wizard/TourRadioPage.cpp
    Wizard/TourFinishPage.cpp
    Wizard/PluginsInstallPage.cpp
    Wizard/BootstrapProgressPage.cpp
    Wizard/TourScrobblesPage.cpp
    Wizard/TourLocationPage.cpp
    Wizard/WizardPage.cpp
    Widgets/ContextLabel.cpp
    Widgets/SimilarArtistWidget.cpp
    Widgets/PushButton.cpp
    Dialogs/BetaDialog.cpp
    Dialogs/CloseAppsDialog.cpp
    Widgets/TrackWidget.cpp
    Dialogs/LicensesDialog.cpp
    Widgets/ScrobblesWidget.cpp
    Widgets/ScrobblesListWidget.cpp
    Fingerprinter/AacSource.cpp
    Fingerprinter/Fingerprinter.cpp
    Fingerprinter/FlacSource.cpp
    Fingerprinter/MadSource.cpp
    Fingerprinter/VorbisSource.cpp
)

if(UNIX AND NOT APPLE)
    list(APPEND lastfm_SOURCES MediaDevices/IpodDevice_linux.cpp)
elseif(APPLE)
    list(APPEND lastfm_SOURCES
        CommandReciever/CommandReciever.mm
        Dialogs/CloseAppsDialog_mac.mm
        Widgets/NothingPlayingWidget_mac.mm
        MediaKeys/MediaKey.mm
        Services/ITunesPluginInstaller/ITunesPluginInstaller_mac.cpp

        # headers
        Services/ITunesPluginInstaller/ITunesPluginInstaller.h

#FIXME: should be an extra target
        ../../lib/3rdparty/SPMediaKeyTap/SPMediaKeyTap.m
        ../../lib/3rdparty/SPMediaKeyTap/SPInvocationGrabbing/NSObject+SPInvocationGrabbing.m
    )
endif()

qt4_wrap_ui(lastfm_UI_SOURCES
    Widgets/TagFilterDialog.ui
    Widgets/PlaybackControlsWidget.ui
    Dialogs/ScrobbleSetupDialog.ui
    Dialogs/DiagnosticsDialog.ui
    Widgets/MetadataWidget.ui
    Settings/PreferencesDialog.ui
    Settings/GeneralSettingsWidget.ui
    Settings/AccountSettingsWidget.ui
    Settings/IpodSettingsWidget.ui
    Settings/ScrobbleSettingsWidget.ui
    Settings/AdvancedSettingsWidget.ui
    Wizard/FirstRunWizard.ui
    Widgets/NothingPlayingWidget.ui
    Widgets/FriendWidget.ui
    Widgets/FriendListWidget.ui
    Dialogs/BetaDialog.ui
    Dialogs/CloseAppsDialog.ui
    Widgets/TrackWidget.ui
    Dialogs/LicensesDialog.ui
    Widgets/ScrobblesWidget.ui
    Widgets/ProfileWidget.ui
)

qt4_add_resources(lastfm_RESOURCES qrc/audioscrobbler.qrc)

list(APPEND lastfm_TARGETS
# internal targets
    unicorn
    listener

# external libs
    ${LIBLASTFM_LIBRARIES}
    ${QT_QTNETWORK_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTSQL_LIBRARY}
    ${QT_QTCORE_LIBRARY}

#FIXME: use proper find modules
#     gpod
    faad
    vorbisfile
    FLAC
    mp4ff
    mad
    z

    /usr/local/lib/liblastfm_fingerprint.dylib
    /usr/local/Cellar/kde-phonon/4.6.0/lib/libphonon.4.6.0.dylib
)

include_directories(${lastfm_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}
# stupid hack for cmake/automoc/uic broken-ness, just add ANY subdir
${CMAKE_CURRENT_LIST_DIR}/Settings/

#FIXME: use find module
#     /usr/include/gpod-1.0/
#     /usr/include/glib-2.0/ /usr/lib64/glib-2.0/include/
)

add_executable(lastfm ${lastfm_SOURCES} ${lastfm_UI_SOURCES}  ${lastfm_RESOURCES})
set_target_properties(lastfm PROPERTIES AUTOMOC TRUE)
target_link_libraries(lastfm ${lastfm_TARGETS})