#include "error.hpp"
#include <iostream>


void error(std::string msg, int exit_code)
{
    std::cerr << msg << "\n";
    std::exit(exit_code);
}
