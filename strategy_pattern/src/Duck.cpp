/*
 * Duck.cpp
 *
 *  Created on: 14-Feb-2019
 *      Author: yadhu
 */

#include "Duck.h"

Duck::Duck(IFlyBehaviour *flyBehaviour, IDisplayBehaviour *displayBehaviour)
    : m_flyBehaviour(flyBehaviour), m_displayBehaviour(displayBehaviour) {}

void Duck::fly() const { m_flyBehaviour->fly(); }

void Duck::display() const { m_displayBehaviour->display(); }

Duck::~Duck() {
  // TODO Auto-generated destructor stub
}
