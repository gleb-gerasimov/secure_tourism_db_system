#include <QApplication>

#include "../include/Controller.h"
#include "../include/Database.h"
#include "../include/SearchManager.h"
#include "../include/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    Database database;

    database.connect("tourism.db");
    database.initialize();

    SearchManager searchManager(&database);

    Controller controller(&database, &searchManager);

    MainWindow window(&controller);

    window.show();

    return application.exec();
}
