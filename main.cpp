//Kacy Rowe
//Project One - Memory leak

#include <iostream>

using namespace std;

//Prototypes
void buildArrays(struct mainArrays& array);
void mainMenu();
void subMenu();
void deallocateArray(struct mainArrays& array);
void deleteCharacter(struct mainArrays& array);
void printArrays(struct mainArrays& array);

struct mainArrays {
    char * pointerArray[20];
    int intArray[20];
    int pointerArraySize;
    int intArraySize;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int choiceForMainMenu = 0;
    int choice2 = 0;
    struct mainArrays array;  //declare mainArrays object
    buildArrays(array);       //build arrays needed
    mainMenu();           //prompt user for input
    cin >> choiceForMainMenu; //get user input for menu
    switch(choiceForMainMenu)
    {
        case 1:
            while(true)
            {
                cout << "\nWhich location of the array would you like to access?" << endl << "Please choose between 0 and 19." << endl;
                cin >> choice2;
                if(choice2 < 0 || choice2 > 19)
                    cout << "Invalid selection, please try again.";
            }
            break;
        case 2:
            cout << "Listing the deallocated memory index(s)";
            //call deallocated list
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
    return 0;
}

//Main menu
void mainMenu()
{
  cout << "Main menu. Please make a selection."   << endl
       << "1. Access a pointer."                  << endl
       << "2. List deallocated memory (index)."   << endl
       << "3. Deallocate all memory."             << endl
       << "4. Exit program and deallocate all memory.";
}
void subMenu()
{
  cout << "Sub menu. Please make a selection."                     << endl
       << "1. Print the first 10 char's in the chosen array."      << endl
       << "2. Delete all the char's associated with this pointer." << endl
       << "3. Return to the main menu";
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
    //srand(static_cast<unsigned int>(time(NULL)));  //built in random function
    srand((time(NULL)));
    for(int i = 1; i < 20; i++)
    {
      //random chars inserted
        for(int j = 0; j < 20; j++)
        {
            array.pointerArray[i] = new char[array.intArray[i]];
            number = rand() % 26; //generate random number
            //cout << "number = " << number << endl;
            character = 'a' + number; //converr to character
            //cout << "character = " << character << endl;
            array.pointerArray[i][j] = character; //insert random character into array
        }
    }
}
void deleteCharacter(struct mainArrays& array, int location)
{
    //delete a specific character at a given pointer location
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
void printArrays(struct mainArrays& array)
{
    //print all values of array
    for(int i = 0; i < 20; i++)
    {
        //cout << a[i];
    }
}
