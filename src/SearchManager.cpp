//
// Created by glebo on 20.04.2026.
//

#include "../include/SearchManager.h"
#include "../include/Database.h"


SearchManager::SearchManager(Database* database)
    : m_database(database) {
}

QVector<Record> SearchManager::findTours(
    const std::optional<QDate>& startDate,
    const std::optional<QDate>& endDate,
    const std::optional<QString>& country,
    const std::optional<QString>& type,
    const std::optional<bool>& hasFlight,
    const std::optional<int>& participants,
    const std::optional<double>& price
) const {

    QVector<Record> result;

    QVector<Record> records = m_database->getAllRecords();

    for (const Record& record : records) {
        bool matches = true;

        if (startDate.has_value()
            && record.startDate < startDate.value()) {

            matches = false;
        }

        if (endDate.has_value()
            && record.endDate > endDate.value()) {

            matches = false;
        }

        if (country.has_value()
            && record.country != country.value()) {

            matches = false;
        }

        if (type.has_value()
            && record.type != type.value()) {

            matches = false;
        }

        if (hasFlight.has_value()
            && record.hasFlight != hasFlight.value()) {

            matches = false;
        }

        if (participants.has_value()
            && record.participants != participants.value()) {

            matches = false;
        }

        if (price.has_value()
            && record.price != price.value()) {

            matches = false;
        }

        if (matches) {
            result.append(record);
        }
    }

    return result;
}

double SearchManager::getAverageDailyCost(
    const QString& country,
    const QString& type
) const {

    QVector<Record> records = m_database->getAllRecords();

    double totalCost = 0.0;
    int count = 0;

    for (const Record& record : records) {
        if (record.country == country
            && record.type == type) {

            qint64 days = record.startDate.daysTo(record.endDate);

            totalCost += record.price / static_cast<double>(days);

            ++count;
        }
    }

    return totalCost / count;
}
