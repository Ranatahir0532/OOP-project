#ifndef COURSE_H
#define COURSE_H
#include <string>

using namespace std;

class Course {
private:
    string courseCode;
    string courseTitle;
public:
    Course(string code = "", string title = ""); // Also acts as default constructor
    string getCode() const;
    string getTitle() const;
    bool operator==(const Course& other) const;
};

#endif