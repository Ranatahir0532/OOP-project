#include "Transcript.h"
#include <iostream>
#include <iomanip>

Transcript::Transcript() { gradeCount = 0; }

void Transcript::addGrade(string courseCode, string grade) { 
    if (grade == "" || grade == " ") grade = "UnGraded";
    
    // Update if it already exists
    for(int i = 0; i < gradeCount; i++) {
        if(courseCodes[i] == courseCode) {
            grades[i] = grade;
            return;
        }
    }
    // Add new grade if under limit
    if(gradeCount < 5) {
        courseCodes[gradeCount] = courseCode;
        grades[gradeCount] = grade;
        gradeCount++;
    }
}

string Transcript::getGrade(string courseCode) const {
    for(int i = 0; i < gradeCount; i++) {
        if(courseCodes[i] == courseCode && grades[i] != "" && grades[i] != " ") {
            return grades[i];
        }
    }
    return "UnGraded";
}

void Transcript::displayTranscript(const Course enrolledCourses[], int courseCount) const {
    cout << "\n============================================\n";
    cout << "             OFFICIAL TRANSCRIPT              \n";
    cout << "============================================\n";
    if (courseCount == 0) { 
        cout << "         No courses enrolled yet.           \n"; 
        cout << "============================================\n";
        return; 
    }
    
    cout << left << setw(20) << " Course Code" << " | " << "Grade" << endl;
    cout << "--------------------------------------------\n";
    for (int i = 0; i < courseCount; i++) {
        cout << " " << left << setw(19) << enrolledCourses[i].getCode() << " | " << getGrade(enrolledCourses[i].getCode()) << endl;
    }
    cout << "============================================\n";
}