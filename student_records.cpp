#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

// Student class
class Student {
public:
    int rollNo;
    string name;
    string branch;
    float cgpa;

    Student(int r, string n, string b, float c)
        : rollNo(r), name(n), branch(b), cgpa(c) {}

    void display() const {
        cout << left << setw(10) << rollNo
             << setw(25) << name
             << setw(25) << branch
             << right << setw(6) << fixed << setprecision(2)
             << cgpa << "\n";
    }
};

vector<Student> records;

// Load student records from file 
// (create file if missing)
void loadFromFile() {
    ifstream file("records.txt");

    if (!file) {
        ofstream newFile("records.txt"); 
        newFile.close();
        return;
    }

    int roll;
    string name, branch;
    float cgpa;

    while (file >> roll) {
        file.ignore(); 
        getline(file, name);
        getline(file, branch);
        file >> cgpa;
        file.ignore(); 
        records.emplace_back(roll, name, branch, cgpa);
    }

    file.close();
}

// Save student records to file
void saveToFile() {
    ofstream file("records.txt");

    for (const auto& s : records) {
        file << s.rollNo << "\n"
             << s.name << "\n"
             << s.branch << "\n"
             << s.cgpa << "\n";
    }

    file.close();
}

// Add student
void addStudent() {
    int roll;
    string name, branch;
    float cgpa;

    cout << "\nAdd Student\n";
    cout << "------------------------------\n";
    cout << "Enter Roll No: ";
    cin >> roll;
    cin.ignore(); 

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Branch: ";
    getline(cin, branch);

    cout << "Enter CGPA: ";
    cin >> cgpa;

    records.emplace_back(roll, name, branch, cgpa);
    cout << "Student added successfully!\n";
}

// Delete student
void deleteStudent() {
    int roll;
    cout << "\nDelete Student\n";
    cout << "------------------------------\n";
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    auto it = remove_if(records.begin(), records.end(),
                        [roll](const Student& s) { return s.rollNo == roll; });

    if (it != records.end()) {
        records.erase(it, records.end());
        cout << "Student deleted successfully!\n";
    } else {
        cout << "Student not found.\n";
    }
}

// Search student
void searchStudent() {
    int roll;
    cout << "\nSearch Student\n";
    cout << "------------------------------\n";
    cout << "Enter Roll No to search: ";
    cin >> roll;

    for (const auto& s : records) {
        if (s.rollNo == roll) {
            cout << "\nStudent Details\n";
            cout << "---------------------------------------------------------------\n";
            cout << left << setw(10) << "Roll No"
                 << setw(25) << "Name"
                 << setw(25) << "Branch"
                 << right << setw(6) << "CGPA\n";
            cout << "---------------------------------------------------------------\n";
            s.display();
            return;
        }
    }

    cout << "Student not found.\n";
}

// List all students
void listStudents() {
    cout << "\nAll Student Records\n";
    cout << "--------------------------------------------------------------------------\n";

    if (records.empty()) {
        cout << "No records available.\n";
        return;
    }

    sort(records.begin(), records.end(),
         [](const Student& a, const Student& b) {
             return a.rollNo < b.rollNo;
         });

    cout << left << setw(10) << "Roll No"
         << setw(25) << "Name"
         << setw(25) << "Branch"
         << right << setw(6) << "CGPA\n";
    cout << "--------------------------------------------------------------------------\n";

    for (const auto& s : records) s.display();
}

// Main program
int main() {
    loadFromFile();

    int choice;
    do {
        cout << "\n======================================\n";
        cout << "  Student Record Management System\n";
        cout << "======================================\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Search Student\n";
        cout << "4. List All Students\n";
        cout << "5. Exit\n";
        cout << "--------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: searchStudent(); break;
            case 4: listStudents(); break;
            case 5: saveToFile(); break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    cout << "\nThank you for using the system!\n";
    return 0;
}
