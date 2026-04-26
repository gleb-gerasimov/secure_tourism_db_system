//
// Created by glebo on 21.04.2026.
//

#ifndef SECURE_TOURISM_DB_SYSTEM_RECORD_H
#define SECURE_TOURISM_DB_SYSTEM_RECORD_H

#include <QDate>
#include <QString>
#include <QByteArray>

struct Record {
    int id = -1;

    QString fullName;
    QString homeAddress;
    QString phoneNumber;

    QString hotelName;
    QString hotelAddress;

    QDate startDate;
    QDate endDate;

    QString type;
    QString country;

    bool hasFlight = false;

    int participants = 0;
    double price = 0.0;
};

#endif // SECURE_TOURISM_DB_SYSTEM_RECORD_H
