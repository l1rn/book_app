#include "ArenaGuard.hpp"
#include <iostream>

ArenaGuard::ArenaGuard(size_t capacity) {
    arena_ = arena_create(capacity);
    if (!arena_) throw std::bad_alloc();
}

ArenaGuard::~ArenaGuard() {
    if (arena_) arena_destroy(arena_);
    std::cout << "Arena destroyed";
}

ArenaGuard::ArenaGuard(ArenaGuard&& other) noexcept : arena_(other.arena_) {
    other.arena_ = nullptr;
}

ArenaGuard &ArenaGuard::operator=(ArenaGuard &&other) noexcept {
    if (this != &other) {
        if (arena_) arena_destroy(arena_);
        arena_ = other.arena_;
        other.arena_ = nullptr;
    }
    return *this;
}

Arena *ArenaGuard::get() const noexcept {
    return arena_;
}

void ArenaGuard::reset() noexcept {
    if (arena_) arena_reset(arena_);
}