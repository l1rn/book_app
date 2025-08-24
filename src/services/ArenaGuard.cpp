#include "ArenaGuard.hpp"
#include <iostream>

ArenaGuard::ArenaGuard(size_t capacity) {
    arena_ = arena_create(capacity);
    if (!arena_) throw std::bad_alloc();
    std::cout << "Arena created: " << arena_ << "\n";
}

ArenaGuard::~ArenaGuard() {
    if (arena_) {
        arena_destroy(arena_);
        std::cout << "Arena destroyed: " << arena_ << "\n";
    }
}

ArenaGuard::ArenaGuard(ArenaGuard&& other) noexcept : arena_(other.arena_) {
    other.arena_ = nullptr;
    std::cout << "Arena moved (ctor). new: " << arena_ << "\n";
}

ArenaGuard &ArenaGuard::operator=(ArenaGuard &&other) noexcept {
    if (this != &other) {
        if (arena_) {
            arena_destroy(arena_);
            std::cout << "Arena destroyed during move-assign: " << arena_ << "\n";
        };
        arena_ = other.arena_;
        other.arena_ = nullptr;
        std::cout << "Arena moved (assign). new: " << arena_ << "\n";
    }
    return *this;
}

Arena *ArenaGuard::get() const noexcept {
    return arena_;
}

void ArenaGuard::reset() noexcept {
    if (arena_) arena_reset(arena_);
}