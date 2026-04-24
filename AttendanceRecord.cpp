#include "AttendanceRecord.h"
#include <iostream>

AttendanceRecord::AttendanceRecord() : date(""), status('A'), course(Course()) {}
AttendanceRecord::AttendanceRecord(string d, char s, Course c) : date(d), status(s), course(c) {}

void AttendanceRecord::displayRecord() const {
    cout << "Date: " << date << " | Course: " << course.getCode() << " | Status: " << status << endl;
}

string AttendanceRecord::getCourseCode() const { return course.getCode(); }
string AttendanceRecord::getDate() const { return date; }
char AttendanceRecord::getStatus() const { return status; }