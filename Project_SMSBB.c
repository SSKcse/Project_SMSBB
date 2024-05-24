#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for student and user data
typedef struct
{
    char name[50]; // Name of the student
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

// Functions
void login();
void registerUser(); // New function for user registration
void addStudent();
void searchStudentByBloodGroup();
void searchStudentByID();
void searchStudentByBatch();
void displayMenu();
void saveDataToFile();
void loadDataFromFile();

// Global variables
Student students[100]; // Assuming a maximum of 100 students
int numStudents = 0;
User users[10]; // Assuming a maximum of 10 users
int numUsers = 0;

int main()
{
    int choice;

    // Load data from file at the start of the program
    loadDataFromFile();

    // Populate some sample data (optional)
    // Initialize some users
    strcpy(users[numUsers].username, "admin");
    strcpy(users[numUsers].password, "admin123");
    strcpy(users[numUsers].role, "teacher");
    numUsers++;

    do
    {
        displayMenu();

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
            saveDataToFile(); // Save data to file before exiting
            printf("Exiting...Thanks For using SMSBB\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Function for display the menu
void displayMenu()
{
    printf("\n===== Student Management System (SMSBB) Menu =====\n");
    printf("1. Teacher Login\n");
    printf("2. Teacher Register\n"); // option for user registration
    printf("3. Add Student (Only for Teachers)\n");
    printf("4. Search Student by Blood Group\n");
    printf("5. Search Student by ID\n");
    printf("6. Search Student by Batch\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
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

            // Check user role
            if (strcmp(users[i].role, "teacher") == 0)
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
    printf("Name: ");
    getchar();                                                                    // Clear the input buffer
    fgets(students[numStudents].name, sizeof(students[numStudents].name), stdin); // Read full name with spaces
    strtok(students[numStudents].name, "\n");                                     // Remove the trailing newline character from fgets
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
    char searchBloodGroup[4];
    int found = 0;
    int count = 0;

    // Prompt the user to enter the blood group to search for
    printf("Enter the blood group to search for: ");
    scanf("%s", searchBloodGroup);

    // Iterate through the students array to find matching blood group
    printf("\nStudents with blood group %s:\n", searchBloodGroup);
    for (int i = 0; i < numStudents; i++)
    {
        if (strcmp(students[i].blood_group, searchBloodGroup) == 0)
        {
            printf("%d. Name: %s, ID: %d, Batch: %s, Semester: %d, Result: %.2f\n", ++count, students[i].name, students[i].id, students[i].batch, students[i].semester, students[i].result);
            found = 1;
        }
    }

    // If no students with the given blood group are found
    if (!found)
    {
        printf("No students found with blood group %s.\n", searchBloodGroup);
    }
}

// Function to search for students by ID
void searchStudentByID()
{
    int searchID;
    int found = 0;

    // Prompt the user to enter the ID to search for
    printf("Enter the ID to search for: ");
    scanf("%d", &searchID);

    // Iterate through the students array to find matching ID
    printf("\nStudents with ID %d:\n", searchID);
    for (int i = 0; i < numStudents; i++)
    {
        if (students[i].id == searchID)
        {
            printf("Name: %s, Batch: %s, Semester: %d, Blood Group: %s, Result: %.2f\n", students[i].name, students[i].batch, students[i].semester, students[i].blood_group, students[i].result);
            found = 1;
            break; // Assuming ID is unique, no need to continue searching
        }
    }

    // If no students with the given ID are found
    if (!found)
    {
        printf("No student found with ID %d.\n", searchID);
    }
}

// Function to search for students by batch
void searchStudentByBatch()
{
    char searchBatch[20];
    int found = 0;
    int count = 0;

    // Prompt the user to enter the batch to search for
    printf("Enter the batch to search for: ");
    scanf("%s", searchBatch);

    // Iterate through the students array to find matching batch
    printf("\nStudents in batch %s:\n", searchBatch);
    for (int i = 0; i < numStudents; i++)
    {
        if (strcmp(students[i].batch, searchBatch) == 0)
        {
            printf("%d. Name: %s, ID: %d, Semester: %d, Blood Group: %s, Result: %.2f\n", ++count, students[i].name, students[i].id, students[i].semester, students[i].blood_group, students[i].result);
            found = 1;
        }
    }

    // If no students in the given batch are found
    if (!found)
    {
        printf("No students found in batch %s.\n", searchBatch);
    }
}

// Function to save student data to a text file
void saveDataToFile()
{
    FILE *file = fopen("student_data.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write each student's data to the file
    for (int i = 0; i < numStudents; i++)
    {
        fprintf(file, "%s;%d;%s;%d;%s;%.2f\n", students[i].name, students[i].id, students[i].batch, students[i].semester, students[i].blood_group, students[i].result);
    }

    fclose(file);
    printf("Data saved to file successfully.\n");
}

// Function to load student data from a text file
void loadDataFromFile()
{
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    // Read each line from the file and parse student data
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        Student newStudent;
        sscanf(line, "%[^;];%d;%[^;];%d;%[^;];%f", newStudent.name, &newStudent.id, newStudent.batch, &newStudent.semester, newStudent.blood_group, &newStudent.result);
        students[numStudents++] = newStudent;
    }

    fclose(file);
    printf("Data loaded from file successfully.\n");
}
