//
// Created by glebo on 21.04.2026.
//

#ifndef SECURE_TOURISM_DB_SYSTEM_RECORD_H
#define SECURE_TOURISM_DB_SYSTEM_RECORD_H

#include <QDate>


struct Record {
    int id;

    QString fullName;
    QString homeAddress;
    QString phoneNumber;

    QDate startDate;
    QDate endDate;

    QString type;
    QString country;

    QString hotelName;
    QString hotelAddress;

    bool hasFlight;

    int participants;
    double price;

    QString startDateHash;
    QString endDateHash;
    QString typeHash;
    QString countryHash;
};



#endif //SECURE_TOURISM_DB_SYSTEM_RECORD_H
