#include "time.hpp"
#include <chrono>

double now()
{
    typedef std::chrono::high_resolution_clock T;
    auto t = T::now();
    return std::chrono::duration_cast<std::chrono::duration<double>>(t.time_since_epoch()).count();
}
