#ifndef STUDENT_H
#define STUDENT_H
#include "User.h"
#include "Course.h"
#include "AttendanceRecord.h"
#include "Transcript.h"

class Student : public User {
private:
    string rollNo; 
    double feeDue;
    
    // Replaced Vectors with standard arrays
    Course enrolledCourses[5]; 
    int courseCount;
    
    AttendanceRecord attendanceHistory[100]; 
    int attendanceCount;
    
    Transcript transcript; 
    bool validateRollNo(string roll);

public:
    Student();
    Student(string n, string r, string e, string p, double fee = 198500.0);
    
    void viewDashboard() const override;
    bool enrollCourse(Course c);
    void viewAttendance(string courseCode) const;
    void viewTranscript() const;
    
    string getRollNo() const;
    double getFeeDue() const;
    const Course* getEnrolledCourses() const;
    int getCourseCount() const;
    const AttendanceRecord* getAttendanceHistory() const;
    int getAttendanceCount() const;
    
    void operator-=(double amount); 

    friend class Admin; 
    friend class Faculty; 
    friend class FileManager;
};

#endif