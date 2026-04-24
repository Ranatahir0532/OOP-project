#include "Admin.h"
#include <iostream>

Admin::Admin() : Employee() {}
Admin::Admin(string n, string e, string p) : Employee(n, e, p, 0.0) {}

void Admin::viewDashboard() const { cout << "\n--- Admin Dashboard ---\nLogged in as System Admin.\n"; }

void Admin::paySalary(Faculty& f, double amount) { 
    f.updateSalary(amount); 
    cout << "Paid Rs. " << amount << " to faculty.\n"; 
}

void Admin::enrollCourseForStudent(Student& s, Course c) { s.enrollCourse(c); }

// Updated to shift the array manually instead of vector erase
void Admin::removeCourseFromStudent(Student& s, string courseCode) {
    for(int i = 0; i < s.courseCount; i++) {
        if(s.enrolledCourses[i].getCode() == courseCode) {
            for(int j = i; j < s.courseCount - 1; j++) {
                s.enrolledCourses[j] = s.enrolledCourses[j+1];
            }
            s.courseCount--; 
            cout << "[+] Course removed.\n"; 
            return; 
        }
    }
}