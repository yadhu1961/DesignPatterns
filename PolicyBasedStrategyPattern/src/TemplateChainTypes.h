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
#include <type_traits>
#include <initializer_list>

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

  void update(const CsiResultHolder&) {}

  void adaptSchedParams(AdaRiCqi& adaRiCqi) {}
};

template <typename Base>
struct FollowRsrcInd
{
  FollowRsrcInd()
      : Base()
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

template <typename Base, typename inputArgs>
struct FollowRi : public Base
{
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
 * @enum SchedulingMode
 * @brief
 *
 */
enum class SchedulingMode
{
  fixedMode,  /**< fixedMode */
  followBo,   /**< followBo */
  followCqi,  /**< followCqi */
  followRiCqi /**< followRiCqi */
};

using FollowRiCqi     = FollowRi<FollowCqi<FollowXIF>, std::vector<Cqi>>;
using FollowBeamRiCqi = FollowRsrcInd<FollowRi<FollowCqi<FollowXIF>, std::vector<Cqi>>>;
