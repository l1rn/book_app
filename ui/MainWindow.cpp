#include "MainWindow.hpp"

#include <QLabel>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Book App");
    resize(800, 600);

    QFile styleFile(":/styles/global");
    setupUI();
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QString::fromUtf8(styleFile.readAll());
        setStyleSheet(style);
    }
}

void MainWindow::setupProfileButton() {
    profile_button = new QPushButton(this);
    profile_button->setIcon(QIcon(":icons/user"));
    profile_button->setText("Profile");
    profile_button->setIconSize(QSize(24, 24));
    profile_button->setFixedSize(100, 35);
    profile_button->setCursor(Qt::PointingHandCursor);
    connect(profile_button, &QPushButton::released, this, &MainWindow::handleButton);
}

void MainWindow::setupHeader() {
    headerWidget = new QWidget(central);
    headerWidget->setObjectName("headerWidget");

    headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(10, 5, 10, 5);
    headerLayout->setSpacing(20);
    headerLayout->addStretch();
    headerLayout->addWidget(profile_button);

    headerWidget->setLayout(headerLayout);
}

void MainWindow::setupContent() {
    contentWidget = new QWidget(central);
    contentWidget->setObjectName("contentWidget");

    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(10, 10, 10, 10);
    contentLayout->setSpacing(10);

    QLabel *label = new QLabel("Main content", contentWidget);
    contentLayout->addWidget(label);

    contentWidget->setLayout(contentLayout);
}

void MainWindow::setupUI() {
    central = new QWidget(this);
    setCentralWidget(central);

    mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    setupProfileButton();
    setupHeader();
    setupContent();

    mainLayout->addWidget(headerWidget, 1);
    mainLayout->addWidget(contentWidget, 4);
}

void MainWindow::handleButton() {
}