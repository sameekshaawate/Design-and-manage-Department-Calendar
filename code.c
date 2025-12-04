#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_APPOINTMENTS 10

typedef struct {
    int day;
    int month;
    int year;
    char description[100];
} Appointment;

Appointment appointments[MAX_APPOINTMENTS];
int appointmentCount = 0;

void displayCalendar(int month, int year);
void addAppointment();
void deleteAppointment();
void viewAppointments(int day, int month, int year);
int isLeapYear(int year);
int getDayOfWeek(int day, int month, int year);
void viewMainMenu();

int main() {
    int choice;

    printf("\nWELCOME TO DEPARTMENT CALENDAR SYSTEM\n\n");

    while (1) {
        viewMainMenu();
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int month, year;
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                displayCalendar(month, year);
                break;
            }
            case 2:
                addAppointment();
                break;
            case 3: {
                int day, month, year;
                printf("Enter the day (1-31): ");
                scanf("%d", &day);
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                viewAppointments(day, month, year);
                break;
            }
            case 4:
                deleteAppointment();
                break;
            case 5:
                printf("Exiting the system...\n");
                exit(0);
            default:
                printf("Invalid option, please try again.\n");
        }
        printf("\n");
    }

    return 0;
}

void viewMainMenu() {
    printf("MAIN MENU\n");
    printf("------------------------\n");
    printf("  1) Display Calendar\n");
    printf("  2) Add Appointment\n");
    printf("  3) View Appointments for a Day\n");
    printf("  4) Delete Appointment\n");
    printf("  5) Exit\n");
    printf("------------------------\n");
}

void displayCalendar(int month, int year) {
    int daysInMonth[] = { 31, (isLeapYear(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int startDay = getDayOfWeek(1, month, year);

    printf("\nCalendar for %d/%d\n", month, year);
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    for (int i = 0; i < startDay; i++) {
        printf("    ");
    }

    for (int day = 1; day <= daysInMonth[month - 1]; day++) {
        printf("%3d ", day);
        if ((startDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Pure basic C: Zeller's Congruence
int getDayOfWeek(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int K = year % 100;
    int J = year / 100;
    int h = (day + 13*(month + 1)/5 + K + K/4 + J/4 + 5*J) % 7;
    return (h + 6) % 7; // 0=Sunday, 1=Monday, ..., 6=Saturday
}

void addAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("Max appointment limit reached.\n");
        return;
    }

    Appointment newAppointment;
    printf("Enter appointment day (1-31): ");
    scanf("%d", &newAppointment.day);
    printf("Enter month (1-12): ");
    scanf("%d", &newAppointment.month);
    printf("Enter year: ");
    scanf("%d", &newAppointment.year);

    getchar(); // Clear newline
    printf("Enter appointment description: ");
    fgets(newAppointment.description, sizeof(newAppointment.description), stdin);
    newAppointment.description[strcspn(newAppointment.description, "\n")] = 0;

    appointments[appointmentCount++] = newAppointment;
    printf("Appointment added successfully.\n");
}

void deleteAppointment() {
    if (appointmentCount == 0) {
        printf("No appointments to delete.\n");
        return;
    }

    int day, month, year;
    printf("Enter the day of appointment to delete (1-31): ");
    scanf("%d", &day);
    printf("Enter month (1-12): ");
    scanf("%d", &month);
    printf("Enter year: ");
    scanf("%d", &year);

    int found = 0;
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].day == day && appointments[i].month == month && appointments[i].year == year) {
            printf("Deleting appointment: %s\n", appointments[i].description);
            for (int j = i; j < appointmentCount - 1; j++) {
                appointments[j] = appointments[j + 1];
            }
            appointmentCount--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No appointment found on this date.\n");
    } else {
        printf("Appointment deleted successfully.\n");
    }
}

void viewAppointments(int day, int month, int year) {
    printf("\nAppointments for %d/%d/%d:\n", day, month, year);
    int found = 0;

    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].day == day && appointments[i].month == month && appointments[i].year == year) {
            printf("Description: %s\n", appointments[i].description);
            found = 1;
        }
    }

    if (!found) {
        printf("No appointments found for this day.\n");
    }
}
