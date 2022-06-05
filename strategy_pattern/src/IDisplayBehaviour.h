/*
 * IDisplayBehaviour.h
 *
 *  Created on: 14-Feb-2019
 *      Author: yadhu
 */

#pragma once

class IDisplayBehaviour {
 public:
  IDisplayBehaviour();
  virtual ~IDisplayBehaviour();

  virtual void display() const = 0;
};
