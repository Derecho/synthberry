#ifndef LOG_H
#define LOG_H

#include <iostream>

#ifdef DEBUG
#define LOG(...) std::cout << __VA_ARGS__ << std::endl
#else
#define LOG(...)
#endif

#endif  // LOG_H
