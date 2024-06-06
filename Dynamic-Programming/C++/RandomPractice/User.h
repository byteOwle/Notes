#pragma once
#include <string>

#include "Bank.h"
// #include <vector>

class User {
    private:
        std::string name;
        Date dob;
        Bank bank;
    public:
        User();
        User(std::string _name, Date& _dob);
        User(std::string _name, Date& _dob, Bank&);
        Bank* getBank() { return &bank; }
        std::string getName();
        Date getDob();
        double getSavingsAccountBalance();
        double getCheckingsAccountBalance();
};

User::User() {
    name = "Mike";
    dob = Date(7, 6, 1998);
    bank.setCheckingBalance(1200);
    bank.setSavingsBalance(800);
    }

User::User(std::string _name, Date& _dob) {
    name = _name;
    dob = _dob;
}

User::User(std::string _name, Date& _dob, Bank& b) {
    name = _name;
    dob = _dob;
    
    bank = b;
}

std::string User::getName() {
    return name;
}

Date User::getDob() {
    return dob;
}

double User::getCheckingsAccountBalance() {
    return bank.getCheckingsAccountBalance();    
}

double User::getSavingsAccountBalance() {
    return bank.getSavingsAccountBalance();
}