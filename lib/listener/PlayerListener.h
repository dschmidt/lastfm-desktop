/*
   Copyright 2005-2009 Last.fm Ltd. 
      - Primarily authored by Max Howell, Jono Cole and Doug Mansell

   This file is part of the Last.fm Desktop Application Suite.

   lastfm-desktop is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   lastfm-desktop is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with lastfm-desktop.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PLAYER_LISTENER_H
#define PLAYER_LISTENER_H

#include "common/HideStupidWarnings.h"
#include "PlayerConnection.h"
#include <QLocalServer>
#include <QMap>
#include "lib/DllExportMacro.h"
#include <stdexcept>


#ifdef WIN32
#include <windows.h>
// ignore the warning about the exception specification
#pragma warning( disable : 4290 )
#endif

#define BUFSIZE 4096



/** listens to external clients via a TcpSocket and notifies a receiver to their
  * commands */
class LISTENER_DLLEXPORT PlayerListener : public QLocalServer
{
    Q_OBJECT

public:
    PlayerListener( QObject* parent = 0 ) throw( std::runtime_error );

signals:
    void newConnection( class PlayerConnection* );
    void bootstrapCompleted( const QString& playerId );
// #ifdef Q_OS_WIN
    void pipeConnected();
// #endif

private slots:
    void onNewConnection();
    void onDataReady();

// #ifdef Q_OS_WIN
    void onPipeConnected();
// #endif

private:
    QString processLine( const QString& line );
// #ifdef Q_OS_WIN

    bool addListener();

    static VOID CALLBACK onConnectedNamedPipe( PVOID lpParameter, BOOLEAN TimerOrWaitFired );
    static VOID CALLBACK onReadFileComplete( DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped );
    static VOID CALLBACK onWriteFileComplete( DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped );
// #endif

private:
    QMap<QString, PlayerConnection*> m_connections;
#ifdef Q_OS_WIN
    HANDLE m_connectEvent;

    struct Listener
    {
        OVERLAPPED overlapped;
        HANDLE pipeHandle;
        PlayerListener* self;
        TCHAR readBuffer[BUFSIZE];
        TCHAR writeBuffer[BUFSIZE];
        bool connected;
    };

    QList<Listener> m_listeners;
    QList<Listener> m_pipes;
#endif
};


#endif
