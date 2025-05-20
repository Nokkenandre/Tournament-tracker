#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void create_tournament_popup();
    void select_tournament();

private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QPushButton *createButton;
    QListWidget *tournamentList;
};

#endif // MAINWINDOW_H
