#ifndef POPPY_TEST_SRC_TSPCITY_H
#define POPPY_TEST_SRC_TSPCITY_H

#include <string>

class TspCity
{
 public:
  TspCity(int x, int y, std::string name = "City")
   : x_(x), y_(y), name_(name) { }

  std::string toString() const;
  double distance(const TspCity& rhs) const;
  int x() const { return x_; }
  int y() const { return y_; }
 private:
  int x_;
  int y_;
  std::string name_;
};

#endif

