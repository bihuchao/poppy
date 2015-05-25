#include <assert.h>
#include <stdio.h>

#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <list>

#include "GeneticTsp.h"
#include "Gene.h"

using std::vector;
using std::list;
using std::next_permutation;

void GeneticTsp::InitGroup()
{
  int citynum = cities_.size();
  assert(citynum > 3);

  vector<Gene> allGenes;
  vector<int> tmp;
  
  int i = 0;
  while (i < initnum_)
  {    
    tmp.clear();
    int j = 0;
    while (j < citynum)
    {
      int item = ::rand() % citynum;
      if (find(tmp.begin(), tmp.end(), item) == tmp.end())
      {
        tmp.push_back(item);
        j++;
      }
    }

    Gene newGene(tmp, &cities_);
    if (find(allGenes.begin(), allGenes.end(), newGene) == allGenes.end())
    {
      allGenes.push_back(newGene);
      i++;
    }
  }

  for (vector<Gene>::iterator ite = allGenes.begin();
        ite != allGenes.end(); ++ite)
  {
    group_.push_back(GenePtr(new Gene(*ite)));
  }
}

void GeneticTsp::evolution()
{
  int matenum = mateprob_ * group_.size();
  matenum = (matenum / 2) * 2;
  if (matenum <= 0)
  {
    return;
  }

  group_.sort(GenePtrCompare);

  list<GenePtr> filials;
  list<GenePtr>::reverse_iterator rite = group_.rbegin();
  for (int i = 0; i < matenum; i += 2)
  {
    list<GenePtr>::reverse_iterator next = ++rite;
    GenePtr curPtr = *rite;
    GenePtr nextPtr = *next;

    filials.push_back(curPtr->mate(*nextPtr));

    rite = ++next;
  }

  std::copy(filials.begin(), filials.end(), std::back_inserter(group_));
  for (list<GenePtr>::iterator ite = group_.begin();
        ite != group_.end(); ++ite)
  {
    (*ite)->variation(varprob_);
  }
  group_.sort(GenePtrCompare);
  for (int i = 0; i < (matenum / 2); i++)
  {
    group_.erase(group_.begin());
  }
}

Gene GeneticTsp::bestGene()
{
  group_.sort(GenePtrCompare);

  return **(group_.rbegin());
}

void GeneticTsp::print()
{
  for (list<GenePtr>::iterator ite = group_.begin();
      ite != group_.end(); ++ite)
  {
    (*ite)->print();
  }
}

bool GeneticTsp::GenePtrCompare(const GenePtr& lhs, const GenePtr& rhs)
{
  return *(lhs) < *(rhs);
}


