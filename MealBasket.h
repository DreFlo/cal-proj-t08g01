//
// Created by andre on 3/20/2021.
//

#ifndef PROJ_MEALBASKET_H
#define PROJ_MEALBASKET_H

#include <iostream>

using namespace std;

//TODO probs vai ter de ser um classe msm
typedef string Address;

class MealBasket {
private:
    unsigned int packageNumber;
    unsigned int invoiceNumber;
    string clientName;
    Address address;
public:
    MealBasket(unsigned int packageNumber, unsigned int invoiceNumber, string clientName, Address address);
    void setPackageNumber(unsigned int packageNumber);
    void setInvoiceNumber(unsigned int invoiceNumber);
    void setClientName(string clientName);
    void setAddress(Address address);
    unsigned int getPackageNumber() const;
    unsigned int getInvoiceNumber() const;
    string getClientName() const;
    Address getAddress() const;
};


#endif //PROJ_MEALBASKET_H
