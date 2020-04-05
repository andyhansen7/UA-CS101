#include <iostream>
#include <fstream>
#include <cctype>

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
      // Build word list from file input
      Word words[10000];
      int wordCount = 0, uniqueCount = 0;

      for(unsigned int i = 0; i < fileString.size(); i++)
      {
        if(!isalpha(fileString.at(i))) fileString.at(i) = ' ';
      }

      size_t last = -1;
      size_t sep = fileString.find_first_of(" ");

      //Build word array from text
      while(sep != string::npos)
      {
        string newWord = fileString.substr(last + 1, sep - last - 1);
        newWord = lower(newWord);
        last = sep;
        sep = fileString.find_first_of(" ", sep + 1);

        if(newWord.size() >= 1 && newWord.compare(" ") != 0)
        {
          bool unique = true;

          for(int i = 0; i < wordCount; i++)
          {
            if(newWord.compare(words[i].Get()) == 0)
            {
              words[i].Add();
              unique = false;
            }
          }
          if(unique)
          {
            words[uniqueCount].SetID(newWord);
            uniqueCount++;
            //cout << " Unique: " << newWord << endl;
            unique = false;
          }
          //cout << "Word " << wordCount << ": \'" << newWord << "\'"<< endl;
          wordCount++;
        }
      }

      //for(int i = 0; i < uniqueCount; i++) cout << words[i].Get() << " " << words[i].GetCount() << endl;

      cout << "The number of words found in the file was " << wordCount << endl;
      cout << "The number of distinct words found in the file was " << uniqueCount << endl << endl;

      bool loop = true;

      while(loop)
      {
        string search;

        cout << "Please enter a word: ";
        cin >> search;

        if(feof(stdin)) loop = false;

        else
        {

          for(int i = 0; i < uniqueCount; i++)
          {
            string currWord = words[i].Get();
            string tmpSearch = search;

            bool match = true;
            int qCount = 0;

            //Count question marks in search term
            for(unsigned int j = 0; j < tmpSearch.size();)
            {
              if(tmpSearch.at(j) == '?'){
                qCount++;
                tmpSearch.erase(tmpSearch.begin() + j);
              }
              else j++;
            }

            if(tmpSearch.size() + qCount < currWord.size() || tmpSearch.size() > currWord.size()) match = false;
            if(currWord.at(0) != tmpSearch.at(0) && tmpSearch.at(0) != '?') match = false;
            //cout << search << " " << qCount << endl;
            while(true)
            {
              if(tmpSearch.size() < 1 || currWord.size() < 1) break;

              size_t pos = currWord.find_first_of(tmpSearch.at(0));
              //cout << pos << endl;
              if(pos != string::npos)
              {
                qCount -= pos;
                currWord = currWord.substr(pos + 1, currWord.size() - pos - 1);
                tmpSearch = tmpSearch.substr(1, tmpSearch.size() - 1);
                //cout << currWord << " : " << search << endl;
              }
              else
              {
                match = false;
                break;
              }
            }
            //Add matches to vector
            if(match == true && qCount >= 0) {
              //cout << curr << endl;
              words[i].SetMatch();
            }
          }

          // Display matches and frequency
          for(int i = 0; i < wordCount; i++)
          {
            if(words[i].IsMatch())
            {
              cout << "The word " << words[i].Get() << " appears " << words[i].GetCount() << " times in the document" << endl;
              words[i].ClearMatch();
            }
          }
          cout << endl;
      }
    }
  }
}
return 0;
}
