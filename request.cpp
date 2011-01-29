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

#include "config.h"
#include "request.h"

#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

void Request::sendRequest(const QObject *receiver, const char *callback, const QString &path, Verb verb, const QString &body)
{
    QNetworkAccessManager *const manager = new QNetworkAccessManager;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), receiver, callback);
    QNetworkRequest request(QUrl(Config::fullAPIPath(path)));
    switch (verb) {
        case GET:
            manager->get(request);
            break;
        case POST:
            manager->post(request, body.toLatin1());
            break;
        case PUT:
            manager->put(request, body.toLatin1());
            break;
        case DELETE:
            manager->deleteResource(request);
            break;
    }
}

Request::Request()
{
}
