#include <iostream>
#include "bank_customer.h"
#include "bank_customer.cpp"
#include "buyer.h"

enum PrimaryPrompt{LOGIN, REGISTER, EXIT};
enum RegisterPrompt{CREATE_BUYER, CREATE_SELLER, BACK};
using namespace std;

int main() {
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    bool loggedIn = false;
    bool isBuyer = false;
    bool isSeller = false;
    BankCustomer customer1(1, "Alice", 1000.0); // Example user
    Buyer buyer1(1, customer1.getName(), customer1);
    // Loop for main prompt
    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN:
                cout << "Login selected." << endl;
                // For now, assume user is logged in as Buyer
                loggedIn = true;
                isBuyer = true;
                while (loggedIn && isBuyer) {
                    cout << "\nBuyer Menu:" << endl;
                    cout << "1. Check Account Status" << endl;
                    cout << "2. Upgrade Account to Seller" << endl;
                    cout << "3. Create Banking Account" << endl;
                    cout << "4. Browse Store" << endl;
                    cout << "5. Order Functionality" << endl;
                    cout << "6. Payment Functionality" << endl;
                    cout << "7. Logout" << endl;
                    cout << "8. Delete Account" << endl;
                    int buyerChoice;
                    cin >> buyerChoice;
                    switch (buyerChoice) {
                        case 1:
                            cout << "\nAccount Status:" << endl;
                            buyer1.getAccount().printInfo();
                            cout << "Buyer Name: " << buyer1.getName() << endl;
                            // If Seller, display seller info here
                            break;
                        case 2:
                            cout << "Upgrade Account to Seller selected." << endl;
                            // Prompt for seller details, link to buyer
                            // Reject if no banking account
                            break;
                        case 3:
                            cout << "Create Banking Account selected." << endl;
                            // Prompt for initial deposit, address, phone, email
                            // Provide banking functions: Balance, History, Deposit, Withdraw
                            break;
                        case 4:
                            cout << "Browse Store selected." << endl;
                            // Display stores, select store, show inventory, add to cart
                            break;
                        case 5:
                            cout << "Order Functionality selected." << endl;
                            // Show cart, remove item, checkout, generate invoice
                            break;
                        case 6:
                            cout << "Payment Functionality selected." << endl;
                            // List invoices, pick invoice, show details, pay
                            break;
                        case 7:
                            cout << "Logout selected. Confirm? (y/n): ";
                            char confirmLogout;
                            cin >> confirmLogout;
                            if (confirmLogout == 'y' || confirmLogout == 'Y') {
                                loggedIn = false;
                                isBuyer = false;
                                cout << "Logged out. Returning to main menu." << endl;
                            } else {
                                cout << "Logout cancelled." << endl;
                            }
                            break;
                        case 8:
                            cout << "Delete Account selected. Confirm? (y/n): ";
                            char confirmDelete;
                            cin >> confirmDelete;
                            if (confirmDelete == 'y' || confirmDelete == 'Y') {
                                // Delete buyer, seller, bank account
                                loggedIn = false;
                                isBuyer = false;
                                cout << "Account deleted. Returning to main menu." << endl;
                            } else {
                                cout << "Delete cancelled." << endl;
                            }
                            break;
                        default:
                            cout << "Invalid option." << endl;
                            break;
                    }
                }
                // If Seller, add seller menu here
                break;
            case REGISTER:
                regPrompt = CREATE_BUYER; // reset regPrompt to CREATE_BUYER when entering register menu
                while (regPrompt != BACK){
                    cout << "Register selected. " << endl;
                    cout << "Select an option: " << endl;
                    cout << "1. Create Buyer Account" << endl;
                    cout << "2. Create Seller Account" << endl;
                    cout << "3. Back" << endl;
                    int regChoice;
                    cin >> regChoice;
                    regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                    switch (regPrompt) {
                        case CREATE_BUYER:
                            cout << "Create Buyer Account selected." << endl;
                            // Prompt for Name, Home Address, Phone, Email
                            break;
                        case CREATE_SELLER:
                            cout << "Create Seller Account selected." << endl;
                            // Prompt for Home Address, Phone, Email, Store Name, Store Address, Store Phone, Store Email, initial deposit
                            break;
                        case BACK:
                            cout << "Back selected." << endl;
                            break;
                        default:
                            cout << "Invalid option." << endl;
                            break;
                    }
                }
                break;
            case EXIT:
                cout << "Exiting." << endl;
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
        cout << endl;
    }
    return 0;
}
