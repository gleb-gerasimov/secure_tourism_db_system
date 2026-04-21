//
// Created by glebo on 21.04.2026.
//

#ifndef SECURE_TOURISM_DB_SYSTEM_RECORD_H
#define SECURE_TOURISM_DB_SYSTEM_RECORD_H

#include <QDate>
#include <QString>
#include <QByteArray>

struct Record {
    int id;

    QByteArray fullNameEncrypted;
    QByteArray homeAddressEncrypted;
    QByteArray phoneNumberEncrypted;

    QByteArray hotelNameEncrypted;
    QByteArray hotelAddressEncrypted;

    QDate startDate;
    QDate endDate;

    QString type;
    QString country;

    bool hasFlight;

    int participants;
    double price;
};

#endif // SECURE_TOURISM_DB_SYSTEM_RECORD_H
