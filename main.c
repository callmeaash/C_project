#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 100
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 20

int userAuthentication();
int manageStudents();
int addStudents();
int viewStudents();
int removeStudents();

typedef struct
{
    char id[10];
    char firstName[20];
    char lastName[20];
    char email[40];
} std;


int main(void)
{
    // Print the Heading
    printf("\nSCHOOL MANAGEMENT SYSTEM\n");

    userAuthentication();
    return 0;
}



int userAuthentication()
{
    char username[USERNAME_LENGTH], password[PASSWORD_LENGTH];

    printf("\n**Admin Login**\n");
    printf("Enter Username: ");
    scanf(" %s", username);

    printf("Enter Password: ");
    scanf(" %s", password);

    char line[LINE_LENGTH];
    char *fileUsername, *filePassword;
    int auth = 0;

    FILE *file = fopen("adminData.csv", "r");
    if (file == NULL)
    {
        printf("\033[0;31m Couldn't load admin data... \033[0m\n");
        return 1;
    }

    fgets(line, sizeof(line), file);

    while(fgets(line, sizeof(line), file) != NULL)
    {
        fileUsername = strtok(line, ",");
        filePassword = strtok(NULL, ",");

        if (filePassword != NULL)
        {
            size_t len = strlen(filePassword);
            if (filePassword[len - 1] == '\n')
            {
                filePassword[len - 1] = '\0';
            }
        }
        
        if (strcmp(username, fileUsername) == 0)
        {
            if (strcmp(password, filePassword) == 0)
            {
                printf("Authentication Successful....\n");
                auth = 1;
                fclose(file);
                return manageStudents();
            }
        }
    }
    if (auth == 0)
    {
        printf("\033[0;31m Invalid username or password!!! \033[0m \n");
        fclose(file);
        return userAuthentication();
    }
}


// Function to handle manageStudent requests
int manageStudents()
{
    char option;

    // Print sub-heading
    printf("\n**Manage Students**\n\n");

    //Print Menu options
    printf("Select a option: \n\n");
    printf("V ---\tView Students\n");
    printf("A ---\tAdd Students\n");
    printf("R ---\tRemove Students\n");
    printf("U ---\tUpdate Students\n");
    printf("E ---\tExit\n");

    printf("\nChoose: ");
    scanf(" %c", &option);

    if (toupper(option) == 'V')
    {
        // call viewStudents function which lists all students
        viewStudents();
    }
    else if (toupper(option) == 'A')
    {
        // call addStudents function which adds new students
        addStudents();
    }
    else if (toupper(option) == 'R')
    {
        // call removeStudents function which removes existing students
        removeStudents();
    }
    else if (toupper(option) == 'U')
    {
        // call updateStudents function which adds new students
        // updateStudents();
    }
    else if (toupper(option) == 'E')
    {
        // Exit the program
        printf("Exiting the program..........");
        return 0;
        
    }
    else
    {
        // Reshow the menu
        printf("\033[0;31m Invalid Option \033[0m\n");
        manageStudents();
    }
}


int addStudents()
{
    // Defining a variable of type std to store student records
    std student;

    FILE *file = fopen("students.csv", "a");
        if (file == NULL)
        {
            printf("\033[0;31m Technical Error... \033[0m\n");
            return 1;
        }

        // If a file is empty add the columns heading
        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0)
        {
            fprintf(file, "ID, firstName, lastName, Email\n");
        }

    while (1)
    {
        char r;
        
        printf("Enter student ID: ");
        scanf(" %s", &student.id);

        printf("Enter First Name: ");
        scanf(" %s", &student.firstName);

        printf("Enter Last Name: ");
        scanf(" %s", &student.lastName);

        printf("Enter Email: ");
        scanf(" %s", &student.email);

        // Write the data into the file
        fprintf(file, "%s, %s, %s, %s\n", student.id, student.firstName, student.lastName, student.email);

        printf("Student record added successfully!!!!\n");

        // Asks if the user wants to add more data
        printf("\nDo you want to add more record? ");
        scanf(" %c", &r);
        if (r == 'n') break;
    }
    fclose(file);
    manageStudents();
}

int viewStudents()
{
    std student;
    char line[LINE_LENGTH];
    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        printf("\033[0;31m No Record found... \033[0m\n");
        manageStudents();
    }

    fgets(line, sizeof(line), file);
    printf("%-10s %-15s %-15s %-30s\n", "ID", "First Name", "Last Name", "Email");
    printf("%-10s %-15s %-15s %-30s\n", "-----", "----------", "----------", "-----------------------");
    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        if (token != NULL) strcpy(student.id, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(student.firstName, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(student.lastName, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(student.email, token);
        printf("%-10s %-15s %-15s %-30s\n", student.id, student.firstName, student.lastName, student.email);

    }
    fclose(file);
    manageStudents()
}


int removeStudents()
{

}
