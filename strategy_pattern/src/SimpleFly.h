/*
 * SimpleFly.h
 *
 *  Created on: 15-Feb-2019
 *      Author: yadhu
 */

#pragma once

#include <iostream>
#include "IFlyBehaviour.h"

class SimpleFly : public IFlyBehaviour {
 public:
  SimpleFly();
  virtual ~SimpleFly();

  virtual void fly() const override final;
};
