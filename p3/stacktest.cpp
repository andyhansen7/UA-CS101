#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
  Stack<int> s;

  s.push(1);
  s.push(2);
  s.push(3);

  cout << s.peek() << endl;

  s.display(cout);

  cout << s.pop() << endl;
  cout << s.pop() << endl;
  cout << s.pop() << endl;

  try
  {
    cout << s.peek() << endl;
  }
  catch(InvalidOperationException &e)
  {
    cout << e.getMessage() << endl;
  }
  

  s.display(cout);

  return 0;
}
