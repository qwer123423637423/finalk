#pragma once

#include <QMainWindow>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void refreshUsers();
    void refreshMessages();
    void disconnectUser();
    void banUser();

private:
    Ui::MainWindow* ui;
    QSqlDatabase db;
    QSqlTableModel* userModel;
    QSqlTableModel* messageModel;

    void connectToDatabase();
    void setupModels();
    void applyStyles();
};
