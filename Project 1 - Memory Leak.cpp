//Kacy Rowe
//Project One - Memory leak

#include <iostream>

using namespace std;

//Prototypes
void buildArrays(struct mainArrays& array);
void mainMenu();
void subMenu();
void deallocateArray(struct mainArrays& array);
void deleteArray(struct mainArrays& array, int index);
void printArrays(struct mainArrays& array, int index);
void printDeallocatedArrays(struct mainArrays& array);

struct mainArrays {
    char * pointerArray[20];
    int intArray[20];
    int pointerArraySize;
    int intArraySize;
};

int main(int argc, const char * argv[]) {
    int choiceForMainMenu, choice2, indexChoice = 0;
    struct mainArrays array;  //declare mainArrays object
    buildArrays(array);       //build arrays needed
    while(true)
    {
        mainMenu();           //prompt user for input
        cin >> choiceForMainMenu; //get user input for menu
        switch(choiceForMainMenu)
        {
            case 1:
                cout << "Which index would you like to manipulate?" << endl;
                cin >> indexChoice;
                subMenu(); //access the submenu
                cin >> choice2; //get submenu choice from user
                switch(choice2)
                {
                case 1:
                    //Print first 10 chars in the chosen array
                    cout << "\nChecking if pointer array was deleted...";
                    if(array.pointerArray[indexChoice] == NULL)
                    {
                      cout << "\nArray was deleted, reinitializing now." << endl;
                      buildArrays(array);
                      printArrays(array, indexChoice);
                    }
                    else
                    {
                      cout << "\nArray was not deleted, printing now." << endl;
                      printArrays(array, indexChoice);
                    }
                    break;
                case 2:
                    //delete all the chars associated in the chosen array
                    deleteArray(array, indexChoice);
                    break;
                case 3:
                    //Return to main menu
                    break;
                default:
                    cout << "\nInvalid choice, please try again.";
                    break;
                }
                break;
            case 2:
                cout << "Listing the deallocated memory index(s)";
                //call deallocated list
                printDeallocatedArrays(array);
                break;
            case 3:
                cout << "Deallocating all memory now.";
                //calls deallocate memory function
                deallocateArray(array);
                break;
            case 4:
                cout << "Quitting program now.";
                //calls deallocate function before quitting
                deallocateArray(array);
                return 0;
            default:
                cout << "Invalid choice, please try again.";
                break;
        }
    }
    return 0;
}
void mainMenu()
{
  //Main menu prompt to user
  cout << "\nMain menu. Please make a selection."      << endl
       << "1. Access a pointer."                       << endl
       << "2. List deallocated memory (index)."        << endl
       << "3. Deallocate all memory."                  << endl
       << "4. Exit program and deallocate all memory." << endl;
}
void subMenu()
{
  //Sub menu prompt to user
  cout << "\nSub menu. Please make a selection."                     << endl
       << "1. Print the first 10 char's in the chosen array."        << endl
       << "2. Delete all the char's associated with this pointer."   << endl
       << "3. Return to the main menu"                               << endl;
}
void buildArrays(struct mainArrays& array)
{
  //Here is where the arrays get built with the random characters and ints
  array.intArray[0] = 2700; //default case
  char character; //character variable holder
  int number; //random number variable holder
  
  //build the int array (doubles each iteration)
  for(int i = 1; i < 20; i++)
  {
    array.intArray[i] = array.intArray[i - 1] * 2;
  }
  
  //build the char array
  srand(static_cast<unsigned int>(time(NULL)));  //built in random function
  //srand((time(NULL)));
  for(int i = 0; i < 20; i++)
  {
    //instantiate new character arrays for pointers
    array.pointerArray[i] = new char[array.intArray[i]];
    //random chars inserted
    for(int j = 0; j < 20; j++)
    {
      number = rand() % 26; //generate random number
      character = 'a' + number; //converr to character
      array.pointerArray[i][j] = character; //insert random character into array
    }
  }
}
void deleteArray(struct mainArrays& array, int location)
{
  //delete a specific character at a given pointer location
  cout << "Deleting pointers in array: " << location;
  delete[] array.pointerArray[location];
  array.pointerArray[location] = NULL;
}
void deallocateArray(struct mainArrays& array)
{
  //deletes all pointers and deallocates memory
  for(int i = 0; i < 20; i++)
  {
    delete[] array.pointerArray[i];
    array.pointerArray[i] = NULL;
  }
}
void printArrays(struct mainArrays& array, int index)
{
  //print the first 10 values of array
  cout << "The first 10 chars in array " << index << " are: " << endl;
  for(int i = 0; i < 10; i++)
  {
    cout << array.pointerArray[index][i] << " ";
  }
  cout << endl;
}
void printDeallocatedArrays(struct mainArrays& array)
{
    //print the indices of the deleted values of array
    cout << "\nThe deallocated values: " << endl;
    for(int i = 0; i < 20; i++)
    {
        if(array.pointerArray[i] == NULL)
        {
            cout << i << " ";
        }
    }
    cout << endl;
}
