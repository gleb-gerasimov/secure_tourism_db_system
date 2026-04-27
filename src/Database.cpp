//
// Created by glebo on 20.04.2026.
//

#include "../include/Database.h"
#include "../include/EncryptionManager.h"

#include <QSqlDatabase>

Database::Database() = default;

Database::~Database() { disconnect(); }

bool Database::connect(const QString &path) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    return db.open();
}

void Database::disconnect() { db.close(); }

bool Database::isOpen() const { return db.isOpen(); }

bool Database::initialize() {
    QSqlQuery query;

    query.prepare(R"(
        CREATE TABLE IF NOT EXISTS records (
            id INTEGER PRIMARY KEY AUTOINCREMENT,

            full_name BLOB NOT NULL,
            home_address BLOB NOT NULL,
            phone_number BLOB NOT NULL,

            hotel_name BLOB NOT NULL,
            hotel_address BLOB NOT NULL,

            start_date TEXT NOT NULL,
            end_date TEXT NOT NULL,

            type TEXT NOT NULL,
            country TEXT NOT NULL,

            has_flight INTEGER NOT NULL,

            participants INTEGER NOT NULL,
            price REAL NOT NULL
        )
    )");

    return executeQuery(query);
}

bool Database::addRecord(const Record &record) {
    QSqlQuery query;

    query.prepare(R"(
        INSERT INTO records (
            full_name,
            home_address,
            phone_number,
            hotel_name,
            hotel_address,
            start_date,
            end_date,
            type,
            country,
            has_flight,
            participants,
            price
        )
        VALUES (
            :full_name,
            :home_address,
            :phone_number,
            :hotel_name,
            :hotel_address,
            :start_date,
            :end_date,
            :type,
            :country,
            :has_flight,
            :participants,
            :price
        )
    )");

    query.bindValue(":full_name", EncryptionManager::encrypt(record.fullName));

    query.bindValue(":home_address", EncryptionManager::encrypt(record.homeAddress));

    query.bindValue(":phone_number", EncryptionManager::encrypt(record.phoneNumber));

    query.bindValue(":hotel_name", EncryptionManager::encrypt(record.hotelName));

    query.bindValue(":hotel_address", EncryptionManager::encrypt(record.hotelAddress));

    query.bindValue(":start_date", record.startDate.toString(Qt::ISODate));

    query.bindValue(":end_date", record.endDate.toString(Qt::ISODate));

    query.bindValue(":type", record.type);
    query.bindValue(":country", record.country);

    query.bindValue(":has_flight", record.hasFlight);

    query.bindValue(":participants", record.participants);
    query.bindValue(":price", record.price);

    return executeQuery(query);
}

QVector<Record> Database::getAllRecords() const {
    QVector<Record> records;

    QSqlQuery query;

    query.prepare("SELECT * FROM records");
    query.exec();

    while (query.next()) {
        records.append(parseRecord(query));
    }

    return records;
}

bool Database::executeQuery(QSqlQuery &query) { return query.exec(); }

Record Database::parseRecord(const QSqlQuery &query) const {
    Record record;

    record.id = query.value("id").toInt();

    record.fullName = EncryptionManager::decrypt(query.value("full_name").toByteArray());

    record.homeAddress = EncryptionManager::decrypt(query.value("home_address").toByteArray());

    record.phoneNumber = EncryptionManager::decrypt(query.value("phone_number").toByteArray());

    record.hotelName = EncryptionManager::decrypt(query.value("hotel_name").toByteArray());

    record.hotelAddress = EncryptionManager::decrypt(query.value("hotel_address").toByteArray());

    record.startDate = QDate::fromString(query.value("start_date").toString(), Qt::ISODate);

    record.endDate = QDate::fromString(query.value("end_date").toString(), Qt::ISODate);

    record.type = query.value("type").toString();
    record.country = query.value("country").toString();

    record.hasFlight = query.value("has_flight").toString();

    record.participants = query.value("participants").toInt();
    record.price = query.value("price").toDouble();

    return record;
}
