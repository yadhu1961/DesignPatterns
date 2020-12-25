/*
 * Duck.h
 *
 *  Created on: 14-Feb-2019
 *      Author: yadhu
 */

#include "IDisplayBehaviour.h"
#include "IFlyBehaviour.h"
#include <memory>

#pragma once

class Duck
{
public:
  Duck(IFlyBehaviour *, IDisplayBehaviour *);
  virtual ~Duck();

  void fly() const;

  void display() const;

private:
  std::unique_ptr<IFlyBehaviour>     m_flyBehaviour;
  std::unique_ptr<IDisplayBehaviour> m_displayBehaviour;
};
