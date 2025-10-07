#include <iostream>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"
#include <vector>
#include <algorithm>

// Simple in-memory stores for this prototype (store pointers because Buyer holds a reference)
static std::vector<BankCustomer*> bankCustomers;
static std::vector<Buyer*> buyers;
static std::vector<seller*> sellers;

enum PrimaryPrompt{LOGIN, REGISTER, EXIT, ADMIN_LOGIN};
enum RegisterPrompt{CREATE_BUYER, CREATE_SELLER, BACK};
using namespace std;

int main() {
    //create a loop prompt 
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    string username, password;

    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN:
                cout << "Login selected." << endl;
                // Very small demo: ask for buyer id and log them in if found
                cout << "Enter buyer id to login: ";
                {
                    int bid; cin >> bid;
                    bool found = false;
                    for (auto *b : buyers) {
                        if (b->getId() == bid) {
                            cout << "Logged in as buyer: " << b->getName() << "\n";
                            // Show minimal buyer menu
                            cout << "Buyer menu: 1) Check Balance 2) Logout\n";
                            int bm; cin >> bm;
                            if (bm == 1) {
                                cout << "Balance: " << b->getAccount().getBalance() << "\n";
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found) cout << "Buyer not found.\n";
                }
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
                            {
                                int newId = (int)bankCustomers.size() + 1;
                                string name;
                                double deposit;
                                cout << "Enter buyer name: ";
                                cin >> ws;
                                getline(cin, name);
                                cout << "Enter initial deposit amount: ";
                                cin >> deposit;
                                bankCustomers.push_back(new BankCustomer(newId, name, deposit));
                                // BankCustomer stored by pointer; Buyer stores a reference so reference must bind to the object pointed to by the pointer.
                                BankCustomer &acct = *bankCustomers.back();
                                buyers.push_back(new Buyer(newId, name, acct));
                                cout << "Buyer created with id " << newId << "\n";
                            }
                            break;
                        case CREATE_SELLER:
                            cout << "Create Seller Account selected." << endl;
                            {
                                if (buyers.empty()) {
                                    cout << "No buyers exist. Please create a buyer first.\n";
                                } else {
                                    cout << "Enter buyer id to upgrade to seller: ";
                                    int bid; cin >> bid;
                                    Buyer *foundBuyer = nullptr;
                                    for (auto *b : buyers) if (b->getId() == bid) { foundBuyer = b; break; }
                                    if (!foundBuyer) { cout << "Buyer not found.\n"; }
                                    else {
                                        int sid = (int)sellers.size() + 1;
                                        string sname;
                                        cout << "Enter store name: ";
                                        cin >> ws;
                                        getline(cin, sname);
                                        seller *s = new seller(*foundBuyer, sid, sname);
                                        sellers.push_back(s);
                                        cout << "Seller created with id " << sid << " linked to buyer " << foundBuyer->getName() << "\n";
                                    }
                                }
                            }
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
            case ADMIN_LOGIN:
                // Prompt for username & password then check the entries with our hard coded features
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                    cout << "Admin login successful.\n";
                    bool adminExit = false;
                    while (!adminExit) {
                        cout << "Admin menu:\n";
                        cout << "1) View all Buyers\n";
                        cout << "2) View all Sellers\n";
                        cout << "3) Search Buyer/Seller\n";
                        cout << "4) Create Buyer\n";
                        cout << "5) Create Seller (link to existing Buyer)\n";
                        cout << "6) Remove Buyer or Seller by ID\n";
                        cout << "7) System report\n";
                        cout << "8) Logout\n";
                        int achoice; cin >> achoice;
                        switch (achoice) {
                            case 1: {
                                cout << "--- Buyers (count=" << buyers.size() << ") ---\n";
                                for (auto *b : buyers) {
                                    cout << "ID=" << b->getId() << " Name='" << b->getName() << "' Balance=" << b->getAccount().getBalance() << "\n";
                                }
                                break;
                            }
                            case 2: {
                                cout << "--- Sellers (count=" << sellers.size() << ") ---\n";
                                for (auto *s : sellers) {
                                    cout << "ID=" << s->getId() << " Name='" << s->getName() << "' Balance=" << s->getAccount().getBalance() << "\n";
                                }
                                break;
                            }
                            case 3: {
                                cout << "Search (1=by id, 2=by name): "; int sm; cin >> sm;
                                if (sm == 1) {
                                    cout << "Enter id: "; int sid; cin >> sid;
                                    bool found = false;
                                    for (auto *b : buyers) if (b->getId() == sid) { cout << "Buyer: ID="<<b->getId()<<" Name="<<b->getName()<<" Balance="<<b->getAccount().getBalance()<<"\n"; found=true; }
                                    for (auto *s : sellers) if (s->getId() == sid) { cout << "Seller: ID="<<s->getId()<<" Name="<<s->getName()<<" Balance="<<s->getAccount().getBalance()<<"\n"; found=true; }
                                    if (!found) cout << "No buyer/seller found with id "<<sid<<"\n";
                                } else if (sm == 2) {
                                    cout << "Enter name (exact match): "; string nm; cin >> ws; getline(cin, nm);
                                    bool found = false;
                                    for (auto *b : buyers) if (b->getName() == nm) { cout << "Buyer: ID="<<b->getId()<<" Name="<<b->getName()<<" Balance="<<b->getAccount().getBalance()<<"\n"; found=true; }
                                    for (auto *s : sellers) if (s->getName() == nm) { cout << "Seller: ID="<<s->getId()<<" Name="<<s->getName()<<" Balance="<<s->getAccount().getBalance()<<"\n"; found=true; }
                                    if (!found) cout << "No buyer/seller found with name '"<<nm<<"'\n";
                                } else {
                                    cout << "Invalid search option.\n";
                                }
                                break;
                            }
                            case 4: {
                                // create buyer
                                int newId = (int)bankCustomers.size() + 1;
                                string name; double deposit;
                                cout << "Enter buyer name: "; cin >> ws; getline(cin, name);
                                cout << "Enter initial deposit: "; cin >> deposit;
                                bankCustomers.push_back(new BankCustomer(newId, name, deposit));
                                BankCustomer &acct = *bankCustomers.back();
                                buyers.push_back(new Buyer(newId, name, acct));
                                cout << "Created buyer ID="<<newId<<" Name='"<<name<<"'\n";
                                break;
                            }
                            case 5: {
                                if (buyers.empty()) { cout << "No buyers to link. Create a buyer first.\n"; break; }
                                cout << "Enter buyer id to link as seller: "; int bid; cin >> bid;
                                Buyer *foundBuyer = nullptr;
                            for (auto *b : buyers) if (b->getId() == bid) { foundBuyer = b; break; }
                                if (!foundBuyer) { cout << "Buyer not found.\n"; break; }
                                int sid = (int)sellers.size() + 1; string sname;
                                cout << "Enter store name: "; cin >> ws; getline(cin, sname);
                            seller *s = new seller(*foundBuyer, sid, sname);
                            sellers.push_back(s);
                                cout << "Created seller ID="<<sid<<" linked to buyer '"<<foundBuyer->getName()<<"'\n";
                                break;
                            }
                            case 6: {
                                cout << "Remove (1=buyer,2=seller): "; int rm; cin >> rm;
                                if (rm == 1) {
                                    cout << "Enter buyer id to remove: "; int bid; cin >> bid;
                                    bool removed = false;
                                    for (auto it = buyers.begin(); it != buyers.end(); ++it) {
                                        if ((*it)->getId() == bid) { delete *it; buyers.erase(it); removed = true; break; }
                                    }
                                    if (removed) cout << "Buyer removed.\n"; else cout << "Buyer id not found.\n";
                                    // Remove bank customer with same id if exists
                                    for (auto it = bankCustomers.begin(); it != bankCustomers.end(); ++it) {
                                        if ((*it)->getId() == bid) { delete *it; bankCustomers.erase(it); break; }
                                    }
                                } else if (rm == 2) {
                                    cout << "Enter seller id to remove: "; int sid; cin >> sid;
                                    bool removed = false;
                                    for (auto it = sellers.begin(); it != sellers.end(); ++it) {
                                        if ((*it)->getId() == sid) { delete *it; sellers.erase(it); removed = true; break; }
                                    }
                                    if (removed) cout << "Seller removed.\n"; else cout << "Seller id not found.\n";
                                } else cout << "Invalid option.\n";
                                break;
                            }
                            case 7: {
                                cout << "System report:\n";
                                cout << "Total Buyers: " << buyers.size() << "\n";
                                cout << "Total Sellers: " << sellers.size() << "\n";
                                cout << "Total Bank Accounts: " << bankCustomers.size() << "\n";
                                break;
                            }
                            case 8: {
                                adminExit = true; cout << "Admin logged out.\n"; break;
                            }
                            default: cout << "Invalid admin option.\n"; break;
                        }
                    }
                } else {
                    cout << "Invalid admin credentials.\n";
                }
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
        cout << endl;
    }

    //BankCustomer customer1(1, "Alice", 1000.0);
    //Buyer buyer1(1, customer1.getName(), customer1);
    // cleanup allocated objects
    for (auto *b : buyers) delete b;
    buyers.clear();
    for (auto *s : sellers) delete s;
    sellers.clear();
    for (auto *bc : bankCustomers) delete bc;
    bankCustomers.clear();

    return 1;
}
