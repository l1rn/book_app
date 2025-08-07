#include <iostream>
#include <QApplication>

#include "src/project/execute.hpp"

extern "C" {
#include "author.h"
#include "book.h"
#include "publisher.h"
#include "db.h"
}

int main(int argc, char *argv[]) {
    if (handle_open() == 1) {
        std::cerr << "Database failed\n";
    }

    return 0;
}
