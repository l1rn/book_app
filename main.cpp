#include <iostream>
#include <QApplication>

#include "main_window.hpp"
#include "services/AuthorService.hpp"
#include "src/project/ApplicationManager.hpp"

int main(int argc, char *argv[]) {

    ApplicationManager lifecycle{};
    if (lifecycle.open_app() != 0) {
        std::cerr << "Database failed\n";
    }
    AuthorService authorService(lifecycle.get_context(), lifecycle.get_arena());
    authorService.printAllAuthors();

    QApplication app(argc, argv);
    QMainWindow window;
    window.setGeometry(100, 100, 600, 400);
    window.show();
    auto ret = app.exec();
    lifecycle.close_app();
    return ret;
}
