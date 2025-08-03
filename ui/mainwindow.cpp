#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent) {
    resize(800, 600);
    setWindowTitle("Booktile");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    button->setText("click me");
    layout->addWidget(button, 0, Qt::AlignCenter);

    setCentralWidget(centralWidget);
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
}

void MainWindow::onButtonClicked() {
    this->close();
}