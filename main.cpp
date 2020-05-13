#include <iostream>

#include "include/scoped_ptr.hpp"
#include "include/shared_ptr.hpp"
#include "include/test_scoped_ptr.hpp"
#include "include/test_shared_ptr.hpp"

int main() {
    std::cout << "Test_scoped_ptr" << std::endl;
    test_scoped_ptr();
    std::cout << "Test_shared_ptr" << std::endl;
    test_shared_ptr();
    return 0;
}
