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
<<<<<<< HEAD
  std::unique_ptr<Duck> simpleDuck(new Duck(new SimpleFly(), new SimpleDisplay()));
=======
  std::cout << "Duck tester\n";
  auto simpleDuck = new Duck(new SimpleFly(), new SimpleDisplay());
>>>>>>> 0a6b05e7e89297bd4c15a9af2193c5431f4bd1ba
  simpleDuck->fly();
  simpleDuck->display();
}
