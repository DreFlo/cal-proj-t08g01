//
// Created by andre on 3/20/2021.
//

#include "MealBasket.h"

#include <utility>

MealBasket::MealBasket(unsigned int packageNumber, unsigned int invoiceNumber, string clientName, Address address)
        : packageNumber(packageNumber), invoiceNumber(invoiceNumber), clientName(std::move(clientName)), address(std::move(address)) {}

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
    this->address = address;
}

unsigned int MealBasket::getPackageNumber() const {
    return packageNumber;
}

unsigned int MealBasket::getInvoiceNumber() const {
    return invoiceNumber;
}

string MealBasket::getClientName() const {
    return clientName;
}

Address MealBasket::getAddress() const {
    return address;
}
