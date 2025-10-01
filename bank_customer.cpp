#include "bank_customer.h"
#include <iostream>


string BankCustomer::getName() const {
    return this->name;
}

int BankCustomer::getId() const {
    return this->id ;
}

double BankCustomer::getBalance() const {
    return this->balance;
}

void BankCustomer::setBalance(double amount) {
    this->balance = amount;
    addTransaction("Set balance to $" + std::to_string(amount));
}

void BankCustomer::addBalance(double amount) {
    this->balance += amount;
    addTransaction("Deposited $" + std::to_string(amount));
}

bool BankCustomer::withdrawBalance(double amount){
    if (amount > this->balance) {
        std::cout << "Rejected: Insufficient funds!" << std::endl;
        addTransaction("Failed withdrawal of $" + std::to_string(amount) + " (Insufficient funds)");
        return false;
    }
    this->balance -= amount;
    addTransaction("Withdrew $" + std::to_string(amount));
    return true;
}

void BankCustomer::addTransaction(const std::string& desc) {
    transactionHistory.push_back(desc);
}

void BankCustomer::printTransactionHistory() const {
    std::cout << "Transaction History for " << name << ":" << std::endl;
    if (transactionHistory.empty()) {
        std::cout << "No transactions yet." << std::endl;
    } else {
        for (const auto& t : transactionHistory) {
            std::cout << "- " << t << std::endl;
        }
    }
}

void BankCustomer::printInfo() const {
    std::cout << "Customer Name: " << this->name << std::endl;
    std::cout << "Customer ID: " << this->id << std::endl;
    std::cout << "Balance: $" << this->balance << std::endl;
}
