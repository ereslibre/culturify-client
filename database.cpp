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
    , m_database(database)
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

QList<QVariantMap> Database::findAll() const
{
    QList<QVariantMap> res;

    auto_ptr<DBClientCursor> cursor = m_connection->query(QString("%1.culture").arg(m_database).toStdString(), BSONObj());
    while (cursor->more()) {
        QVariantMap newMap;
        BSONObj obj = cursor->next();
        std::set<std::string> fields;
        obj.getFieldNames(fields);
        std::set<std::string>::iterator it = fields.begin();
        while (it != fields.end()) {
            const std::string field = (*it);
            newMap[QString::fromStdString(field)] = QString::fromStdString(obj[field].str());
            ++it;
        }
        res << newMap;
    }

    return res;
}
