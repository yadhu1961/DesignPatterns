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

  std::cout << "Duck tester\n";

=======
  std::unique_ptr<Duck> simpleDuck(new Duck(new SimpleFly(), new SimpleDisplay()));
>>>>>>> a753112 (Updated .gitignore)
  simpleDuck->fly();
  simpleDuck->display();
}
