#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// ─────────────────────────────────────────────
//  Student Structure
// ─────────────────────────────────────────────
struct Student {
    int    id;
    char   name[50];
    char   department[30];
    float  cgpa;
    long long phone;
};

const string FILE_NAME = "students.dat";

// ─────────────────────────────────────────────
//  Utility helpers
// ─────────────────────────────────────────────
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void printHeader(const string& title) {
    cout << "\n  ╔══════════════════════════════════════════╗\n";
    cout << "  ║   " << left << setw(41) << title << "║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
}

void printTableHeader() {
    cout << "  " << string(72, '-') << "\n";
    cout << "  " << left
         << setw(6)  << "ID"
         << setw(20) << "Name"
         << setw(16) << "Department"
         << setw(8)  << "CGPA"
         << setw(14) << "Phone"
         << "\n";
    cout << "  " << string(72, '-') << "\n";
}

void printStudent(const Student& s) {
    cout << "  " << left
         << setw(6)  << s.id
         << setw(20) << s.name
         << setw(16) << s.department
         << setw(8)  << fixed << setprecision(2) << s.cgpa
         << setw(14) << s.phone
         << "\n";
}

bool idExists(int id) {
    ifstream fin(FILE_NAME, ios::binary);
    Student s;
    while (fin.read(reinterpret_cast<char*>(&s), sizeof(s)))
        if (s.id == id) { fin.close(); return true; }
    fin.close();
    return false;
}

// ─────────────────────────────────────────────
//  1. ADD STUDENT
// ─────────────────────────────────────────────
void addStudent() {
    clearScreen();
    printHeader("ADD NEW STUDENT");

    Student s;

    cout << "  Enter Student ID     : ";
    cin  >> s.id;

    if (idExists(s.id)) {
        cout << "\n  ✖  A student with ID " << s.id << " already exists!\n";
        pause(); return;
    }

    cin.ignore();
    cout << "  Enter Name           : "; cin.getline(s.name, 50);
    cout << "  Enter Department     : "; cin.getline(s.department, 30);

    cout << "  Enter CGPA (0-10)    : ";
    while (!(cin >> s.cgpa) || s.cgpa < 0 || s.cgpa > 10) {
        cout << "  Invalid! Enter CGPA between 0 and 10: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "  Enter Phone Number   : ";
    cin >> s.phone;

    ofstream fout(FILE_NAME, ios::binary | ios::app);
    fout.write(reinterpret_cast<char*>(&s), sizeof(s));
    fout.close();

    cout << "\n  ✔  Student added successfully!\n";
    pause();
}

// ─────────────────────────────────────────────
//  2. DISPLAY ALL STUDENTS
// ─────────────────────────────────────────────
void displayAll() {
    clearScreen();
    printHeader("ALL STUDENT RECORDS");

    ifstream fin(FILE_NAME, ios::binary);
    if (!fin) { cout << "  No records found.\n"; pause(); return; }

    Student s;
    int count = 0;
    printTableHeader();

    while (fin.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        printStudent(s);
        count++;
    }
    fin.close();

    cout << "  " << string(72, '-') << "\n";
    if (count == 0) cout << "  No student records found.\n";
    else cout << "  Total Records: " << count << "\n";
    pause();
}

// ─────────────────────────────────────────────
//  3. SEARCH STUDENT
// ─────────────────────────────────────────────
void searchStudent() {
    clearScreen();
    printHeader("SEARCH STUDENT");

    int id;
    cout << "  Enter Student ID to search: ";
    cin  >> id;

    ifstream fin(FILE_NAME, ios::binary);
    if (!fin) { cout << "\n  No records found.\n"; pause(); return; }

    Student s;
    bool found = false;

    while (fin.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == id) {
            found = true;
            cout << "\n  ─── Student Found ───────────────────────\n";
            cout << "  ID         : " << s.id         << "\n";
            cout << "  Name       : " << s.name       << "\n";
            cout << "  Department : " << s.department << "\n";
            cout << "  CGPA       : " << fixed << setprecision(2) << s.cgpa << "\n";
            cout << "  Phone      : " << s.phone      << "\n";
            cout << "  ─────────────────────────────────────────\n";
            break;
        }
    }
    fin.close();

    if (!found) cout << "\n  ✖  Student with ID " << id << " not found.\n";
    pause();
}

// ─────────────────────────────────────────────
//  4. UPDATE STUDENT
// ─────────────────────────────────────────────
void updateStudent() {
    clearScreen();
    printHeader("UPDATE STUDENT RECORD");

    int id;
    cout << "  Enter Student ID to update: ";
    cin  >> id;

    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    if (!file) { cout << "\n  No records found.\n"; pause(); return; }

    Student s;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == id) {
            found = true;
            cout << "\n  Current record:\n";
            printTableHeader();
            printStudent(s);
            cout << "  " << string(72, '-') << "\n\n";

            cin.ignore();
            cout << "  New Name           : "; cin.getline(s.name, 50);
            cout << "  New Department     : "; cin.getline(s.department, 30);

            cout << "  New CGPA (0-10)    : ";
            while (!(cin >> s.cgpa) || s.cgpa < 0 || s.cgpa > 10) {
                cout << "  Invalid! Enter CGPA between 0 and 10: ";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "  New Phone Number   : ";
            cin  >> s.phone;

            // Seek back one record and overwrite
            file.seekp(-static_cast<int>(sizeof(s)), ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(s));

            cout << "\n  ✔  Student record updated successfully!\n";
            break;
        }
    }
    file.close();

    if (!found) cout << "\n  ✖  Student with ID " << id << " not found.\n";
    pause();
}

// ─────────────────────────────────────────────
//  5. DELETE STUDENT
// ─────────────────────────────────────────────
void deleteStudent() {
    clearScreen();
    printHeader("DELETE STUDENT RECORD");

    int id;
    cout << "  Enter Student ID to delete: ";
    cin  >> id;

    ifstream fin(FILE_NAME, ios::binary);
    if (!fin) { cout << "\n  No records found.\n"; pause(); return; }

    ofstream fout("temp.dat", ios::binary);
    Student s;
    bool found = false;

    while (fin.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.id == id) { found = true; continue; }   // skip deleted record
        fout.write(reinterpret_cast<char*>(&s), sizeof(s));
    }
    fin.close();
    fout.close();

    remove(FILE_NAME.c_str());
    rename("temp.dat", FILE_NAME.c_str());

    if (found) cout << "\n  ✔  Student with ID " << id << " deleted successfully!\n";
    else        cout << "\n  ✖  Student with ID " << id << " not found.\n";
    pause();
}

// ─────────────────────────────────────────────
//  MAIN MENU
// ─────────────────────────────────────────────
void showMenu() {
    clearScreen();
    cout << "\n  ╔══════════════════════════════════════════╗\n";
    cout << "  ║      STUDENT MANAGEMENT SYSTEM           ║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
    cout << "       1.  Add Student\n";
    cout << "       2.  Display All Students\n";
    cout << "       3.  Search Student\n";
    cout << "       4.  Update Student\n";
    cout << "       5.  Delete Student\n";
    cout << "       6.  Exit\n\n";
    cout << "  Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();
        while (!(cin >> choice)) {
            cout << "  Invalid input. Enter a number: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: addStudent();    break;
            case 2: displayAll();    break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                clearScreen();
                cout << "\n  Thank you for using Student Management System!\n\n";
                break;
            default:
                cout << "\n  ✖  Invalid choice! Please enter 1-6.\n";
                pause();
        }
    } while (choice != 6);

    return 0;
}
