#include <iostream>
#include <fstream>
#include <cctype>
//include <cstring>

using namespace std;

class Word
{
  public:
    void SetID(string word) { id = word; }
    string Get() { return id; }
    void Add() { count++; }
    void SetMatch() { match = true; }
    void ClearMatch() { match = false; }
    bool IsMatch() { return match; }
    int GetCount() { return count; }
  private:
    int count = 1;
    string id = "";
    bool match = false;
};


string readFile(string fileName)
{
  ifstream file;
  string filetext = "",
    line;

  file.open(fileName);

  if(file.is_open())
  {
    while(getline(file, line))
    {
      filetext.append(line);
      filetext.append(" ");
    }
    file.close();
  }
  return filetext;
}

string lower(string s)
{
  string l = s;

  for(unsigned int i = 0; i < l.size(); i++)
  {
    if(l[i] >= 'A' && s[i] <= 'Z') l[i] += 32;
  }
  return l;
}

Word breakText(const string filetext)
{
  //Filter non-alphabetic characters from file text
  string filtered = filetext;

  for(unsigned int i = 0; i < filtered.size(); i++)
  {
    if(!isalpha(filtered.at(i))) filtered.at(i) = ' ';
  }

  Word words[10000];
  size_t last = -1;
  size_t sep = filtered.find_first_of(" ");

  //Build word array from text
  while(sep != string::npos)
  {
    string newWord = filtered.substr(last + 1, sep - last - 1);
    last = sep;
    sep = filtered.find_first_of(" ", sep + 1);
    if(newWord != "")
    {
      bool unique = true;
      for(unsigned int i = 0; i < words.size(); i++)
      {
        if(newWord.compare(words[i].Get()) == 0)
        {
          words[i].Add();
          unique = false;
        }
      }
      if(unique)
      {
        words[words.size()] = new Word();
        words[words.size()].SetID(newWord);
      }
    }
  }
  return words;
}

bool promptSearch(Word words[])
{
  string search;

  cout << "Please enter a word: ";
  cin >> search;

  if(feof(stdin)) return false;

  else {

    for(unsigned int i = 0; i < words.size(); i++)
    {
      string curr = words[i].Get();
      bool match = true;
      unsigned int j;

      //Match search with words
      if(curr.size() < search.size())
      {
        for(j = 0; j < curr.size(); j++)
        {
          if(curr.at(j) != search.at(j) && search.at(j) != '?') match = false;
        }

        for(;j < search.size(); j++)
        {
          if(search.at(j) != '?') match = false;
        }
      }
      else if(curr.size() == search.size())
      {
        for(j = 0; j < search.size(); j++)
        {
          if(curr.at(j) != search.at(j) && search.at(j) != '?') match = false;
        }
      }
      else match = false;

      //Add matches to vector
      if(match == true) {
        cout << curr << endl;
        words[i].SetMatch();
      }
    }

    // Display matches and frequency
    for(unsigned int i = 0; i < words.size(); i++)
    {
      if(words[i].IsMatch())
      {
        cout << "The word " << words[i].Get() << " appears " << words[i].GetCount() << " times in the document" << endl;
        words[i].ClearMatch();
      }
    }
    return true;
  }
}

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    cout << "[ERROR]: Incorrect command line arguments. Correct usage of this program is " << argv[0] << " [FILE]." << endl;
    return 0;
  }
  else
  {
    string fileString = readFile(argv[1]);

    if(fileString == "")
    {
      cout << "[ERROR]: The specified file could not be opened for reading." << endl;
      return 0;
    }
    else
    {
      Word words[10000] = breakText(fileString);
      cout << "The number of words found in the file was " << words.size() << endl;
      cout << "The number of unique words found in the file was " << words.size() << endl << endl;

      bool loop = true;

      while(loop) loop = promptSearch(words);
    }
    return 0;
  }
  return 0;
}
