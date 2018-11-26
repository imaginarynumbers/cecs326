//  CECS 326 - Fork Project
//  Operating Systems - CECS 326
//  Professor Ratana Ngo

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

//Prototypes
int searchForText(ifstream& file,string search);
int replaceText(string oldText, string newText);
string getWord();
string getReplace();
void dotGen();

int main(int argc, const char * argv[])
{
  string input;
  string newWord;
  // opens alice in wonderland text file
  // for project use only, no copyright infringement intended
  ifstream file;
  file.open("alice.txt");
  if(!file) // checks if text file was opened
  {
    cout << "Unable to open file" << endl;
    exit(1);
  }
  cout << getpid() <<"Parent: Process" << endl;
  while( (input = getWord()) != "wq" && (newWord = getReplace()) != "wq")
  {
    int childPID = fork();
    if(childPID > 0)
    {
      cout << "Parent: " << getpid() << ", ppid " << getppid() << ", child " << childPID << endl;
      wait(0);
    }
    else if (childPID == 0)
    {
      int checker = 0;
      while(checker == 0)
      {
        checker = searchForText(file, input);
        if(checker == 0) cout << ".";
      }
      //found a word to replace
      int replaceCounter;
      replaceCounter = replaceText(input, newWord);
      cout << "Replaced: " << replaceCounter << " words" << endl;
      exit(0);
    }
//    if(childPID < 0)
//    {
//      cout << "Search failed." << endl;
//      break;
//    }
    else
    {
      wait(0);
      dotGen();  //print 1000 periods to signify waiting
      cout << "\nError." << endl;
    }
    //cout << "Found: " << checker << " '" << input << "'" << endl;
//    if(checker > 1)
//    {
//      //found a word to replace
//      string newWord = "";
//
//      int replaceCounter;
//      //childPID = fork(); // create new child process
//      cout << "Child process: pid " << getpid() << ", ppid " << getppid() << ", child " << childPID << endl;
//      cout << "Enter the replacement word" << endl;
//      cin >> newWord;
//      replaceCounter = replaceText(input, newWord);
//      cout << "Replaced: " << replaceCounter << " words" << endl;
//    }
//    checker = 1;
  }
  file.close();
  exit(0);
} // end of main()
//-----------------------------------------------------------
string getWord()
{
  string word;
  cout << "Enter a word to search for." << endl;
  cin >> word;
  return word;
}
//-----------------------------------------------------------
string getReplace()
{
  string word;
  cout << "Enter a word to replace." << endl;
  cin >> word;
  return word;
}
//-----------------------------------------------------------
int searchForText(ifstream& file,string searchFor)
{
  string line; // string line object
  int counter = 0; // keep track of how many droids we find
  size_t pos; // position object
  //cout << "searching..." << endl;
  while(!file.eof()) // goes to the end of the file
  {
    getline(file,line); // get line from file
    pos=line.find(searchFor); // search
    if(pos!=string::npos) // string::npos is returned if string is not found
    {
      counter++; // increment counter
    }
  }
  return counter;
} // end of searchForText()
//-----------------------------------------------------------
int replaceText(string oldText, string newText)
{
  //replace text here
  ifstream original; //  original text file object
  int subLength; // holds length of a sub string
  int replaceCounter = 0;
  original.open("alice.txt"); // opens original text file
  ofstream newFile; // edited text file object
  newFile.open("replace.txt"); // opens text file for edited text
  if(!newFile) // make sure the file was opened correctly
  {
    cout << "Output file error." << endl;
  }
  string tempString; // holds a temporary string object
  while(!original.eof()) // goes till the end of the original text file
  {
    string stringHolder; // holds line string from text file
    getline(original, stringHolder); // gets line from text file
    istringstream iss(stringHolder); // takes line and converts to single substring
    string sub; // holder for sub string
    iss >> sub; // place sub string into string object
    stringHolder = sub; // replace string with sub string
    //begin of removing punctuation
    subLength = stringHolder.size();
    for (int i = 0; i < subLength; i++)
    {
      if (ispunct(stringHolder[i]))
      {
        //transform(stringHolder.begin(), stringHolder.end(), stringHolder.begin(), ::tolower); // converts to lowercase, not working
        stringHolder.erase(i--, 1);
        subLength = stringHolder.size();
      }
    }
    //cout << "SH:" << stringHolder << endl; // debugging purposes
    if(stringHolder.compare(oldText) == 0)
    {
      // found the droids we are looking for
      tempString = newText; // change the old text with user input
      newFile << tempString << " ";
      replaceCounter++;
    }
    else newFile << stringHolder << " "; // not the droids we are looking for
  }
  cout << "completed replacing: " << oldText << " with " << newText << endl;
  original.close(); // close file object
  newFile.close(); // close file object
  return replaceCounter;
} // end of replaceText()
//-----------------------------------------------------------
void dotGen()
{
    //prints 1000 periods when waiting
    for(int i = 0; i < 1000; i++)
    {
        cout << ".";
    }
}
//-----------------------------------------------------------
