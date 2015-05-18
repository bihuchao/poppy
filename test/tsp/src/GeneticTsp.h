#ifndef POPPY_TEST_SRC_GENETICTSP_H
#define POPPY_TEST_SRC_GENETICTSP_H

#include <list>
#include <tr1/memory>

#include "TspCity.h"
#include "Gene.h"

class GeneticTsp
{
 public:
  typedef std::tr1::shared_ptr<Gene> GenePtr;
  
  GeneticTsp(const std::vector<TspCity> cities, int initnum,
             double varprob, double mateprob)
   : cities_(cities), initnum_(initnum),
     varprob_(varprob), mateprob_(mateprob) { }

  void InitGroup();
  void evolution();
  Gene bestGene();

  void print();

  static bool GenePtrCompare(const GenePtr& lhs, const GenePtr& rhs);
 private:
  std::vector<TspCity> cities_;
  std::list<GenePtr> group_;

  int initnum_;
  double varprob_;
  double mateprob_;
};

#endif

