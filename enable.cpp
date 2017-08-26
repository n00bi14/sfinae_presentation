#include <iostream>
#include <iomanip>
#include <type_traits>
#include <typeinfo>

using namespace std;

template<class T, class Enable = void>
class A {
public:
  void print(){cout << "primary template" << endl;}
  void print(T t){cout << t << endl;}
}; // primary template

template<class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
public:
  void print(){ cout << "specialization for floating point types" << endl; }
  void print(T t){cout << t << endl;}
  void only_here(){cout << "specialization special" << endl;}
}; // specialization for floating point types

int main()
{
  A<int> a1; // OK, matches the primary template
  A<double> a2; // OK, matches the partial specialization

  a1.print();
  a2.print();

  a1.print(1.2);
  a2.print(2);

  //a1.only_here();
  a2.only_here();


  cout << is_integral<float>::value << endl;
  cout << is_integral<int>::value << endl;

  //Ab C++14
  cout << is_integral<float>() << endl;
  cout << is_integral<int>() << endl;
}
