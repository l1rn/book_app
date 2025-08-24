#ifndef BOOK_LIST_APP_ARENAGUARD_HPP
#define BOOK_LIST_APP_ARENAGUARD_HPP

#include <cstddef>
#include <stdexcept>

extern "C"{
#include "core/memory/arena_api.h"
}

class ArenaGuard {
public:
    explicit ArenaGuard(size_t capacity = 64*1024);
    ~ArenaGuard();

    ArenaGuard(const ArenaGuard&) = delete;
    ArenaGuard& operator=(const ArenaGuard&) = delete;

    ArenaGuard(ArenaGuard&& other) noexcept;
    ArenaGuard& operator=(ArenaGuard&& other) noexcept;

    Arena* get() const noexcept;
    void reset() noexcept;
private:
    Arena *arena_;
};


#endif //BOOK_LIST_APP_ARENAGUARD_HPP