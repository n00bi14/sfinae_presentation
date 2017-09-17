#include <iostream>
#include <sstream>
#include <type_traits>

using namespace std;

class A
{
public:
  std::string toString()
  {
    std::stringstream s;
    s << 4;
    return s.str();
  }
};

class B
{
};


template<class T, char (*)[sizeof(&T::toString) > 0] = nullptr> std::string ToString(T& t)
{
  return "Aus der Methode: " + t.toString();
}



int main()
{

  A a;
  cout << ToString<A>(a) << endl;

  B b;
  cout << ToString<B>(b) << endl;

  return 0;
}
