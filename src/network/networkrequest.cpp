/*************************************************************************************************
 *                                                                                                *
 *  file: networkrequest.cpp                                                                      *
 *                                                                                                *
 *  Alexandra Video Library                                                                       *
 *  Copyright (C) 2014-2015 Eugene Melnik <jeka7js@gmail.com>                                     *
 *                                                                                                *
 *  Alexandra is free software; you can redistribute it and/or modify it under the terms of the   *
 *  GNU General Public License as published by the Free Software Foundation; either version 2 of  *
 *  the License, or (at your option) any later version.                                           *
 *                                                                                                *
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;     *
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.     *
 *  See the GNU General Public License for more details.                                          *
 *                                                                                                *
 *  You should have received a copy of the GNU General Public License along with this program.    *
 *  If not, see <http://www.gnu.org/licenses/>.                                                   *
 *                                                                                                *
  *************************************************************************************************/

#include "networkrequest.h"
#include "debug.h"

void NetworkRequest::run( const QUrl& url )
{
    DebugPrintFuncA( "NetworkRequest::run", url.toString() );

    data.clear();
    reply = accessManager.get( QNetworkRequest( url ) );

    connect( reply, &QNetworkReply::downloadProgress, this, [this] (quint64 received, quint64 total) { emit Progress( received, total ); } );
    connect( reply, &QNetworkReply::readyRead, this, &NetworkRequest::ReadyRead );
    connect( reply, &QNetworkReply::finished, this, &NetworkRequest::Finished );
    connect( reply, &QNetworkReply::finished, reply, &QObject::deleteLater );
}

QByteArray& NetworkRequest::runSync( const QUrl& url )
{
    DebugPrintFuncA( "NetworkRequest::runSync", url.toString() );

    data.clear();
    reply = accessManager.get( QNetworkRequest( url ) );

    QEventLoop loop;
    connect( reply, &QNetworkReply::downloadProgress, this, [this] (quint64 received, quint64 total) { emit Progress( received, total ); } );
    connect( reply, &QNetworkReply::readyRead, this, &NetworkRequest::ReadyRead );
    connect( reply, &QNetworkReply::finished, this, &NetworkRequest::CheckForRedirect );
    connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    loop.exec();

    reply->deleteLater();
    return( data );
}

void NetworkRequest::CheckForRedirect()
{
    DebugPrintFunc( "NetworkRequest::CheckForRedirect" );
    QVariant redirectionTarget = reply->attribute( QNetworkRequest::RedirectionTargetAttribute );

    if( !redirectionTarget.isNull() )
    {
        QUrl newUrl = reply->url().resolved( redirectionTarget.toUrl() );
        DebugPrint( "Redirected to: " + newUrl.toString() );
        runSync( newUrl );
    }
}

void NetworkRequest::ReadyRead()
{
    DebugPrintFunc( "NetworkRequest::ReadyRead" );
    data.append( reply->readAll() );
    DebugPrint( QString( "New data size: %1" ).arg( data.size() ) );
}

void NetworkRequest::Finished()
{
    DebugPrintFunc( "NetworkRequest::Finished" );

    CheckForRedirect();

    if( reply->error() )
    {
        DebugPrint( "Error: " + reply->errorString() );
        emit DataLoadError( reply->errorString() );
    }
    else
    {
        emit DataLoaded( data );
    }
}