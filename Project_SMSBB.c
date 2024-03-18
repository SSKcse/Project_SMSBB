#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for student and user data
typedef struct
{
    int id;
    char batch[20];
    int semester;
    char blood_group[4];
    float result;
} Student;

typedef struct
{
    char username[20];
    char password[20];
    char role[10]; // New field to store user role (e.g., teacher or admin)
} User;

// Function prototypes
void login();
void registerUser(); // New function for user registration
void addStudent();
void searchStudentByBloodGroup();
void searchStudentByID();
void searchStudentByBatch();

// Global variables
Student students[100]; // Assuming a maximum of 100 students
int numStudents = 0;
User users[10]; // Assuming a maximum of 10 users
int numUsers = 0;

int main()
{
    int choice;

    // Populate some sample data (optional)
    // Initialize some users
    strcpy(users[numUsers].username, "admin");
    strcpy(users[numUsers].password, "admin123");
    strcpy(users[numUsers].role, "admin");
    numUsers++;

    do
    {
        printf("\n===== Student Management System (SMSBB) Menu =====\n");
        printf("1. Login\n");
        printf("2. Register\n"); // option for user registration
        printf("3. Add Student\n");
        printf("4. Search Student by Blood Group\n");
        printf("5. Search Student by ID\n");
        printf("6. Search Student by Batch\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            login();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            addStudent();
            break;
        case 4:
            searchStudentByBloodGroup();
            break;
        case 5:
            searchStudentByID();
            break;
        case 6:
            searchStudentByBatch();
            break;
        case 7:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Function to handle user login
void login()
{
    char username[20];
    char password[20];
    int i;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Check if the username and password match any existing user
    for (i = 0; i < numUsers; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            printf("Login successful!\n");

            // Optionally, you can provide access based on user role
            if (strcmp(users[i].role, "admin") == 0)
            {
                printf("Welcome, Admin!\n");
                // Additional admin privileges or options can be added here
            }
            else if (strcmp(users[i].role, "teacher") == 0)
            {
                printf("Welcome, Teacher!\n");
                // Additional teacher privileges or options can be added here
            }
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
}

// Function for user registration
void registerUser()
{
    // Code to allow teachers to register their accounts
    char username[20];
    char password[20];

    printf("Enter desired username: ");
    scanf("%s", username);
    printf("Enter desired password: ");
    scanf("%s", password);

    // Check if the username already exists
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(username, users[i].username) == 0)
        {
            printf("Username already exists. Please choose another one.\n");
            return;
        }
    }

    // Add the new user
    strcpy(users[numUsers].username, username);
    strcpy(users[numUsers].password, password);
    strcpy(users[numUsers].role, "teacher"); // Set user role to teacher
    numUsers++;

    printf("Account created successfully!\n");
}

// Function to add a new student
void addStudent()
{
    // Check if the user is logged in as a teacher
    int isLoggedInAsTeacher = 0;
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].role, "teacher") == 0)
        {
            isLoggedInAsTeacher = 1;
            break;
        }
    }

    if (!isLoggedInAsTeacher)
    {
        printf("Only teachers can add students. Please login as a teacher.\n");
        return;
    }

    // Check if there is space to add a new student
    if (numStudents >= 100)
    {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    // Prompt the user to enter student details
    printf("Enter student details:\n");
    printf("ID: ");
    scanf("%d", &students[numStudents].id);
    printf("Batch: ");
    scanf("%s", students[numStudents].batch);
    printf("Semester: ");
    scanf("%d", &students[numStudents].semester);
    printf("Blood Group: ");
    scanf("%s", students[numStudents].blood_group);
    printf("Result: ");
    scanf("%f", &students[numStudents].result);

    // Increment the number of students in the system
    numStudents++;

    printf("Student added successfully!\n");
}

// Function to search for students by blood group
void searchStudentByBloodGroup()
{
    // Code to search for students by blood group
}

// Function to search for students by ID
void searchStudentByID()
{
    // Code to search for students by ID
}

// Function to search for students by batch
void searchStudentByBatch()
{
    // Code to search for students by batch
}
