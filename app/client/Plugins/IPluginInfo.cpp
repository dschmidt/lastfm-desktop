
#include <QSettings>
#include <QStringList>
#include <QCoreApplication>
#include <QProcess>
#include <QDebug>

#include <windows.h>
#include <shellapi.h>
#include <wtsapi32.h>

#include "lib/unicorn/UnicornSettings.h"

#include "IPluginInfo.h"
#include "KillProcess.h"

QString
Version::toString() const
{
    return QString( "%1.%2.%3.%4" ).arg( QString::number( m_major ),
                                         QString::number( m_minor ),
                                         QString::number( m_build ),
                                         QString::number( m_revision ) );
}

Version
Version::fromString( const QString& string )
{
    QStringList versionList = string.split( "." );

    int major = versionList.count() > 0 ? versionList.at( 0 ).toUInt() : 0;
    int minor = versionList.count() > 1 ? versionList.at( 1 ).toUInt() : 0;
    int build = versionList.count() > 2 ? versionList.at( 2 ).toUInt() : 0;
    int revision = versionList.count() > 3 ? versionList.at( 3 ).toUInt() : 0;

    return Version( major, minor, build, revision );
}

IPluginInfo::IPluginInfo( QObject* parent )
    :QObject( parent ), m_install( false )
{}

void
IPluginInfo::doInstall()
{
    QString installer = QString( "\"%1\"" ).arg( QCoreApplication::applicationDirPath() + "/plugins/" + pluginInstaller() );
    qDebug() << installer;
    QProcess* installerProcess = new QProcess( this );
    installerProcess->start( installer );
    bool finished = installerProcess->waitForFinished( -1 );
    qDebug() << finished << installerProcess->error() << installerProcess->errorString();
}

bool
IPluginInfo::install() const
{
    return m_install;
}


void
IPluginInfo::install( bool install )
{
    m_install = install;
}

bool
IPluginInfo::isAppInstalled() const
{
    pluginInstallPath();
    return true;
}

BOOL
IPluginInfo::isWow64()
{
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    void* fnIsWow64Process = GetProcAddress(
    GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

    if(NULL != fnIsWow64Process)
    {
        if (!IsWow64Process(GetCurrentProcess(),&bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}


bool
IPluginInfo::isInstalled() const
{
    QSettings settings( "HKEY_LOCAL_MACHINE\\SOFTWARE\\Last.fm\\Client\\Plugins", QSettings::NativeFormat );
    return settings.childGroups().contains( id() );
}

Version
IPluginInfo::installedVersion() const
{
    QSettings settings( "HKEY_LOCAL_MACHINE\\SOFTWARE\\Last.fm\\Client\\Plugins\\" + id(), QSettings::NativeFormat );
    return Version::fromString( settings.value( "Version", "0.0.0.0" ).toString() );
}

bool
IPluginInfo::canBootstrap() const
{
    return bootstrapType() != NoBootstrap;
}

QString
IPluginInfo::programFilesX86() const
{
    return QString( getenv( "ProgramFiles(x86)" ) );
}

QString
IPluginInfo::programFiles64() const
{
    return QString( getenv( "ProgramW6432" ) );
}

