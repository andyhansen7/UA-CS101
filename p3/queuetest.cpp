#include "queue.h"
#include <iostream>

using namespace std;

int main()
{
  Queue<int> q;

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  q.display(cout);

  cout << q.dequeue() << endl;
  cout << q.dequeue() << endl;
  cout << q.dequeue() << endl;
  q.display(cout);
  cout << q << endl;
  cout << q.size() << q.empty() << endl;

  try
  {
      q.dequeue();
  }
  catch(InvalidOperationException &e)
  {
      cout << e.getMessage() << endl;
  }
  

  return 0;
}
