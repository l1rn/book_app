#include <QApplication>
#include <QPushButton>

#include "ui/mainwindow.h"

extern "C" {
#include "models/author.h"
#include "models/book.h"
#include "models/publisher.h"
}

int main(int argc, char *argv[]) {
    Author a = create_author("Brian", "Kelly");
    print_author(&a);

    return 0;
}
