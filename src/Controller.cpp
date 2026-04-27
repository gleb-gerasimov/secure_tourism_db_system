//
// Created by glebo on 21.04.2026.
//

#include "../include/Controller.h"
#include "Database.h"
#include "SearchManager.h"


Controller::Controller(Database *database, SearchManager *searchManager) :
    m_database(database), m_searchManager(searchManager) {}

bool Controller::addRecord(const Record &record) const { return m_database->addRecord(record); }

QVector<Record> Controller::getAllRecords() const { return m_database->getAllRecords(); }

QVector<Record> Controller::findTours(const std::optional<QDate> &startDate, const std::optional<QDate> &endDate,
                                      const std::optional<QString> &country, const std::optional<QString> &type,
                                      const std::optional<QString> &hasFlight, const std::optional<int> &participants,
                                      const std::optional<double> &price) const {
    return m_searchManager->findTours(startDate, endDate, country, type, hasFlight, participants, price);
}

double Controller::getAverageDailyCost(const QString &country, const QString &type) const {
    return m_searchManager->getAverageDailyCost(country, type);
}
