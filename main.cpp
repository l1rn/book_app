#include <iostream>
#include <QApplication>

#include "MainWindow.hpp"
#include "src/project/ApplicationManager.hpp"
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    ApplicationManager lifecycle;
    if (lifecycle.open_app() != 0) {
        std::cerr << "Database failed\n";
    }
    QApplication app(argc, argv);

    int fontId = QFontDatabase::addApplicationFont(":fonts/raleway-regular");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    app.setStyleSheet(QString(R"(
        QPushButton {
            font-family: '%1';
        }
    )").arg(family));

    MainWindow mainWindow;
    mainWindow.show();
    auto ret = app.exec();
    lifecycle.close_app();
    return ret;
}
