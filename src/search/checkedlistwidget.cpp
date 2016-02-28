/*************************************************************************************************
 *                                                                                                *
 *  file: checkedlistwidget.cpp                                                                   *
 *                                                                                                *
 *  Alexandra Video Library                                                                       *
 *  Copyright (C) 2014-2016 Eugene Melnik <jeka7js@gmail.com>                                     *
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

#include "checkedlistwidget.h"
#include "tools/debug.h"

#include <QKeyEvent>


CheckedListWidget::CheckedListWidget( QWidget* parent ) : QListWidget( parent )
{
    setEditTriggers( QAbstractItemView::NoEditTriggers );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setSelectionMode( QAbstractItemView::SingleSelection );
    setContextMenuPolicy( Qt::CustomContextMenu );

    connect( this, &QWidget::customContextMenuRequested, this, &CheckedListWidget::ShowContextMenu );
    connect( &searchTimer, &QTimer::timeout, this, &CheckedListWidget::ClearSearch );
}


void CheckedListWidget::AddItem( QString itemTitle )
{
    QListWidgetItem* item = new QListWidgetItem( itemTitle, this );
    item->setCheckState( Qt::Unchecked );
    addItem( item );
}


void CheckedListWidget::AddItems( QStringList itemsTitles )
{
    for( QString title : itemsTitles )
    {
        AddItem( title );
    }
}


QStringList CheckedListWidget::GetSelectedItems() const
{
    QStringList result;

    for( int row = 0; row < count(); ++row )
    {
        if( item(row)->checkState() == Qt::Checked )
        {
            result.append( item(row)->text() );
        }
    }

    return( result );
}


void CheckedListWidget::keyPressEvent( QKeyEvent* event )
{
    if( event->text().isEmpty() )
    {
        QListWidget::keyPressEvent(event);
    }
    else
    {
        searchText.append( event->text() );
        searchTimer.stop();

          // Search for an item by the text
        for( int row = 0; row < count(); ++row )
        {
            QListWidgetItem* it = item( row );
            QString itemText = it->text().left( searchText.length() );

            if( itemText.compare( searchText, Qt::CaseInsensitive ) == 0 )
            {
                setCurrentItem( it );
                break;
            }
        }

        searchTimer.start( 1000 ); // 1 second
    }
}


void CheckedListWidget::ShowContextMenu( QPoint pos )
{
    if( count() > 0 )
    {
        QMenu menu;
        menu.addAction( tr( "Select all" ), this, SLOT(SelectAll()) );
        menu.addAction( tr( "Unselect all" ), this, SLOT(UnselectAll()) );
        menu.addAction( tr( "Invert selection" ), this, SLOT(InvertSelection()) );
        menu.addSeparator();
        menu.addAction( tr( "Scroll to checked" ), this, SLOT(ScrollToChecked()) );
        menu.exec( this->mapToGlobal(pos) );
    }
}


void CheckedListWidget::SetAllChecked( Qt::CheckState checked )
{
    for( int row = 0; row < count(); ++row )
    {
        item(row)->setCheckState( checked );
    }
}


void CheckedListWidget::InvertSelection()
{
    for( int row = 0; row < count(); ++row )
    {
        item(row)->setCheckState( (item(row)->checkState() == Qt::Unchecked) ? Qt::Checked : Qt::Unchecked );
    }
}


void CheckedListWidget::ScrollToChecked()
{
    for( int row = 0; row < count(); ++row )
    {
        if( item(row)->checkState() == Qt::Checked )
        {
            setCurrentItem( item(row) );
            break;
        }
    }
}

