#include <iostream>
#include <QApplication>

#include "main_window.hpp"
#include "src/project/execute.hpp"

extern "C" {
    #include "db.h"
}

int main(int argc, char *argv[]) {
    if (handle_db() == 1) {
        std::cerr << "Database failed\n";
    }

    QApplication app(argc, argv);
    QMainWindow window;
    window.setGeometry(100, 100, 600, 400);
    window.show();
    auto ret = app.exec();
    db_close();
    return ret;
}
