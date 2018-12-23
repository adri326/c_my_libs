#include "time.h"

double getMillis() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  return (double)ts.tv_sec * 1e3 + (double)ts.tv_nsec / 1e6;
}

void sleep(double millis) {
  double start = getMillis();
  while (getMillis() > start + millis) {};
}
