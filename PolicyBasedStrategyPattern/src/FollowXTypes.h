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
  FollowXIF() = default;

  template <typename inputArgs>
  FollowXIF(inputArgs&)
  {}

  void update(const CsiResultHolder&) {}

  void adaptSchedParams(AdaRiCqi& adaRiCqi) {}
};

template <typename Base>
struct FollowRsrcInd
{
  template <typename inputArgs>
  FollowRsrcInd(const inputArgs& inInputArgs)
      : Base(inInputArgs)
      , resourceIndicator{}
  {}

  void update(const CsiResultHolder& csiResultHolder)
  {
    std::cout << "FollowRi update\n";
    if (csiResultHolder.resourceIndicator.isValid())
    {
      resourceIndicator = csiResultHolder.resourceIndicator;
    }
    Base::update(csiResultHolder);
  }

  void adaptSchedParams(AdaRiCqi& adaRiCqi)
  {
    std::cout << "FollowRi adaptSchedParams\n";
    adaRiCqi.resourceIndicator = resourceIndicator;
    Base::update(adaRiCqi);
  }

  ResourceIndicator resourceIndicator;
};

template <typename Base>
struct FollowRi : public Base
{
  template <typename inputArgs>
  FollowRi(inputArgs& inInputArgs)
      : Base(inInputArgs)
      , rankIndicator{}
  {}

  void update(const CsiResultHolder& csiResultHolder)
  {
    if (csiResultHolder.ri.isValid())
    {
      rankIndicator = csiResultHolder.ri;
    }
    std::cout << "FollowRi update\n";
    Base::update(csiResultHolder);
  }

  void adaptSchedParams(AdaRiCqi& adaRiCqi)
  {
    std::cout << "FollowRi adaptSchedParams\n";
    adaRiCqi.ri = rankIndicator;
    Base::adaptSchedParams(adaRiCqi);
  }

  Ri rankIndicator;
};

template <typename Base>
struct FollowCqi : public Base
{
  FollowCqi(std::vector<Cqi> inCqiTable)
      : Base()
      , channelQualityIndicator{0}
      , cqiTable{inCqiTable}
  {}

  void update(const CsiResultHolder& csiResultHolder)
  {
    channelQualityIndicator = csiResultHolder.cqi;
    std::cout << "FollowCqi update\n";
    Base::update(csiResultHolder);
  }

  void adaptSchedParams(AdaRiCqi& adaRiCqi)
  {
    std::cout << "FollowCqi adaptSchedParams\n";
    adaRiCqi.cqi = channelQualityIndicator;
    Base::adaptSchedParams(adaRiCqi);
  }

  Cqi                    channelQualityIndicator;
  const std::vector<Cqi> cqiTable;
};

/**
 * @struct FollowFixed default mode is followFixed, It is dummy.
 * @brief
 *
 */
struct FollowFixed
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
struct FollowBo
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

/**
 * Now create followModes in all the permutation and combinations as necessary.
 */
using FollowRiCqi_AdaptRankMcs         = FollowRi<FollowCqi<FollowXIF>>;
using FollowRi_AdaptRank               = FollowRi<FollowXIF>;
using FollowBeam_AdaptBeam             = FollowRsrcInd<FollowXIF>;
using FollowBeamRiCqi_AdaptBeamRankMcs = FollowRsrcInd<FollowRi<FollowCqi<FollowXIF>>>;
using FollowBeamCqi_AdaptBeamMcs       = FollowRsrcInd<FollowCqi<FollowXIF>>;
