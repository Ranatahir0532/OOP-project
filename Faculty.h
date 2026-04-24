#ifndef FACULTY_H
#define FACULTY_H
#include "Employee.h"
#include "Course.h"
#include "Student.h"

class Faculty : public Employee {
private:
    Course coursesTaught[5];
    int courseCount;
public:
    Faculty();
    Faculty(string n, string e, string p, double s = 0.0);
    
    void viewDashboard() const override;
    void assignCourse(Course c);
    bool teachesCourse(string code) const;
    void markAttendance(Student& s, Course c, string date, char status);
    void assignGrade(Student& s, Course c, string grade);
    
    const Course* getCoursesTaught() const;
    int getCourseCount() const;
    
    friend class FileManager;
};

#endif