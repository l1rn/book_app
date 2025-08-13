

#include "main_window.hpp"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Book App");
    resize(800, 600);

    auto central_widget =  new QWidget(this);
    setCentralWidget(central_widget);
}
