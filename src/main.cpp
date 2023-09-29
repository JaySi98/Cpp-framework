#include <iostream>
#include <tmp/tmp.hpp>

int main(int argc, char** argv) 
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "2 + 2 = " << tmp::add(2,2) << std::endl;

    return EXIT_SUCCESS;
}