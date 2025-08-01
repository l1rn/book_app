#include "../include/publisher.h"

#include <string.h>

Publisher createPublisher(const char* name) {
    Publisher p = { 0 };
    strncpy(p.company_name, name, sizeof p.company_name-1);
    p.bookCount = 0;
    p.books = NULL;

    return p;
}
