//
// Created by andre on 3/20/2021.
//

#ifndef PROJ_MEALBASKET_H
#define PROJ_MEALBASKET_H

#include <iostream>


//TODO probs vai ter de ser um classe msm
typedef std::string Address;

class MealBasket {
private:
    unsigned int packageNumber;
    unsigned int invoiceNumber;
    std::string clientName;
    Address destAddress;
public:
    MealBasket(unsigned int packageNumber, unsigned int invoiceNumber, std::string clientName, Address address);
    void setPackageNumber(unsigned int packageNumber);
    void setInvoiceNumber(unsigned int invoiceNumber);
    void setClientName(std::string clientName);
    void setAddress(Address address);
    unsigned int getPackageNumber() const;
    unsigned int getInvoiceNumber() const;
    std::string getClientName() const;
    Address getAddress() const;
    bool operator<(const MealBasket &rhs) const;
};


#endif //PROJ_MEALBASKET_H
