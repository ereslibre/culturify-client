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

#include "database.h"

#include <iostream>
#include <client/dbclient.h>

using namespace mongo;

Database::Database(const QString &host, quint32 port, const QString &database, const QString &username, const QString &password)
    : m_connection(new DBClientConnection)
{
    std::string error;

    HostAndPort hostAndPort(host.toStdString(), port);
    m_connection->connect(hostAndPort);
    m_connection->auth(database.toStdString(), username.toStdString(), password.toStdString(), error);
}

Database::~Database()
{
    delete m_connection;
}
