
#ifndef __HPTL_H_
#define __HPTL_H_ 1

#if defined(__cplusplus)
extern "C" {
#endif

struct performance_info {
  unsigned long long start_clock;
  unsigned long long end_clock;
  unsigned long long clock_freq;
};

extern void init_performance_info(struct performance_info *pi);
extern void performance_start(struct performance_info *pi);
extern void performance_stop(struct performance_info *pi);
extern double performance_duration(struct performance_info *pi);

#if defined(__cplusplus)
}
#endif

#endif
