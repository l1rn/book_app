
#include <iostream>

extern "C"{
    #include "db.h"
}

int handle_open() {
    if (db_open("../data/local.db") != 0) {
        std::cerr << "Database open failed\n";
        db_close();
        return 1;
    }
    if (db_check() != 0) {
        if (db_init("../data/schemes/001_init.sql") != 0) {
            std::cerr << "Database schema init failed.\n";
            db_close();
            return 1;
        }
    }

    std::cout << "Database ready!\n";
    return 0;
}