/*
 * This file is part of Culturify
 *
 * Copyright (C) 2011 Rafael Fernández López <ereslibre@ereslibre.es>
 *
 * Culturify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Culturify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Culturify. If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "request.h"
#include "database.h"

#include <qjson/parser.h>

#include <QtCore/QDebug>
#include <QtNetwork/QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_database(0)
{
    m_ui->setupUi(this);

    Request::sendRequest(this, SLOT(finished(QNetworkReply*)), "/ddbb");
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_database;
}

void MainWindow::finished(QNetworkReply *reply)
{
    bool ok;

    QJson::Parser parser;
    const QVariant contents_ = parser.parse(reply->readAll(), &ok);

    if (ok) {
        const QVariantMap contents = contents_.toMap();
        if (!contents["status"].toInt()) {
            const QVariantMap data = contents["data"].toMap();
            m_database = new Database(data["host"].toString(), data["port"].toUInt(), data["database"].toString(), data["username"].toString(), data["password"].toString());
        }
    }
}
