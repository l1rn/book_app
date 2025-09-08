#include "MainWindow.hpp"

#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Book App");
    resize(800, 600);

    setupUI();
}

void MainWindow::setupUI() {
    profile_button = new QPushButton(this);
    profile_button->setIcon(QIcon(":icons/user"));
    profile_button->setText("Profile");
    profile_button->setIconSize(QSize(24, 24));
    profile_button->setStyleSheet("QPu");
    connect(profile_button, &QPushButton::released, this, &MainWindow::handleButton);

}

void MainWindow::handleButton() {
    profile_button->setText("Hello");
}