#include <iostream>

using namespace std;


class A
{
public:
    typedef bool type;
};

void print(long l)
{
    cout << "l: " << l << endl;
}

template<class T> void print(T t)
{
    cout << "T: " << t << endl;
}

template<class T> void print(T* t)
{
    cout << "T*: " << *t << endl;
}

//Substitution in den Parametern - kein Problem
template<class T> void print(typename T::type t)
{
    cout << boolalpha;
    cout << "T::type: " << t << endl;
}

//Substitution beim Rückgabetyp - kein Problem
template<class T> typename T::type print(T t)
{
    cout << "T=>: " << t << endl;
}

//Substitution bei der Implementierung - Problem
/*template<class T> void print(T t)
{
   typename T::type x;             // <= kein SFINAE => Compiler-Fehler
   cout << "T: " << t << endl;
}*/

int main()
{
    int n = 42;
    print(43L);
    print(n);
    print(&n);
    print<A>(true);
}
