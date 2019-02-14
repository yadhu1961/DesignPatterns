/*
 * Duck.h
 *
 *  Created on: 14-Feb-2019
 *      Author: yadhu
 */

#include "IDisplayBehaviour.h"
#include "IFlyBehaviour.h"

#pragma once

class Duck {
 public:
  Duck(IFlyBehaviour *, IDisplayBehaviour *);
  virtual ~Duck();

  void fly() const;

  void display() const;

 private:
  IFlyBehaviour *m_flyBehaviour;
  IDisplayBehaviour *m_displayBehaviour;
};
