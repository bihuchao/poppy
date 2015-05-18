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
  for (int i = 0; i < citynum; i++)
  {
    tmp.push_back(i);
  }

  do
  {
    allGenes.push_back(Gene(tmp,  &cities_));
  } while(next_permutation(tmp.begin(), tmp.end()));

  int i = 0;
  tmp.clear();
  while (i < initnum_ || tmp.size() >= allGenes.size())
  {
    int randidx = ::rand() % allGenes.size();
    if (std::find(tmp.begin(), tmp.end(), randidx) == tmp.end())
    {
      group_.push_back(GenePtr(new Gene(allGenes[randidx])));
      tmp.push_back(randidx);
      ++i;
    }
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

	filials.push_back(GenePtr(new Gene(curPtr->mate(*nextPtr))));
	
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


