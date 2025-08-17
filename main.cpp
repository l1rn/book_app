#include <iostream>
#include <QApplication>

#include "main_window.hpp"
#include "src/project/execute.hpp"

extern "C" {
    #include "memory/arena.h"
}

int main(int argc, char *argv[]) {
    Arena *a = arena_create(ARENA_MAX_SIZE);
    if (!a) return 1;

    if (handle_open_app(a) != 0) {
        std::cerr << "Database failed\n";
    }

    QApplication app(argc, argv);
    QMainWindow window;
    window.setGeometry(100, 100, 600, 400);
    window.show();
    auto ret = app.exec();
    handle_close_app(a);
    return ret;
}
