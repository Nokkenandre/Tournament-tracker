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
    const int displaySize = 10;
    int displayIndex = 0;
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
            "  font-size: 24px;"
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

        connect(createButton, &QPushButton::clicked, this, &mainPage::createTournamentPopup);
        connect(tournamentList, &QListWidget::itemDoubleClicked, this, &mainPage::selectTournament);
        updateTournamentList(displayIndex, displaySize);
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
            apiClient::createTournament(values["Tournament name"], values["Match format"]);
            updateTournamentList(displayIndex, displaySize);
        }
    }

    void selectTournament() {
        QListWidgetItem *item = tournamentList->currentItem();
        if (item) {
            QString name = item->text();
            int id = item->data(Qt::UserRole).toInt();
            
            emit goToTournamentPage();
        }
    }

    void updateTournamentList(int displayIndex, int displaySize) {
        tournamentList->clear();
        nlohmann::json tournamentSubset = apiClient::getTournaments(displayIndex, displaySize);
        for (const auto& tournament : tournamentSubset) {
            std::string name = tournament["name"];
            int id = tournament["id"];
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(name));
            item->setData(Qt::UserRole, id);
            tournamentList->addItem(item);
        }
        
    }

signals:
    void goToTournamentPage();

private:
    QPushButton* createButton;
    QListWidget* tournamentList;
};