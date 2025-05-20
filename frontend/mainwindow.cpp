#include "mainwindow.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "api_client.h"
#include "input_dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);

    QLabel *title = new QLabel("Tournament Manager");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");

    createButton = new QPushButton("➕ Create New Tournament", this);
    createButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #3498db;"
        "  color: white;"
        "  padding: 10px;"
        "  border-radius: 8px;"
        "  font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #2980b9;"
        "}"
    );

    tournamentList = new QListWidget(this);
    tournamentList->setStyleSheet(
        "QListWidget {"
        "  font-size: 16px;"
        "  padding: 5px;"
        "  border: 1px solid #ccc;"
        "  border-radius: 5px;"
        "}"
    );

    layout->addWidget(title);
    layout->addWidget(createButton);
    layout->addWidget(tournamentList);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    setCentralWidget(centralWidget);
    setWindowTitle("Tournament Manager");
    resize(400, 500);

    connect(createButton, &QPushButton::clicked, this, &MainWindow::create_tournament_popup);
    connect(tournamentList, &QListWidget::itemDoubleClicked, this, &MainWindow::select_tournament);
}


MainWindow::~MainWindow() {}

void MainWindow::create_tournament_popup() {
    QString dialog_name = "Create new tournament";
    QList<Field> fields = {
        { "Tournament name", Field::Text },
        { "Match format", Field::Dropdown, {"Race to 2", "Mercy 5"}, {"First team to score 2 points wins", "Win by having most points when the time runs out or by leading by 5 points"} },
    };

    DynamicInputDialog dialog(dialog_name, fields, this);
    if (dialog.exec() == QDialog::Accepted) {
        QMap<QString, QString> values = dialog.getValues();
        tournamentList->addItem(values["Tournament name"]);
    }
}

void MainWindow::select_tournament() {
    QListWidgetItem *item = tournamentList->currentItem();
    if (item) {
        QString name = item->text();
        QMessageBox::information(this, "Tournament Selected", "You selected: " + name);
    }
}