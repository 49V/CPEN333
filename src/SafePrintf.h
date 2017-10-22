//
// Created by Antonio on 2017-10-19.
//

#ifndef LAB6_SAFEPRINT_H
#define LAB6_SAFEPRINT_H

#include <cstdio>
#include <mutex>
void SafePrintf(char const * const format, ...)
{
  va_list args;
  va_start(args, format);
  static std::mutex mutex;
  {
    std::lock_guard<decltype(mutex)> lock(mutex);
    std::vprintf(format, args);
  }
  va_end(args);
}

#endif //LAB6_SAFEPRINT_H
