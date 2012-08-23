#ifndef DEVICE_SCROBBLER_H_
#define DEVICE_SCROBBLER_H_

#include <QDialogButtonBox>

#include "../Dialogs/ScrobbleSetupDialog.h"
#include "lib/unicorn/UnicornSession.h"
#include "lib/unicorn/UnicornSettings.h"
#include <lastfm/User.h>
#include "IpodDevice.h"

#ifdef Q_WS_X11
#include <QPointer>
#include "IpodDevice_linux.h"
#endif

using unicorn::Session;

class DeviceScrobbler : public QObject
{
    Q_OBJECT
public:
    DeviceScrobbler();

signals:
    void detectedIPod( const QString& id );
    void processingScrobbles( const QString& id );
    void noScrobblesFound( const QString& id );
    void foundScrobbles( const QList<lastfm::Track>& tracks, const QString& id );

public slots:
#ifdef __linux__
    void onScrobbleIpodTriggered();
#endif

private slots:
    void onScrobbleSetupClicked( bool scrobble, bool alwaysAsk, QString username, QString deviceId, QString deviceName, QStringList iPodFiles );
#ifdef __linux__
    void onCalculatingScrobbles( int trackCount );
    void scrobbleIpodTracks( int trackCount );
    void onIpodScrobblingError();
#endif

public:
    void checkCachedIPodScrobbles();
    void handleMessage( const QStringList& );
    void iPodDetected( const QStringList& arguments );

private:
#ifdef __linux__
    QPointer<IpodDeviceLinux> iPod;
#endif
    void twiddled( QStringList arguments );
    void scrobbleIpodFiles( QStringList iPodScrobbleFiles, const IpodDevice& ipod );

    lastfm::User associatedUser( QString deviceId );
};

#endif //DEVICE_SCROBBLER_H_
