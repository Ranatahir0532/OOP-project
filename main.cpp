#include "FileManager.h"
#include "Admin.h"
#include <iostream>

Course availableCourses[5] = {
    Course("CL1004", "Object Oriented Programming"),
    Course("EE1005", "Digital Logic Design"),
    Course("MT1008", "Multivariable Calculus"),
    Course("SS1014", "Expository Writing"),
    Course("SS1015", "Pakistan Studies")
};

int main() {
    Student students[100]; int studentCount = 0;
    Faculty facultyList[50]; int facultyCount = 0;
    Admin adminList[10]; int adminCount = 0;

    FileManager::loadStudents("students.txt", students, studentCount);
    FileManager::loadFaculty("faculty.txt", facultyList, facultyCount);
    FileManager::loadAdmins("admins.txt", adminList, adminCount);

    if(studentCount == 0) { students[0] = Student("Abdullah", "24K-0001", "abdullah@saos.edu", "pass123"); studentCount++; }
    if(facultyCount == 0) { facultyList[0] = Faculty("Dr. Smith", "smith@saos.edu", "fac123"); facultyCount++; }
    if(adminCount == 0) { adminList[0] = Admin("System Admin", "admin@saos.edu", "admin123"); adminCount++; }

    bool systemRunning = true;
    
    while(systemRunning) {
        int userType;
        cout << "\n==============================\n";
        cout << " Welcome to SAOS Portal \n";
        cout << "==============================\n";
        cout << "1. Student\n2. Faculty\n3. Admin\n4. Exit System\nSelect Role: ";
        cin >> userType;

        if (userType == 4) {
            cout << "\n[+] Saving all data. Exiting SAOS. Goodbye!\n";
            break;
        }

        string email, pass;
        cout << "Email: "; cin >> email;
        cout << "Password: "; cin >> pass;

        // --- STUDENT PORTAL ---
        if (userType == 1) {
            bool loggedIn = false;
            for (int i = 0; i < studentCount; i++) {
                Student& s = students[i];
                if (s.verifyLogin(email, pass)) {
                    loggedIn = true;
                    cout << "\n[+] Login Successful! Welcome " << s.getName() << ".\n";
                    int choice;
                    do {
                        cout << "\n--- Student Menu ---\n1. Dashboard\n2. Enroll\n3. Pay Fee\n4. View Attendance\n5. View Transcript\n6. Logout\nSelect: ";
                        cin >> choice;
                        
                        if (choice == 1) s.viewDashboard();
                        else if (choice == 2) {
                            cout << "\n--- Available Courses to Enroll ---\n";
                            bool hasOptions = false;
                            const Course* enrolled = s.getEnrolledCourses();
                            for (int j = 0; j < 5; j++) {
                                bool isEnrolled = false;
                                for (int k = 0; k < s.getCourseCount(); k++) {
                                    if (enrolled[k].getCode() == availableCourses[j].getCode()) { isEnrolled = true; break; }
                                }
                                if (!isEnrolled) { 
                                    cout << j << ". " << availableCourses[j].getCode() << " - " << availableCourses[j].getTitle() << "\n";
                                    hasOptions = true;
                                }
                            }
                            if (!hasOptions) cout << "[!] You are already enrolled in all available courses!\n";
                            else {
                                cout << "Enter index to enroll: "; int idx; cin >> idx;
                                if (idx >= 0 && idx <= 4) s.enrollCourse(availableCourses[idx]);
                                else cout << "[!] Error: Invalid Selection.\n";
                            }
                        }
                        else if (choice == 3) {
                            cout << "\n--- Fee Payment ---\n";
                            cout << "Current Due Amount: Rs. " << s.getFeeDue() << "\n";
                            if(s.getFeeDue() <= 0) cout << "You have no pending dues.\n";
                            else { double amt; cout << "Enter amount to pay: "; cin >> amt; s -= amt; }
                        }
                        else if (choice == 4) {
                            string c; cout << "\nEnter Course Code (e.g., CL1004): "; cin >> c;
                            s.viewAttendance(c);
                        }
                        else if (choice == 5) s.viewTranscript();

                    } while (choice != 6);
                    FileManager::saveStudents("students.txt", students, studentCount);
                    cout << "[+] Logged out successfully. Data Saved.\n";
                    break;
                }
            }
            if(!loggedIn) cout << "[!] Invalid Student Credentials.\n";
        } 
        
        // --- FACULTY PORTAL ---
        else if (userType == 2) {
            bool loggedIn = false;
            for (int i = 0; i < facultyCount; i++) {
                Faculty& f = facultyList[i];
                if (f.verifyLogin(email, pass)) {
                    loggedIn = true;
                    cout << "\n[+] Login Successful! Welcome " << f.getName() << ".\n";
                    int choice;
                    do {
                        cout << "\n--- Faculty Menu ---\n1. Dashboard\n2. Mark Single Attendance\n3. Mark Bulk Attendance\n4. Assign Grade\n5. View Salary\n6. Redeem Salary\n7. Logout\nSelect: ";
                        cin >> choice;
                        
                        if (choice == 1) f.viewDashboard();
                        else if (choice == 2) {
                            string cCode; cout << "\nEnter Course Code (e.g., CL1004): "; cin >> cCode;
                            if (cCode.find("K-") != string::npos) { cout << "[!] ERROR: You accidentally typed a Roll Number in the Course Code field!\n"; continue; }
                            if (!f.teachesCourse(cCode)) { cout << "[!] Error: You do not teach " << cCode << ". Access Denied.\n"; continue; }
                            
                            string roll, date; char stat;
                            cout << "Student Roll No (e.g., 24K-0001): "; cin >> roll; 
                            cout << "Date (DD/MM/YYYY): "; cin >> date; 
                            cout << "Status (P/A): "; cin >> stat;
                            
                            bool studentFound = false;
                            for(int j = 0; j < studentCount; j++) {
                                if(students[j].getRollNo() == roll) { f.markAttendance(students[j], Course(cCode,""), date, stat); studentFound = true; break; }
                            }
                            if(!studentFound) cout << "[!] Error: Student " << roll << " not found in system.\n";
                        }
                        else if (choice == 3) {
                            string cCode; cout << "\nEnter Course Code (e.g., CL1004): "; cin >> cCode;
                            if (cCode.find("K-") != string::npos) { cout << "[!] ERROR: You accidentally typed a Roll Number in the Course Code field!\n"; continue; }
                            if (!f.teachesCourse(cCode)) { cout << "[!] Error: You do not teach " << cCode << ". Access Denied.\n"; continue; }
                            
                            string date; char stat;
                            cout << "Date (DD/MM/YYYY): "; cin >> date; 
                            cout << "Status to assign to all entered students (P/A): "; cin >> stat;
                            
                            cout << "\n--- Bulk Entry Mode ---\n";
                            cout << "Enter Student Roll Numbers one by one.\n";
                            cout << "Type 'DONE' (all caps) when you are finished.\n";
                            
                            string roll;
                            while(true) {
                                cout << "> Roll No (or DONE): ";
                                cin >> roll;
                                if(roll == "DONE") break;
                                
                                bool studentFound = false;
                                for(int j = 0; j < studentCount; j++) {
                                    if(students[j].getRollNo() == roll) { 
                                        f.markAttendance(students[j], Course(cCode,""), date, stat); 
                                        studentFound = true; 
                                        break; 
                                    }
                                }
                                if(!studentFound) cout << "[!] Error: Student " << roll << " not found in system.\n";
                            }
                            cout << "[+] Bulk attendance marking completed.\n";
                        }
                        else if (choice == 4) {
                            string cCode; cout << "\nEnter Course Code (e.g., CL1004): "; cin >> cCode;
                            if (cCode.find("K-") != string::npos) { cout << "[!] ERROR: You accidentally typed a Roll Number in the Course Code field!\n"; continue; }
                            if (!f.teachesCourse(cCode)) { cout << "[!] Error: You do not teach " << cCode << ". Access Denied.\n"; continue; }
                            
                            string roll, grade;
                            cout << "Student Roll No (e.g., 24K-0001): "; cin >> roll; 
                            cout << "Grade (A+, A, B, etc): "; cin >> grade;
                            
                            bool studentFound = false;
                            for(int j = 0; j < studentCount; j++) {
                                if(students[j].getRollNo() == roll) { f.assignGrade(students[j], Course(cCode,""), grade); studentFound = true; break; }
                            }
                            if(!studentFound) cout << "[!] Error: Student " << roll << " not found in system.\n";
                        }
                        else if (choice == 5) f.viewSalary();
                        else if (choice == 6) { // NEW REDEEM SALARY FEATURE
                            cout << "\n--- Redeem Salary ---\n";
                            cout << "Current Balance: Rs. " << f.getSalary() << "\n";
                            if (f.getSalary() <= 0) {
                                cout << "[!] You have no salary credited to redeem right now.\n";
                            } else {
                                double amt;
                                cout << "Enter amount to redeem: ";
                                cin >> amt;
                                f.redeemSalary(amt);
                            }
                        }

                    } while (choice != 7); // Updated loop exit condition
                    
                    FileManager::saveFaculty("faculty.txt", facultyList, facultyCount);
                    FileManager::saveStudents("students.txt", students, studentCount); 
                    cout << "[+] Logged out successfully. Data Saved.\n";
                    break;
                }
            }
            if(!loggedIn) cout << "[!] Invalid Faculty Credentials.\n";
        }

        // --- ADMIN PORTAL ---
        else if (userType == 3) {
            bool loggedIn = false;
            for (int i = 0; i < adminCount; i++) {
                Admin& sysAdmin = adminList[i];
                if (sysAdmin.verifyLogin(email, pass)) {
                    loggedIn = true;
                    cout << "\n[+] Admin Login Successful.\n";
                    int choice;
                    do {
                        cout << "\n--- Admin Menu ---\n1. Dashboard\n2. Pay Faculty Salary\n3. Enroll Student Course\n4. Remove Student Course\n5. Logout\nSelect: ";
                        cin >> choice;
                        
                        if (choice == 1) sysAdmin.viewDashboard();
                        else if (choice == 2) {
                            string fEmail; double amt;
                            cout << "Faculty Email: "; cin >> fEmail; cout << "Amount to pay: "; cin >> amt;
                            bool found = false;
                            for(int j = 0; j < facultyCount; j++) {
                                if(facultyList[j].getEmail() == fEmail) { sysAdmin.paySalary(facultyList[j], amt); found = true; break; }
                            }
                            if(found) FileManager::saveFaculty("faculty.txt", facultyList, facultyCount);
                            else cout << "[!] Error: Faculty member not found.\n";
                        }
                        else if (choice == 3) { 
                            string roll, cCode; cout << "Student Roll No: "; cin >> roll; cout << "Course Code to Enroll (e.g., CL1004): "; cin >> cCode;
                            bool validCourse = false; Course cToEnroll;
                            for(int j = 0; j < 5; j++) {
                                if(availableCourses[j].getCode() == cCode) { cToEnroll = availableCourses[j]; validCourse = true; break; }
                            }
                            if(!validCourse) { cout << "[!] Error: Invalid course code.\n"; continue; }

                            bool found = false;
                            for(int j = 0; j < studentCount; j++) {
                                if(students[j].getRollNo() == roll) { sysAdmin.enrollCourseForStudent(students[j], cToEnroll); found = true; break; }
                            }
                            if(!found) cout << "[!] Error: Student not found.\n";
                        }
                        else if (choice == 4) {
                            string roll, cCode; cout << "Student Roll No: "; cin >> roll; cout << "Course Code to Remove (e.g., CL1004): "; cin >> cCode;
                            bool found = false;
                            for(int j = 0; j < studentCount; j++) {
                                if(students[j].getRollNo() == roll) { sysAdmin.removeCourseFromStudent(students[j], cCode); found = true; break; }
                            }
                            if(!found) cout << "[!] Error: Student not found.\n";
                        }
                    } while (choice != 5);
                    
                    FileManager::saveStudents("students.txt", students, studentCount); 
                    FileManager::saveAdmins("admins.txt", adminList, adminCount);
                    cout << "[+] Admin logged out.\n";
                    break;
                }
            }
            if (!loggedIn) cout << "[!] Invalid Admin Credentials.\n";
        }
    }
    return 0;
}