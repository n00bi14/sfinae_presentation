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




template<typename T> class hasToString
{
    typedef char one;
    typedef long two;

    template<typename C> static one test(decltype(&C::toString));
    template<typename C> static two test(...);

  public:
    enum
    {
      value = sizeof(test<T>(0) == sizeof(char))
    };
};




template<class T, class Enable = void> std::string ToString(...)
{
  return "Ellipsis...";
}

template<class T, typename std::enable_if<hasToString<T>::value>::type = 0> std::string ToString(T& t)
{
  return "Aus der Methode (enable_if): " + t.toString();
}

//template<class T, char (*)[sizeof(&T::toString) > 0] = nullptr> std::string ToString(T& t)
//{
//  return "Aus der Methode (Array): " + t.toString();
//}




int main()
{
  if(hasToString<A>::value)
  {
    A a;
    cout << "Aus dem if: " << a.toString() << endl;
  }

  A a;
  cout << ToString<A>(a) << endl;

  B b;
  cout << ToString<B>(b) << endl;

  return 0;
}
