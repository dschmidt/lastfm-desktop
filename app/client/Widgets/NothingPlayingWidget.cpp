
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "../Application.h"

#include "QuickStartWidget.h"

#include "lib/unicorn/widgets/Label.h"

#include "NothingPlayingWidget.h"

#ifdef Q_OS_MAC
#define ITUNES_BUNDLEID "com.apple.iTunes"
#include <ApplicationServices/ApplicationServices.h>

//This macro clashes with Qt headers
#undef check
#endif

NothingPlayingWidget::NothingPlayingWidget( QWidget* parent )
    :StylableWidget( parent )
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );

    layout->addWidget( ui.hello = new Label( tr( "Hello! Let's start a RadioStation..." ) ) );
    ui.hello->setObjectName( "hello" );
    setUser( User() );

    layout->addWidget( ui.type = new QLabel( tr( "Type an artist or genre into the box and press play, or visit the Radio tab for more advanced options." ) ) );
    ui.type->setObjectName( "type" );
    ui.type->setWordWrap( true );

    layout->addWidget( ui.quickStart = new QuickStartWidget( this ) );
    ui.quickStart->setObjectName( "quickStart" );

    layout->addWidget( ui.split = new QLabel( tr( "OR" ) ) );
    ui.split->setObjectName( "split" );

    layout->addWidget( ui.scrobble = new QLabel( tr( "Scrobble from your music player." ) ) );
    ui.scrobble->setObjectName( "scrobble" );

    layout->addWidget( ui.scrobbleExplain = new QLabel( tr( "Effortlessly keep your Last.fm profile updated with the tracks you're playing on other media players. You can see more about the track you're playing on the scrobbles tab." ) ) );
    ui.scrobbleExplain->setObjectName( "scrobbleExplain" );
    ui.scrobbleExplain->setWordWrap( true );

#if  defined( Q_OS_WIN32 ) || defined( Q_OS_MAC )
    layout->addWidget( ui.clickPlayers = new QLabel( tr( "Click on a player below to launch it." ) ) );
    ui.clickPlayers->setObjectName( "clickPlayers" );

    layout->addWidget( ui.players = new StylableWidget );
    ui.players->setObjectName( "players" );
    QHBoxLayout* hl = new QHBoxLayout( ui.players );
    hl->setContentsMargins( 0, 0, 0, 0 );
    hl->setSpacing( 0 );

    hl->addStretch( 1 );

    hl->addWidget( ui.itunes = new QPushButton( this ) );
    ui.itunes->setObjectName( "itunes" );
    ui.itunes->setAttribute( Qt::WA_LayoutUsesWidgetRect );

    connect( ui.itunes, SIGNAL(clicked()), SLOT(oniTunesClicked()));

#ifndef Q_OS_MAC
    hl->addWidget( ui.wmp = new QPushButton( this ) );
    ui.wmp->setObjectName( "wmp" );
    ui.wmp->setAttribute( Qt::WA_LayoutUsesWidgetRect );
    hl->addWidget( ui.winamp = new QPushButton( this ) );
    ui.winamp->setObjectName( "winamp" );
    ui.winamp->setAttribute( Qt::WA_LayoutUsesWidgetRect );
    hl->addWidget( ui.foobar = new QPushButton( this ) );
    ui.foobar->setObjectName( "foobar" );
    ui.foobar->setAttribute( Qt::WA_LayoutUsesWidgetRect );
#endif
    hl->addStretch( 1 );
#endif

    layout->addStretch( 1 );

    connect( aApp, SIGNAL(sessionChanged(unicorn::Session*)), SLOT(onSessionChanged(unicorn::Session*)) );
}


void
NothingPlayingWidget::onSessionChanged( unicorn::Session* session )
{
    setUser( session->userInfo() );
}

void
NothingPlayingWidget::setUser( const lastfm::User& user )
{
    if ( !user.name().isEmpty() )
        ui.hello->setText( tr( "Hello, %1! Let's start a radio station..." ).arg( user.name() ) );
}

void
NothingPlayingWidget::oniTunesClicked()
{
#ifdef Q_OS_MAC
    // launch iTunes!
    FSRef appRef;
    LSFindApplicationForInfo( kLSUnknownCreator, CFSTR( ITUNES_BUNDLEID ), NULL, &appRef, NULL );

    LSApplicationParameters params;
    params.version = 0;
    params.flags = kLSLaunchAndHide;
    params.application = &appRef;
    params.asyncLaunchRefCon = NULL;
    params.environment = NULL;


    AEAddressDesc target;
    AECreateDesc( typeApplicationBundleID, CFSTR( ITUNES_BUNDLEID ), 16, &target);

    AppleEvent event;
    AECreateAppleEvent ( kCoreEventClass,
            kAEReopenApplication ,
            &target,
            kAutoGenerateReturnID,
            kAnyTransactionID,
            &event );

    params.initialEvent = &event;

    LSOpenApplication( &params, NULL );
#endif
}
