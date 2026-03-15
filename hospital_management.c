#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_PATIENTS 50
#define MAX_RECORDS 5
#define MAX_NAME_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100
#define MAX_PAYMENTS 10

const char *valid_blood_groups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

struct Payment {
    char medicine[MAX_DESCRIPTION_LENGTH];
    double amount;
    char date[11];
};

struct patient {
    char regn[20];
    char name[MAX_NAME_LENGTH];
    char fname[MAX_NAME_LENGTH]; // Guardian's name
    char gender;
    char bg[5];
    int age;
    char ph[12]; // Changed to allow only 10-digit phone numbers
    char dob[11]; // Added date of birth field
};

struct Record {
    char description[MAX_DESCRIPTION_LENGTH];
    char disease[MAX_DESCRIPTION_LENGTH];
    char doctor[30];
    double doctor_payment;
    struct Payment *payments[MAX_PAYMENTS];
    int payment_count;
};

struct employee {
    char id[20];
    char name[30];
    char role[30];
    double salary;
    char date_of_joining[11];
    int experience_years;
    char employment_type[20];
    union {
        char ward_number[10]; // For specialist
        char cabin_specialist[30]; // For cabin
    };
};

struct HospitalManagementSystem {
    struct patient *patients[MAX_PATIENTS];
    struct Record *records[MAX_PATIENTS][MAX_RECORDS];
    int patient_count;
    struct employee *employees[MAX_PATIENTS];
    int employee_count;
};

void menu(struct HospitalManagementSystem *hms);
void patient_menu(struct HospitalManagementSystem *hms);
void employee_menu(struct HospitalManagementSystem *hms);
void add_patient(struct HospitalManagementSystem *hms);
void insert_record(struct HospitalManagementSystem *hms);

void display_patients(struct HospitalManagementSystem *hms);
void add_payment(struct HospitalManagementSystem *hms);
void display_payment_history(struct HospitalManagementSystem *hms, int patient_index);
void view_medical_shop();
void add_employee(struct HospitalManagementSystem *hms);
void delete_employee(struct HospitalManagementSystem *hms);
void admit_patient(struct HospitalManagementSystem *hms);

int main() {
    struct HospitalManagementSystem hms;
    hms.patient_count = 0;
    hms.employee_count = 0;

    menu(&hms);

    return 0;
}
void menu(struct HospitalManagementSystem *hms) {
    char choice;
    while (1) {
        printf("\n\t*HOSPITAL MANAGEMENT SYSTEM*\n");
        printf("\n\t1. Patient Record\n\t2. Employee Record\n\t3. View Medical Store\n\t4. Exit\n");
        printf("\nEnter your choice: ");
        fflush(stdin);
        choice = getchar();
        switch (choice) {
            case '1':
                patient_menu(hms);
                break;
            case '2':
                employee_menu(hms);
                break;
            case '3':
                view_medical_shop(); // Call the function to display medical store
                // Clear input buffer
                while (getchar() != '\n');
                break;
            case '4':
                printf("\nExiting program.\n");
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
                // Clear input buffer
                while (getchar() != '\n');
                break;
        }
    }
}




void patient_menu(struct HospitalManagementSystem *hms) {
    char choice;
    while (1) {
        printf("\n\t*PATIENT DATABASE MANAGEMENT*\n");
        printf("\n\t1. Add New Patient\n\t2. Insert Medical Record\n\t3. Display All Records\n\t4. Add Payment\n\t5. Display Payment History\n\t6. Admit Patient\n\t7. Exit to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);  // Notice the space before %c to consume leading whitespaces

        // Clear input buffer
        while (getchar() != '\n');

        switch (choice) {
            case '1':
                add_patient(hms);
                break;
            case '2':
                insert_record(hms);
                break;
           
            case '3':
                display_patients(hms);
                break;
            case '4':
                add_payment(hms);
                break;
            case '5':
                if (hms->patient_count > 0)
                    display_payment_history(hms, hms->patient_count - 1);
                else
                    printf("No patients in the database.\n");
                break;
            case '6':
                admit_patient(hms);
                break;
            case '7':
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    }
}

bool is_valid_name(const char *name) {
    while (*name) {
        if (!isalpha(*name) && *name != ' ' && *name != '-' && *name != '\'')
            return false;
        name++;
    }
    return true;
}
bool is_valid_blood_group(const char *blood_group) {
    for (int i = 0; i < sizeof(valid_blood_groups) / sizeof(valid_blood_groups[0]); i++) {
        if (strcmp(valid_blood_groups[i], blood_group) == 0) {
            return true;
        }
    }
    return false;
}
bool is_valid_phone_number(const char *phone_number) {
    int digit_count = 0;
    while (*phone_number) {
        if (isdigit(*phone_number)) {
            digit_count++;
        }
        phone_number++;
    }
    return digit_count == 10; // Return true if exactly 10 digits, false otherwise
}



void add_patient(struct HospitalManagementSystem *hms) {
    if (hms->patient_count >= MAX_PATIENTS) {
        printf("\nHospital is full. Cannot add more patients.\n");
        return;
    }

    struct patient *new_patient = (struct patient *)malloc(sizeof(struct patient));
    if (new_patient == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }

    printf("\nEnter the Registration Number of the patient (must start with 23 and only integer values): ");
    while (1) {
        scanf("%s", new_patient->regn);

        // Check if registration number starts with 23 and only contains digits 
        if (strlen(new_patient->regn) > 0 && new_patient->regn[0] == '2' && new_patient->regn[1] == '3') {
            int i;
            for (i = 2; i < strlen(new_patient->regn); i++) {
                if (!isdigit(new_patient->regn[i])) {
                    printf("Invalid registration number. Must start with 23 and only contain digits. Enter again: ");
                    continue;
                }
            }
            if (i == strlen(new_patient->regn)) {
                printf("Registration number is valid.\n");
                break;
            }
        } else {
            printf("Invalid registration number. Must start with 23 and only contain digits. Enter again: ");
        }
    }

    printf("Enter the name of the patient: ");
    while (1) {
        scanf("%s", new_patient->name);
        if (!is_valid_name(new_patient->name)) {
            printf("Invalid name. Name can only contain alphabets or special characters (space, hyphen, apostrophe).\n");
            printf("Enter the name of the patient again: ");
        } else {
            break;
        }
    }

    do {
        printf("Enter the age of the patient (only integer values): ");
        scanf("%d", &new_patient->age);

        if (new_patient->age < 0) {
            printf("Invalid age. Please enter a non-negative integer.\n");
        } else if (new_patient->age < 18) {
            printf("Enter the name of the Guardian: ");
            scanf("%s", new_patient->fname);
        }
    } while (new_patient->age < 0);

    do {
        printf("Enter the gender of the patient (M/male or F/female): ");
        scanf(" %c", &new_patient->gender);

        if (new_patient->gender != 'M' && new_patient->gender != 'F') {
            printf("Invalid gender. Please enter M/male or F/female.\n");
        }
    } while (new_patient->gender != 'M' && new_patient->gender != 'F');

    printf("Enter the blood group of the patient: ");
     while (1) {
        scanf("%s", new_patient->bg);
        if (!is_valid_blood_group(new_patient->bg)) {
            printf("Invalid blood group. Please enter a valid blood group (e.g., A+, B-, AB+, O-).\n");
            printf("Enter the blood group of the patient again: ");
        } else {
            break;
        }
    }

    printf("Enter the phone number of the patient (only 10-digit values): ");
    while (1) {
        scanf("%s", new_patient->ph);
        if (!is_valid_phone_number(new_patient->ph)) {
            printf("Invalid phone number. Please enter exactly 10 digits.\n");
            printf("Enter the phone number of the patient again: ");
        } else {
            break;
        }
    }
    printf("Enter the date of birth of the patient (format: dd/mm/yyyy): ");
    scanf("%s", new_patient->dob);

    hms->patients[hms->patient_count++] = new_patient;
    printf("Patient added successfully.\n");
}


// Modify the insert_record function
void insert_record(struct HospitalManagementSystem *hms) {
    char reg[20];
    int i;

    printf("\nEnter the Registration Number of the patient: ");
    scanf("%s", reg);

    for (i = 0; i < hms->patient_count; i++) {
        if (strcmp(hms->patients[i]->regn, reg) == 0) {
            break;
        }
    }

    if (i < hms->patient_count) {
        if (hms->records[i][0] == NULL) {
            hms->records[i][0] = (struct Record *)malloc(sizeof(struct Record));
            if (hms->records[i][0] == NULL) {
                printf("\nMemory allocation failed.\n");
                return;
            }
        }

        printf("Enter record description: ");
        scanf(" %[^\n]s", hms->records[i][0]->description);
        printf("Enter type of disease: ");
        scanf(" %[^\n]s", hms->records[i][0]->disease);

        // Suggesting doctor based on disease
        if (strcmp(hms->records[i][0]->disease, "") != 0) {
            if (strcmp(hms->records[i][0]->disease, "malaria") == 0) {
                strcpy(hms->records[i][0]->doctor, "Dr. Ravi");
                hms->records[i][0]->doctor_payment = 500.00;
            } else if (strcmp(hms->records[i][0]->disease, "dengue") == 0) {
                strcpy(hms->records[i][0]->doctor, "Dr. Suresh");
                hms->records[i][0]->doctor_payment = 800.00;
            } // Add similar cases for other diseases
            else {
                // Default doctor suggestion for any other disease
                strcpy(hms->records[i][0]->doctor, "Dr. Unknown");
                hms->records[i][0]->doctor_payment = 400.00; // You can set a default payment here
            }

            printf("Suggested Doctor: %s\n", hms->records[i][0]->doctor); // Display suggested doctor
        } else {
            printf("No disease specified.\n");
        }
    } else {
        printf("Invalid registration number.\n");
    }
}

void display_patients(struct HospitalManagementSystem *hms) {
    if (hms->patient_count == 0) {
        printf("No patients in the database.\n");
        return;
    }

    printf("\n\t*PATIENT RECORDS*\n");
    printf("\nRegistration Number\tName\t\tAge\tGender\tBlood Group\tPhone Number\tDate of Birth\n");
    for (int i = 0; i < hms->patient_count; i++) {
        printf("%s\t\t%s\t\t%d\t%c\t%s\t%s\t%s\n", hms->patients[i]->regn, hms->patients[i]->name,
               hms->patients[i]->age, hms->patients[i]->gender, hms->patients[i]->bg, hms->patients[i]->ph,
               hms->patients[i]->dob);
    }
}

void add_payment(struct HospitalManagementSystem *hms) {
    char reg[20];
    int i, j;

    printf("\nEnter the Registration Number of the patient: ");
    scanf("%s", reg);

    for (i = 0; i < hms->patient_count; i++) {
        if (strcmp(hms->patients[i]->regn, reg) == 0) {
            break;
        }
    }

    if (i < hms->patient_count) {
        if (hms->records[i][0] == NULL) {
            printf("\nNo records found for this patient. Please insert a record first.\n");
            return;
        }

        char medicine[MAX_DESCRIPTION_LENGTH];
        double amount;

        printf("\nEnter the medicines and their payment amounts (enter 'done' when finished):\n");
        while (1) {
            printf("Medicine: ");
            scanf("%s", medicine);

            if (strcmp(medicine, "done") == 0) {
                break;
            }

            printf("Amount (Rs.): ");
            scanf("%lf", &amount);

            if (hms->records[i][0]->payment_count < MAX_PAYMENTS) {
                hms->records[i][0]->payments[hms->records[i][0]->payment_count] =
                    (struct Payment *)malloc(sizeof(struct Payment));
                if (hms->records[i][0]->payments[hms->records[i][0]->payment_count] != NULL) {
                    strcpy(hms->records[i][0]->payments[hms->records[i][0]->payment_count]->medicine, medicine);
                    hms->records[i][0]->payments[hms->records[i][0]->payment_count]->amount = amount;
                    printf("Date (format: dd/mm/yyyy): ");
                    scanf("%s", hms->records[i][0]->payments[hms->records[i][0]->payment_count]->date);
                    hms->records[i][0]->payment_count++;
                } else {
                    printf("\nMemory allocation failed.\n");
                    return;
                }
            } else {
                printf("\nMaximum payment records reached.\n");
                break;
            }
        }
        printf("Payments added successfully.\n");
    } else {
        printf("Invalid registration number.\n");
    }
}

void display_payment_history(struct HospitalManagementSystem *hms, int patient_index) {
    if (hms->records[patient_index][0] == NULL || hms->records[patient_index][0]->payment_count == 0) {
        printf("No payment records found for this patient.\n");
        return;
    }

    printf("\n\t*PAYMENT HISTORY*\n");
    printf("\nMedicine\tAmount (Rs.)\tDate\n");
    for (int i = 0; i < hms->records[patient_index][0]->payment_count; i++) {
        printf("%s\t%.2lf\t%s\n", hms->records[patient_index][0]->payments[i]->medicine,
               hms->records[patient_index][0]->payments[i]->amount,
               hms->records[patient_index][0]->payments[i]->date);
    }
}

void employee_menu(struct HospitalManagementSystem *hms) {
    char choice;
    while (1) {
        printf("\n\t*EMPLOYEE DATABASE MANAGEMENT*\n");
        printf("\n\t1. Add New Employee\n\t2. Delete Employee\n\t3. Exit to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);

        // Clear input buffer
        while (getchar() != '\n');

        switch (choice) {
            case '1':
                add_employee(hms);
                break;
            case '2':
                delete_employee(hms);
                break;
            case '3':
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    }
}

bool is_valid_integer_salary(int salary) {
    return salary >= 10000 && salary <= 1000000;
}

bool is_valid_double_salary(double salary) {
    return salary >= 10000 && salary <= 1000000;
}
bool is_valid_employee_name(const char *name) {
    while (*name) {
        if (!isalpha(*name) && *name != ' ' && *name != '-' && *name != '\'')
            return false;
        name++;
    }
    return true;
}

bool is_valid_employee_role(const char *role) {
    while (*role) {
        if (!isalpha(*role) && *role != ' ' && *role != '-' && *role != '\'')
            return false;
        role++;
    }
    return true;
}
bool is_valid_integer(const char *input) {
    while (*input) {
        if (!isdigit(*input))
            return false;
        input++;
    }
    return true;
}

void add_employee(struct HospitalManagementSystem *hms) {
    if (hms->employee_count >= MAX_PATIENTS) {
        printf("\nHospital employee capacity reached. Cannot add more employees.\n");
        return;
    }

    struct employee *new_employee = (struct employee *)malloc(sizeof(struct employee));
    if (new_employee == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }

    printf("\nEnter the employee ID (must start with 23 and only integer values): ");
    while (1) {
        scanf("%s", new_employee->id);

        // Check if employee ID starts with 23 and only contains digits 
        if (strlen(new_employee->id) > 0 && new_employee->id[0] == '2' && new_employee->id[1] == '3') {
            int i;
            for (i = 2; i < strlen(new_employee->id); i++) {
                if (!isdigit(new_employee->id[i])) {
                    printf("Invalid employee ID. Must start with 23 and only contain digits. Enter again: ");
                    continue;
                }
            }
            if (i == strlen(new_employee->id)) {
                printf("Employee ID is valid.\n");
                break;
            }
        } else {
            printf("Invalid employee ID. Must start with 23 and only contain digits. Enter again: ");
        }
    }

    printf("Enter the name of the employee: ");
    scanf("%s", new_employee->name);

    printf("Enter the role of the employee: ");
    scanf("%s", new_employee->role);

    printf("Enter the salary of the employee (between 10,000 and 1,000,000): ");
    while (1) {
        scanf("%lf", &new_employee->salary);

        if (new_employee->salary < 10000 || new_employee->salary > 1000000) {
            printf("Invalid salary. Salary must be between 10,000 and 1,000,000. Enter again: ");
            continue;
        }
        break;
    }

    printf("Enter the date of joining of the employee (format: dd/mm/yyyy): ");
    scanf("%s", new_employee->date_of_joining);

    printf("Enter the years of experience of the employee: ");
    while (1) {
        scanf("%d", &new_employee->experience_years);

        if (new_employee->experience_years < 0) {
            printf("Invalid years of experience. Please enter a non-negative integer.\n");
            continue;
        }
        break;
    }

    printf("Enter the employment type (cabin/specialist): ");
    scanf("%s", new_employee->employment_type);

    if (strcmp(new_employee->employment_type, "specialist") == 0) {
        printf("Enter the ward number: ");
        scanf("%s", new_employee->ward_number);
    } else if (strcmp(new_employee->employment_type, "cabin") == 0) {
        printf("Enter the cabin number: ");
        scanf("%s", new_employee->cabin_specialist);
    } else {
        printf("Invalid employment type.\n");
        free(new_employee);
        return;
    }

    hms->employees[hms->employee_count++] = new_employee;
    printf("Employee added successfully.\n");
}

void delete_employee(struct HospitalManagementSystem *hms) {
    char id[20];
    int i;

    printf("\nEnter the Employee ID to be deleted: ");
    scanf("%s", id);

    for (i = 0; i < hms->employee_count; i++) {
        if (strcmp(hms->employees[i]->id, id) == 0) {
            free(hms->employees[i]);
            hms->employees[i] = NULL;
            for (int j = i; j < hms->employee_count - 1; j++) {
                hms->employees[j] = hms->employees[j + 1];
            }
            hms->employee_count--;
            printf("Employee record deleted successfully.\n");
            return;
        }
    }

    printf("Employee not found.\n");
}

void admit_patient(struct HospitalManagementSystem *hms) {
    char reg[20];
    char disease[MAX_DESCRIPTION_LENGTH];
    int room_number;

    printf("\nEnter the Registration Number of the patient: ");
    scanf("%s", reg);

    for (int i = 0; i < hms->patient_count; i++) {
        if (strcmp(hms->patients[i]->regn, reg) == 0) {
            printf("Enter the disease of the patient: ");
            scanf("%s", disease);
            if (strcmp(disease, "malaria") == 0 || strcmp(disease, "typhoid") == 0 || strcmp(disease, "dengue") == 0 || strcmp(disease, "fever") == 0 || strcmp(disease, "cold") == 0) {
                if (strcmp(disease, "malaria") == 0) {
                    room_number = 101;
                } else if (strcmp(disease, "typhoid") == 0) {
                    room_number = 102;
                } else if (strcmp(disease, "dengue") == 0) {
                    room_number = 103;
                } else if (strcmp(disease, "fever") == 0) {
                    room_number = 104;
                } else if (strcmp(disease, "cold") == 0) {
                    room_number = 105;
                }

                printf("Patient admitted successfully. Room number assigned: %d\n", room_number);
                return;
            } else {
                printf("Invalid disease entered. Cannot admit patient.\n");
                return;
            }
        }
    }

    printf("Patient not found.\n");
}
void view_medical_shop() {
    printf("\n\t*MEDICAL SHOP*\n");
    printf("\nMedicine\t\tPrice (Rs.)\n");
    printf("1. Paracetamol\t\t50.00\n");
    printf("2. Amoxicillin\t\t100.00\n");
    printf("3. Aspirin\t\t80.00\n");
    printf("4. Omeprazole\t\t120.00\n");
    printf("5. Atorvastatin\t\t150.00\n");
    
} 
