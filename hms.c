#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define PATIENT_FILE "patients.dat"
#define DOCTOR_FILE "doctors.dat"
#define APPOINTMENT_FILE "appointments.dat"

typedef enum { ROLE_ADMIN = 1, ROLE_DOCTOR, ROLE_RECEPTIONIST, ROLE_NONE } UserRole;


typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char diagnosis[100];
    double billAmount;
    int isBillApproved;
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[50];
    char schedule[50];
} Doctor;

typedef struct {
    int appointmentId;
    int patientId;
    int doctorId;
    char date[20];
    char time[20];
} Appointment;

UserRole loginPortal();
void maskPassword(char *password, int maxLength);

void adminMenu();
void doctorMenu(int doctorId);
void receptionistMenu();

void addPatient();
void viewPatients();
void searchPatient();
void editPatient();
void deletePatient();

void addDoctor();
void viewDoctors();

void bookAppointment();
void viewAppointments();

void generateBill();
void approveBills();

int main() {
    UserRole currentRole = ROLE_NONE;
    int choice;

    while (1) {
        system("cls || clear");
        printf("==================================================\n");
        printf("         HOSPITAL MANAGEMENT SYSTEM               \n");
        printf("==================================================\n");
        printf("1. Login to Portal\n");
        printf("2. Exit System\n");
        printf("==================================================\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            currentRole = loginPortal();
            if (currentRole == ROLE_ADMIN) {
                adminMenu();
            } else if (currentRole == ROLE_DOCTOR) {
                doctorMenu(101);
            } else if (currentRole == ROLE_RECEPTIONIST) {
                receptionistMenu();
            }
        } else if (choice == 2) {
            printf("\nExiting System. Data safely recorded in local flat files.\n");
            break;
        } else {
            printf("\nInvalid selection. Try again.\n");
            getch();
        }
    }
    return 0;
}

UserRole loginPortal() {
    char username[30];
    char password[30];

    system("cls || clear");
    printf("==================================================\n");
    printf("               AUTHENTICATION PORTAL              \n");
    printf("==================================================\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    maskPassword(password, 30);
    printf("\n==================================================\n");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Access Granted: Welcome Admin.\n");
        getch();
        return ROLE_ADMIN;
    } else if (strcmp(username, "doctor") == 0 && strcmp(password, "doc123") == 0) {
        printf("Access Granted: Welcome Doctor.\n");
        getch();
        return ROLE_DOCTOR;
    } else if (strcmp(username, "receptionist") == 0 && strcmp(password, "recep123") == 0) {
        printf("Access Granted: Welcome Receptionist.\n");
        getch();
        return ROLE_RECEPTIONIST;
    } else {
        printf("Authentication Failed! Incorrect Username or Password.\n");
        getch();
        return ROLE_NONE;
    }
}

void maskPassword(char *password, int maxLength) {
    int i = 0;
    char ch;
    while (i < maxLength - 1) {
        ch = _getch();
        if (ch == 13) { 
            break;
        } else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}

void adminMenu() {
    int choice;
    while (1) {
        system("cls || clear");
        printf("==================================================\n");
        printf("               ADMINISTRATOR DASHBOARD            \n");
        printf("==================================================\n");
        printf("1. Manage Employee Credentials (Add Doctor)\n");
        printf("2. View Registered Doctors\n");
        printf("3. View All Patient Database\n");
        printf("4. Override & Approve Pending Bills\n");
        printf("5. Logout\n");
        printf("==================================================\n");
        printf("Select Operational Option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: viewDoctors(); break;
            case 3: viewPatients(); break;
            case 4: approveBills(); break;
            case 5: return;
            default: printf("Invalid entry.\n"); getch();
        }
    }
}

void doctorMenu(int doctorId) {
    int choice;
    while (1) {
        system("cls || clear");
        printf("==================================================\n");
        printf("                 DOCTOR DASHBOARD                 \n");
        printf("==================================================\n");
        printf("1. View Patient Medical Histories & Diagnostics\n");
        printf("2. View Personal Appointment Schedules\n");
        printf("3. Logout\n");
        printf("==================================================\n");
        printf("Select Operational Option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewPatients(); break;
            case 2: viewAppointments(); break;
            case 3: return;
            default: printf("Invalid entry.\n"); getch();
        }
    }
}

void receptionistMenu() {
    int choice;
    while (1) {
        system("cls || clear");
        printf("==================================================\n");
        printf("               RECEPTIONIST DASHBOARD             \n");
        printf("==================================================\n");
        printf("1. Add New Patient Check-in\n");
        printf("2. Search Patient Record\n");
        printf("3. Modify/Edit Patient Information\n");
        printf("4. Book Appointment Slots\n");
        printf("5. Generate Patient Billing Invoice\n");
        printf("6. Remove Patient Record\n");
        printf("7. Logout\n");
        printf("==================================================\n");
        printf("Select Operational Option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: searchPatient(); break;
            case 3: editPatient(); break;
            case 4: bookAppointment(); break;
            case 5: generateBill(); break;
            case 6: deletePatient(); break;
            case 7: return;
            default: printf("Invalid entry.\n"); getch();
        }
    }
}

void addPatient() {
    FILE *fp = fopen(PATIENT_FILE, "ab");
    if (!fp) { printf("File Streaming Error.\n"); return; }

    Patient p;
    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);
    printf("Enter Patient Name: ");
    fflush(stdin);
    scanf(" %[^\n]s", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Gender: ");
    scanf("%s", p.gender);
    printf("Enter Clinical Diagnosis: ");
    scanf(" %[^\n]s", p.diagnosis);
    p.billAmount = 0.0;
    p.isBillApproved = 0;

    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);
    printf("\nPatient recorded successfully.\n");
    getch();
}

void viewPatients() {
    FILE *fp = fopen(PATIENT_FILE, "rb");
    if (!fp) {
        printf("\nNo patient records found.\n");
        getch();
        return;
    }

    Patient p;
    printf("\n%-10s %-20s %-5s %-10s %-25s %-10s %-10s\n", "ID", "Name", "Age", "Gender", "Diagnosis", "Bill", "Status");
    printf("-----------------------------------------------------------------------------------------\n");
    while (fread(&p, sizeof(Patient), 1, fp)) {
        printf("%-10d %-20s %-5d %-10s %-25s %-10.2f %-10s\n", 
               p.id, p.name, p.age, p.gender, p.diagnosis, p.billAmount, 
               p.isBillApproved ? "Approved" : "Pending");
    }
    fclose(fp);
    getch();
}

void searchPatient() {
    FILE *fp = fopen(PATIENT_FILE, "rb");
    if (!fp) { printf("\nDatabase flat file missing.\n"); getch(); return; }

    int targetId, found = 0;
    Patient p;
    printf("\nEnter Patient ID to search: ");
    scanf("%d", &targetId);

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == targetId) {
            found = 1;
            printf("\n--- Record Found ---\n");
            printf("Name: %s\nAge: %d\nGender: %s\nDiagnosis: %s\nBill: %.2f (%s)\n", 
                   p.name, p.age, p.gender, p.diagnosis, p.billAmount, p.isBillApproved ? "Approved" : "Pending");
            break;
        }
    }
    if (!found) printf("\nPatient record not found.\n");
    fclose(fp);
    getch();
}

void editPatient() {
    FILE *fp = fopen(PATIENT_FILE, "rb+");
    if (!fp) { printf("\nFile modification error.\n"); getch(); return; }

    int targetId, found = 0;
    Patient p;
    printf("\nEnter Patient ID to modify: ");
    scanf("%d", &targetId);

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == targetId) {
            found = 1;
            printf("Enter New Clinical Diagnosis: ");
            scanf(" %[^\n]s", p.diagnosis);
            
            fseek(fp, -sizeof(Patient), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);
            printf("\nPatient entry updated successfully.\n");
            break;
        }
    }
    if (!found) printf("\nRecord matching ID not found.\n");
    fclose(fp);
    getch();
}

void deletePatient() {
    FILE *fp = fopen(PATIENT_FILE, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) { printf("\nFile error.\n"); return; }

    int targetId, found = 0;
    Patient p;
    printf("\nEnter Patient ID to remove: ");
    scanf("%d", &targetId);

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == targetId) {
            found = 1;
        } else {
            fwrite(&p, sizeof(Patient), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);

    remove(PATIENT_FILE);
    rename("temp.dat", PATIENT_FILE);

    if (found) printf("\nPatient record purged successfully.\n");
    else printf("\nRecord not found.\n");
    getch();
}

void addDoctor() {
    FILE *fp = fopen(DOCTOR_FILE, "ab");
    if (!fp) { printf("File error.\n"); return; }

    Doctor d;
    printf("\nEnter Doctor ID: ");
    scanf("%d", &d.id);
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]s", d.name);
    printf("Enter Specialization: ");
    scanf(" %[^\n]s", d.specialization);
    printf("Enter Availability Shift (e.g., 09AM-02PM): ");
    scanf(" %[^\n]s", d.schedule);

    fwrite(&d, sizeof(Doctor), 1, fp);
    fclose(fp);
    printf("\nPhysician registry updated successfully.\n");
    getch();
}

void viewDoctors() {
    FILE *fp = fopen(DOCTOR_FILE, "rb");
    if (!fp) { printf("\nNo doctors registered.\n"); getch(); return; }

    Doctor d;
    printf("\n%-10s %-20s %-20s %-15s\n", "Doc ID", "Name", "Specialization", "Schedule");
    printf("--------------------------------------------------------------------\n");
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        printf("%-10d %-20s %-20s %-15s\n", d.id, d.name, d.specialization, d.schedule);
    }
    fclose(fp);
    getch();
}

void bookAppointment() {
    FILE *fp = fopen(APPOINTMENT_FILE, "ab");
    if (!fp) { printf("File tracking error.\n"); return; }

    Appointment a;
    printf("\nEnter Appointment Unique ID: ");
    scanf("%d", &a.appointmentId);
    printf("Enter Patient ID: ");
    scanf("%d", &a.patientId);
    printf("Enter Doctor ID: ");
    scanf("%d", &a.doctorId);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s", a.date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", a.time);

    fwrite(&a, sizeof(Appointment), 1, fp);
    fclose(fp);
    printf("\nAppointment slotted successfully.\n");
    getch();
}

void viewAppointments() {
    FILE *fp = fopen(APPOINTMENT_FILE, "rb");
    if (!fp) { printf("\nNo scheduled appointments found.\n"); getch(); return; }

    Appointment a;
    printf("\n%-15s %-12s %-12s %-12s %-10s\n", "Appt ID", "Patient ID", "Doctor ID", "Date", "Time");
    printf("-----------------------------------------------------------------\n");
    while (fread(&a, sizeof(Appointment), 1, fp)) {
        printf("%-15d %-12d %-12d %-12s %-10s\n", a.appointmentId, a.patientId, a.doctorId, a.date, a.time);
    }
    fclose(fp);
    getch();
}

void generateBill() {
    FILE *fp = fopen(PATIENT_FILE, "rb+");
    if (!fp) { printf("\nDatabase empty.\n"); getch(); return; }

    int targetId, found = 0;
    Patient p;
    double baseFee;

    printf("\nEnter Patient ID to generate billing invoice: ");
    scanf("%d", &targetId);

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == targetId) {
            found = 1;
            printf("Enter Consultancy / Procedure Base Cost: ");
            scanf("%lf", &baseFee);
            
            p.billAmount = baseFee;
            p.isBillApproved = 0;

            fseek(fp, -sizeof(Patient), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);
            printf("\nInvoice sent to Administrator approval queue.\n");
            break;
        }
    }
    if (!found) printf("\nPatient not found.\n");
    fclose(fp);
    getch();
}

void approveBills() {
    FILE *fp = fopen(PATIENT_FILE, "rb+");
    if (!fp) { printf("\nNo invoices found.\n"); getch(); return; }

    Patient p;
    int choice, reviewed = 0;

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.isBillApproved == 0 && p.billAmount > 0) {
            reviewed = 1;
            system("cls || clear");
            printf("--- Invoice Awaiting Admin Clearance ---\n");
            printf("Patient: %s\nDiagnosed: %s\nPending Bill Amount: %.2f PKR\n", p.name, p.diagnosis, p.billAmount);
            printf("\nApprove payment? (1 = Yes, 2 = Skip): ");
            scanf("%d", &choice);

            if (choice == 1) {
                p.isBillApproved = 1;
                fseek(fp, -sizeof(Patient), SEEK_CUR);
                fwrite(&p, sizeof(Patient), 1, fp);
                fflush(fp);
                printf("Payment cleared successfully.\n");
                getch();
            }
        }
    }
    if (!reviewed) {
        printf("\nNo pending billing workflows left to process.\n");
        getch();
    }
    fclose(fp);
}
