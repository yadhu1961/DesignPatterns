#include <iostream>
#include <memory>

class PimplImpl;

class Pimpl
{
public:
  Pimpl();
  ~Pimpl();

  void display();

private:
  std::unique_ptr<PimplImpl> m_pimplImpl;
};