//
// Created by glebo on 20.04.2026.
//

#ifndef SECURE_TOURISM_DB_SYSTEM_SEARCHMANAGER_H
#define SECURE_TOURISM_DB_SYSTEM_SEARCHMANAGER_H

#include "../include/Record.h"

#include <optional>


class Database;

class SearchManager {
public:
    explicit SearchManager(Database *database);

    [[nodiscard]] QVector<Record> findTours(const std::optional<QDate> &startDate, const std::optional<QDate> &endDate,
                                            const std::optional<QString> &country, const std::optional<QString> &type,
                                            const std::optional<QString> &hasFlight,
                                            const std::optional<int> &participants,
                                            const std::optional<double> &price) const;

    [[nodiscard]] double getAverageDailyCost(const QString &country, const QString &type) const;

private:
    Database *m_database;
};

#endif // SECURE_TOURISM_DB_SYSTEM_SEARCHMANAGER_H
