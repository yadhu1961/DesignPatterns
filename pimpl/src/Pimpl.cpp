#include "Pimpl.h"

class PimplImpl
{
public:
  void display() { std::cout << "Display from PimplImpl\n"; }
};

Pimpl::Pimpl()
    : m_pimplImpl{std::make_unique<PimplImpl>()}
{}

Pimpl::~Pimpl() = default;

void Pimpl::display() { m_pimplImpl->display(); }
