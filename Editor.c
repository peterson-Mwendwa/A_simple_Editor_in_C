#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void welcome_message();
void create_file();
void open_file();
void append_to_file();
void search_in_file();
void view_file_contents();
void modify_or_delete_line();
void highlight_keywords(const char *line);
void save_and_exit();
void error_message(const char *message);

int main() {
    welcome_message();
    int choice;

    while (1) {
        printf("\n---------- C Text Editor Menu ----------\n");
        printf("1. Create New File\n");
        printf("2. Open Existing File\n");
        printf("3. Append Text to File\n");
        printf("4. View File Contents\n");
        printf("5. Search for Text in File\n");
        printf("6. Modify or Delete Lines\n");
        printf("7. Save and Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf

        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                open_file();
                break;
            case 3:
                append_to_file();
                break;
            case 4:
                view_file_contents();
                break;
            case 5:
                search_in_file();
                break;
            case 6:
                modify_or_delete_line();
                break;
            case 7:
                save_and_exit();
                break;
            default:
                printf("Invalid choice. Please choose a valid option.\n");
                break;
        }
    }
    return 0;
}

// Function to display a welcome message
void welcome_message() {
    printf("========================================\n");
    printf("        Welcome to Enhanced C Editor    \n");
    printf("     Created by Peterson Mwendwa        \n");
    printf("     Enhance your coding experience!    \n");
    printf("========================================\n");
}

// Function to create a new file
void create_file() {
    char filename[100];
    FILE *file;
    char ch;

    printf("\nEnter the filename to create (with extension): ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove the newline character

    file = fopen(filename, "w");
    if (file == NULL) {
        error_message("Error creating the file.");
        return;
    }

    printf("File '%s' created successfully! Start typing your content below:\n", filename);
    printf("Press 'Ctrl+D' (or 'Ctrl+Z' on Windows) to save and stop writing.\n");

    while ((ch = getchar()) != EOF) {
        fputc(ch, file);
    }

    fclose(file);
    printf("\nFile '%s' saved successfully!\n", filename);
}

// Function to open an existing file
void open_file() {
    char filename[100];
    FILE *file;
    char ch;

    printf("\nEnter the filename to open (with extension): ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove the newline character

    file = fopen(filename, "r");
    if (file == NULL) {
        error_message("Error opening the file. Make sure the file exists.");
        return;
    }

    printf("\n--- Contents of '%s' ---\n", filename);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    printf("\n--- End of file ---\n");
}

// Function to append text to an existing file
void append_to_file() {
    char filename[100];
    FILE *file;
    char ch;

    printf("\nEnter the filename to append to (with extension): ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove the newline character

    file = fopen(filename, "a");
    if (file == NULL) {
        error_message("Error opening the file for appending. Make sure the file exists.");
        return;
    }

    printf("Start typing the text you want to append below:\n");
    printf("Press 'Ctrl+D' (or 'Ctrl+Z' on Windows) to stop appending.\n");

    while ((ch = getchar()) != EOF) {
        fputc(ch, file);
    }

    fclose(file);
    printf("\nFile '%s' appended successfully!\n", filename);
}

// Function to view file contents with syntax highlighting
void view_file_contents() {
    char filename[100];
    FILE *file;
    char line[256];

    printf("\nEnter the filename to view (with extension): ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove the newline character

    file = fopen(filename, "r");
    if (file == NULL) {
        error_message("Error opening the file. Make sure the file exists.");
        return;
    }

    printf("\n--- Contents of '%s' (with basic syntax highlighting) ---\n", filename);
    while (fgets(line, sizeof(line), file)) {
        highlight_keywords(line);
    }

    fclose(file);
    printf("\n--- End of file ---\n");
}

// Function to highlight specific C language keywords
void highlight_keywords(const char *line) {
    const char *keywords[] = {"int", "return", "void", "if", "else", "while", "for", "char", "float", "double", "#include"};
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
    int i, j, is_keyword;

    char word[100];
    int word_index = 0;

    for (i = 0; line[i] != '\0'; i++) {
        if (isalnum(line[i]) || line[i] == '_') {
            word[word_index++] = line[i];
        } else {
            if (word_index > 0) {
                word[word_index] = '\0'; // End the word
                is_keyword = 0;
                for (j = 0; j < num_keywords; j++) {
                    if (strcmp(word, keywords[j]) == 0) {
                        printf("\033[1;32m%s\033[0m", word); // Highlight keyword in green
                        is_keyword = 1;
                        break;
                    }
                }
                if (!is_keyword) {
                    printf("%s", word); // Print non-keyword words normally
                }
                word_index = 0;
            }
            putchar(line[i]); // Print the non-alphanumeric character
        }
    }
}

// Function to search for specific text in a file
void search_in_file() {
    char filename[100], search_text[100], line[256];
    FILE *file;
    int line_number = 1, found = 0;

    printf("\nEnter the filename to search (with extension): ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove the newline character

    printf("Enter the text to search for: ");
    fgets(search_text, 100, stdin);
    search_text[strcspn(search_text, "\n")] = 0; // Remove the newline character

    file = fopen(filename, "r");
    if (file == NULL) {
        error_message("Error opening the file. Make sure the file exists.");
        return;
    }

    printf("\nSearching for \"%s\" in '%s'...\n", search_text, filename);
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_text) != NULL) {
            printf("Found on line %d: %s", line_number, line);
            found = 1;
        }
        line_number++;
    }

    if (!found) {
        printf("No occurrences of \"%s\" found in the file.\n", search_text);
    }

    fclose(file);
}

// Function to modify or delete lines in the file
void modify_or_delete_line() {
    char filename[100], line[256], new_line[256];
    FILE *file, *temp_file;
    int line_number, current_line = 1, choice;

    printf("\nEnter the filename to modify (with extension): ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove the newline character

    file = fopen(filename, "r");
    if (file == NULL) {
        error_message("Error opening the file. Make sure the file exists.");
        return;
    }

    printf("Enter the line number to modify or delete: ");
    scanf("%d", &line_number);
    getchar(); // Consume the newline character left by scanf

    printf("Choose an action:\n");
    printf("1. Modify line\n");
    printf("2. Delete line\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &choice);
    getchar(); // Consume the newline character

    temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        fclose(file);
        error_message("Error creating temporary file.");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (current_line == line_number) {
            if (choice == 1) {
                printf("Enter the new content for line %d: ", line_number);
                fgets(new_line, sizeof(new_line), stdin);
                new_line[strcspn(new_line, "\n")] = 0; // Remove the newline character
                fprintf(temp_file, "%s\n", new_line);
            } // Skip line if deleting
        } else {
            fprintf(temp_file, "%s", line);
        }
        current_line++;
    }

    fclose(file);
    fclose(temp_file);
    remove(filename);
    rename("temp.txt", filename);

    printf("Changes saved successfully to '%s'.\n", filename);
}

// Function to display an error message
void error_message(const char *message) {
    printf("\033[1;31mError: %s\033[0m\n", message); // Display error in red
}

// Function to save the file and exit
void save_and_exit() {
    printf("Saving files and exiting the C Text Editor...\n");
    printf("Thank you for using this editor. Goodbye!\n");
    exit(0);
}
