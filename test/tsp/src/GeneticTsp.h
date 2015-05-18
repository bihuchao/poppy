#ifndef POPPY_TEST_SRC_GENETICTSP_H
#define POPPY_TEST_SRC_GENETICTSP_H

#include <list>

#include "TspCity.h"
#include "Gene.h"

class GeneticTsp
{
 public:
  GeneticTsp(const std::vector<TspCity> cities, int initnum,
             double varprob, double mateprob)
   : cities_(cities), initnum_(initnum),
     varprob_(varprob), mateprob_(mateprob) { }

  void InitGroup();
  void evolution();
  Gene bestGene();

  void print();
 private:
  std::vector<TspCity> cities_;
  std::list<Gene> group_;

  int initnum_;
  double varprob_;
  double mateprob_;
};

#endif

