#ifndef PROJ_MEALBASKET_H
#define PROJ_MEALBASKET_H

#include <iostream>

class MealBasket {
private:
    static unsigned int counter;                        //Used to assign different invoice numbers
    unsigned int packageNumber;                         //Number of packages
    unsigned int invoiceNumber;                         //Unique invoice number
    std::string clientName;                             //Client Name
    std::pair<long double, long double> destAddress;    //Destination address in x and y coordinates
public:
    MealBasket();
    MealBasket(unsigned int packageNumber, std::string clientName, std::pair<long double, long double> address);
    void setPackageNumber(unsigned int packageNumber);
    void setClientName(std::string clientName);
    void setAddress(std::pair<long double, long double> address);
    unsigned int getPackageNumber() const;
    unsigned int getInvoiceNumber() const;
    std::string getClientName() const;
    std::pair<long double, long double> getAddress() const;

    bool operator<(const MealBasket &rhs) const;

    bool operator>(const MealBasket &rhs) const;

    bool operator<=(const MealBasket &rhs) const;

    bool operator>=(const MealBasket &rhs) const;
};


#endif //PROJ_MEALBASKET_H
