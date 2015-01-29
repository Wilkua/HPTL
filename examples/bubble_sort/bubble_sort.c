
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__WIN32) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#endif

#if defined(__linux__)
#include <unistd.h>
#include <time.h>
#endif

#include "../../hptl.h"

/* Performs a simple bubble sort on an array of data.

   PRE:
       int data[]    The array to be sorted.
       size_t count  The number of items in the array.

   POST:
      Returns: Nothing.
*/
void bubble_sort(int data[], size_t count) {
  int flip_occured = 1;
  int tmp = 0;
  size_t moving_count = count;

  while (flip_occured) {
    flip_occured = 0;

    if (moving_count > 0) {
      moving_count--;
    }

    for (size_t i = 0; i < moving_count; i++) {
      if (data[i] > data[i+1]) {
        tmp = data[i];
        data[i] = data[i+1];
        data[i+1] = tmp;
        flip_occured = 1;
      }
    }
  } // end while (flip_occured)
} // end bubble_sort

/* Fills an array with random integer data.
   The data is non-unique, so there will be duplicates, especially if
   the array is a small size (less than 1000 items).

   PRE:
       int data[]    The array to be filled with data.
                     (Existing data will be overwritten.)
       size_t count  The number of items in the array.

   POST:
       Returns: Nothing.
*/
void array_fill_random(int data[], size_t count) {
  // Seed the random number generator
#if defined(_WIN32)
  srand(GetTickCount());
#endif
#if defined(__linux__)
  // Linux is crazy...
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) { srand(ts.tv_nsec); }
  else { srand(1234567890L); }
#endif
  // Blank the array, just to be safe.
  memset(data, 0, count * sizeof(int));

  // Loop through the array and fill it with random data.
  for (size_t i = 0; i < count; i++) {
    data[i] = (rand() % 100) + 1;
  }
} // end array_fill_random

/* Checks to make sure the array really got sorted by the sort function.

   PRE:
       int data[]    The array in which to check for order.
       size_t count  The number of items in the array.

   POST:
       Returns: Non-zero (1) if the array is in order. Zero otherwise.
*/
int check_array_in_order(int data[], size_t count) {
  // Initialize the value to true (1)
  int in_order = 1;

  // Loop through the array and check all the values for
  // ascending order. If an item at index 'i' is greater than
  // an item at index 'i+1' then the array is not in order.
  // this is the same process that bubble_sort uses to check if
  // items should be swapped.
  for (size_t i = 0; i < count - 1; i++) {
    if (data[i] > data[i+1]) {
      in_order = 0;
    }
  }

  return in_order;
} // end check_array_in_order

int main(int argc, const char* argv[]) {
  // Create a performance_info object to track
  // the performance information.
  struct performance_info perf_info;

  // This is the array of items we're going to
  // sort through.
  int data[5000];

  // Fill the array with random data.
  array_fill_random(data, 5000);

  // The performance information must be initialized before
  // it can be used. This process calculates the CPU's timing
  // frequency used later in calculations.
  init_performance_info(&perf_info);

  // Call this function with the performance info object
  // to store the current performance timer information.
  performance_start(&perf_info);

  // Now call your function youw ant to time.
  bubble_sort(data, 5000);

  // After calling the function youw ant tot ime, call this
  // function to save the timer's ending value. This will be
  // used for calcuations.
  performance_stop(&perf_info);

  // Check to see if the array was put in order.
  // We need to notify the user that the sort didn't
  // order the array correctly. If the array isn't ordered
  // then the timing isn't accurate because the sort didn't
  // perform the task it was meant to perform.
  if (check_array_in_order(data, 5000)) {
    puts("Array is in order.");
  }
  else {
    puts("Sort failed to order array.");
  }

  // Output the timing information
  printf("Frequency:  %lld\n", perf_info.clock_freq);
  printf("Start time: %lld\n", perf_info.start_clock);
  printf("End time:   %lld\n\n", perf_info.end_clock);

  // Display the calculated timing (in microseconds)
  printf("Time: %f microseconds\n", performance_duration(&perf_info));

  return 0;
}
