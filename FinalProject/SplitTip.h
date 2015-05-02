#ifndef SPLITTIP_H
#define SPLITTIP_H
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cstring>

class SplitTip
{
    struct foodItem
    {
        std::string name;
        std::string restaurant;
        float price = 0.0;
        foodItem* next;

    };
    struct cardInfo
    {
        std::string holderName;
        std::string company;
        int cardNumber;
        float percentToPay;
    };
    public:
        float totalCost = 0;
        void printHelpMessage();
        void displayRestaurants();
        void displayMenus(int selection);
        void addItemToCart(std::string restaurant, std::string name, float price);
        void printCart();
        void removeItemFromCart(std::string name);
        void emptyCart();
        void checkOut();
        void addCards(int);
        bool isCartEmpty();
        void displayCards();
        void evenCheckout(float);
        void unevenCheckout();
        std::vector <cardInfo*> cards;
        SplitTip();
        virtual ~SplitTip();
    protected:
    private:
        foodItem* root = NULL;
};

#endif // SPLITTIP_H
