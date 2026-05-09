# Student Management System 🎓

A console-based Student Management System built in **C++** that efficiently manages student records using file handling and menu-driven operations.

---

## 📌 Project Overview

This project is developed as part of the **Thiranex C++ Internship Program**. It demonstrates core C++ concepts including structs, binary file handling, and menu-driven console applications.

---

## ✨ Features

- ➕ **Add Student** — Add new student records with ID, name, department, CGPA, and phone number
- 📋 **Display All Students** — View all student records in a formatted table
- 🔍 **Search Student** — Search for a student by their unique ID
- ✏️ **Update Student** — Modify existing student information
- 🗑️ **Delete Student** — Remove a student record permanently
- 💾 **Persistent Storage** — All data is stored in a binary file (`students.dat`) and retained after the program closes

---

## 🛠️ Tech Stack

- **Language:** C++
- **Concepts Used:** Structs, Binary File I/O (`fstream`), Menu-driven loops, Input validation

---

## 🚀 How to Run

### Prerequisites
- A C++ compiler (g++ recommended)

### Compile & Run

```bash
# Compile
g++ main.cpp -o student_management

# Run on Linux/Mac
./student_management

# Run on Windows
student_management.exe
```

---

## 📂 File Structure

```
Student-management-system-cpp/
│
├── main.cpp          # Main source code
├── README.md         # Project documentation
└── .gitignore        # Ignores generated data files
```

---

## 📸 Menu Preview

```
  ╔══════════════════════════════════════════╗
  ║      STUDENT MANAGEMENT SYSTEM          ║
  ╚══════════════════════════════════════════╝

       1.  Add Student
       2.  Display All Students
       3.  Search Student
       4.  Update Student
       5.  Delete Student
       6.  Exit
```

---

## 📝 Expected Outcome

A functional application that allows users to add, update, delete, and display student information with persistent data storage for reliable record management.

---

## 👨‍💻 Author

Developed by **ARULSELVAN** as part of the Thiranex Internship Program.
