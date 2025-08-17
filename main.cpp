#include <iostream>
#include <QApplication>

#include "main_window.hpp"
#include "services/author_service.hpp"
#include "src/project/execute.hpp"

int main(int argc, char *argv[]) {

    Execute execute;
    if (execute.open_app() != 0) {
        std::cerr << "Database failed\n";
    }
    AuthorService author_service;

    QApplication app(argc, argv);
    QMainWindow window;
    window.setGeometry(100, 100, 600, 400);
    window.show();
    author_service.printAllAuthors();
    auto ret = app.exec();
    execute.close_app();
    return ret;
}
