//============================================================================
// Name        : Crtp.cpp
// Author      : Yadu
// Copyright   : Your copyright notice
// Description : Example of Curiously Recurring Template Pattern
// Base class is templated with derived class type.
// mainly used to avoid virtual tables hence dynamic polymorphism and run time overhead
//============================================================================

#include <iostream>

using namespace std;

template <typename T>
class Base
{
public:
  void DerivedFunc() { std::cout << "Base\n"; }

  void interface()
  {
    std::cout << "base class interface\n";
    static_cast<T*>(this)->food();
  }
};

class DerivedA : public Base<DerivedA>
{
public:
  void DerivedFunc() { std::cout << "DerivedA\n"; }

  void food() { std::cout << "food from A\n"; }
};

class DerivedB : public Base<DerivedB>
{
public:
  void DerivedFunc() { std::cout << "DerivedB\n"; }

  void food() { std::cout << "food from B\n"; }
};

int main()
{
  cout << "!!!Hello World!!!" << endl;

  DerivedA a;
  DerivedB b;

  a.interface();
  b.interface();

  return 0;
}
