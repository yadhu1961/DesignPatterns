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

static auto followXfactory(const SchedulingMode schedulingMode, std::vector<Cqi>&& cqiVector)
{
  switch (schedulingMode)
  {
    case SchedulingMode::followRiCqi:
      return new TFollowXScheduler(new FollowRi(new FollowCqi(new FollowXDummy(), cqiVector)), SchedulingMode::followRiCqi);
    case SchedulingMode::followBo: return new TFollowXScheduler(new FollowBo(), SchedulingMode::followBo);
    case SchedulingMode::followRi: return new TFollowXScheduler(new FollowRi(new FollowXDummy()), SchedulingMode::followRi);
    default: return new TFollowXScheduler(new FollowFixed(), SchedulingMode::followFixed);
  }
}

}   // namespace

int main()
{
  cout << "DecoratorPattern\n" << endl;

  std::unique_ptr<TFollowXScheduler> followXScheduler{followXfactory(SchedulingMode::followRiCqi, CqiTable{0, 1, 2, 3, 4})};

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
