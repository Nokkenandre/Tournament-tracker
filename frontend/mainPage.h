#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "apiClient.h"
#include "inputDialog.h"

class mainPage : public QWidget {
    Q_OBJECT

public:
    explicit mainPage(QWidget* parent = nullptr) : QWidget(parent) {
        auto* layout = new QVBoxLayout(this);

        QLabel* title = new QLabel("Tournament Manager");
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

        connect(createButton, &QPushButton::clicked, this, &mainPage::goToTournamentPage);
    }

    void createTournamentPopup() {
        QString dialogName = "Create new tournament";
        QList<Field> fields = {
            { "Tournament name", Field::Text },
            { "Match format", Field::Dropdown, {"Race to 2", "Mercy 5"}, {"First team to score 2 points wins", "Win by having most points when the time runs out or by leading by 5 points"} },
        };
    
        DynamicInputDialog dialog(dialogName, fields, this);
        if (dialog.exec() == QDialog::Accepted) {
            QMap<QString, QString> values = dialog.getValues();
            tournamentList->addItem(values["Tournament name"]);
            ApiClient::createTournament(values["Tournament name"], values["Match format"]);
        }
    }

    void selectTournament() {
        QListWidgetItem *item = tournamentList->currentItem();
        if (item) {
            QString name = item->text();
            QMessageBox::information(this, "Tournament Selected", "You selected: " + name);
        }
    }

signals:
    void goToTournamentPage();

private:
    QPushButton* createButton;
    QListWidget* tournamentList;
};