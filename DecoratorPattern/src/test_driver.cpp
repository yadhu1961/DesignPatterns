//============================================================================
// Name        : DecoratorPattern.cpp
// Author      : Yadu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <type_traits>

#include "FollowXTypes.h"
#include "IFollowXScheduler.h"

using namespace std;

namespace {

static IFollowXScheduler* followXfactory(const SchedulingMode schedulingMode, std::vector<Cqi>&& cqiVector)
{
  switch (schedulingMode)
  {
    case SchedulingMode::followRiCqi: return new TFollowXScheduler(FollowRi(FollowCqi(FollowXDummy(), cqiVector)), SchedulingMode::followRiCqi);
    case SchedulingMode::followBo: return new TFollowXScheduler(FollowBo(), SchedulingMode::followBo);
    case SchedulingMode::followRi: return new TFollowXScheduler(FollowRi(FollowXDummy()), SchedulingMode::followRi);
    default: return new TFollowXScheduler(FollowFixed(), SchedulingMode::followFixed);
  }
}

}   // namespace

int main()
{
  cout << "DecoratorPattern\n" << endl;

  std::unique_ptr<IFollowXScheduler> followXScheduler{followXfactory(SchedulingMode::followRiCqi, CqiTable{0, 1, 2, 3, 4})};

  followXScheduler->update(CsiResultHolder(ResourceIndicator{0}, Cqi{0}, Ri{0}));

  followXScheduler->adaptSchedParams();

  return 0;
}
