# Condon_CSCI2270_FinalProject

Project summary:
  This is a proof of concept application called SplitTip that I would actually like to make in the future, but for 
  this final project the application will be strictly for presenting the idea of the app. It is a food ordering app
  that has the ability to split the total cost between multiple debit or credit cards. The program will present a  menu
  of different restaurants to order from. The user will be prompted to select a restaurant and then a menu for that
  restuarant will be presented. The user will add whatever food items they wish to order. Then when finished the user
  will be prompted for the number of people who will be splitting the bill. Once finished entering the delivery info, the user will add a credit card number or
  multiple credit card numbers and the total cost will be split evenly or non evenly which will be up to the user.
  The food items are stored within a linked list of structs and the credit card info will be stored in a vector of 
  structs.
  
How to run:
  1. Open the terminal in linux
  2. If you have not done so already install g++ by using the following command: sudo apt-get install g++
  3. Now download "FinalProject.cpp", "SplitTip.cpp", and "SplitTip.h" from the get hub repository by:
      entering the command git clone https://github.com/SuperialCondon/Condon_CSCI2270_FinalProject.git
  4. Now navigate to the folder you cloned that to.
  5. Open the FinalProject.cpp file in Code Blocks
  
Dependencies: This program has all third-party libraries included in the code itself and nothing should need to be installed for the code to run. These libraries were included:#include <string> #include <vector> #include <iostream>
#include <math.h> 

System Requirements:
  This program is designed to run on CodeBlocks on Linux.

Group Members:
  Michael Condon
  
Contributors:
  None so far.
  
Known Bugs/Issues:
  When the user is entering the credit card info for each person the user is prompted for a credit card number
  then the user has to press enter twice instead of once. I have hidden this bug by implementing a print statement 
  that says "Press Enter to Continue..." But I would like the user to only have to press enter once.
  
  The program cannot tell if the user has given meaningful information when they are entering the card info.
  For example, 
        Out: "Please Enter Your Credit Card Number:"
        In: "William Shatner"
        The program continues.
  
  This point is not an issue, but one suggestion for improvement would be to allow the user to edit payment info     for each person after it has been entered.
