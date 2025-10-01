#include "bank_customer.h"
#include <iostream>
#include <vector>

class Bank{
private:
    string name;
    vector<BankCustomer> Accounts{};
    int customerCount;

public:
    Bank(const string& name){
        this->name = name;
        this->customerCount = 0;
    }

    void addAccount(const BankCustomer& customer) {
        Accounts.push_back(customer);
        customerCount++;
    }

    BankCustomer* getAccountById(int id) {
        for (auto& acc : Accounts) {
            if (acc.getId() == id) return &acc;
        }
        return nullptr;
    }

    void printAllAccounts() const {
        std::cout << "Bank: " << name << std::endl;
        for (const auto& acc : Accounts) {
            acc.printInfo();
        }
    }
};
