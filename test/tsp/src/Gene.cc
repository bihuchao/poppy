#include <time.h>
#include <stdio.h>
#include <sys/time.h>

#include "Gene.h"

const int Gene::kInvalidIndex;

void Gene::variation(double prob)
{
  int pos1 = ::rand() % tspCityIdxs.size();
  int pos2 = ::rand() % tspCityIdxs.size();
  int intprob = prob * 100;
  int randprob = ::rand() % 100;

  if (pos1 == pos2 || randprob > intprob)
  {
    return;
  }

  std::swap(tspCityIdxs[pos1], tspCityIdxs[pos2]);
}

Gene Gene::mate(const Gene& rhs)
{
  assert(tspCityIdxs.size() == rhs.tspCityIdxs.size());

  int pos1 = ::rand() % tspCityIdxs.size();
  int pos2 = ::rand() % tspCityIdxs.size();

  if (pos1 > pos2)
  {
    std::swap(pos1, pos2);
  }

  std::vector<int> filialIdxs(tspCityIdxs.size(), kInvalidIndex);

  std::copy(tspCityIdxs.begin() + pos1, tspCityIdxs.begin() + pos2 + 1,
            filialIdxs.begin() + pos1);

  for (size_t i = 0; i < rhs.tspCityIdxs.size(); i++)
  {
    std::vector<int>::iterator pos;

    pos = std::find(filialIdxs.begin(), filialIdxs.end(), rhs.tspCityIdxs[i]);
    if (pos != filialIdxs.end())
    {
      continue;
    }

    pos = std::find(filialIdxs.begin(), filialIdxs.end(), kInvalidIndex);
    if (pos == filialIdxs.end())
    {
      break;
    }

    *pos = rhs.tspCityIdxs[i];
  }

  return Gene(filialIdxs, cities_);
}

double Gene::adaptiveValue() const
{
  double totalDistance = 0.0;
  for (size_t i = 0; i < tspCityIdxs.size(); i++)
  {
    size_t prev = i;
    size_t next = (i + 1) % tspCityIdxs.size();

    prev = tspCityIdxs[prev];
    next = tspCityIdxs[next];
    totalDistance += cities_->at(prev).distance(cities_->at(next));
  }

  return 1/totalDistance;
}


void Gene::print()
{
  ::printf("\n");
  for (size_t i = 0; i < tspCityIdxs.size(); i++)
  {
    ::printf("%02d ", tspCityIdxs[i]);
  }
  ::printf("\n");
}
