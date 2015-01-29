/*******************************************************************************
 * High Performance Time Library
 * Written by William Drescher
 * Written on 23 January 2015
 *
 * Library used to time applications using high performance, high resolution
 * timers in an easy-to-use and (semi)portable way.
 *
 * NOTICE: This library is NOT a benchmarking tool! This library is desigend
 * to time functions and program features RELATIVE to themselves. This library
 * will ALWAYS produce different values based on system architecture, list of
 * running applications, and many other factors. The wrapping functions also
 * produce an overhead when timing functions. The overhead will only be
 * consistent relative to the particular instance (and thread) of the process
 * that calls the wrapper functions. Therefore, this library should only be used
 * for performance testing and not for benchmarking.
 *
 * For more accurate timings, use the platform specific, high performance timing
 * functions yourself instead of relying on this wrapper library. This library is
 * only made available for quick-and-dirty timing testing.
 *
 *********************************************************************************/
#if defined(__WIN32) || defined(_WIN32) || defined(WIN32)
#define PLATFORM_WIN32 1
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#endif

#if defined(__linux__)
#define PLATFORM_LINUX 1
#include <time.h>
#endif

#include "hptl.h"

#if defined(__cplusplus)
extern "C" {
#endif
void init_performance_info(struct performance_info *pi) {
  pi->start_clock = 0;
  pi->end_clock = 0;
  pi->clock_freq = 0;

#if defined(PLATFORM_WIN32)
  // Win32 code
#endif
#if defined(PLATFORM_LINUX)
  struct timespec tmp;
  if (clock_getres(CLOCK_THREAD_CPUTIME_ID, &tmp) != -1) {
    pi->clock_freq = (unsigned long long)tmp.tv_nsec +
      ((unsigned long long)tmp.tv_sec * 1000000000L);
  }
  else {
    pi->clock_freq = 1;
  }
#endif
}
#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)
extern "C" {
#endif
void performance_start(struct performance_info *pi) {
#if defined(PLATFORM_WIN32)
  // Win32 code
#endif
#if defined(PLATFORM_LINUX)
  struct timespec tmp;
  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tmp) != -1) {
    pi->start_clock = (unsigned long long)tmp.tv_nsec +
      ((unsigned long long)tmp.tv_sec * 1000000000L);
  }
  else {
    pi->start_clock = 0;
  }
#endif
}
#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)
extern "C" {
#endif
void performance_stop(struct performance_info *pi) {
#if defined(PLATFORM_WIN32)
  // Win32 code
#endif
#if defined(PLATFORM_LINUX)
  struct timespec tmp;
  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tmp) != -1) {
    pi->end_clock = (unsigned long long)tmp.tv_nsec +
      ((unsigned long long)tmp.tv_sec * 1000000000L);
  }
  else {
    pi->end_clock = 0;
  }
#endif
}
#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)
extern "C" {
#endif
double performance_duration(struct performance_info *pi) {
  if (pi != (void*)0) {
    return (double)((double)(pi->end_clock - pi->start_clock) /
      (double)pi->clock_freq) / 1000.0f;
  }
  return 0;
}
#if defined(__cplusplus)
}
#endif
