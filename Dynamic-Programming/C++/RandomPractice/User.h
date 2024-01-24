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