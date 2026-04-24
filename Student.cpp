#include "Student.h"
#include <iostream>
#include <cctype>

Student::Student() : User(), rollNo(""), feeDue(0.0), courseCount(0), attendanceCount(0) {}

Student::Student(string n, string r, string e, string p, double fee) : User(n, e, p), rollNo(r), feeDue(fee) {
    courseCount = 0;
    attendanceCount = 0;
    if (!validateRollNo(r)) cout << "[!] Warning: Roll number " << r << " does not match XXK-XXXX format.\n";
}

bool Student::validateRollNo(string roll) {
    if(roll.length() != 8 || roll[2] != 'K' || roll[3] != '-') return false;
    for(int i=0; i<2; i++) if(!isdigit(roll[i])) return false;
    for(int i=4; i<8; i++) if(!isdigit(roll[i])) return false;
    return true;
}

void Student::viewDashboard() const {
    cout << "\n============================================\n";
    cout << "              STUDENT DASHBOARD               \n";
    cout << "============================================\n";
    cout << " Name    : " << name << "\n";
    cout << " Roll No : " << rollNo << "\n";
    cout << " Fee Due : Rs. " << feeDue << "\n";
    cout << "--------------------------------------------\n";
    cout << " Enrolled Courses:\n";
    if (courseCount == 0) {
        cout << "  > No courses currently enrolled.\n";
    } else {
        for(int i = 0; i < courseCount; i++) {
            cout << "  > " << enrolledCourses[i].getCode() << " - " << enrolledCourses[i].getTitle() << "\n";
        }
    }
    cout << "============================================\n";
}

bool Student::enrollCourse(Course c) {
    if(courseCount >= 5) { cout << "[!] Error: Enrollment limit reached.\n"; return false; }
    for(int i = 0; i < courseCount; i++) {
        if(enrolledCourses[i] == c) { cout << "[!] Error: Already enrolled in " << c.getCode() << endl; return false; }
    }
    enrolledCourses[courseCount] = c;
    courseCount++;
    transcript.addGrade(c.getCode(), "UnGraded");
    cout << "[+] Successfully enrolled in " << c.getCode() << " - " << c.getTitle() << endl;
    return true;
}

void Student::operator-=(double amount) {
    if (amount <= 0) { cout << "[!] Error: Invalid amount entered.\n"; return; }
    if (amount > feeDue) { cout << "[!] Error: Cannot overpay! Due amount is Rs. " << feeDue << endl; } 
    else { 
        feeDue -= amount; 
        cout << "[+] Payment Successful! Paid Rs. " << amount << ". Remaining balance: Rs. " << feeDue << endl; 
    }
}

void Student::viewAttendance(string courseCode) const {
    cout << "\n--- Attendance for " << courseCode << " ---\n";
    bool found = false;
    for(int i = 0; i < attendanceCount; i++) {
        if(attendanceHistory[i].getCourseCode() == courseCode) {
            attendanceHistory[i].displayRecord();
            found = true;
        }
    }
    if (!found) cout << "No attendance records found for this course.\n";
}

void Student::viewTranscript() const { transcript.displayTranscript(enrolledCourses, courseCount); }
string Student::getRollNo() const { return rollNo; }
double Student::getFeeDue() const { return feeDue; }
const Course* Student::getEnrolledCourses() const { return enrolledCourses; }
int Student::getCourseCount() const { return courseCount; }
const AttendanceRecord* Student::getAttendanceHistory() const { return attendanceHistory; }
int Student::getAttendanceCount() const { return attendanceCount; }