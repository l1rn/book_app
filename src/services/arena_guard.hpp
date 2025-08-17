#ifndef BOOK_LIST_APP_ARENAGUARD_HPP
#define BOOK_LIST_APP_ARENAGUARD_HPP

#include <cstddef>
#include <stdexcept>

extern "C"{
#include "core/memory/arena_api.h"
}

class ArenaGuard {
public:
    explicit ArenaGuard(size_t capacity = 64*1024) {
        arena_ = arena_create(capacity);
        if (!arena_) throw std::bad_alloc();
    }

    ~ArenaGuard() {
        if (arena_) arena_destroy(arena_);
    }

    ArenaGuard(const ArenaGuard&) = delete;
    ArenaGuard& operator=(const ArenaGuard&) = delete;

    ArenaGuard(ArenaGuard&& other) noexcept : arena_(other.arena_) {
        other.arena_ = nullptr;
    }

    ArenaGuard& operator=(ArenaGuard&& other) noexcept {
        if (this != &other) {
            if (arena_) arena_destroy(arena_);
            arena_ = other.arena_;
            other.arena_ = nullptr;
        }
        return *this;
    }

    Arena* get() const noexcept { return arena_; }
    void reset() noexcept { if (arena_) arena_reset(arena_); }
private:
    Arena *arena_;
};


#endif //BOOK_LIST_APP_ARENAGUARD_HPP