#include <iostream>
#include <QApplication>

#include "MainWindow.hpp"
#include "src/project/ApplicationManager.hpp"

int main(int argc, char *argv[]) {
    ApplicationManager lifecycle;
    if (lifecycle.open_app() != 0) {
        std::cerr << "Database failed\n";
    }
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    auto ret = app.exec();
    lifecycle.close_app();
    return ret;
}
