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

  std::unique_ptr<Duck> simpleDuck(new Duck(new SimpleFly(), new SimpleDisplay()));

  std::cout << "Duck tester\n";

  simpleDuck->fly();
  simpleDuck->display();
}
