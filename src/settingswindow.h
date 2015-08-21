/*************************************************************************************************
 *                                                                                                *
 *  file: settingswindow.h                                                                        *
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

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "ui_settingswindow.h"

#include "alexandrasettings.h"

#include <QDialog>
#include <QList>
#include <QString>
#include <QStringList>

class SettingsWindow : public QDialog, public Ui::SettingsWindow
{
    Q_OBJECT

    public:
        SettingsWindow( AlexandraSettings* s, QWidget* parent = nullptr );

        void show();

    signals:
        void DatabaseSettingsChanged();
        void SettingsChanged();
        void ViewChanged();
        void EraseDatabase();

    private slots:
        void OkButtonClicked();
        void SetIsSettingsChanged() { isSettingsChanged = true; }
        void SetIsViewChanged() { SetIsSettingsChanged(); isViewChanged = true; }
        void SetIsNeedReboot() { SetIsSettingsChanged(); isNeedReboot = true; }
        void SetIsDatabaseSettingsChanged() { SetIsSettingsChanged(); isDatabaseSettingsChanged = true; }

        void StyleChanged();
        void SelectFont();
        void SelectFontDefault();
        void SelectExternalPlayer();
        void SetDefaultExternalPlayer();

        void OpenDatabaseFile();
        void SelectColorUnavailable();
        void CreateDatabase();
        void EraseDatabaseQuestion();
        void OpenPostersFolder();

        void SetShortcutPlayDefault() { ksePlay->setKeySequence( QKeySequence( "Alt+Return" ) ); }

    private:
        void ConfigureAppearanceTab();
        void ReconfigureAppearanceTab();
        void ConfigureApplicationTab();
        void ReconfigureApplicationTab();
        void ConfigureShortcutsTab();
        void ReconfigureShortcutsTab();

        // Variables
        AlexandraSettings* settings;
        bool isSettingsChanged;
        bool isDatabaseSettingsChanged;
        bool isViewChanged;
        bool isNeedReboot;

        // Toolbar styles
        typedef struct {
            QString name;
            Qt::ToolButtonStyle style;
        } ToolStyle;

        const QList<ToolStyle> toolStyles = { { tr("Icon only"),            Qt::ToolButtonIconOnly },
                                              { tr("Text only"),            Qt::ToolButtonTextOnly },
                                              { tr("Text beside icon"),     Qt::ToolButtonTextBesideIcon },
                                              { tr("Text under icon"),      Qt::ToolButtonTextUnderIcon },
                                              { tr("<Follow system style>"),Qt::ToolButtonFollowStyle } };

        // App styles
        const QStringList appStyles = { tr( "Theme" ),
                                            "CDE",
                                            "Cleanlooks",
                                            "GTK+",
                                            "Motif",
                                            "Plastique",
                                            "Windows" };

        // Saving formats
        typedef struct {
            QString title;
            QString format;
            int quality;
        } PosterFormat;

        const QList<PosterFormat> savingFormats = { { tr( "PNG (compressed)" ),   "png",  0 },
                                                    { tr( "JPG (quality 95)" ),   "jpg", 95 },
                                                    { tr( "JPG (quality 85)" ),   "jpg", 85 },
                                                    { tr( "JPG (quality 75)" ),   "jpg", 75 },
                                                    { tr( "BMP (uncompressed)" ), "bmp", -1 } };
};

#endif // SETTINGSWINDOW_H
