
#include <QComboBox>

#include "lib/unicorn/UnicornSettings.h"
#include "lib/unicorn/QMessageBoxBuilder.h"

#include "../Application.h"

#include "ui_GeneralSettingsWidget.h"
#include "GeneralSettingsWidget.h"


#ifdef Q_OS_MAC
#define APP_LAUNCH "scrobbler"
#else
#define APP_LAUNCH "Client"
#endif

GeneralSettingsWidget::GeneralSettingsWidget( QWidget* parent )
    :SettingsWidget( parent ),
      ui( new Ui::GeneralSettingsWidget )
{
    ui->setupUi( this );

    populateLanguages();
    connect( ui->languages, SIGNAL( currentIndexChanged( int ) ), SLOT( onSettingsChanged() ) );

    ui->notifications->setChecked( unicorn::Settings().value( SETTING_NOTIFICATIONS, ui->notifications->isChecked() ).toBool() );
    ui->lastRadio->setChecked( unicorn::Settings().value( SETTING_LAST_RADIO, ui->lastRadio->isChecked() ).toBool() );
    ui->sendCrashReports->setChecked( unicorn::Settings().value( SETTING_SEND_CRASH_REPORTS, ui->sendCrashReports->isChecked() ).toBool() );

    connect( ui->notifications, SIGNAL(stateChanged(int)), SLOT( onSettingsChanged() ) );
    connect( ui->lastRadio, SIGNAL(stateChanged(int)), SLOT( onSettingsChanged() ) );
    connect( ui->sendCrashReports, SIGNAL(stateChanged(int)), SLOT( onSettingsChanged() ) );

#ifdef Q_OS_MAC
    ui->showAs->hide();

    ui->showWhere->addItem( tr("Menu bar and dock icons") );
    ui->showWhere->addItem( tr("Only dock icon (hide menu bar icon)") );
    ui->showWhere->addItem( tr("Only menu bar icon (hide dock icon)") );

    int showWhereIndex = unicorn::Settings().value( SETTING_SHOW_WHERE, -1 ).toInt();

    if ( showWhereIndex == -1 )
    {
        bool showAs = unicorn::Settings().value( SETTING_SHOW_AS, true ).toBool();
        ui->showWhere->setCurrentIndex( showAs ? 0 : 1 );
        unicorn::Settings().setValue( SETTING_SHOW_WHERE, ui->showWhere->currentIndex() );
    }
    else
        ui->showWhere->setCurrentIndex( showWhereIndex );

    connect( ui->showWhere, SIGNAL(currentIndexChanged(int)), SLOT(onSettingsChanged()) );

#else
    ui->showWhere->hide();

    ui->showAs->setChecked( unicorn::Settings().value( SETTING_SHOW_AS, ui->showAs->isChecked() ).toBool() );
    connect( ui->showAs, SIGNAL(stateChanged(int)), SLOT( onSettingsChanged() ) );
//FIXME: hideDock doesnt exist?!
//     ui->hideDock->hide();
#endif

#ifndef Q_WS_X11
    ui->launch->setChecked( unicorn::AppSettings( APP_LAUNCH ).value( SETTING_LAUNCH_ITUNES, ui->launch->isChecked() ).toBool() );
    ui->updates->setChecked( unicorn::Settings().value( SETTING_CHECK_UPDATES, ui->updates->isChecked() ).toBool() );
    connect( ui->launch, SIGNAL(stateChanged(int) ), SLOT( onSettingsChanged() ) );
    connect( ui->updates, SIGNAL(stateChanged(int)), SLOT( onSettingsChanged() ) );
#else
    ui->launch->hide();
    ui->updates->hide();
#endif
}

void
GeneralSettingsWidget::populateLanguages()
{
    ui->languages->addItem( tr( "System Language" ), "" );
    ui->languages->addItem( "English", QLocale( QLocale::English ).name().left( 2 ) );
    ui->languages->addItem( QString::fromUtf8( "français" ), QLocale( QLocale::French ).name().left( 2 ) );
    ui->languages->addItem( "Italiano", QLocale( QLocale::Italian ).name().left( 2 )  );
    ui->languages->addItem( "Deutsch", QLocale( QLocale::German ).name().left( 2 ) );
    ui->languages->addItem( QString::fromUtf8( "Español" ), QLocale( QLocale::Spanish ).name().left( 2 ) );
    ui->languages->addItem( QString::fromUtf8( "Português" ), QLocale( QLocale::Portuguese ).name().left( 2 ) );
    ui->languages->addItem( "Polski", QLocale( QLocale::Polish ).name().left( 2 ) );
    ui->languages->addItem( "Svenska", QLocale( QLocale::Swedish ).name().left( 2 ) );
    ui->languages->addItem( QString::fromUtf8( "Türkçe" ), QLocale( QLocale::Turkish ).name().left( 2 ) );
    ui->languages->addItem( QString::fromUtf8( "Руccкий" ), QLocale( QLocale::Russian ).name().left( 2 ) );
    ui->languages->addItem( QString::fromUtf8( "简体中文" ), QLocale( QLocale::Chinese ).name().left( 2 ) );
    ui->languages->addItem( QString::fromUtf8( "日本語" ), QLocale( QLocale::Japanese ).name().left( 2 ) );

    QString currLanguage = unicorn::AppSettings().value( "language", "" ).toString();
    int index = ui->languages->findData( currLanguage );
    if ( index != -1 )
    {
        ui->languages->setCurrentIndex( index );
    }
}

void
GeneralSettingsWidget::saveSettings()
{
    qDebug() << "has unsaved changes?" << hasUnsavedChanges();
    if ( hasUnsavedChanges() )
    {
        int currIndex = ui->languages->currentIndex();
        QString currLanguage = ui->languages->itemData( currIndex ).toString();

        if ( unicorn::AppSettings().value( "language", "" ) != currLanguage )
        {
            if ( currLanguage == ""  )
                QLocale::setDefault( QLocale::system() );
            else
                QLocale::setDefault( QLocale( currLanguage ) );

            unicorn::AppSettings().setValue( "language", currLanguage );
//            QMessageBoxBuilder( 0 )
//                .setIcon( QMessageBox::Information )
//                .setTitle( tr( "Restart needed" ) )
//                .setText( tr( "You need to restart the application for the language change to take effect." ) )
//                .exec();
        }

        // setting is for the 'Client' aplication for compatibility with old media player plugins
        unicorn::AppSettings( APP_LAUNCH ).setValue( SETTING_LAUNCH_ITUNES, ui->launch->isChecked() );

        unicorn::Settings().setValue( SETTING_NOTIFICATIONS, ui->notifications->isChecked() );
        unicorn::Settings().setValue( SETTING_LAST_RADIO, ui->lastRadio->isChecked() );
        unicorn::Settings().setValue( SETTING_SEND_CRASH_REPORTS, ui->sendCrashReports->isChecked() );
        unicorn::Settings().setValue( SETTING_CHECK_UPDATES, ui->updates->isChecked() );

#ifdef Q_OS_MAC
        int showWhereIndex = unicorn::Settings().value( SETTING_SHOW_WHERE, -1 ).toInt();
        bool showAs = ui->showWhere->currentIndex() != 1;

        unicorn::Settings().setValue( SETTING_SHOW_WHERE, ui->showWhere->currentIndex() );
        unicorn::Settings().setValue( SETTING_SHOW_AS, showAs );

        aApp->showAs( showAs );
        aApp->hideDockIcon( ui->showWhere->currentIndex() == 2 );

        if ( ( showWhereIndex != 2 && ui->showWhere->currentIndex() == 2 )
             || (showWhereIndex == 2 && ui->showWhere->currentIndex() != 2) )
        {
            int button = QMessageBoxBuilder( 0 )
                                .setIcon( QMessageBox::Question )
                                .setTitle( tr( "Restart now?" ) )
                                .setText( tr( "Would you like to restart now for the dock setting to take effect?" ) )
                                .setButtons( QMessageBox::Yes | QMessageBox::No )
                                .exec();

            if ( button == QMessageBox::Yes )
                aApp->restart();
        }
#else
        unicorn::Settings().setValue( SETTING_SHOW_AS, ui->showAs->isChecked() );
        aApp->showAs( ui->showAs->isChecked() );
#endif

        onSettingsSaved();
    }
}
