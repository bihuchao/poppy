#ifndef POPPY_TEST_SRC_TSP_H
#define POPPY_TEST_SRC_TSP_H

struct CityPos
{
  CityPos(int x_, int y_)
      : x(x_), y(y_) { }
  int x;
  int y;
};

class GeneticTsp
{
 public:
  GeneticTsp(std::vector<CityPos> cityPoss, int maxite);

  static std::vector<CityPos> createAllCitPos(int num, int width, int, height);
};

#endif

