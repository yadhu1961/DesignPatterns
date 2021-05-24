//============================================================================
// Name        : templateChain.cpp
// Author      : Yadu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "TemplateChainTypes.h"
#include "IFollowXScheduler.h"

using namespace std;

// static FollowMode* createFollowMode(const SchedulingModeConfig& schedulingModeConfig)
//{
//  if constexpr (std::is_same_v<FollowMode, FollowRiCqi>)
//  {
//    return new FollowMode(schedulingModeConfig);
//  }
//  else
//  {
//    return nullptr;
//  }
//}

int main()
{
  cout << "TemplateChaining\n" << endl;   // prints TemplateChaining

  std::vector<Cqi> cqiVector{0, 1, 2, 3, 4};

  IFollowXScheduler<FollowRiCqi> followXScheduler{new FollowRiCqi(cqiVector)};

  followXScheduler.update(CsiResultHolder(ResourceIndicator{0}, Cqi{0}, Ri{0}));

  //  FollowRiCqi followRiCqi(cqiTable);
  //
  //  followRiCqi.update(CsiResultHolder(ResourceIndicator{0}, Cqi{0}, Ri{0}));
  //
  //  AdaRiCqi adaRiCqi(ResourceIndicator{-1}, Cqi{-1}, Ri{-1});
  //
  followXScheduler.adaptSchedParams();
  //
  //  std::cout << adaRiCqi.toString();

  return 0;
}
