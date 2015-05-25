#ifndef POPPY_TEST_SRC_GENEOFPORTER_H
#define POPPY_TEST_SRC_GENEOFPORTER_H

#if 0
class GeneOfPorter : public Gene
{
 public:
  typedef std::tr1::shared_ptr<Gene> GenePtr;

  GeneOfPorter(const std::vector<int>& idxs, const std::vector<TspCity> *cities)
   : Gene(idxs, cities) { }
  GeneOfPorter(const GeneOfPorter& rhs)
   : Gene(rhs.tspCityIdxs, rhs.cities_) { }

  GenePtr mate(const Gene& rhs);
  void variation(double prob);
  double adaptiveValue() const;
};
#endif

#endif
