#include "time.hpp"
#include "error.hpp"
#include <sys/resource.h>
#include <sys/time.h>
#include <chrono>

unsigned long now_usage()
{
    rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    return ((ru.ru_utime.tv_sec + ru.ru_stime.tv_sec) * 1000 +
        (ru.ru_utime.tv_usec + ru.ru_stime.tv_usec) / 1000);
}

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        error("Nie mogę zmierzyć czasu.");
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

double now()
{
    typedef std::chrono::high_resolution_clock T;
    auto t = T::now();
    return std::chrono::duration_cast<std::chrono::duration<double>>(t.time_since_epoch()).count();
}
