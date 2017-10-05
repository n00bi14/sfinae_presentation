#include <iostream>

using namespace std;

// Diese Funktion wird genommen, wenn I gerade ist
template<int I> void div(char(*)[I % 2 == 0] = nullptr)
{
  cout << "I ist gerade: " << I << endl;
}


// Diese Funktion wird genommen, wenn I ungerade ist
template<int I> void div(char(*)[I % 2 == 1] = nullptr)
{
  cout << "I ist ungerade: " << I << endl;
}







void test(...)
{
    std::cout << "Catch-all overload called\n";
}

template<class C, class F>
auto test(C c, F f) -> decltype((void)(c.*f)(), void())
{
    std::cout << "Reference overload called\n";
}

template<class C, class F>
auto test(C c, F f) -> decltype((void)(c->*f)(), void())
{
    std::cout << "Pointer overload called\n";
}

struct X { void f() {} };










int main()
{
  div<3>();
  div<2>();
  //div<3.14>();








  X x;
  test( x, &X::f);
  test(&x, &X::f);
  test(42, 1337);
}
