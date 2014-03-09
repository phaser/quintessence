// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIGameEntry.
//
//    QUIGameEntry is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIGameEntry is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIGameEntry.  If not, see <http://www.gnu.org/licenses/>.

#ifndef PACKAGES_QUI_QUIGAMEENTRY_DEV_SOURCE_QT5_MAINWINDOW_H_
#define PACKAGES_QUI_QUIGAMEENTRY_DEV_SOURCE_QT5_MAINWINDOW_H_

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}  // namespace Ui

class OpenGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 private:
    Ui::MainWindow *ui;
    OpenGLWidget *glWidget;
};

#endif  // PACKAGES_QUI_QUIGAMEENTRY_DEV_SOURCE_QT5_MAINWINDOW_H_
