/*
 * IFollowXScheduler.h
 *
 *  Created on: May 24, 2021
 *      Author: yadhu
 */

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "TemplateChainTypes.h"

/**
 * @class FollowXScheduler
 * @brief
 *
 * @tparam FollowMode
 * @tparam SchedulingModeConfig
 */
template <typename FollowMode>
class IFollowXScheduler
{
public:
  IFollowXScheduler(FollowMode* followMode)
      : followMode{followMode}
  {}

  void update(const CsiResultHolder& csiReportHolder)
  {
    std::cout << "updating: " << __func__ << std::endl;
    followMode->update(csiReportHolder);
  }

  /**
   * @fn AdaRiCqi adaptSchedParams()
   * @brief
   *
   * @pre
   * @post
   * @return
   */
  AdaRiCqi adaptSchedParams(/*AssignmentItem here*/)
  {
    AdaRiCqi adaCqiParams;
    std::cout << "adaptSchedParams: " << __func__ << ", before: " << adaCqiParams.toString() << std::endl;

    followMode->adaptSchedParams(adaCqiParams);

    std::cout << "adaptSchedParams: " << __func__ << ", after: " << adaCqiParams.toString() << std::endl;
    return adaCqiParams;
  }

  /**
   * @fn SchedulingMode getSchedulingMode()
   * @brief
   *
   * @pre
   * @post
   * @return
   */
  constexpr SchedulingMode getSchedulingMode()
  {
    if constexpr (std::is_same_v<FollowMode, FollowRiCqi>)
    {
      return SchedulingMode::followRiCqi;
    }
    else
    {
      return SchedulingMode::fixedMode;
    }
  }

private:
  std::unique_ptr<FollowMode> followMode;
};
