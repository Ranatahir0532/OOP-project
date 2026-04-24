#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "User.h"

class Employee : public User {
protected:
    double salary;
public:
    Employee();
    Employee(string n, string e, string p, double s = 0.0);
    virtual void viewSalary() const;
    void updateSalary(double amount);
    bool redeemSalary(double amount); // NEW FEATURE
    double getSalary() const;
};

#endif