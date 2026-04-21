//
// Created by glebo on 20.04.2026.
//

#ifndef SECURE_TOURISM_DB_SYSTEM_DATABASE_H
#define SECURE_TOURISM_DB_SYSTEM_DATABASE_H

#include <QVector>
#include <QSqlQuery>
#include "Record.h"


class Database {
public:
    Database();
    ~Database();

    bool connect(const QString& path);
    void disconnect();
    [[nodiscard]] bool isOpen() const;

    bool initialize();

    bool addRecord(const Record& record);
    bool updateRecord(const Record& record);
    bool deleteRecord(int id);

    QVector<Record> getAllRecords();

private:
    QSqlDatabase db;

    bool executeQuery(QSqlQuery& query);
    [[nodiscard]] Record parseRecord(const QSqlQuery& query) const;
};



#endif //SECURE_TOURISM_DB_SYSTEM_DATABASE_H
