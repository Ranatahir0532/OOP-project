#include "Course.h"

Course::Course(string code, string title) : courseCode(code), courseTitle(title) {}

string Course::getCode() const { return courseCode; }
string Course::getTitle() const { return courseTitle; }

bool Course::operator==(const Course& other) const { 
    return this->courseCode == other.courseCode; 
}