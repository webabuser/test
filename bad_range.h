#pragma once
#include <exception>

class BadRange : public std::exception {
 public:
    BadRange() = default;
    
    virtual const char* what() const noexcept override {
        return "ОШИБКА: Вне диапазона контейнера.";
    }
};


class BadLength : public std::exception {
 public:
    BadLength() = default;
    
    virtual const char* what() const noexcept override {
        return "ОШИБКА: Неправильная длина масcива.";
    }
};
