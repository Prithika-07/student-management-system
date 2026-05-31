# Student Management System

A console-based **Student Management System** built in **C++** that efficiently manages student records using **file handling** and **menu-driven operations**.

---

## Features

- **Add** new student records (auto-incremented ID)
- **Display** all students in a formatted table
- **Search** a student by ID
- **Update** student information (name, age, course, GPA)
- **Delete** a student with confirmation prompt
- **Persistent storage** — all data is saved to `students.dat`

---

## How to Compile & Run

### On Linux / macOS
```bash
g++ -o student_management student_management.cpp
./student_management
```

### On Windows (MinGW / g++)
```bash
g++ -o student_management.exe student_management.cpp
student_management.exe
```

### On Windows (MSVC)
```bash
cl student_management.cpp
student_management.exe
```

---

## Menu Options

| Option | Description |
|--------|-------------|
| 1 | Add a new student |
| 2 | Display all students |
| 3 | Search student by ID |
| 4 | Update student details |
| 5 | Delete a student |
| 6 | Exit |

---

## File Structure

```
student_management.cpp   → Main source code
students.dat             → Auto-created data file (persistent storage)
README.md                → Project documentation
```

---

## Technologies Used

- **Language:** C++
- **Concepts:** File I/O, Structs, Vectors, Menu-driven programming

---

## Author

Your Name — [Your GitHub Profile](https://github.com/yourusername)
