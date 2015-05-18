#ifndef POPPY_TEST_SRC_GENE_H
#define POPPY_TEST_SRC_GENE_H

#include <assert.h>

#include <vector>
#include <algorithm>

#include "TspCity.h"

class Gene
{
  friend const bool operator==(const Gene& lhs, const Gene& rhs);
  friend const bool operator<(const Gene& lhs, const Gene& rhs);
 public:
  Gene(const std::vector<int>& idxs, const std::vector<TspCity> *cities)
    :tspCityIdxs(idxs), cities_(cities)
  {
    assert(tspCityIdxs.size() > 3);
    assert(tspCityIdxs.size() == cities->size());
  }

  Gene(const Gene& rhs, const std::vector<TspCity> *cities)
    :tspCityIdxs(rhs.tspCityIdxs), cities_(cities) { }

  Gene mate(const Gene& rhs);
  void variation(double prob);
  double adaptiveValue() const;
  std::vector<int> sequenceOfIdx() const {return tspCityIdxs; }

  void print();

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

  return std::equal(lhs.tspCityIdxs.begin(), lhs.tspCityIdxs.end(),
                    rhs.tspCityIdxs.begin());
}

inline const bool operator<(const Gene& lhs, const Gene& rhs)
{
  return lhs.adaptiveValue() < rhs.adaptiveValue();
}

#endif

