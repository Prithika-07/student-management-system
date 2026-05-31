#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// ─────────────────────────────────────────
//  Student Structure
// ─────────────────────────────────────────
struct Student {
    int    id;
    string name;
    int    age;
    string course;
    float  gpa;
};

const string FILE_NAME = "students.dat";

// ─────────────────────────────────────────
//  Helper: Load all students from file
// ─────────────────────────────────────────
vector<Student> loadAll() {
    vector<Student> list;
    ifstream fin(FILE_NAME);
    if (!fin.is_open()) return list;

    Student s;
    while (fin >> s.id >> ws) {
        getline(fin, s.name);
        fin >> s.age >> ws;
        getline(fin, s.course);
        fin >> s.gpa;
        fin.ignore();
        list.push_back(s);
    }
    fin.close();
    return list;
}

// ─────────────────────────────────────────
//  Helper: Save all students to file
// ─────────────────────────────────────────
void saveAll(const vector<Student>& list) {
    ofstream fout(FILE_NAME, ios::trunc);
    for (const auto& s : list) {
        fout << s.id   << "\n"
             << s.name << "\n"
             << s.age  << "\n"
             << s.course << "\n"
             << fixed << setprecision(2) << s.gpa << "\n";
    }
    fout.close();
}

// ─────────────────────────────────────────
//  Helper: Print a single student row
// ─────────────────────────────────────────
void printHeader() {
    cout << "\n" << string(65, '-') << "\n";
    cout << left
         << setw(6)  << "ID"
         << setw(20) << "Name"
         << setw(5)  << "Age"
         << setw(20) << "Course"
         << setw(6)  << "GPA"
         << "\n";
    cout << string(65, '-') << "\n";
}

void printStudent(const Student& s) {
    cout << left
         << setw(6)  << s.id
         << setw(20) << s.name
         << setw(5)  << s.age
         << setw(20) << s.course
         << fixed << setprecision(2) << s.gpa
         << "\n";
}

// ─────────────────────────────────────────
//  1. ADD Student
// ─────────────────────────────────────────
void addStudent() {
    vector<Student> list = loadAll();

    Student s;
    // Auto-generate ID
    int maxId = 0;
    for (auto& x : list) if (x.id > maxId) maxId = x.id;
    s.id = maxId + 1;

    cin.ignore();
    cout << "\n--- Add New Student ---\n";
    cout << "Name   : "; getline(cin, s.name);
    cout << "Age    : "; cin >> s.age;
    cin.ignore();
    cout << "Course : "; getline(cin, s.course);
    cout << "GPA    : "; cin >> s.gpa;

    list.push_back(s);
    saveAll(list);

    cout << "\n[SUCCESS] Student added with ID: " << s.id << "\n";
}

// ─────────────────────────────────────────
//  2. DISPLAY All Students
// ─────────────────────────────────────────
void displayAll() {
    vector<Student> list = loadAll();
    if (list.empty()) {
        cout << "\n[INFO] No student records found.\n";
        return;
    }
    printHeader();
    for (auto& s : list) printStudent(s);
    cout << string(65, '-') << "\n";
    cout << "Total students: " << list.size() << "\n";
}

// ─────────────────────────────────────────
//  3. SEARCH Student by ID
// ─────────────────────────────────────────
void searchStudent() {
    int id;
    cout << "\nEnter Student ID to search: "; cin >> id;

    vector<Student> list = loadAll();
    for (auto& s : list) {
        if (s.id == id) {
            printHeader();
            printStudent(s);
            cout << string(65, '-') << "\n";
            return;
        }
    }
    cout << "\n[NOT FOUND] No student with ID " << id << ".\n";
}

// ─────────────────────────────────────────
//  4. UPDATE Student
// ─────────────────────────────────────────
void updateStudent() {
    int id;
    cout << "\nEnter Student ID to update: "; cin >> id;

    vector<Student> list = loadAll();
    for (auto& s : list) {
        if (s.id == id) {
            cin.ignore();
            cout << "\nLeave blank and press Enter to keep current value.\n";

            string tmp;
            cout << "New Name   [" << s.name   << "]: "; getline(cin, tmp);
            if (!tmp.empty()) s.name = tmp;

            cout << "New Age    [" << s.age    << "]: "; getline(cin, tmp);
            if (!tmp.empty()) s.age = stoi(tmp);

            cout << "New Course [" << s.course << "]: "; getline(cin, tmp);
            if (!tmp.empty()) s.course = tmp;

            cout << "New GPA    [" << s.gpa    << "]: "; getline(cin, tmp);
            if (!tmp.empty()) s.gpa = stof(tmp);

            saveAll(list);
            cout << "\n[SUCCESS] Student ID " << id << " updated.\n";
            return;
        }
    }
    cout << "\n[NOT FOUND] No student with ID " << id << ".\n";
}

// ─────────────────────────────────────────
//  5. DELETE Student
// ─────────────────────────────────────────
void deleteStudent() {
    int id;
    cout << "\nEnter Student ID to delete: "; cin >> id;

    vector<Student> list = loadAll();
    auto it = remove_if(list.begin(), list.end(),
                        [id](const Student& s){ return s.id == id; });

    if (it == list.end()) {
        cout << "\n[NOT FOUND] No student with ID " << id << ".\n";
        return;
    }

    char confirm;
    cout << "Are you sure you want to delete Student ID " << id << "? (y/n): ";
    cin >> confirm;
    if (tolower(confirm) != 'y') {
        cout << "[CANCELLED] Delete operation cancelled.\n";
        return;
    }

    list.erase(it, list.end());
    saveAll(list);
    cout << "\n[SUCCESS] Student ID " << id << " deleted.\n";
}

// ─────────────────────────────────────────
//  Menu
// ─────────────────────────────────────────
void showMenu() {
    cout << "\n╔══════════════════════════════════╗\n";
    cout <<   "║   STUDENT MANAGEMENT SYSTEM      ║\n";
    cout <<   "╠══════════════════════════════════╣\n";
    cout <<   "║  1. Add Student                  ║\n";
    cout <<   "║  2. Display All Students         ║\n";
    cout <<   "║  3. Search Student by ID         ║\n";
    cout <<   "║  4. Update Student               ║\n";
    cout <<   "║  5. Delete Student               ║\n";
    cout <<   "║  6. Exit                         ║\n";
    cout <<   "╚══════════════════════════════════╝\n";
    cout <<   "Enter your choice: ";
}

// ─────────────────────────────────────────
//  Main
// ─────────────────────────────────────────
int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addStudent();    break;
            case 2: displayAll();    break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "\nGoodbye!\n"; break;
            default: cout << "\n[ERROR] Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
