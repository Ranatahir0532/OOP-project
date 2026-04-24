#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "Student.h"
#include "Faculty.h"
#include "Admin.h"
#include <string>

// Passes arrays by reference using size integers instead of Vectors
class FileManager {
public:
    static void loadStudents(const string& filename, Student students[], int& studentCount);
    static void saveStudents(const string& filename, const Student students[], int studentCount);
    
    static void loadFaculty(const string& filename, Faculty facultyList[], int& facultyCount);
    static void saveFaculty(const string& filename, const Faculty facultyList[], int facultyCount);
    
    static void loadAdmins(const string& filename, Admin adminList[], int& adminCount);
    static void saveAdmins(const string& filename, const Admin adminList[], int adminCount);
};

#endif