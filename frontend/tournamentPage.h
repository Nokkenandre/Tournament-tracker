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
        
        QPixmap pixmap(":backButton.png");
        QIcon icon(pixmap);

        QPushButton* backButton = new QPushButton;
        backButton->setIcon(icon);
        backButton->setIconSize(QSize(64, 64));
        backButton->setStyleSheet(R"(
            QPushButton {
                border: none;
            })"
        );

        QHBoxLayout* topRow = new QHBoxLayout();
        topRow->setContentsMargins(10, 10, 10, 0);
        topRow->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        topRow->addWidget(backButton);

        QHBoxLayout* tournamentDisplay = new QHBoxLayout;


        
        layout->addWidget(title);
        layout->addLayout(topRow);
        layout->addLayout(tournamentDisplay);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(15);

        connect(backButton, &QPushButton::clicked, this, &tournamentPage::goToMainPage);
    }

signals:
    void goToMainPage();
private:

};