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

#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QVariantMap>

namespace mongo {
    class DBClientConnection;
}

class Database
{
public:
    Database(const QString &host, quint32 port, const QString &database, const QString &username, const QString &password);
    virtual ~Database();

    QList<QVariantMap> findAll() const;

private:
    QString                          m_database;
    mongo::DBClientConnection *const m_connection;
};

#endif // DATABASE_H
