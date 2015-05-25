#ifndef POPPY_TEST_SRC_GENE_H
#define POPPY_TEST_SRC_GENE_H

#include <assert.h>

#include <vector>
#include <algorithm>
#include <tr1/memory>

#include "TspCity.h"

class Gene
{
  friend const bool operator==(const Gene& lhs, const Gene& rhs);
  friend const bool operator<(const Gene& lhs, const Gene& rhs);
 public:
  typedef std::tr1::shared_ptr<Gene> GenePtr;

  Gene(const std::vector<int>& idxs, const std::vector<TspCity> *cities)
    :tspCityIdxs(idxs), cities_(cities)
  {
    assert(tspCityIdxs.size() > 3);
    assert(tspCityIdxs.size() == cities->size());
  }

  Gene(const Gene& rhs, const std::vector<TspCity> *cities)
    :tspCityIdxs(rhs.tspCityIdxs), cities_(cities) { }

  virtual GenePtr mate(const Gene& rhs);
  virtual void variation(double prob);
  virtual double adaptiveValue() const;

  std::vector<int> sequenceOfIdx() const {return tspCityIdxs; }

  void print();

  virtual ~Gene() { }

  static const int kInvalidIndex = -1;
 private:
  std::vector<int> tspCityIdxs;
  const std::vector<TspCity> *cities_;

  bool isNull(int idx) { return tspCityIdxs[idx] == kInvalidIndex; }
};

inline const bool operator==(const Gene& lhs, const Gene& rhs)
{
  if (lhs.tspCityIdxs.size() != rhs.tspCityIdxs.size())
  {
    return false;
  }

  if (lhs.cities_ != rhs.cities_)
  {
    return false;
  }

  return std::equal(lhs.tspCityIdxs.begin(), lhs.tspCityIdxs.end(),
                    rhs.tspCityIdxs.begin());
}

inline const bool operator<(const Gene& lhs, const Gene& rhs)
{
  return lhs.adaptiveValue() < rhs.adaptiveValue();
}

#endif

