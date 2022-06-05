/*
 * IFlyBehaviour.h
 *
 *  Created on: 14-Feb-2019
 *      Author: yadhu
 */

#pragma once

class IFlyBehaviour {
 public:
  IFlyBehaviour();
  virtual ~IFlyBehaviour();

  virtual void fly() const = 0;
};
