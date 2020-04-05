#include "dll.h"
#include <iostream>

using namespace std;

int main()
{
  int arr[] = {1,2,3,4,5};
  int c = 5;

  Dll<int> d(arr, c);
  cout << "List 1 created." << endl;
  /*Dll<int> e;
  cout << "List 2 created." << endl;
  Dll<int> f(d);
  cout << "List 3 created." << endl << endl << endl;
  f.display(cout);

  e.insert(0,1);
  e.display(cout);
  e.remove(0);
  e.display(cout);

  f.insert(2,7);
  f.display(cout);
  f.insert(0,9);
  f.insert(f.size(), 11);
  f.display(cout);

  f.remove(1);
  f.display(cout);

  f.remove(f.size() - 1);
  f.display(cout);

  f.clear();
  f.display(cout);

  Dll<int> g;
  g = d;
  g.display(cout);*/
  d.display(cout);
  d.remove(3);
  d.display(cout);
  d.remove(3);
  d.display(cout);
  d.remove(0);
  d.display(cout);

  d.insert(0, 1);
  d.display(cout);
  d.insert(1, 7);
  d.display(cout);
  d.insert(4, 11);
  d.display(cout);

  cout << d.at(0) << endl << d.at(2) << endl << d.at(4) << endl;

  d.clear();
  d.display(cout);
  d.insert(0, 1);
  d.display(cout);

  Dll<int> f(d);
  f.display(cout);
  cout << "copy const" << endl;

  Dll<int> e;
  e.display(cout);
  e.insert(0,1);
  e.remove(0);
  e.display(cout);



  return 0;
}
