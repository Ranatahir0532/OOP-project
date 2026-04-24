#include "User.h"

User::User() : Account(), name("") {}
User::User(string n, string e, string p) : Account(e, p), name(n) {}

string User::getName() const { return name; }