# Hospital Management System (C)

A console-based **Hospital Management System** developed using the **C programming language**.  
This project manages hospital operations such as patient records, employee data, payments, and patient admissions through a menu-driven interface.

---

## Repository Structure

```
Hospital-Management-System
│
├── Hospital management c file   # Source code of the program
├── c_project.exe                # Executable file to run the program directly
└── README.md                    # Project documentation
```

---

## Project Description

This system simulates basic hospital management functionality.  
It allows users to manage hospital data efficiently using a simple command-line interface.

The program includes features such as:

- Patient registration
- Medical record management
- Medicine payment tracking
- Employee management
- Patient admission system
- Medical store display

The implementation uses **C structures, arrays, pointers, and dynamic memory allocation**.

---

## Features

### Patient Management
- Add new patients
- Store patient information including registration number, name, age, gender, blood group, phone number, and date of birth
- Display patient records

### Medical Records
- Insert medical records for patients
- Store disease description
- Suggest doctor based on disease type

### Payment Management
- Record payments for medicines
- Store payment date and amount
- Display payment history

### Patient Admission
- Admit patients based on disease
- Automatically assign hospital rooms

### Employee Management
- Add employee details
- Store employee information such as ID, role, salary, and experience
- Delete employee records

### Medical Store
Displays available medicines and their prices.

---

## How to Run the Program

### Method 1: Run Executable File

You can directly run the program using the provided executable file:

```
c_project.exe
```

This will open the console application and display the hospital management menu.

---

### Method 2: Compile the Source Code

If you want to compile the program yourself:

Compile the program:

```
gcc "hospital_management" -o hospital
```

Run the program:

```
./hospital
```

---

## Example Menu

```
HOSPITAL MANAGEMENT SYSTEM

1. Patient Record
2. Employee Record
3. View Medical Store
4. Exit
```

---

## Future Improvements

Possible improvements for this project:

- File handling for permanent data storage
- Database integration
- Search functionality for patients and employees
- Billing system
- Graphical User Interface (GUI)

---

## Author

M.Likhitha Reddy
---

## License

This project is created for educational and learning purposes.
