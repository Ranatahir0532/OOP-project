# 🎓 SAOS University Portal — Student & Academic Operations System

> A comprehensive C++ application for managing university academic operations including student enrollment, faculty management, attendance tracking, grading, and administrative control — built entirely using advanced Object-Oriented Programming principles.

---

## 👥 Group Members

| Name | Student ID |
|------|------------|
| Muhammad Anas | 25K-0899 |
| Abdullah Moin | 25K-0991 |
| Syed Alyan Hussain | 25K-0648 |

**Course:** Object-Oriented Programming (CS2001) — Lab Semester Project

---

## 📋 Project Description

The **SAOS University Portal** is a role-based, multi-user console application that simulates a real-world university academic management system. The system supports three distinct user roles — **Students**, **Faculty**, and **Admins** — each with a dedicated portal and specific capabilities.

Built without STL containers (no `vector`, no `map`), the system instead uses raw arrays with manual size tracking, demonstrating mastery of low-level C++ memory and data management. Data is persisted across sessions using structured `.txt` flat-files, and the entire codebase is organized into a clean modular architecture with separate header and source files for every class.

---

## 🚀 Key Use Cases

### 1. 🎓 Student Enrollment & Course Management
Students can browse available courses and self-enroll (up to 5 courses). Admins can also enroll or remove courses on a student's behalf. Duplicate enrollment and over-enrollment are both guarded with validation errors.

### 2. 💳 Fee Payment System
Students can view their current outstanding fee balance and make partial or full payments using an overloaded `-=` operator. The system prevents overpayments and invalid (zero or negative) amounts.

### 3. 📅 Attendance Marking (Single & Bulk)
Faculty can mark attendance for individual students or switch to **Bulk Entry Mode** to process an entire class at once by entering roll numbers sequentially. The system enforces that a student must be formally enrolled in a course before attendance can be recorded for it.

### 4. 📝 Grade Assignment & Transcript Viewing
Faculty can assign letter grades (A+, A, B-, etc.) to enrolled students for courses they teach. Students can view their official formatted transcript at any time, showing all enrolled courses and their current grades.

### 5. 💰 Faculty Salary Management & Redemption
Admins can credit salary payments to individual faculty members. Faculty can then view their credited balance and redeem any portion of it — with validation to prevent over-redemption or invalid amounts.

### 6. 💾 Persistent Data Storage Across Sessions
All student records (courses, attendance, grades, fee balances), faculty data (assigned courses, salary), and admin credentials are automatically saved to `.txt` files on logout and reloaded on the next startup — ensuring no data is lost between sessions.

### 7. 🛡️ Role-Based Access Control
The system enforces strict access boundaries. Faculty can only mark attendance and assign grades for courses they are assigned to teach. All login attempts are validated against stored credentials before granting portal access.

---

## 🏗️ Core OOP Concepts Applied

| Concept | Implementation |
|---------|---------------|
| **Encapsulation** | All data members (`salary`, `feeDue`, `password`) are `private`/`protected`, accessed only via getters and setters |
| **Inheritance** | Multi-level hierarchy: `Account` → `User` → `Employee` → `Faculty` / `Admin`, and `User` → `Student` |
| **Polymorphism** | `viewDashboard()` is a pure virtual function in `User`, overridden distinctly in `Student`, `Faculty`, and `Admin` |
| **Abstraction** | `User` is an abstract class (pure virtual `viewDashboard()`); `Account` serves as the authentication base interface |
| **Operator Overloading** | `Student::operator-=` for fee payment; `Course::operator==` for enrollment duplicate checks |
| **Friend Classes** | `Faculty` and `Admin` are declared `friend` in `Student` for controlled direct-array access (e.g., attendance marking) |
| **File I/O** | `FileManager` uses a fully static interface to serialize/deserialize all entities to/from structured flat-files |

---

## 📁 Project File Structure

```
SAOS-Portal/
├── Account.h / Account.cpp         # Base authentication class
├── User.h / User.cpp               # Abstract user base with virtual dashboard
├── Employee.h / Employee.cpp       # Salary management for all staff
├── Student.h / Student.cpp         # Student entity with enrollment & attendance
├── Faculty.h / Faculty.cpp         # Faculty entity with grading & attendance tools
├── Admin.h / Admin.cpp             # Admin entity with override permissions
├── Course.h / Course.cpp           # Course data object with equality operator
├── AttendanceRecord.h / .cpp       # Single attendance record (date, status, course)
├── Transcript.h / Transcript.cpp   # Grade storage and transcript display
├── FileManager.h / FileManager.cpp # Static file persistence for all entities
├── main.cpp                        # Entry point with all portal menus
├── students.txt                    # Persistent student data store
├── faculty.txt                     # Persistent faculty data store
└── admins.txt                      # Persistent admin credentials store
```

---

## 🔧 Instructions to Compile & Run

### Option A — Dev-C++

1. **Create a Project:** Go to `File > New > Project...`
2. **Select Console Application:** Choose `C++ Project`, name it `SAOSPortal`, and click OK.
3. **Add All Files:** Right-click the project in the sidebar → `Add to Project` → select all `.cpp` and `.h` files.
4. **Configure Compiler:** Go to `Tools > Compiler Options`. Check "Add the following commands when calling the compiler" and enter:
   ```
   -std=c++11
   ```
5. **Build & Run:** Press `F11` to compile and launch the system.

---

### Option B — VS Code

**Prerequisite:** Install the `C/C++` and `C++ Runner` extensions from the VS Code marketplace.

1. **Open Folder:** Open the project root directory in VS Code (`File > Open Folder`).
2. **Open Terminal:** Press `` Ctrl+` `` to open the integrated terminal.
3. **Compile** using the following single command (ensure all files are in the same directory):

```bash
g++ -std=c++11 Account.cpp User.cpp Employee.cpp Student.cpp Faculty.cpp Admin.cpp Course.cpp AttendanceRecord.cpp Transcript.cpp FileManager.cpp main.cpp -o SAOSPortal
```

4. **Run** the compiled executable:

```bash
# On Linux / macOS
./SAOSPortal

# On Windows
SAOSPortal.exe
```

---

### Option C — Command Line (Linux / macOS / Git Bash)

```bash
# Compile
g++ -std=c++11 *.cpp -o SAOSPortal

# Run
./SAOSPortal
```

---

## 🖥️ How to Use the System

When launched, the system presents the main login screen:

```
==============================
 Welcome to SAOS Portal
==============================
1. Student
2. Faculty
3. Admin
4. Exit System
Select Role:
```

### 🔐 Default Login Credentials

| Role | Email | Password |
|------|-------|----------|
| Admin | `admin@saos.edu` | `admin123` |
| Faculty | `fatima@saos.edu` | `fac123` |
| Student | `abdullah@saos.edu` | `pass123` |

> These credentials are loaded from the `.txt` files on startup. If the files are missing or empty, the system auto-creates one default user per role.

---

### 👨‍🎓 Student Portal Walkthrough

After logging in, the student menu offers:

| Option | Action |
|--------|--------|
| `1. Dashboard` | View name, roll number, fee due, and enrolled courses |
| `2. Enroll` | Browse and enroll in available courses (max 5) |
| `3. Pay Fee` | Enter a payment amount to reduce outstanding fee balance |
| `4. View Attendance` | Enter a course code (e.g., `CL1004`) to see attendance history |
| `5. View Transcript` | See a formatted table of all enrolled courses and grades |
| `6. Logout` | Save data and return to the main menu |

---

### 👨‍🏫 Faculty Portal Walkthrough

| Option | Action |
|--------|--------|
| `1. Dashboard` | View name and list of assigned courses |
| `2. Mark Single Attendance` | Enter course code, student roll no., date, and P/A status |
| `3. Mark Bulk Attendance` | Enter course code, date, status — then enter roll numbers one by one; type `DONE` to finish |
| `4. Assign Grade` | Enter course code, student roll no., and grade (e.g., `A+`) |
| `5. View Salary` | Display current credited salary balance |
| `6. Redeem Salary` | Withdraw a specified amount from credited salary |
| `7. Logout` | Save all data and return to the main menu |

---

### 🛡️ Admin Portal Walkthrough

| Option | Action |
|--------|--------|
| `1. Dashboard` | Display admin session info |
| `2. Pay Faculty Salary` | Enter faculty email and amount to credit to their balance |
| `3. Enroll Student Course` | Enter student roll no. and a valid course code to enroll them |
| `4. Remove Student Course` | Enter student roll no. and course code to drop them from a course |
| `5. Logout` | Save all data and return to the main menu |

---

### 📚 Available Courses

| Course Code | Course Title |
|-------------|-------------|
| `CL1004` | Object Oriented Programming |
| `EE1005` | Digital Logic Design |
| `MT1008` | Multivariable Calculus |
| `SS1014` | Expository Writing |
| `SS1015` | Pakistan Studies |

---

## ⚠️ Assumptions & Limitations

- **No STL Containers:** The system deliberately avoids `vector`, `map`, and other STL containers. All collections use fixed-size C-style arrays with manual index counters, as required by the course constraints.

- **Fixed Capacity Limits:** A student can enroll in a maximum of **5 courses** and store up to **100 attendance records**. Faculty can be assigned a maximum of **5 courses**. The system supports up to **100 students**, **50 faculty**, and **10 admins** loaded in memory at once.

- **Roll Number Format:** Student roll numbers must strictly follow the `XXK-XXXX` format (e.g., `24K-0001`). The system will display a warning during object creation if the format is invalid.

- **Date Format:** Dates for attendance records should be entered in `DD/MM/YYYY` format (e.g., `19/02/2026`). No automatic date validation is enforced beyond what the user enters.

- **Data Persistence:** All data is stored in plain-text `.txt` files (`students.txt`, `faculty.txt`, `admins.txt`) in the same directory as the executable. The program must have **read and write permissions** in its working directory.

- **Save on Logout:** Data is saved automatically when a user selects Logout. If the program is closed abruptly (e.g., via terminal interrupt), unsaved changes from the current session will be lost.

- **Password Security:** Passwords are stored and compared as plain text. This is intentional for the scope of this academic project and is not intended for production use.

- **Compiler Standard:** The project requires `C++11` or higher due to the use of range-based features and string utilities. Compilation with older standards will produce errors.
