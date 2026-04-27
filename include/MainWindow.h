#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../include/Controller.h"

#include <QMainWindow>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Controller *controller, QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void addRecord();
    void findTours();
    void calculateAverageCost();

private:
    Ui::MainWindow *ui;

    Controller *m_controller;

    void loadRecords(const QVector<Record> &records) const;
    Record getRecordFromForm() const;
};

#endif // MAINWINDOW_H
