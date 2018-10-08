/* ============================================================
* Falkon - Qt web browser
* Copyright (C) 2010-2018 David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef WEBTAB_H
#define WEBTAB_H

#include <QWidget>
#include <QIcon>
#include <QUrl>

#include "ctrl_common.h"

class QVBoxLayout;
class QSplitter;

class BrowserWindow;
class TabbedWebView;
class WebInspector;
class LocationBar;
class TabIcon;
class MYTabBar;
class LoadRequest;

class WebTab : public QWidget
{
    Q_OBJECT
public:
    explicit WebTab(QWidget *parent = nullptr);

public:
    void reload();
    void stop();
    int tabIndex();

private:
   
};

#endif // WEBTAB_H
