#include "MealBasket.h"



using namespace std;

unsigned int MealBasket::counter = 1;

MealBasket::MealBasket(): invoiceNumber(counter++) {}

MealBasket::MealBasket(unsigned int packageNumber, string clientName, std::pair<long double, long double> address)
        : packageNumber(packageNumber), invoiceNumber(counter++),  clientName(std::move(clientName)), destAddress(address) {
}

void MealBasket::setPackageNumber(unsigned int packageNumber) {
    this->packageNumber = packageNumber;
}

void MealBasket::setClientName(string clientName) {
    this->clientName = std::move(clientName);
}

void MealBasket::setAddress(std::pair<long double, long double> address) {
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

std::pair<long double, long double> MealBasket::getAddress() const {
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

