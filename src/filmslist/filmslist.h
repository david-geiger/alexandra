/*************************************************************************************************
 *                                                                                                *
 *  file: filmslist.h                                                                             *
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

#ifndef FILMSLIST_H
#define FILMSLIST_H

#include "alexandrasettings.h"
#include "filmslist/film.h"

#include <QList>
#include <QObject>
#include <QMutex>
#include <QString>
#include <QStringList>

class FilmsList : public QObject
{
    Q_OBJECT

    public:
        explicit FilmsList( AlexandraSettings* s, QObject* parent = nullptr );
        virtual ~FilmsList();

        void LoadFromFile( const QString& fileName );
        void SaveToFile( const QString& fileName );
        void SaveToFileAsync( const QString& fileName );

    public slots:
        int         GetNumberOfFilms() const;
        const Film* GetFilmByTitle( const QString& title );

        const QList<Film>* GetFilmsList() const;
        QStringList GetTitlesList() const;

        QStringList*  GetFileNamesList() const;
        QList<Film*>* GetUnavailablesList();

        const Film* GetCurrentFilm() const;
        QString GetCurrentFilmTitle() const;
        QString GetCurrentFilmFileName() const;

        int GetFilmsCount() const;
        int GetIsViewedCount() const;
        int GetIsFavouriteCount() const;

        void AddFilm( Film film );

        void SetCurrentFilm( const QString& title );
        void ChangeCurrentFilm( const Film& f );
        void SetCurrentFilmIsViewed( bool b );
        void SetCurrentFilmIsFavourite( bool b );
        void IncCurrentFilmViewsCounter();

        void RemoveCurrentFilm();
        void RemoveFilmByTitle( const QString& title );
        void FilmsMoved();

        void EraseAll();
        void ResetViews();

    signals:
        void DatabaseReadError();
        void DatabaseWriteError();
        void DatabaseIsWrong();
        void DatabaseIsEmpty();
        void DatabaseIsReadonly();

        void DatabaseLoaded();
        void DatabaseChanged();

    private:
        void RemoveFilm( const Film& film );

        // Variables
        AlexandraSettings* settings = nullptr;
        QList<Film>* films = nullptr;
        Film* currentFilm = nullptr;
        QMutex asyncSaveToFileMutex;
        bool isDatabaseChanged = false;
};

#endif // FILMSLIST_H