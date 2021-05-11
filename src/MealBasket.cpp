//
// Created by andre on 3/20/2021.
//

#include "MealBasket.h"

#include <utility>

using namespace std;

MealBasket::MealBasket(unsigned int packageNumber, unsigned int invoiceNumber, string clientName, Address address)
        : packageNumber(packageNumber), invoiceNumber(invoiceNumber), clientName(std::move(clientName)), destAddress(std::move(address)) {}

void MealBasket::setPackageNumber(unsigned int packageNumber) {
    this->packageNumber = packageNumber;
}

void MealBasket::setInvoiceNumber(unsigned int invoiceNumber) {
    this->invoiceNumber = invoiceNumber;
}

void MealBasket::setClientName(string clientName) {
    this->clientName = clientName;
}

void MealBasket::setAddress(Address address) {
    this->destAddress = address;
}

unsigned int MealBasket::getPackageNumber() const {
    return this->packageNumber;
}

unsigned int MealBasket::getInvoiceNumber() const {
    return this->invoiceNumber;
}

string MealBasket::getClientName() const {
    return this->clientName;
}

Address MealBasket::getAddress() const {
    return this->destAddress;
}

bool MealBasket::operator<(const MealBasket &rhs) const {
    return packageNumber < rhs.packageNumber;
}

bool MealBasket::operator>(const MealBasket &rhs) const {
    return rhs < *this;
}

bool MealBasket::operator<=(const MealBasket &rhs) const {
    return !(rhs < *this);
}

bool MealBasket::operator>=(const MealBasket &rhs) const {
    return !(*this < rhs);
}

