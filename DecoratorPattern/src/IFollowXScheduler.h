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
#include <type_traits>
#include <memory>

#include "FollowXTypes.h"

/**
 * @class FollowXScheduler
 * @brief
 *
 * @tparam FollowMode
 * @tparam SchedulingModeConfig
 */
class TFollowXScheduler
{
public:
  TFollowXScheduler(FollowXIF* followMode, SchedulingMode mode)
      : followMode{followMode}
      , schedulingMode{mode}
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
   * @post   TODO extend for new followModes
   * @return
   */
  constexpr SchedulingMode getSchedulingMode() { return schedulingMode; }

private:
  std::unique_ptr<FollowXIF> followMode;
  SchedulingMode             schedulingMode;
};
