#include "Faculty.h"
#include <iostream>

Faculty::Faculty() : Employee(), courseCount(0) {}

Faculty::Faculty(string n, string e, string p, double s) : Employee(n, e, p, s) {
    courseCount = 0;
}

void Faculty::viewDashboard() const {
    cout << "\n--- Faculty Dashboard ---\nName: " << name << "\nCourses Taught:\n";
    for(int i = 0; i < courseCount; i++) cout << "- " << coursesTaught[i].getCode() << " : " << coursesTaught[i].getTitle() << endl;
}

void Faculty::assignCourse(Course c) { 
    if(courseCount < 5) {
        coursesTaught[courseCount] = c;
        courseCount++;
    }
}

bool Faculty::teachesCourse(string code) const {
    for(int i = 0; i < courseCount; i++) if(coursesTaught[i].getCode() == code) return true;
    return false;
}

void Faculty::markAttendance(Student& s, Course c, string date, char status) {
    if(teachesCourse(c.getCode())) {
        
        // Strict Enrollment Check
        bool enrolled = false;
        for(int i = 0; i < s.getCourseCount(); i++) {
            if(s.getEnrolledCourses()[i].getCode() == c.getCode()) { enrolled = true; break; }
        }
        if(!enrolled) { 
            cout << "[!] Error: Student " << s.getRollNo() << " is not formally enrolled in " << c.getCode() << "!\n"; 
            return; 
        }

        if (s.getAttendanceCount() < 100) {
            // Uses a friend shortcut to safely bypass private status
            s.attendanceHistory[s.attendanceCount] = AttendanceRecord(date, status, c);
            s.attendanceCount++;
            cout << "[+] Attendance marked for " << s.getRollNo() << endl;
        } else { cout << "[!] Attendance storage full for this student.\n"; }
    } else { cout << "[!] You do not teach this course.\n"; }
}

void Faculty::assignGrade(Student& s, Course c, string grade) {
    if(teachesCourse(c.getCode())) {
        
        // Strict Enrollment Check
        bool enrolled = false;
        for(int i = 0; i < s.getCourseCount(); i++) {
            if(s.getEnrolledCourses()[i].getCode() == c.getCode()) { enrolled = true; break; }
        }
        if(!enrolled) { 
            cout << "[!] Error: Student " << s.getRollNo() << " is not formally enrolled in " << c.getCode() << "!\n"; 
            return; 
        }

        s.transcript.addGrade(c.getCode(), grade);
        cout << "[+] Grade " << grade << " assigned to " << s.getRollNo() << endl;
    } else { cout << "[!] You do not teach this course.\n"; }
}

const Course* Faculty::getCoursesTaught() const { return coursesTaught; }
int Faculty::getCourseCount() const { return courseCount; }