//============================================================================
// Name        : templateChain.cpp
// Author      : Yadu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include "FollowXTypes.h"
#include "IFollowXScheduler.h"

using namespace std;

namespace {

static IFollowXScheduler* followXfactory(const SchedulingMode schedulingMode, std::vector<Cqi>&& cqiVector)
{
  bool dummyParam{false};
  switch (schedulingMode)
  {
    case SchedulingMode::followRiCqi: return new TFollowXScheduler(FollowRiCqi_AdaptRankMcs(cqiVector));
    case SchedulingMode::followBo: return new TFollowXScheduler(FollowBo());
    case SchedulingMode::followRi: return new TFollowXScheduler(FollowRi_AdaptRank(dummyParam));
    default: return new TFollowXScheduler(FollowFixed());
  }
}

}   // namespace

int main()
{
  cout << "PolicyBasedDesign +  StrategyPattern\n" << endl;   // prints TemplateChaining

  std::unique_ptr<IFollowXScheduler> followXScheduler{followXfactory(SchedulingMode::followRiCqi, CqiTable{0, 1, 2, 3, 4})};

  followXScheduler->update(CsiResultHolder(ResourceIndicator{0}, Cqi{0}, Ri{0}));

  //  FollowRiCqi followRiCqi(cqiTable);
  //
  //  followRiCqi.update(CsiResultHolder(ResourceIndicator{0}, Cqi{0}, Ri{0}));
  //
  //  AdaRiCqi adaRiCqi(ResourceIndicator{-1}, Cqi{-1}, Ri{-1});
  //
  followXScheduler->adaptSchedParams();

  return 0;
}
