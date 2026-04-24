#include "Employee.h"
#include <iostream>

Employee::Employee() : User(), salary(0.0) {}
Employee::Employee(string n, string e, string p, double s) : User(n, e, p), salary(s) {}

void Employee::viewSalary() const { 
    cout << "Current Credited Salary: Rs. " << salary << endl; 
}

void Employee::updateSalary(double amount) { 
    salary += amount; 
}

bool Employee::redeemSalary(double amount) {
    if (amount <= 0) {
        cout << "[!] Error: Invalid amount. Please enter a value greater than 0.\n";
        return false;
    }
    if (amount > salary) {
        cout << "[!] Error: Insufficient funds! You only have Rs. " << salary << " credited.\n";
        return false;
    }
    salary -= amount;
    cout << "[+] Success! You have redeemed Rs. " << amount << ".\n";
    cout << "    Remaining Credited Balance: Rs. " << salary << "\n";
    return true;
}

double Employee::getSalary() const { return salary; }