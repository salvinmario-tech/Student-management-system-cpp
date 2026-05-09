#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;

    void addStudent();
    void displayStudents();
    void searchStudent();
    void updateStudent();
    void deleteStudent();
};

void Student::addStudent() {
    ofstream file("students.txt", ios::app);

    cout << "Enter Student ID: ";
    cin >> id;

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, name);

    cout << "Enter Student Age: ";
    cin >> age;

    file << id << " " << name << " " << age << endl;

    file.close();

    cout << "
Student Added Successfully!
";
}

void Student::displayStudents() {
    ifstream file("students.txt");

    cout << "
===== Student Records =====
";

    while(file >> id >> name >> age) {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Age: " << age << endl;
    }

    file.close();
}

void Student::searchStudent() {
    ifstream file("students.txt");

    int searchId;
    bool found = false;

    cout << "Enter Student ID to Search: ";
    cin >> searchId;

    while(file >> id >> name >> age) {
        if(id == searchId) {
            cout << "
Student Found:
";
            cout << "ID: " << id
                 << " | Name: " << name
                 << " | Age: " << age << endl;
            found = true;
        }
    }

    if(!found)
        cout << "Student Not Found!
";

    file.close();
}

void Student::updateStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int updateId;
    bool found = false;

    cout << "Enter Student ID to Update: ";
    cin >> updateId;

    while(file >> id >> name >> age) {
        if(id == updateId) {
            found = true;

            cout << "Enter New Name: ";
            cin >> name;

            cout << "Enter New Age: ";
            cin >> age;
        }

        temp << id << " " << name << " " << age << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        cout << "Student Updated Successfully!
";
    else
        cout << "Student Not Found!
";
}

void Student::deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int deleteId;
    bool found = false;

    cout << "Enter Student ID to Delete: ";
    cin >> deleteId;

    while(file >> id >> name >> age) {
        if(id != deleteId) {
            temp << id << " " << name << " " << age << endl;
        }
        else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        cout << "Student Deleted Successfully!
";
    else
        cout << "Student Not Found!
";
}

int main() {
    Student s;
    int choice;

    do {
        cout << "
===== STUDENT MANAGEMENT SYSTEM =====
";
        cout << "1. Add Student
";
        cout << "2. Display Students
";
        cout << "3. Search Student
";
        cout << "4. Update Student
";
        cout << "5. Delete Student
";
        cout << "6. Exit
";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                s.addStudent();
                break;

            case 2:
                s.displayStudents();
                break;

            case 3:
                s.searchStudent();
                break;

            case 4:
                s.updateStudent();
                break;

            case 5:
                s.deleteStudent();
                break;

            case 6:
                cout << "Exiting Program...
";
                break;

            default:
                cout << "Invalid Choice!
";
        }

    } while(choice != 6);

    return 0;
}
