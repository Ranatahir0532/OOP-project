#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H
#include "Course.h"
#include <string>

using namespace std;

class AttendanceRecord {
private:
    string date;
    char status;
    Course course;
public:
    AttendanceRecord(); // Default constructor for arrays
    AttendanceRecord(string d, char s, Course c);
    void displayRecord() const;
    string getCourseCode() const;
    string getDate() const;
    char getStatus() const;
};

#endif