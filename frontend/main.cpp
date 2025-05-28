#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <QStackedWidget>

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "apiClient.h"
#include "inputDialog.h"
#include "mainPage.h"
#include "tournamentPage.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow* mainwindow = new QMainWindow;
    
    auto* stackedWidget = new QStackedWidget;
    auto* mainpage = new mainPage;
    auto* tournamentpage = new tournamentPage;

    stackedWidget->addWidget(mainpage); // index 0
    stackedWidget->addWidget(tournamentpage); // index 1

    mainwindow->setCentralWidget(stackedWidget);
    

    QObject::connect(mainpage, &mainPage::goToTournamentPage, [&]() {
        stackedWidget->setCurrentIndex(1);
    });

    QObject::connect(tournamentpage, &tournamentPage::goToMainPage, [&]() {
        stackedWidget->setCurrentIndex(0);
    });

    app.setWindowIcon(QIcon(":/favicon.ico"));
    mainwindow->showMaximized();
    return app.exec();
}

