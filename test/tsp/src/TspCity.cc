#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <time.h>

#include "TspCity.h"

std::string TspCity::toString() const
{
  char buf[256];
  ::snprintf(buf, sizeof(buf), "%03d-%03d", x_, y_);

  return name_ + ":" + buf;
}

double TspCity::distance(const TspCity& rhs) const
{
  double xdis = ::fabs(x_ - rhs.x_);
  double ydis = ::fabs(y_ - rhs.y_);

  double ret = ::sqrt(xdis * xdis + ydis * ydis);
  //printf("%d %d : %d %d, %lf\n", x_, y_, rhs.x_, rhs.y_, ret);
  return ret;
}
