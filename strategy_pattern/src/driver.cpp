//============================================================================
// Name        : strategy_pattern.cpp
// Author      : Yadu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Duck.h"
#include "SimpleDisplay.h"
#include "SimpleFly.h"

using namespace std;

int main() {
  cout << "!!!Hello World!!!" << endl;  // prints !!!Hello World!!!

  auto simpleDuck = new Duck(new SimpleFly(), new SimpleDisplay());

  simpleDuck->fly();

  return 0;
}
