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

#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include "./OpenGLWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGLFormat format;
    format.setVersion(3, 1);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);

    glWidget = new OpenGLWidget(format);
    glWidget->setMinimumSize(960, 640);
    glWidget->setMaximumSize(960, 640);
    this->ui->scrollArea->setWidget(glWidget);
}

MainWindow::~MainWindow()
{
    delete glWidget;
    delete ui;
}
