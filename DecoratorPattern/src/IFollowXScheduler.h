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
 * @class IFollowXScheduler
 * @brief IF Class for all the FollowXSchedulers.
 *
 */
class IFollowXScheduler
{
public:
  virtual AdaRiCqi adaptSchedParams()             = 0;
  virtual void     update(const CsiResultHolder&) = 0;

  virtual SchedulingMode getSchedulingMode() = 0;

  virtual ~IFollowXScheduler() = default;
};

/**
 * @class FollowXScheduler
 * @brief
 *
 * @tparam FollowMode
 * @tparam SchedulingModeConfig
 */
template <typename FollowX>
class TFollowXScheduler : public IFollowXScheduler
{
public:
  TFollowXScheduler(FollowX followMode, SchedulingMode mode)
      : followMode{followMode}
      , schedulingMode{mode}
  {}

  void update(const CsiResultHolder& csiReportHolder) override final
  {
    std::cout << "updating: " << __func__ << std::endl;
    followMode.update(csiReportHolder);
  }

  /**
   * @fn AdaRiCqi adaptSchedParams()
   * @brief
   *
   * @pre
   * @post
   * @return
   */
  AdaRiCqi adaptSchedParams(/*AssignmentItem here*/) override final
  {
    AdaRiCqi adaCqiParams;
    std::cout << "adaptSchedParams: " << __func__ << ", before: " << adaCqiParams.toString() << std::endl;

    followMode.adaptSchedParams(adaCqiParams);

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
  FollowX        followMode;
  SchedulingMode schedulingMode;
};
