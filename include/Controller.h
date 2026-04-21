//
// Created by glebo on 21.04.2026.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QVector>
#include <QString>
#include <optional>

#include "Record.h"
#include "Database.h"
#include "SearchManager.h"


class Controller {
public:
    Controller(Database* database, SearchManager* searchManager);

    [[nodiscard]] QVector<Record> getAllRecords() const;

    [[nodiscard]] QVector<Record> findTours(
        const std::optional<QDate>& startDate,
        const std::optional<QDate>& endDate,
        const std::optional<QString>& country,
        const std::optional<QString>& type
    ) const;

    [[nodiscard]] QVector<Record> findByFilters(
        const QDate& startDate,
        const QDate& endDate,
        const QString& country,
        const QString& type
    ) const;

    [[nodiscard]] double getAverageDailyCost(
        const QString& country,
        const QString& type
    ) const;

private:
    Database* m_database;
    SearchManager* m_searchManager;
};

#endif // CONTROLLER_H
