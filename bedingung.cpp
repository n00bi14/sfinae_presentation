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

/*
The syntax char(*)[C] means:
Pointer to an array with element type char and size C.
If C is false (0 here), then we get the invalid type char(*)[0], pointer to a zero sized array:
SFINAE makes it so that the template will be ignored then.
*/






// this overload is always in the set of overloads
// ellipsis parameter has the lowest ranking for overload resolution
void test(...)
{
    std::cout << "Catch-all overload called\n";
}

// this overload is added to the set of overloads if
// C is a reference-to-class type and F is a member function pointer
template<class C, class F>
auto test(C c, F f) -> decltype((void)(c.*f)(), void())
{
    std::cout << "Reference overload called\n";
}

// this overload is added to the set of overloads if
// C is a pointer-to-class type and F is a member function pointer
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
