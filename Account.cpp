#include "Account.h"

Account::Account() : email(""), password("") {}
Account::Account(string e, string p) : email(e), password(p) {}

bool Account::verifyLogin(string e, string p) const { 
    return email == e && password == p; 
}

string Account::getEmail() const { return email; }
string Account::getPassword() const { return password; }