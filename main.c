#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 100
#define MAX_LINES 1000
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 20

int userAuthentication();
int manageStudents();
int addStudents();
int viewStudents();
int removeStudents();
int updateStudents();
int searchStudents();
void strlower(char *word);

typedef struct
{
    char id[10];
    char firstName[20];
    char lastName[20];
    char class[10];
    char email[40];
} std;


int main(void)
{
    // Print the Heading
    printf("\nSTUDENT MANAGEMENT SYSTEM\n\n");
    char n;
    printf("Select an option: \n\n");
    printf("L --- Login\n");
    printf("E --- Exit\n");
    while (1){
        printf("Option: ");
        scanf("%c", &n);
        if (toupper(n) == 'L')
            return userAuthentication();
        else if (toupper(n) == 'E'){
            printf("Exiting the program......");
            return 0;
        }
        else
            printf("Invalid Option!!!!!");
        }
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
    printf("S ---\tSearch Students\n");
    printf("E ---\tExit\n");

    printf("\nChoose: ");
    scanf(" %c", &option);

    if (toupper(option) == 'V')
    {
        // call viewStudents function which lists all students
        return viewStudents();
    }
    else if (toupper(option) == 'A')
    {
        // call addStudents function which adds new students
        return addStudents();
    }
    else if (toupper(option) == 'R')
    {
        // call removeStudents function which removes existing students
        return removeStudents();
    }
    else if (toupper(option) == 'U')
    {
        // call updateStudents function which adds new students
        return updateStudents();
    }
    else if (toupper(option) == 'S')
    {
        // call searchStudents function which search students
        return searchStudents();
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
        return manageStudents();
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
            fprintf(file, "ID,firstName,lastName,class,Email\n");
        }

    while (1)
    {
        char r;
        
        printf("Enter student ID: ");
        scanf(" %s", student.id);

        printf("Enter First Name: ");
        scanf(" %s", student.firstName);

        printf("Enter Last Name: ");
        scanf(" %s", student.lastName);

        printf("Enter Class: ");
        scanf(" %10[^\n]", student.class);

        printf("Enter Email: ");
        scanf(" %s", student.email);

        // Write the data into the file
        fprintf(file, "%s,%s,%s,%s,%s\n", student.id, student.firstName, student.lastName, student.class, student.email);

        printf("Student record added successfully!!!!\n");

        // Asks if the user wants to add more data
        printf("\nDo you want to add more record? ");
        scanf(" %c", &r);
        if (r == 'n') break;
    }
    fclose(file);
    return manageStudents();
}

int viewStudents()
{
    std student;
    char line[LINE_LENGTH];
    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        printf("\033[0;31m No Records found!!! \033[0m\n");
        return manageStudents();
    }

    fgets(line, sizeof(line), file);
    printf("%-10s %-15s %-15s %-10s %-30s\n", "ID", "First Name", "Last Name", "Class", "Email");
    printf("%-10s %-15s %-15s %-10s %-30s\n", "-----", "----------", "----------", "------", "-----------------------");

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
        if (token != NULL) strcpy(student.class, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(student.email, token);

        printf("%-10s %-15s %-15s %-10s %-30s\n", student.id, student.firstName, student.lastName, student.class, student.email);

    }
    fclose(file);
    return manageStudents();
}


int removeStudents()
{
    char id[10];
    char c;
    int count = 0;
    int skip_index= -1;
    std student;

    printf("Enter the student ID: ");
    scanf("%s", id);

    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        printf("\033[0;31m File Not found!!!! \033[0m\n");
        return manageStudents();
    }

    char line[MAX_LINES][LINE_LENGTH];
    while(fgets(line[count], sizeof(line[count]), file) != NULL)
    {
        char check_line[LINE_LENGTH];
        strcpy(check_line, line[count]);
        char *token = strtok(check_line, ",");
        char file_id[10];
        strcpy(file_id, token);

        if (strcmp(file_id, id) == 0)
        {
            skip_index = count;
        }
        count++;
    }
    fclose(file);

    if (skip_index == -1)
    {
        printf("\033[0;31m Student with ID %s doesn't exist!!! \033[0m\n", id);
        return manageStudents();

    }

    file = fopen("students.csv", "w");
    if (file == NULL) {
        printf("\033[0;31mError writing to file!\033[0m\n");
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        if (skip_index != i)
        {
            fputs(line[i], file);
        }
    }
    fclose(file);
    printf("Student with ID %s has been removed!!!\n", id);
    return manageStudents();
}


int updateStudents()
{
    char id[10];
    int count = 0;
    int skip_index = -1;
    std student;
    printf("Enter the Student ID: ");
    scanf("%s", id);

    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        printf("\033[0;31m File Not found!!!! \033[0m\n");
        return manageStudents();
    }

    char line[MAX_LINES][LINE_LENGTH];
    while(fgets(line[count], sizeof(line[count]), file) != NULL)
    {
        char check_line[LINE_LENGTH];
        strcpy(check_line, line[count]);
        char *token = strtok(check_line, ",");
        char file_id[10];
        strcpy(file_id, token);

        if (strcmp(id, file_id) == 0)
        {
            skip_index = count;
            printf("Enter First Name: ");
            scanf(" %s", student.firstName);

            printf("Enter Last Name: ");
            scanf(" %s", student.lastName);

            printf("Enter Class: ");
            scanf(" %10[^\n]", student.class);

            printf("Enter Email: ");
            scanf(" %s", student.email);

            snprintf(line[skip_index], LINE_LENGTH, "%s,%s,%s,%s,%s\n",
                    id, student.firstName, student.lastName, student.class, student.email);
        }
        count++;
    }
    fclose(file);
    if(skip_index == -1)
    {
        printf("\033[0;31m Student with ID %s doesn't exist!!! \033[0m\n", id);
        return manageStudents();
    }

    file = fopen("students.csv", "w");
    if (file == NULL) {
        printf("\033[0;31mError writing to file!\033[0m\n");
        return 1;
    }
    
    for (int i = 0; i < count; i++)
    {
        fputs(line[i], file);
    }
    fclose(file);
    printf("Student with ID %s has been updated!!!\n", id);

    return manageStudents();
}


int searchStudents()
{
    char name[20];
    int count = 0;
    int found = 0;
    std student;

    printf("Enter the Student First Name: ");
    scanf("%s", name);

    FILE *file = fopen("students.csv", "r");
    if (file == NULL)
    {
        printf("\033[0;31m File Not found!!!! \033[0m\n");
        return manageStudents();
    }

    char line[MAX_LINES][LINE_LENGTH];
    while(fgets(line[count], sizeof(line[count]), file) != NULL)
    {
        char *token = strtok(line[count], ",");
        strcpy(student.id, token);
        token = strtok(NULL, ",");
        strcpy(student.firstName, token);
        strlower(name);
        strlower(student.firstName);

        if (strcmp(name, student.firstName) == 0)
        {
            found++;
            token = strtok(NULL, ",");
            strcpy(student.lastName, token);
            token = strtok(NULL, ",");
            strcpy(student.class, token);
            token = strtok(NULL, ",");
            strcpy(student.email, token);
            student.email[strcspn(student.email, "\n")] = 0;
            if (found == 1)
            {
                printf("%-10s %-15s %-15s %-10s %-30s\n", "ID", "First Name", "Last Name", "Class", "Email");
                printf("%-10s %-15s %-15s %-10s %-30s\n", "-----", "----------", "----------", "------", "-----------------------");
            }
            printf("%-10s %-15s %-15s %-10s %-30s\n", student.id, student.firstName, student.lastName, student.class, student.email);
        }
        count++;
    }
    fclose(file);
    if(found == 0)
    {
        printf("\033[0;31m Student with FirstName %s doesn't exist!!! \033[0m\n", name);
    }
    return manageStudents();
}

void strlower(char *word)
{
    int i = 0;
    while (word[i] != '\0') {
        word[i] = tolower(word[i]);
        i++;
    }
}

