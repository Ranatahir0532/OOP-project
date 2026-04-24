#ifndef USER_H
#define USER_H
#include "Account.h"

class User : public Account {
protected:
    string name;
public:
    User();
    User(string n, string e, string p);
    virtual void viewDashboard() const = 0; 
    virtual ~User() {}
    string getName() const;
};

#endif