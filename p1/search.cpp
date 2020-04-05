#include <iostream>

using namespace std;

int main() {
  string currWord = "and";
  string search = "a??";
  bool match = true;
  int qCount = 0;

  for(unsigned int i = 0; i < search.size();)
  {
    if(search.at(i) == '?'){
      qCount++;
      search.erase(search.begin() + i);
    }
    else i++;
  }
  cout << search << " " << qCount << endl;

  while(true)
  {
    if(search.size() < 1 || currWord.size() < 1) break;

    size_t pos = currWord.find_first_of(search.at(0));
    cout << pos << endl;
    if(pos != string::npos)
    {
      qCount -= pos;
      currWord = currWord.substr(pos + 1, currWord.size() - pos - 1);
      search = search.substr(1, search.size() - 1);
      cout << currWord << " : " << search << endl;
    }
    else
    {
      match = false;
      break;
    }
  }
  //Add matches to vector
  if(match == true && qCount >= 0) {
    cout << "MATCH" << endl;
  }
  cout << qCount << endl;
  return 0;
}
