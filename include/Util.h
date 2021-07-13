#pragma once

#include <cmath>  /* for std::abs(double) */

inline bool isEqual(double x, double y)
{
  const double epsilon = 1e-5;
  return std::abs(x - y) <= epsilon * std::abs(x);
}

inline bool isNearlyZero(double x) {
    const double epsilon = 1e-5;
    return std::abs(x) <= epsilon;
}