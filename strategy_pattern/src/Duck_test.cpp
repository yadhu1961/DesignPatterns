/*
 * Duck_test.cpp
 *
 *  Created on: 14-Feb-2019
 *      Author: yadhu
 */

#include <iostream>
#include "Duck.h"
#include "SimpleDisplay.h"
#include "SimpleFly.h"

int main() {
  auto simpleDuck = new Duck(new SimpleFly(), new SimpleDisplay());
  simpleDuck->fly();
}
