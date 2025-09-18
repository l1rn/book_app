#include "MainWindow.hpp"

#include <QLabel>
#include <QFile>
#include <QFontDatabase>
#include <QGraphicsBlurEffect>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Book App");
    resize(800, 600);

    int fontId = QFontDatabase::addApplicationFont(":fonts/raleway-regular");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    mainFont = family;
    boldMainFont = family;
    mainFont.setPointSize(14);
    boldMainFont.setPointSize(12);
    boldMainFont.setBold(true);

    QFile styleFile(":/styles/global");
    setupUI();
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QString::fromUtf8(styleFile.readAll());
        setStyleSheet(style);
    }
}

void MainWindow::setupProfileButton() {
    profileButton = new QPushButton(this);

    profileButton->setIcon(QIcon(":icons/user"));
    profileButton->setText("Profile");
    profileButton->setFont(mainFont);
    profileButton->setIconSize(QSize(24, 24));
    profileButton->setFixedSize(100, 35);
    profileButton->setCursor(Qt::PointingHandCursor);

    connect(profileButton, &QPushButton::released, this, &MainWindow::handleButton);
}

void MainWindow::setupHeader() {
    headerWidget = new QWidget(central);
    headerWidget->setObjectName("headerWidget");

    headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(10, 5, 10, 5);
    headerLayout->setSpacing(20);
    headerLayout->addStretch();

    // added search input first because we need to put it in the center
    searchInput = new QLineEdit();
    searchInput->setFont(mainFont);
    searchInput->setPlaceholderText("Enter text here...");
    searchInput->setMaxLength(10);

    searchButton = new QPushButton();
    searchButton->setFont(mainFont);
    searchButton->setFixedSize(30, 30);
    searchButton->setIcon(QIcon(":icons/search"));
    searchButton->setCursor(Qt::PointingHandCursor);

    headerLayout->addWidget(searchInput);
    headerLayout->addWidget(searchButton);
    headerLayout->addWidget(profileButton);

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