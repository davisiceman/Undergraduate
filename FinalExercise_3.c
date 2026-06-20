#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 128
#define MAX_DATE 64
#define MAX_EMAIL_ADDRESS 128

typedef struct employee_data {
    int employeeId;
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    char middleName[MAX_NAME];
    char emailAddress[MAX_EMAIL_ADDRESS];
    char title[MAX_EMAIL_ADDRESS];
    float annualSalary;
    char dateOfHire[MAX_DATE];
    struct employee_data *pNext;
} EmployeeInformation;

// Function prototypes
void loadRecords(FILE *file, EmployeeInformation **head);
void insertSorted(EmployeeInformation **head, EmployeeInformation *newNode);
void displayEmployee(EmployeeInformation *head);
void editEmployeeSalary(EmployeeInformation *head);
void removeEmployee(EmployeeInformation **head);
void listAllEmployees(EmployeeInformation *head);
EmployeeInformation *createNode(EmployeeInformation *record);

int main(int argc, char *argv[]) {
    EmployeeInformation *head = NULL;
    FILE *file = NULL;

    // If a filename is provided, open it; otherwise, use stdin
    if (argc > 1) {
        file = fopen(argv[1], "rb");
        if (!file) {
            perror("Failed to open file");
            return EXIT_FAILURE;
        }
    } else {
        file = stdin; // Read from stdin for piped input
    }

    loadRecords(file, &head);

    if (file != stdin) {
        fclose(file);
    } else {
        // Reopen stdin for menu interaction
        freopen("/dev/tty", "r", stdin);
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display Employee\n");
        printf("2. Edit Employee Salary\n");
        printf("3. Remove Employee\n");
        printf("4. List All Employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                displayEmployee(head);
                break;
            case 2:
                editEmployeeSalary(head);
                break;
            case 3:
                removeEmployee(&head);
                break;
            case 4:
                listAllEmployees(head);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void loadRecords(FILE *file, EmployeeInformation **head) {
    EmployeeInformation temp;
    size_t recordSize = sizeof(EmployeeInformation) - sizeof(struct employee_data *);

    while (fread(&temp, recordSize, 1, file) == 1) {
        EmployeeInformation *newNode = createNode(&temp);
        insertSorted(head, newNode);
    }

    if (file == stdin) {
        // Clear any remaining binary data from stdin
        int ch;
        while ((ch = getchar()) != EOF && ch != '\n') {
            // Discard remaining input
        }
    }
}

EmployeeInformation *createNode(EmployeeInformation *record) {
    EmployeeInformation *newNode = (EmployeeInformation *)malloc(sizeof(EmployeeInformation));
    if (!newNode) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    *newNode = *record;
    newNode->pNext = NULL;
    return newNode;
}

void insertSorted(EmployeeInformation **head, EmployeeInformation *newNode) {
    if (*head == NULL || (*head)->employeeId > newNode->employeeId) {
        newNode->pNext = *head;
        *head = newNode;
    } else {
        EmployeeInformation *current = *head;
        while (current->pNext && current->pNext->employeeId < newNode->employeeId) {
            current = current->pNext;
        }
        newNode->pNext = current->pNext;
        current->pNext = newNode;
    }
}

void displayEmployee(EmployeeInformation *head) {
    int id;
    printf("Enter employee ID to display: ");
    scanf("%d", &id);

    EmployeeInformation *current = head;
    while (current) {
        if (current->employeeId == id) {
            printf("Employee ID: %d\n", current->employeeId);
            printf("Name: %s %s %s\n", current->firstName, current->middleName, current->lastName);
            printf("Email: %s\n", current->emailAddress);
            printf("Title: %s\n", current->title);
            printf("Annual Salary: %.2f\n", current->annualSalary);
            printf("Date of Hire: %s\n", current->dateOfHire);
            return;
        }
        current = current->pNext;
    }
    printf("Employee ID %d not found.\n", id);
}

void editEmployeeSalary(EmployeeInformation *head) {
    int id;
    float newSalary;

    printf("Enter employee ID to edit salary: ");
    scanf("%d", &id);

    EmployeeInformation *current = head;
    while (current) {
        if (current->employeeId == id) {
            printf("Enter new salary: ");
            scanf("%f", &newSalary);
            current->annualSalary = newSalary;
            printf("Salary updated successfully.\n");
            return;
        }
        current = current->pNext;
    }
    printf("Employee ID %d not found.\n", id);
}

void removeEmployee(EmployeeInformation **head) {
    int id;
    printf("Enter employee ID to remove: ");
    scanf("%d", &id);

    EmployeeInformation *current = *head;
    EmployeeInformation *prev = NULL;

    while (current) {
        if (current->employeeId == id) {
            if (prev) {
                prev->pNext = current->pNext;
            } else {
                *head = current->pNext;
            }
            free(current);
            printf("Employee removed successfully.\n");
            return;
        }
        prev = current;
        current = current->pNext;
    }
    printf("Employee ID %d not found.\n", id);
}

void listAllEmployees(EmployeeInformation *head) {
    if (!head) {
        printf("No employees in the list.\n");
        return;
    }

    EmployeeInformation *current = head;
    while (current) {
        printf("\nEmployee ID: %d\n", current->employeeId);
        printf("Name: %s %s %s\n", current->firstName, current->middleName, current->lastName);
        printf("Email: %s\n", current->emailAddress);
        printf("Title: %s\n", current->title);
        printf("Annual Salary: %.2f\n", current->annualSalary);
        printf("Date of Hire: %s\n", current->dateOfHire);
        current = current->pNext;
    }
}
