/*
 * SimpleDisplay.h
 *
 *  Created on: 15-Feb-2019
 *      Author: yadhu
 */

#pragma once

#include <iostream>
#include "IDisplayBehaviour.h"

class SimpleDisplay : public IDisplayBehaviour {
 public:
  SimpleDisplay();
  virtual ~SimpleDisplay();

  virtual void display() const override final;
};
