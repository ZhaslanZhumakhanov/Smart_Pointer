#pragma once
#include <iostream>
#include <cassert>

template <typename T>
class scoped_ptr {
private:
    T* ptr_;
public:
    typedef T element_type; // просто оставьте это здесь.

    explicit scoped_ptr(T *ptr = nullptr) : ptr_(ptr){
        std::cout << "SmartPointer is created and wraps a ptr" << std::endl;
    } // явный конструктор для оборачивания указателя

    scoped_ptr(const scoped_ptr&) = delete ;// удалите конструктор копирования

    scoped_ptr(scoped_ptr&&) = delete ;// удалите конструктор перемещения

    ~scoped_ptr(){
        std::cout << "Deleting SmartPointer and original ptr" << std::endl;
        delete ptr_;
    } // деструктор

    T* get() const { return ptr_; } // метод get чтобы взять указатель

    T* operator ->() const { return ptr_; } // оператор -> чтобы взять указатель.

    T& operator *() const { return *ptr_; } // оператор * разыменования указателя и получения ссылки на объект T

    void reset(T* ptr = nullptr) {
        delete ptr_;
        ptr_=ptr;
    } // метод reset для очистки или замены указателя

    T* release(){
        auto new_ptr = ptr_;
        ptr_ = nullptr;
        return new_ptr;
    }// метод release чтобы отдать сырой указатель, НО НЕ УДАЛЯТЬ его

    // это оператор, чтобы можно было писать if (sptr) { ... }.
    explicit operator bool() const{ return ptr_ != nullptr; }
};

