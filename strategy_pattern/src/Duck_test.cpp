/*
 * Duck_test.cpp
 *
 *  Created on: 14-Feb-2019
 *      Author: yadhu
 */

#include "Duck.h"
#include <iostream>
#include "SimpleDisplay.h"
#include "SimpleFly.h"

int main()
{
  std::cout << "Duck tester\n";
  auto simpleDuck = new Duck(new SimpleFly(), new SimpleDisplay());
  simpleDuck->fly();
}
