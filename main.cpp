#include <iostream>
#include <cassert>
#include <string>
#include "scoped_ptr.h"

using namespace std;

struct foo {
    int field1;
    int field2;
};

void bar() {
    scoped_ptr<foo> foo_ptr(new foo {0, 111});
    cout << (*foo_ptr).field1 << " " << foo_ptr->field2 << " " << foo_ptr.get() << endl;

    if (foo_ptr) foo_ptr->field1 += 1;

    cout << foo_ptr.get() << endl;
    cout << foo_ptr->field1 << endl;

}

static void test_scoped_ptr() {
    static_assert(
            !std::is_convertible<int *, scoped_ptr<int>>::value,
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
            std::is_constructible<bool, scoped_ptr<int>>::value // explicit conversion
                                                        && !std::is_convertible<scoped_ptr<int>,
            bool>::value, // implicit conversion
            "scoped ptr should convertible to the bool, but not implicitly");

    {
        scoped_ptr<int> empty_ptr;

        assert(!empty_ptr);
        assert(empty_ptr.get() == nullptr);
    }

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

    {
        int *i = new int{10};
        scoped_ptr<int> ptr{i};

        assert(i == ptr.release());

        delete i;
    }
}

int main() {
    bar();
    test_scoped_ptr();
    return 0;
}
