#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    userModel(nullptr), messageModel(nullptr) {
    ui->setupUi(this);
    connectToDatabase();
    setupModels();
    applyStyles();

    connect(ui->btnRefreshUsers, &QPushButton::clicked, this, &MainWindow::refreshUsers);
    connect(ui->btnRefreshMessages, &QPushButton::clicked, this, &MainWindow::refreshMessages);
    connect(ui->btnDisconnect, &QPushButton::clicked, this, &MainWindow::disconnectUser);
    connect(ui->btnBan, &QPushButton::clicked, this, &MainWindow::banUser);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connectToDatabase() {
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("messenger");
    db.setUserName("postgres");
    db.setPassword("your_password");

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных");
    }
}

void MainWindow::setupModels() {
    userModel = new QSqlTableModel(this, db);
    userModel->setTable("users");
    userModel->select();
    ui->tableUsers->setModel(userModel);

    messageModel = new QSqlTableModel(this, db);
    messageModel->setTable("messages");
    messageModel->select();
    ui->tableMessages->setModel(messageModel);
}

void MainWindow::refreshUsers() {
    userModel->select();
}

void MainWindow::refreshMessages() {
    messageModel->select();
}

void MainWindow::disconnectUser() {
    auto idx = ui->tableUsers->currentIndex();
    if (!idx.isValid()) return;

    int userId = userModel->data(userModel->index(idx.row(), 0)).toInt();
    QSqlQuery query;
    query.prepare("UPDATE users SET is_connected = false WHERE id = :id");
    query.bindValue(":id", userId);
    query.exec();

    refreshUsers();
}

void MainWindow::banUser() {
    auto idx = ui->tableUsers->currentIndex();
    if (!idx.isValid()) return;

    int userId = userModel->data(userModel->index(idx.row(), 0)).toInt();
    QSqlQuery query;
    query.prepare("UPDATE users SET is_banned = true WHERE id = :id");
    query.bindValue(":id", userId);
    query.exec();

    refreshUsers();
}

void MainWindow::applyStyles() {
    QFile file(":/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = file.readAll();
        setStyleSheet(styleSheet);
    }
}
