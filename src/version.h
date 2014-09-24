#ifndef VERSION_H
#define VERSION_H

#include <QString>

namespace Alexandra
{
        const QString appName = QString( "alexandra" );
        const QString appNameGui = QString( "Alexandra Video Library" );
        const QString appAuthor = QString( "Eugene Melnik <jeka7js@gmail.com>" );
        const QString appLicense = QString( "GNU GPL v2" );

        const QString orgName = "The Higggs Development";
        const QString orgDomain = "higggs.com";

        const quint8 major = 0;
        const quint8 minor = 1;
        const quint8 fix = 0;
        const QString appVersionFull = QString( "%1.%2.%3" ).arg( major ).arg( minor ).arg( fix );
}

#endif // VERSION_H