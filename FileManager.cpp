#include "FileManager.h"
#include <fstream>
#include <sstream>

// Advanced helper to strip out hidden Windows characters and spaces
void cleanStr(string& s) {
    while(!s.empty() && (s.back() == '\r' || s.back() == ' ' || s.back() == '\n')) s.pop_back();
    while(!s.empty() && (s.front() == ' ')) s.erase(0, 1);
}

string getCourseTitleHelper(string code) {
    if(code == "CL1004") return "Object Oriented Programming";
    if(code == "EE1005") return "Digital Logic Design";
    if(code == "MT1008") return "Multivariable Calculus";
    if(code == "SS1014") return "Expository Writing";
    if(code == "SS1015") return "Pakistan Studies";
    return "Unknown Course";
}

void FileManager::loadStudents(const string& filename, Student students[], int& studentCount) {
    studentCount = 0;
    ifstream file(filename);
    string line, name, roll, email, pass, feeStr, coursesStr;
    
    while (getline(file, line) && studentCount < 100) {
        cleanStr(line);
        stringstream ss(line);
        getline(ss, name, ','); getline(ss, roll, ','); getline(ss, email, ',');
        getline(ss, pass, ','); getline(ss, feeStr, ','); getline(ss, coursesStr, ',');

        Student s(name, roll, email, pass, stod(feeStr));
        
        stringstream cs(coursesStr);
        string courseData;
        while(getline(cs, courseData, ';')) {
            cleanStr(courseData);
            if(courseData.empty()) continue;
            
            stringstream cds(courseData);
            string cCode, grade, attStr;
            
            getline(cds, cCode, ':'); cleanStr(cCode);
            getline(cds, grade, ':'); cleanStr(grade);
            getline(cds, attStr, ':'); cleanStr(attStr);
            
            Course c(cCode, getCourseTitleHelper(cCode));
            
            if(s.courseCount < 5) {
                s.enrolledCourses[s.courseCount] = c;
                s.courseCount++;
            }
            s.transcript.addGrade(cCode, grade);

            // BULLETPROOF PARSING: Manual string slicing for attendance
            if(!attStr.empty()) {
                size_t pos = 0;
                string token;
                while (true) {
                    pos = attStr.find(',');
                    token = (pos == string::npos) ? attStr : attStr.substr(0, pos);
                    cleanStr(token);

                    if (!token.empty()) {
                        size_t eqPos = token.find('=');
                        if (eqPos != string::npos) {
                            string dateStr = token.substr(0, eqPos);
                            string statusStr = token.substr(eqPos + 1);
                            cleanStr(dateStr); cleanStr(statusStr);

                            if (!statusStr.empty() && s.attendanceCount < 100) {
                                s.attendanceHistory[s.attendanceCount] = AttendanceRecord(dateStr, statusStr[0], c);
                                s.attendanceCount++;
                            }
                        }
                    }
                    if (pos == string::npos) break;
                    attStr.erase(0, pos + 1);
                }
            }
        }
        students[studentCount] = s;
        studentCount++;
    }
}

void FileManager::saveStudents(const string& filename, const Student students[], int studentCount) {
    ofstream file(filename);
    for (int i = 0; i < studentCount; i++) {
        const Student& s = students[i];
        file << s.getName() << "," << s.getRollNo() << "," << s.getEmail() << "," << s.getPassword() << "," << s.getFeeDue() << ",";
        
        const Course* courses = s.getEnrolledCourses();
        int cCount = s.getCourseCount();
        for (int j = 0; j < cCount; j++) {
            string cCode = courses[j].getCode();
            string grade = s.transcript.getGrade(cCode);
            file << cCode << ":" << grade << ":"; 
            
            bool firstAtt = true;
            const AttendanceRecord* atts = s.getAttendanceHistory();
            int aCount = s.getAttendanceCount();
            for (int k = 0; k < aCount; k++) {
                if (atts[k].getCourseCode() == cCode) {
                    if (!firstAtt) file << ",";
                    file << atts[k].getDate() << "=" << atts[k].getStatus(); 
                    firstAtt = false;
                }
            }
            if (j < cCount - 1) file << ";";
        }
        file << "\n";
    }
}

void FileManager::loadFaculty(const string& filename, Faculty facultyList[], int& facultyCount) {
    facultyCount = 0; ifstream file(filename);
    string line, name, email, pass, salStr, coursesStr;
    while(getline(file, line) && facultyCount < 50) {
        cleanStr(line);
        stringstream ss(line);
        getline(ss, name, ','); getline(ss, email, ','); getline(ss, pass, ','); 
        getline(ss, salStr, ','); getline(ss, coursesStr, ',');
        
        double salary = salStr.empty() ? 0.0 : stod(salStr);
        Faculty f(name, email, pass, salary); 
        
        stringstream cs(coursesStr); string cCode;
        while(getline(cs, cCode, ';')) {
            cleanStr(cCode);
            if(!cCode.empty()) f.assignCourse(Course(cCode, getCourseTitleHelper(cCode)));
        }
        facultyList[facultyCount] = f;
        facultyCount++;
    }
}

void FileManager::saveFaculty(const string& filename, const Faculty facultyList[], int facultyCount) {
    ofstream file(filename);
    for(int i = 0; i < facultyCount; i++) {
        const Faculty& f = facultyList[i];
        file << f.getName() << "," << f.getEmail() << "," << f.getPassword() << "," << f.getSalary() << ",";
        const Course* courses = f.getCoursesTaught();
        int cCount = f.getCourseCount();
        for (int j = 0; j < cCount; j++) {
            file << courses[j].getCode();
            if(j < cCount - 1) file << ";";
        }
        file << "\n";
    }
}

void FileManager::loadAdmins(const string& filename, Admin adminList[], int& adminCount) {
    adminCount = 0; ifstream file(filename); string line, name, email, pass;
    while(getline(file, line) && adminCount < 10) {
        cleanStr(line);
        stringstream ss(line); getline(ss, name, ','); getline(ss, email, ','); getline(ss, pass, ',');
        if(!name.empty()) {
            adminList[adminCount] = Admin(name, email, pass);
            adminCount++;
        }
    }
}

void FileManager::saveAdmins(const string& filename, const Admin adminList[], int adminCount) {
    ofstream file(filename);
    for(int i = 0; i < adminCount; i++) {
        file << adminList[i].getName() << "," << adminList[i].getEmail() << "," << adminList[i].getPassword() << "\n";
    }
}