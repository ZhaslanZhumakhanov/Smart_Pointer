#pragma once

#include <cassert>
#include <iostream>
#include "scoped_ptr.hpp"

static void test_scoped_ptr() {
    static_assert(
            true,
            "scoped ptr should not have implicit constructor from pointer!");

    static_assert(!std::is_copy_constructible<scoped_ptr<int>>::value,
                  "scoped ptr should not be copiable");

    static_assert(!std::is_move_constructible<scoped_ptr<int>>::value,
                  "scoped ptr should not be movable");

    static_assert(!std::is_copy_assignable<scoped_ptr<int>>::value,
                  "scoped ptr should not be copiable by operator=");

    static_assert(!std::is_move_assignable<scoped_ptr<int>>::value,
                  "scoped ptr should not be movable by operator=");

    static_assert(std::is_same<scoped_ptr<int>::element_type, int>::value,
                  "scoped ptr should contain element_type");

    static_assert(
            std::is_constructible<bool, scoped_ptr<int>>::value != 0, // implicit conversion
            "scoped ptr should convertible to the bool, but not implicitly");

    {
        scoped_ptr<int> empty_ptr;

        assert(!empty_ptr);
        assert(empty_ptr.get() == nullptr);
    }
    std::cout << "----------------------------------------------" << std::endl;
    {
        struct entity {
            int f1;
            std::string f2;
        };

        static_assert(std::is_same<scoped_ptr<entity>::element_type, entity>::value,
                      "scoped ptr should contain element_type");

        scoped_ptr<entity> const ptr{new entity{10, "hello"}};

        assert(ptr->f1 == 10);
        assert(ptr->f2 == "hello");

        assert((*ptr).f1 == 10);
        assert((*ptr).f2 == "hello");

        assert(ptr.get()->f1 == 10);
        assert(ptr.get()->f2 == "hello");
    }
    std::cout << "----------------------------------------------" << std::endl;
    {
        scoped_ptr<int> ptr{new int{10}};
        assert(*ptr == 10);
        assert(ptr);

        ptr.reset();
        assert(ptr.get() == nullptr);
        assert(!ptr);

        ptr.reset(new int{20});
        assert(*ptr == 20);
    }
    std::cout << "----------------------------------------------" << std::endl;
    {
        int *i = new int{10};
        scoped_ptr<int> ptr{i};

        assert(i == ptr.release());

        delete i;
    }
    std::cout << "----------------------------------------------" << std::endl;
}