#pragma once
#include <string>

#include "Date.h"
#include <vector>
#include <type_traits>

enum class Transaction_Type {
    DEPOSIT, WITHDRAWAL, TRANSFER
};

enum class ACCOUNT_TYPE {
    CHECKING, SAVINGS
};

struct Transaction {
    std::string name;
    // double balance_before;
    double amount;
    Date date;
    
    Transaction_Type transaction_type;
    Transaction() {
        name = "WALMART";
        amount = 100.0;
        date.random();
    }
    Transaction(const Transaction& TN) {
        name = TN.name;
        amount = TN.amount;
        date = TN.date;
    }
    Transaction(std::string _name, double _amount) {
        name = _name;
        // balance_before = _balancebefore;
        amount = _amount;
        date.random();
    }
    Transaction(std::string _name, double _amount, Date& d) {
        name = _name;
        // balance_before = _balancebefore;
        amount = _amount;
        date = d;
    }
    Transaction& operator=(const Transaction& rhs) {
        if(this != &rhs) {
            name = rhs.name;
            amount = rhs.amount;
            date = rhs.date;
        }

        return *this;
    }
    // void setBalanceBefore
};

template<ACCOUNT_TYPE Account_T>
struct Account : Transaction {
    double balance = 0.0;
    std::vector<Transaction> transaction_history;
    std::string account_type = (Account_T == ACCOUNT_TYPE::CHECKING ? "CHECKING" : "SAVINGS");

    public:
        Account() = default;
        Account(const Account& a) {
            balance = a.balance;
            transaction_history = a.getTransactionHistory();
        }        
        std::vector<Transaction> getTransactionHistory() const { return transaction_history; }
        void deposit(Transaction& T) { 
            balance += T.amount;
            transaction_history.push_back(T);
        }
        void withdraw(Transaction& T) { 
            balance -= T.amount;
            transaction_history.push_back(T); 
        }
        void setBalance(int amount) { balance = amount; }
        double getBalance() { return balance; }
        void printaccountBalance() { 
            std::cout << "[Account]:\t" << account_type << "\n[Balance]:\t" << balance << std::endl;
        }
        // void setType() { account_type = Account_T; }
        ACCOUNT_TYPE getType() { return Account_T; }
        Account getAccount() { return *this; }
};

// struct Checking : Transaction {
//     double balance = 0.0;
//     std::vector<Transaction> transaction_history;

//     public:
//         std::vector<Transaction> getTransactionHistory() { return transaction_history; }
//         void deposit(Transaction& T) { 
//             balance += T.amount;
//             transaction_history.push_back(T);
//         }
//         void withdraw(Transaction& T) { balance -= T.amount; }
//         void setBalance(int amount) { balance = amount; }
//         double getBalance() { return balance; }
// };

// struct Savings : Transaction {
//     double balance = 0.0;
//     std::vector<Transaction> transaction_history;

//     public:
//         std::vector<Transaction> getTransactionHistory() { return transaction_history; }
//         void deposit(Transaction& T) { 
//             balance += T.amount;
//             transaction_history.push_back(T);
//         }
//         void withdraw(Transaction& T) { balance -= T.amount; }
//         void setBalance(int amount) { balance = amount; }
//         double getBalance() { return balance; }
// };

class Bank {
    private:
        std::string name;
        Account<ACCOUNT_TYPE::CHECKING> checkings;
        Account<ACCOUNT_TYPE::SAVINGS> savings;

        Account<ACCOUNT_TYPE::CHECKING> getCheckingsAccount() const { return checkings; }
        Account<ACCOUNT_TYPE::SAVINGS> getSavingsAccount() const { return savings; }
        
    public:
        Bank();
        Bank(const Bank& b);
        Bank(std::string bank_name);
        ~Bank();

        void deposit(Transaction& T, ACCOUNT_TYPE);
        void withdraw(Transaction& T, ACCOUNT_TYPE);
        // void transfer(double amount, Transaction_Location);

        // void operator=(const Bank& rhs);
        void setCheckingBalance(int amount);
        void setSavingsBalance(int amount);
        void printTransactionHistory();
        void printAccountBalance(ACCOUNT_TYPE TL);
        void getCheckingBalance();
        void getSavingsBalance();
        template<ACCOUNT_TYPE type>
        Account<type> getAccount();

        Bank& operator=(const Bank& rhs);
};

Bank::Bank() {
    name = "CHASE";
}

Bank::Bank(std::string bank_name) {
    name = bank_name;
}

Bank::~Bank() {

}

Bank::Bank(const Bank& b) {
    checkings = b.getCheckingsAccount();
    savings = b.getSavingsAccount();
}

void Bank::deposit(Transaction& T, ACCOUNT_TYPE AT) {
    AT == ACCOUNT_TYPE::CHECKING ? checkings.deposit(T) : savings.deposit(T);
}

void Bank::withdraw(Transaction& T, ACCOUNT_TYPE AT) {
    AT == ACCOUNT_TYPE::CHECKING ? checkings.withdraw(T) : savings.withdraw(T);
}

void Bank::setCheckingBalance(int amount) {
    checkings.setBalance(amount);
}

void Bank::setSavingsBalance(int amount) {
    savings.setBalance(amount);
}

void Bank::getCheckingBalance() {
    checkings.printaccountBalance();
}

void Bank::getSavingsBalance() {
    savings.printaccountBalance();
}

// void Bank::printAccountBalance(ACCOUNT_TYPE AT) {
//     using UnderLyingType = typename std::underlying_type<ACCOUNT_TYPE>::type;
//     UnderLyingType type = static_cast<UnderLyingType>(AT);
//     std::cout << type << std::endl;
//     // auto account = getAccount<type>(AT);
// }

template<ACCOUNT_TYPE type>
Account<type> Bank::getAccount() {
    if constexpr (type == ACCOUNT_TYPE::CHECKING)
        return getCheckingsAccount();
    else 
        return getSavingsAccount();
}

void Bank::printTransactionHistory() {
    auto checking_th = checkings.getTransactionHistory();
    std::cout << "[TRANSACTION HISTORY FOR CHECKING ACCOUNT] " << checking_th.size() << " recorded\n";
    getCheckingBalance();
    for(auto transaction : checking_th) {
        std::cout << "[Amount]:\t" << transaction.amount << "\n[Transaction name]:\t" << transaction.name << 
            "\n[Transaction Date]:\t";
            transaction.date.printDate(); std::cout << "\n"; 
    }

    auto savings_th = savings.getTransactionHistory();
    std::cout << "[TRANSACTION HISTORY FOR SAVINGS ACCOUNT] " << savings_th.size() << " recorded\n";
    getSavingsBalance();
    for(auto transaction : savings_th) {
        std::cout << "\n[Amount]:\t" << transaction.amount << "\n[Transaction name]:\t" << transaction.name <<
            "\n[Transaction Date]:\t"; 
            transaction.date.printDate(); std::cout << "\n";
    }
}

// void Bank::transfer(int amount, Transaction_Location TL) {
//     balance += amount;
// }

Bank& Bank::operator=(const Bank& rhs) {
    if(this != &rhs) {
        checkings = rhs.getCheckingsAccount();
        savings = rhs.getSavingsAccount();
    }

    return *this;
}