/*
 * TemplateChainTypes.h
 *
 *  Created on: May 21, 2021
 *      Author: yadhu
 */

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>

struct ResourceIndicator
{
  std::int32_t resourceIndicator{-1};
  bool         isValid() const { return resourceIndicator != -1; }

  std::string toString() const { return std::string("ResourceIndicator: ").append(std::to_string(resourceIndicator)); }
};

struct Ri
{
  std::int32_t ri{-1};
  bool         isValid() const { return ri != -1; }

  std::string toString() const { return std::string("Ri: ").append(std::to_string(ri)); }
};

struct Cqi
{
  std::int32_t cqi{-1};
  Cqi(std::int32_t inCqi)
      : cqi{inCqi}
  {}

  bool isValid() const { return cqi != -1; }

  std::string toString() const { return std::string("Cqi: ").append(std::to_string(cqi)); }
};

struct CsiResultHolder
{
  CsiResultHolder() = default;

  CsiResultHolder(ResourceIndicator inResourceIndicator, Cqi inCqi, Ri inRi)
      : resourceIndicator{inResourceIndicator}
      , ri{inRi}
      , cqi{inCqi}
  {}

  ResourceIndicator resourceIndicator;
  Ri                ri;
  Cqi               cqi;
};

struct AdaRiCqi
{
  AdaRiCqi() = default;

  AdaRiCqi(ResourceIndicator inResourceIndicator, Cqi inCqi, Ri inRi)
      : resourceIndicator{inResourceIndicator}
      , ri{inRi}
      , cqi{inCqi}
  {}

  std::string toString() { return resourceIndicator.toString() + "," + ri.toString() + ", " + cqi.toString(); }

  ResourceIndicator resourceIndicator{-1};
  Ri                ri{-1};
  Cqi               cqi{-1};
};

struct FollowXIF
{
  virtual ~FollowXIF(){};

  void virtual update(const CsiResultHolder&) = 0;

  void virtual adaptSchedParams(AdaRiCqi& adaRiCqi) = 0;
};

struct FollowXDummy : public FollowXIF
{
  void virtual update(const CsiResultHolder&) override final{};

  void virtual adaptSchedParams(AdaRiCqi&) override final{};
};

struct FollowRsrcInd : public FollowXIF
{
  FollowRsrcInd(FollowXIF* inFollowX)
      : resourceIndicator{}
      , followXIf(inFollowX)
  {}

  void update(const CsiResultHolder& csiResultHolder)
  {
    std::cout << "FollowRi update\n";
    if (csiResultHolder.resourceIndicator.isValid())
    {
      resourceIndicator = csiResultHolder.resourceIndicator;
    }
    followXIf->update(csiResultHolder);
  }

  void adaptSchedParams(AdaRiCqi& adaRiCqi)
  {
    std::cout << "FollowRi adaptSchedParams\n";
    adaRiCqi.resourceIndicator = resourceIndicator;
    followXIf->adaptSchedParams(adaRiCqi);
  }

  ResourceIndicator          resourceIndicator;
  std::unique_ptr<FollowXIF> followXIf;
};

struct FollowRi : public FollowXIF
{
  FollowRi(FollowXIF* inFollowX)
      : rankIndicator{}
      , followXIf(inFollowX)
  {}

  void update(const CsiResultHolder& csiResultHolder)
  {
    if (csiResultHolder.ri.isValid())
    {
      rankIndicator = csiResultHolder.ri;
    }
    std::cout << "FollowRi update\n";
    followXIf->update(csiResultHolder);
  }

  void adaptSchedParams(AdaRiCqi& adaRiCqi)
  {
    std::cout << "FollowRi adaptSchedParams\n";
    adaRiCqi.ri = rankIndicator;
    followXIf->adaptSchedParams(adaRiCqi);
  }

  Ri                         rankIndicator;
  std::unique_ptr<FollowXIF> followXIf;
};

struct FollowCqi : public FollowXIF
{
  FollowCqi(FollowXIF* inFollowXIf, std::vector<Cqi> inCqiTable)
      : channelQualityIndicator{0}
      , cqiTable{inCqiTable}
      , followXIf{inFollowXIf}
  {}

  void update(const CsiResultHolder& csiResultHolder)
  {
    channelQualityIndicator = csiResultHolder.cqi;
    std::cout << "FollowCqi update\n";
    followXIf->update(csiResultHolder);
  }

  void adaptSchedParams(AdaRiCqi& adaRiCqi)
  {
    std::cout << "FollowCqi adaptSchedParams\n";
    adaRiCqi.cqi = channelQualityIndicator;
    followXIf->adaptSchedParams(adaRiCqi);
  }

  Cqi                        channelQualityIndicator;
  const std::vector<Cqi>     cqiTable;
  std::unique_ptr<FollowXIF> followXIf;
};

/**
 * @struct FollowFixed default mode is followFixed, It is dummy.
 * @brief
 *
 */
struct FollowFixed : public FollowXIF
{
  void update(const CsiResultHolder& csiResultHolder) { std::cout << "FollowFixed update\n"; }

  void adaptSchedParams(AdaRiCqi& adaRiCqi)
  {
    std::cout << "FollowFixed adaptSchedParams\n";
    /**
     * Just return the user configured scheduling params
     */
  }
};

/**
 * @struct FollowBo is orthogonal to other follow modes
 * @brief
 *
 */
struct FollowBo : public FollowXIF
{
  void update(const CsiResultHolder& csiResultHolder)
  {
    // Store the BO value here.
    std::cout << "FollowBo update\n";
  }

  void adaptSchedParams(AdaRiCqi& adaRiCqi)
  {
    std::cout << "FollowBo adaptSchedParams\n";
    /**
     * Impl logic to select MCS and RIV based on the BO value.
     */
  }
};

/**
 * @enum SchedulingMode
 * @brief
 *
 */
enum class SchedulingMode
{
  followFixed, /**< followFixed */
  followBo,    /**< followBo */
  followCqi,   /**< followCqi */
  followRi,    /**< followRi */
  followBeam,  /**< followBeam */
  followRiCqi  /**< followRiCqi */
};
using CqiTable = std::vector<Cqi>;
