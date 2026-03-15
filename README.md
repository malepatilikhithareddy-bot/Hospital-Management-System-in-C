# Hospital Management System (C)

A console-based **Hospital Management System** developed using the **C programming language**.  
This project manages hospital operations such as patient records, medical history, employee data, payments, and admissions through a menu-driven interface.

---

## Project Description

The Hospital Management System is designed to manage hospital information efficiently.  
It allows users to:

- Register patients
- Store medical records
- Track medicine payments
- Manage employee information
- Admit patients to hospital rooms
- View medicines available in the medical store

The program uses **structures, pointers, arrays, and dynamic memory allocation** in C.

---

## Features

### Patient Management
- Add new patient records
- Validate patient details (name, blood group, phone number)
- Store patient information including:
  - Registration number
  - Name
  - Age
  - Gender
  - Blood group
  - Phone number
  - Date of birth

### Medical Records
- Insert medical records for patients
- Store disease information
- Suggest doctors based on disease type
- Maintain medical descriptions

### Payment Management
- Add medicine payment records
- Record payment amount and date
- Display payment history of patients

### Patient Admission
- Admit patients based on disease
- Automatically assign room numbers

### Employee Management
- Add hospital employees
- Store employee details including:
  - Employee ID
  - Name
  - Role
  - Salary
  - Date of joining
  - Experience
  - Employment type
- Delete employee records

### Medical Store
Displays a list of available medicines and their prices.

---

## Technologies Used

- C Programming
- Structures
- Pointers
- Dynamic Memory Allocation
- Arrays
- Input Validation
- Menu Driven Interface

---

## Project Structure

```
Hospital-Management-System-C
│
├── hospital_management.c
└── README.md
```

---

## How to Compile and Run

### Compile the program

```bash
gcc hospital_management.c -o hospital
```

### Run the program

```bash
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

- Add file handling for permanent data storage
- Add search functionality for patients
- Add billing system
- Add login authentication
- Create graphical user interface
- Connect to database (MySQL/SQLite)

---

## Author

Likhitha Reddy.M

---

## License

This project is developed for educational and learning purposes.
