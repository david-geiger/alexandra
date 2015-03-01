/*************************************************************************************************
 *                                                                                                *
 *  file: mainwindow.h                                                                            *
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "filmslist.h"

#include "aboutwindow.h"
#include "addfilmwindow.h"
#include "alexandrasettings.h"
#include "editfilmwindow.h"
#include "filminfowindow.h"
#include "searchwindow.h"
#include "settingswindow.h"
#include "splashscreen.h"

#include <QCloseEvent>
#include <QMainWindow>
#include <QProcess>
#include <QString>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow( QWidget* parent = nullptr );
        ~MainWindow();

    protected:
        void closeEvent( QCloseEvent* event );

    private slots:
        void SettingsChanged();
        void DatabaseSettingsChanged();

        void DatabaseChanged();
        void DatabaseReadError();
        void DatabaseIsEmpty();
        void DatabaseIsReadonly();

        void ShowEditFilmWindow();
        void RemoveFilm();
        void RemoveFile();

        void ShowFilmContextMenu( QPoint p );
        void FilmSelected( const Film* f );
        void ShowShortInfo( QString s );

        void PlayFilm();
        void PlayerStarted();
        void PlayerClosed();

        void UpdateStatusBar();

    private:
        // Additional functions
        void ConfigureSubwindows();
        void ClearTextFields();

        void LoadSettings();
        void SaveSettings();

        void SetAllFunctionsEnabled( bool b );
        void SetEmptyMode( bool b = true );
        void SetReadOnlyMode( bool b = true );

        // Subwindows
        AboutWindow* aboutWindow = nullptr;
        AddFilmWindow* addFilmWindow = nullptr;
        EditFilmWindow* editFilmWindow = nullptr;
        FilmInfoWindow* filmInfoWindow = nullptr;
        SearchWindow* searchWindow = nullptr;
        SettingsWindow* settingsWindow = nullptr;
        SplashScreen* splashScreen = nullptr;

        // Variables
        AlexandraSettings* settings = nullptr;
        QProcess* externalPlayer = nullptr;
};

#endif // MAINWINDOW_H
