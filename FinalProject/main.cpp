#include <iostream>
#include "SplitTip.h"

using namespace std;

/*
Function prototype:
void printMainMenu()

Function description:
This is a very straight forward method that prints the initial menu for the program.

Precondition: The only precondition that is required is that this method cant be called withing another menu option screen.
Post condition: Prints menu options to the screen.
*/
void printMainMenu()
{
    cout<<"======Main Menu======"<<endl;
    cout<<"Please Select an Option:"<<endl;
    cout<<"1. Browse Restaurants"<<endl;
    cout<<"2. Show Cart"<<endl;
    cout<<"3. Remove an Item From the Cart"<<endl;
    cout<<"4. Empty Cart"<<endl;
    cout<<"5. Check Out"<<endl;
    cout<<"6. Help"<<endl;
    cout<<"7. Exit"<<endl;
}

int main()
{
    cout<<"******** Welcome to SplitTip ********"<<endl;
    cout<<endl;
    printMainMenu();
    SplitTip split; // initializes the class SplitTip
    bool isquit = false;
    while(isquit == false){ //While the program is not quit
        int userOption;
        string foodItem;
        cin>>userOption;
        cin.clear();
        cin.ignore(10000, '\n');//these two lines simply clear the cin so getline() will work correctly
        switch (userOption){//switch is an easy way of navigating a menu for the user using typed commands
        case 1://if the user enters a 1
            split.displayRestaurants();
            printMainMenu();
            break;
        case 2://if the user enters a 2
            split.printCart();
            printMainMenu();
            break;
        case 3://so on an so forth
            cout<<"What Food Item Would You Like to Delete?"<<endl;
            getline(cin, foodItem);
            split.removeItemFromCart(foodItem);
            printMainMenu();
            break;
        case 4:
            split.emptyCart();
            printMainMenu();
            break;
        case 5:
            split.checkOut();//checks out and also quits program
            cout<<"Goodbye!"<<endl;
            isquit = true;
            break;
        case 6:
            split.printHelpMessage();
            printMainMenu();
            break;
        case 7:
            cout<<"Goodbye!"<<endl;
            isquit = true;
            break;
        default:
            cout<<"Please select a valid option."<<endl;//user entered an invalid command
            break;
        }
    }
    return 0;
}
