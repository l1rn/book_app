#include <iostream>
#include <QApplication>

#include "main_window.hpp"
#include "services/AuthorService.hpp"
#include "src/project/ExecuteManager.hpp"

int main(int argc, char *argv[]) {

    ExecuteManager execute;
    if (execute.open_app() != 0) {
        std::cerr << "Database failed\n";
    }
    AuthorService authorService(execute.get_context());
    authorService.printAllAuthors();

    QApplication app(argc, argv);
    QMainWindow window;
    window.setGeometry(100, 100, 600, 400);
    window.show();
    auto ret = app.exec();
    execute.close_app();
    return ret;
}
