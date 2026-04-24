#ifndef ADMIN_H
#define ADMIN_H
#include "Employee.h"
#include "Student.h"
#include "Faculty.h"

class Admin : public Employee {
public:
    Admin();
    Admin(string n, string e, string p);
    void viewDashboard() const override;
    void paySalary(Faculty& f, double amount);
    void enrollCourseForStudent(Student& s, Course c);
    void removeCourseFromStudent(Student& s, string courseCode);
};

#endif