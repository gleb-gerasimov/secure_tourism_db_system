#include "../include/mainwindow.h"
#include "../forms/ui_mainwindow.h"

#include <QTableWidgetItem>


MainWindow::MainWindow(Controller *controller, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), m_controller(controller) {

    ui->setupUi(this);

    connect(ui->addRecordPushButton, &QPushButton::clicked, this, &MainWindow::addRecord);

    connect(ui->tableFindPushButton, &QPushButton::clicked, this, &MainWindow::findTours);

    connect(ui->averagePricePushButton, &QPushButton::clicked, this, &MainWindow::calculateAverageCost);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::addRecord() {
    Record record = getRecordFromForm();

    if (record.fullName.trimmed().isEmpty() || record.homeAddress.trimmed().isEmpty() ||
        record.phoneNumber.trimmed().isEmpty() || record.hotelName.trimmed().isEmpty() ||
        record.hotelAddress.trimmed().isEmpty() || record.startDate == QDate(2000, 1, 1) ||
        record.endDate == QDate(2000, 1, 1) || record.type.trimmed().isEmpty() || record.country.trimmed().isEmpty() ||
        record.hasFlight.trimmed().isEmpty() || record.participants == 0 || record.price == 0.0) {
        ui->recordFeedbackLabel->setText("Ошибка: Заполните все поля!");
        return;
    }

    m_controller->addRecord(record);

    ui->recordFeedbackLabel->setText("Успешно: Запись добавлена!");
}

void MainWindow::findTours() {

    std::optional<QDate> startDate;
    std::optional<QDate> endDate;

    std::optional<QString> country;
    std::optional<QString> type;

    std::optional<QString> hasFlight;

    std::optional<int> participants;
    std::optional<double> price;

    if (ui->tableStartDateDateEdit->date() != QDate(2000, 1, 1)) {

        startDate = ui->tableStartDateDateEdit->date();
    }

    if (ui->tableEndDateDateEdit->date() != QDate(2000, 1, 1)) {

        endDate = ui->tableEndDateDateEdit->date();
    }

    if (!ui->tableCountryLineEdit->text().trimmed().isEmpty()) {

        country = ui->tableCountryLineEdit->text();
    }

    if (!ui->tableTypeLineEdit->text().trimmed().isEmpty()) {

        type = ui->tableTypeLineEdit->text();
    }

    if (!ui->tableHasFlightComboBox->currentText().isEmpty()) {
        hasFlight = ui->tableHasFlightComboBox->currentText();
    }

    if (ui->tableParticipantsSpinBox->value() > 0) {
        participants = ui->tableParticipantsSpinBox->value();
    }

    if (ui->tablePriceDoubleSpinBox->value() > 0.0) {
        price = ui->tablePriceDoubleSpinBox->value();
    }

    QVector<Record> records =
            m_controller->findTours(startDate, endDate, country, type, hasFlight, participants, price);

    loadRecords(records);
}

void MainWindow::calculateAverageCost() {
    double averageCost =
            m_controller->getAverageDailyCost(ui->averageCountryLineEdit->text(), ui->averageTypeLineEdit->text());

    ui->averageResultLabel->setText("Средняя стоимость: " + QString::number(averageCost));
}

void MainWindow::loadRecords(const QVector<Record> &records) const {

    ui->tableTableWidget->clearContents();

    ui->tableTableWidget->setRowCount(records.size());

    for (int row = 0; row < records.size(); ++row) {
        const Record &record = records[row];

        ui->tableTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(record.id)));

        ui->tableTableWidget->setItem(row, 1, new QTableWidgetItem(record.fullName));

        ui->tableTableWidget->setItem(row, 2, new QTableWidgetItem(record.homeAddress));

        ui->tableTableWidget->setItem(row, 3, new QTableWidgetItem(record.phoneNumber));

        ui->tableTableWidget->setItem(row, 4, new QTableWidgetItem(record.hotelName));

        ui->tableTableWidget->setItem(row, 5, new QTableWidgetItem(record.hotelAddress));

        ui->tableTableWidget->setItem(row, 6, new QTableWidgetItem(record.startDate.toString("dd.MM.yyyy")));

        ui->tableTableWidget->setItem(row, 7, new QTableWidgetItem(record.endDate.toString("dd.MM.yyyy")));

        ui->tableTableWidget->setItem(row, 8, new QTableWidgetItem(record.type));

        ui->tableTableWidget->setItem(row, 9, new QTableWidgetItem(record.country));

        ui->tableTableWidget->setItem(row, 10, new QTableWidgetItem(record.hasFlight));

        ui->tableTableWidget->setItem(row, 11, new QTableWidgetItem(QString::number(record.participants)));

        ui->tableTableWidget->setItem(row, 12, new QTableWidgetItem(QString::number(record.price)));
    }
}

Record MainWindow::getRecordFromForm() const {
    Record record;

    record.fullName = ui->recordFullNameLineEdit->text();

    record.homeAddress = ui->recordHomeAddressLineEdit->text();

    record.phoneNumber = ui->recordPhoneNumberLineEdit->text();

    record.hotelName = ui->recordHotelNameLineEdit->text();

    record.hotelAddress = ui->recordHotelAddressLineEdit->text();

    record.startDate = ui->recordStartDateDateEdit->date();

    record.endDate = ui->recordEndDateDateEdit->date();

    record.type = ui->recordTypeLineEdit->text();

    record.country = ui->recordCountryLineEdit->text();

    record.hasFlight = ui->recordHasFlightComboBox->currentText();

    record.participants = ui->recordParticipantsSpinBox->value();

    record.price = ui->recordPriceDoubleSpinBox->value();

    return record;
}
