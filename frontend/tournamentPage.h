#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "apiClient.h"
#include "inputDialog.h"

class tournamentPage : public QWidget {
    Q_OBJECT

public:
    explicit tournamentPage(QWidget* parent = nullptr) : QWidget(parent) {
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

        connect(createButton, &QPushButton::clicked, this, &tournamentPage::goToMainPage);
    }

signals:
    void goToMainPage();

private:
    QPushButton* createButton;
    QListWidget* tournamentList;
};