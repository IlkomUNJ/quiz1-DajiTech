#pragma once
#include "buyer.h"
#include "item.h"
#include <string>
#include <vector>
#include <iostream>

class seller : public Buyer {

private:
    int sellerId;
    std::string sellerName;
    std::string storeName;
    std::string storeAddress;
    std::string storePhone;
    std::string storeEmail;
    bool upgradedFromBuyer = false; // Track if upgraded from Buyer
    bool idDisplayed(int itemId) const {
        // Example implementation, can be customized
        return itemId > 0; // Assuming valid IDs are positive integers
    }

    vector<Item> items; // Assuming seller has a collection of items


public:
    seller() = default;

    seller(Buyer buyer, int sellerId, const std::string& sellerName)
        : Buyer(buyer.getId(), buyer.getName(), buyer.getAccount()), sellerId(sellerId), sellerName(sellerName) {
            Buyer::setId(buyer.getId());
        }

    virtual ~seller() = default;

    void addNewItem(int newId, const std::string& newName, int newQuantity, double newPrice) {
        Item newItem(newId, newName, newQuantity, newPrice);
        items.push_back(newItem);
    }

    void updateItem(int itemId, const std::string& newName, int newQuantity, double newPrice) {
        for (auto& item : items) {
            if (item.getId() == itemId) {
                item.alterItemById(itemId, newName, newQuantity, newPrice); // Assuming alterItemById is a method
            }
        }
    }

    void makeItemVisibleToCustomer(int itemId) {
        for (auto& item : items) {
            if (item.getId() == itemId) {
                item.setDisplay(true); // Assuming setDisplay is a method in Item class
                break;
            }
        }
    }

    // Add seller-specific members here
    void setStoreDetails(const std::string& name, const std::string& address, const std::string& phone, const std::string& email) {
        storeName = name;
        storeAddress = address;
        storePhone = phone;
        storeEmail = email;
    }

    void setUpgradedFromBuyer(bool upgraded) {
        upgradedFromBuyer = upgraded;
    }

    bool isUpgradedFromBuyer() const {
        return upgradedFromBuyer;
    }

    std::string getStoreName() const { return storeName; }
    std::string getStoreAddress() const { return storeAddress; }
    std::string getStorePhone() const { return storePhone; }
    std::string getStoreEmail() const { return storeEmail; }
    int getSellerId() const { return sellerId; }
    std::string getSellerName() const { return sellerName; }
    void printSellerInfo() const {
        std::cout << "Seller Name: " << sellerName << std::endl;
        std::cout << "Seller ID: " << sellerId << std::endl;
        std::cout << "Store Name: " << storeName << std::endl;
        std::cout << "Store Address: " << storeAddress << std::endl;
        std::cout << "Store Phone: " << storePhone << std::endl;
        std::cout << "Store Email: " << storeEmail << std::endl;
        std::cout << "Upgraded from Buyer: " << (upgradedFromBuyer ? "Yes" : "No") << std::endl;
    }
};
