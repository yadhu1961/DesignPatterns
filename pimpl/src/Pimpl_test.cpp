#include "Pimpl.h"
#include <iostream>

int main()
{
  std::cout << "Pimpl driver\n";
  std::unique_ptr<Pimpl> pimpl{std::make_unique<Pimpl>()};

  pimpl->display();
}
