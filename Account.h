#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

using namespace std;

class Account {
protected:
    string email;
    string password;
public:
    Account();
    Account(string e, string p);
    bool verifyLogin(string e, string p) const;
    string getEmail() const;
    string getPassword() const;
};

#endif