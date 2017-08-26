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

int main()
{
  div<3>();
  div<2>();
}
