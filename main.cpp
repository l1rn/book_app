#include <iostream>
#include <QApplication>

#include "data/execute.hpp"

extern "C" {
#include "models/include/author.h"
#include "models/include/book.h"
#include "models/include/publisher.h"
#include "data/db.h"

}

int main(int argc, char *argv[]) {
    if (handle_open() == 1) {
        std::cerr << "Database failed\n";
    }

    return 0;
}
