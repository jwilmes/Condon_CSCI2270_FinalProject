#include "SplitTip.h"
#include <iostream>
#include <vector>
#include <math.h>


using namespace std;


SplitTip::SplitTip()
{

}

SplitTip::~SplitTip()
{
    //dtor
}

/*
Function prototype:
void SplitTip::addItemToCart(string, string, float)

Function description:
This method adds a food item (of type struct:fooditem) to a linked list (named the cart) at the end of the list.

Example:
SplitTip st;
st.addItemToCart("Panda Express", "Orange Chicken", 8.99)

Precondition: There is a root pointer that points to the beginning of the linked list. If the root is NULL, the root points
to the newly created food item, otherwise the node will be added to the end of the linked list. This method must only be
accessed in the main menu screen and not on any other menu screen. The string restaurant and name should not be numbers
and float price is a decimal number greater than 0.

Post condition: Depending on the previous state of the linked list, the root pointer is updated or the last element in
the linked list is updated to point to a newly created fooditem with the inputted attributes. The total cost float value
is also incremented by the given price.
*/
void SplitTip::addItemToCart(string restaurant, string name, float price)
{
    foodItem* newFood = new foodItem;//creates new fooditem
    newFood->name = name;
    newFood->restaurant = restaurant;
    newFood->price = price;
    newFood->next = NULL;
    if(root == NULL)//checks to see if the cart is empty
    {
        root = newFood;
    }
    else
    {
        foodItem* temp = root;
        while(temp->next != NULL)//iterates through the cart til the last element
        {
            temp = temp->next;
        }
        temp->next = newFood;//new food is add to the end
    }
    totalCost += price;//total cost is adjusted
    cout<<name<<" from "<<restaurant<<" has been added to the cart."<<endl;
}

/*
Function prototype:
void SplitTip::printCart()

Function description:
This method iterates through the linked list (cart) and prints the restaurant, food name, and price of every element
then prints the total cost of all items.

Example:
SplitTip st;
st.printCart()

Precondition: This method does not really need any preconditions. Can be accessed at any time throughout the program
when needed.

Post condition: If cart is empty, prints "the cart is empty", otherwise prints all elements in the cart.
*/
void SplitTip::printCart()
{
    if (root == NULL)//is the cart empty?
    {
        cout<<"The Cart is Empty"<<endl;
    }
    else
    {
        foodItem* temp = root;
        while(temp != NULL)
        {
            cout<<temp->restaurant<<", "<<temp->name<<": "<<temp->price<<endl;
            temp = temp->next;
        }
        cout<<"Sub-Total: "<<totalCost<<endl;//sub-total because this is the price before taxes
    }
}

/*
Function prototype:
void SplitTip::emptyCart()

Function description:
This method iterates through the linked list (cart) and deletes every element until the cart no longer contains any elements.
It deletes the last element in the cart until the root points to NULL.

Example:
SplitTip st;
st.emptyCart()

Precondition: This method requires that the user is not in the check out menu.

Post condition: The cart no longer contains any elements
*/
void SplitTip::emptyCart()
{
    while(root != NULL)//While the cart still has elements
    {
        foodItem* temp = root;
        while(temp->next != NULL)//Find the last element
        {
            temp = temp->next;
        }
        removeItemFromCart(temp->name);//Delete the last element
    }
    cout<<"The Cart has been Emptied."<<endl;
}
/*
Function prototype:
bool SplitTip::isCartEmpty()

Function description:
This method simply checks if the cart is empty by checking if the root points to anything. If root points to NULL
return true, otherwise return false

Example:
SplitTip st;
st.isCartEmpty()

Precondition: The user is not in the check out menu

Post condition: Returns the current state of the cart
*/
bool SplitTip::isCartEmpty()
{
    if (root == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
Function prototype:
void SplitTip::addCards(int)

Function description:
This method prompts the user a inputted number of times (the number must be between 0 and 6) for the info of credit cards:
Card name, company, and number, the method then stores the info into a vector.

Example:
SplitTip st;
st.addCards(4)

Precondition: The user has finished adding items to the cart, and the cart is not empty. The user has entered an integer
above 0 and below 6, to represent how many people will be splitting the cost of the cart.

Post condition: A new item struct:cardinfo is created a number of times as chosen by the user. Each item is added to a
vector called "cards"
*/

void SplitTip::addCards(int numberOfCards)
{
    for(int i = 0; i < numberOfCards; i++)
    {
        cin.clear();
        cin.ignore(10000, '\n');//cin is cleared for getline() to work correctly
        string name;
        string company;
        string number;
        cout<<"Card Number: "<<i + 1<<endl;
        cout<<"Please Enter the First and Last Name of this Cardholder:"<<endl;
        getline(cin, name);
        cout<<"Please Enter the Name of the Card Company:"<<endl;
        getline(cin, company);
        cout<<"Please Enter the Credit Card Number"<<endl;
        getline(cin, number);
        if (i != numberOfCards - 1)
        {
            cout<<"Press Enter to Continue to the next Card"<<endl;
        }
        cardInfo* newCard = new cardInfo;// a new card is created with the users inputted information
        newCard->holderName = name;
        newCard->company = company;
        newCard->cardNumber = atoi(number.c_str());
        cards.push_back(newCard);// the new card is added to vector
    }
}
/*
Function prototype:
void SplitTip::displayCards()

Function description:
This method iterates through the vector (cards) and prints the cardholder's name, card company, and card number

Example:
SplitTip st;
st.displayCards()

Precondition: The vector (cards) is not empty

Post condition: Contents of vector (cards) are printed to the screen
*/
void SplitTip::displayCards()
{
    cout<<endl;
    cout<<"Card Info: "<<endl;
    for(unsigned int i = 0; i <cards.size(); i++)
    {
        cout<<cards[i]->holderName<<endl;
        cout<<cards[i]->company<<": "<<cards[i]->cardNumber<<endl;
        cout<<endl;
    }
}

/*
Function prototype:
void SplitTip::evenCheckout(float)

Function description:
This method splits the total cost (with taxes) between every card evenly. For example, if the total was $10.00
and there are 2 cards. Every card is charged $5.00

Example:
SplitTip st;
st.evenCheckout(14.98)

Precondition: The cart is not empty, the vector (cards) is not empty, the user has selected to split the cost evenly
within the checkout method, and the float "total" is greater than 0

Post condition: Amount to be charged to each card is printed to the screen with the corresponding card holder names
*/
void SplitTip::evenCheckout(float total)
{
    for (unsigned int i = 0; i < cards.size(); i++)
    {
        cout<<cards[i]->holderName<<" has been charged: $"<<floor((total / cards.size()) * 100.00 + 0.5 ) / 100.00<<endl;
        //the total is divided evenly by the amount of cards in vector cards and the rounded to 2 decimal places
    }
}

/*
Function prototype:
void SplitTip::unevenCheckout()

Function description:
This method is similar to evenCheckout, but it splits the totals by chosen percentages, instead of evenly splitting them.
It works by iterating through the vector, cards, and prompting the user for a percentage for each card that will
represent what portion of the total bill that card will be charged. No one can charge more that 100% and the total
amount of percent cannot surpass 100% either. The last card in the vector is charged 100% - the total percent of all other
cards to ensure the total comes out to exactly 100%.

Example:
SplitTip st;
st.unevenCheckout()

Precondition: The user must have selected to not split the cards evenly in the checkout method, the vector, cards, is
not empty, the linked list, cart, is not empty and the totalCost is > 0

Post condition:Every Cardholder's name is printed on the screen with the price that person will pay.
*/
void SplitTip::unevenCheckout()
{
    string percentString;
    float currentPercentage;
    float percentLeft = 100.0;
    cout<<"Please Enter how Much Each Person Will Pay."<<endl;
    cout<<endl;
    for(unsigned int i = 0; i < cards.size() - 1; i++)// goes through every card in cards except the last one
    {
        currentPercentage = 101.0;
        cin.clear();
        cout<<"What percentage should "<<cards[i]->holderName<<" pay?"<<endl;
        while (currentPercentage <= 0 ||  currentPercentage >= percentLeft)// loop until the user enters a valid percent
        {
            cout<<"Percent left: "<<percentLeft<<"%"<<endl;
            getline(cin, percentString);
            currentPercentage = ::atof(percentString.c_str());//converts user input to float
            if (currentPercentage <= 0 ||  currentPercentage >= percentLeft)
            {
                cout<<currentPercentage<<" is not a valid percentage. The percentage is either below 0 or above the percentage left."<<endl;
            }
        }
        cards[i]->percentToPay = currentPercentage;
        percentLeft = percentLeft - currentPercentage;
    }
    cards[cards.size() - 1]->percentToPay = percentLeft; //assigns the last element in cards with the remaining percentage
    for(unsigned int i = 0; i < cards.size(); i++)
    {
        cout<<cards[i]->holderName<<" has been charged: $"<<floor(((cards[i]->percentToPay / 100) * (totalCost * 1.08)) * 100.00 + 0.5 ) / 100.00<<endl;
    }

}

/*
Function prototype:
void SplitTip::checkOut()

Function description:
This function first checks to make sure that the linked list (cart) is not empty. It then calls printCart() and calculates
the total cost with taxes. From there, it asks the user for the number of cards to split the bill with. It then asks the
user if they would like to split the bill evenly or not evenly. If the user selects evenly then evenCheckout() is called
otherwise unEvenCheckOut() is called

Example:
SplitTip st;
st.checkOut()

Precondition: The user selected checkout and the cart is not empty.

Post condition:Cart is printed, total with tax is calculated, the amount of cards to be split is brought in buy user
and evenCheckout or unevenCheckout is called.
*/
void SplitTip::checkOut()
{
    if (isCartEmpty())
    {
        cout<<"Cannot Check out until the Cart has Items in it"<<endl;
    }
    else
    {
        int numberOfPeople = 0;
        cout<<"Your Cart: "<<endl;
        cout<<endl;
        printCart();
        float totalWithTax = roundf((totalCost * 1.08) * 100) / 100;
        cout<<endl;
        cout<<"Total: "<<totalWithTax<<endl;
        cout<<endl;
        cout<<"How many people are splitting this tab? (Note, the max number of cards is 5)"<<endl;
        while(numberOfPeople <= 0 ||  numberOfPeople > 5)
        {
            cin>>numberOfPeople;
            if (numberOfPeople <= 0 || numberOfPeople > 5)
            {
            cout<<"That is not a valid number of people."<<endl;
            cout<<"Please try again."<<endl;
            }
        }
        addCards(numberOfPeople);
        displayCards();
        cout<<"Press Enter to Continue"<<endl;
        cin.clear();
        cin.ignore(10000, '\n');
        string option;
        cout<<"Would you like to split the check evenly? (Y/N)"<<endl;
        while (option != "Y" || option != "N")
        {
            getline(cin, option);
            if (option == "Y")
            {
                evenCheckout(totalWithTax);
                break;
            }
            else if(option == "N")
            {
                unevenCheckout();
                break;
            }
            else
            {
                cout<<"Not a Valid Response, Try Again"<<endl;
            }
        }
    }
}

/*
Function prototype:
void SplitTip::removeItemFromCart(string)

Function description:
This method takes in the name of a food item, and removes it from the linked list (cart). From there the pointers
in the cart are updated.

Example:
SplitTip st;
st.removeItemFromCart("Orange Chicken")

Precondition: The input should be a string and not a number or the food item will not be found. If the cart is empty
an error message is printed to the screen. This method must be accessed outside of the checkout menu.

Post condition:If the root is the element to be deleted then the root pointer is updated to point to the next element.
Otherwise, the previous element's pointer "next" is updated and the element to be removed is deleted.
*/

void SplitTip::removeItemFromCart(string name)
{
    bool found = false;
    if (root == NULL)//is cart empty?
    {
        cout<<"Sorry, the Cart is Empty"<<endl;
    }
    else
    {
        if (root->name == name)//is the root the element to be deleted
        {
            totalCost = (totalCost - root->price);//total is updated
            if (root->next == NULL)//is the root the only element in the cart?
                    {
                        foodItem* del = root;
                        root = NULL;
                        delete del;
                        cout<<"Deleted"<<endl;
                        found = true;
                    }
            else
            {
                foodItem* del = root;
                root = root->next;
                delete del;
                cout<<"Deleted"<<endl;
                found = true;
            }
        }
        else
        {
            foodItem* temp = root;
            while(temp->next != NULL)//loop through the cart
            {
                if (temp->next->name == name)//found element
                {
                    totalCost = (totalCost - temp->next->price);//total updated
                    if (temp->next->next == NULL)//is this the last element?
                    {
                        foodItem* del = temp->next;
                        temp->next = NULL;
                        delete del;
                        cout<<"Deleted"<<endl;
                        found = true;
                        break;
                    }
                    else
                    {
                        foodItem* del = temp->next;
                        temp->next = temp->next->next;
                        delete del;
                        cout<<"Deleted"<<endl;
                        found = true;
                        break;
                    }
                }
                else
                {
                temp = temp->next;
                }
            }
        }
        if (!found)
        {
            cout<<"Sorry, "<<name<<" was not Found in the Cart."<<endl;//cound not find element
        }
    }
}

/*
Function prototype:
void SplitTip::displayRestaurants()

Function description:
This method displays a menu for the user to navigate their options for restaurants. Depending on what option the user
chooses, a different version of displayMenus is called.

Example:
SplitTip st;
st.displayRestaurants()

Precondition: This method must be called outside the checkout menu.

Post condition:Menu of restaurants is printed and displayMenus is called
*/

void SplitTip::displayRestaurants()
{
    cout<<endl;
    cout<<"Please select a restaurant: "<<endl;
    cout<<"1. Pizza Shack"<<endl;
    cout<<"2. McRonald's"<<endl;
    cout<<"3. Chinese Express"<<endl;
    cout<<"4. Jimmy James"<<endl;
    cout<<"5. Wing City"<<endl;
    bool selectionMade = false;
    while(selectionMade == false){//Loop until user selects a valid option
        int userOption;
        cin>>userOption;
        cin.clear();
        cin.ignore(10000, '\n');//clears cin
        switch (userOption){
        case 1:
            cout<<"Pizza Shack selected"<<endl;
            cout<<endl;
            displayMenus(1);
            selectionMade = true;
            break;
        case 2:
            cout<<"McRonald's selected"<<endl;
            cout<<endl;
            displayMenus(2);
            selectionMade = true;
            break;
        case 3:
            cout<<"Chinese Express selected"<<endl;
            cout<<endl;
            displayMenus(3);
            selectionMade = true;
            break;
        case 4:
            cout<<"Jimmy James selected"<<endl;
            cout<<endl;
            displayMenus(4);
            selectionMade = true;
            break;
        case 5:
            cout<<"Wing City selected"<<endl;
            cout<<endl;
            displayMenus(5);
            selectionMade = true;
            break;
        default:
            cout<<"Please select a valid restaurant."<<endl;
            cout<<endl;
            break;
        }
    }
}

/*
Function prototype:
void SplitTip::displayMenus(int)

Function description:
This method displays food options for the user's chosen restaurant. When the user selects a food item, addItemToCart
is called with that fooditem's information.

Example:
SplitTip st;
st.displayMenus(3)

Precondition: int selection is an integer value above 0 and below 6. Accessed through displayRestaurants.

Post condition:An item of the user's choice is added to linked list (cart);
*/

void SplitTip::displayMenus(int selection)
{
    int foodSelection;
    cout<<"Choose what items you would like to order: "<<endl;
    if (selection == 1)
    {
        cout<<"1. Pepperoni Pizza: $10.99"<<endl;
        cout<<"2. Cheese Pizza: $10.99"<<endl;
        cout<<"3. Bread Sticks: $2.99"<<endl;
        cin>>foodSelection;
        if (foodSelection == 1)
        {
            addItemToCart("Pizza Shack", "Pepperoni Pizza", 10.99);
        }
        else if(foodSelection == 2)
        {
            addItemToCart("Pizza Shack", "Cheese Pizza", 10.99);
        }
        else if (foodSelection == 3)
        {
            addItemToCart("Pizza Shack", "Bread Sticks", 2.99);
        }
        else
        {
            cout<<"Invalid Input"<<endl;
            displayMenus(selection);
        }
    }
    else if (selection == 2)
    {
        cout<<"1. Single Cheeseburger: $.99"<<endl;
        cout<<"2. Double Cheeseburger: $1.99"<<endl;
        cout<<"3. Chicken Nuggets: $1.99"<<endl;
        cin>>foodSelection;
        if (foodSelection == 1)
        {
            addItemToCart("McRonald's", "Single Cheeseburger", .99);
        }
        else if(foodSelection == 2)
        {
            addItemToCart("McRonald's", "Double Cheeseburger", 1.99);
        }
        else if (foodSelection == 3)
        {
            addItemToCart("McRonald's", "Chicken Nuggets", 1.99);
        }
        else
        {
            cout<<"Invalid Input"<<endl;
            displayMenus(selection);
        }
    }
    else if (selection == 3)
    {
        cout<<"1. Orange Chicken: $8.99"<<endl;
        cout<<"2. Low Mein: $3.99"<<endl;
        cout<<"3. Egg Rolls: $2.99"<<endl;
        cin>>foodSelection;
        if (foodSelection == 1)
        {
            addItemToCart("China Express", "Orange Chicken", 8.99);
        }
        else if(foodSelection == 2)
        {
            addItemToCart("China Express", "Low Mein", 3.99);
        }
        else if (foodSelection == 3)
        {
            addItemToCart("China Express", "Egg Rolls", 2.99);
        }
        else
        {
            cout<<"Invalid Input"<<endl;
            displayMenus(selection);
        }
    }
    else if (selection == 4)
    {
        cout<<"1. Spicy Italian 6 inch-Sub: $5.99"<<endl;
        cout<<"2. Tossed Salad: $5.99"<<endl;
        cout<<"3. Creamy Tomato Soup: $1.99"<<endl;
        cin>>foodSelection;
        if (foodSelection == 1)
        {
            addItemToCart("Jimmy James", "Spicy Italian 6 inch-Sub", 5.99);
        }
        else if(foodSelection == 2)
        {
            addItemToCart("Jimmy James", "Tossed Salad", 5.99);
        }
        else if (foodSelection == 3)
        {
            addItemToCart("Jimmy James", "Creamy Tomato Soup", 1.99);
        }
        else
        {
            cout<<"Invalid Input"<<endl;
            displayMenus(selection);
        }
    }
    else
    {
        cout<<"1. 6 Traditional Mild Wings: $5.99"<<endl;
        cout<<"2. 6 Boneless Mild Wings: $6.99"<<endl;
        cout<<"3. Atomic Hell Challenge: $15.99"<<endl;
        cin>>foodSelection;
        if (foodSelection == 1)
        {
            addItemToCart("Wing City", "6 Traditional Mild Wings", 5.99);
        }
        else if(foodSelection == 2)
        {
            addItemToCart("Wing City", "6 Boneless Mild Wings", 6.99);
        }
        else if (foodSelection == 3)
        {
            addItemToCart("Wing City", "Atomic Hell Challenge", 15.99);
        }
        else
        {
            cout<<"Invalid Input"<<endl;
            displayMenus(selection);
        }
    }

}

/*
Function prototype:
void SplitTip::printHelpMessage()

Function description:
This method is very basic and prints a message explaining what the program does and the background of the program.

Example:
SplitTip st;
st.printHelpMessage()

Precondition: This cant be accessed outside the main menu.

Post condition:Message printed to the screen with info surrounding the program.
*/

void SplitTip::printHelpMessage()
{
    cout<<"SplitTip is a food delivery program which has the"<<endl;
    cout<<"ability to split the cost between multiple charge cards."<<endl;
    cout<<"The idea came from the constant problem of my college"<<endl;
    cout<<"friends and I arguing about who would pay the pizza guy."<<endl;
    cout<<"Most college and high school aged kids don't carry"<<endl;
    cout<<"much cash on them so splitting the cost of delivery is"<<endl;
    cout<<"very hard. This is the solution to that problem."<<endl;
    cout<<"To begin using SplitTip, browse the selection"<<endl;
    cout<<"of restaurants and select the one you would like to order"<<endl;
    cout<<"from using the number keys. From there add food items to"<<endl;
    cout<<"to your shopping cart and when you are ready select check out."<<endl;
    cout<<"You may view your shopping cart at any time. When checking out,"<<endl;
    cout<<"Enter the billing information of all the members of your party,"<<endl;
    cout<<"Then select how much each person will pay. Once completed, eat up"<<endl;
    cout<<"and enjoy!"<<endl;
}
