#include <stdio.h> // Standard Input Output
#include <stdlib.h> // For other libraries: system("cls")
#include <unistd.h> // For usleep function
#include <conio.h> // for getch();
#include <time.h> // For getting current time
#include <string.h> // For string, more than one characters. 
#include <ctype.h> 

char year;

void classroommanagement_header() {
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen

    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                                                                                      |\n");
    printf("|                               P H I L T E C H   C L A S S R O O M   M A N A G E M E N T                              |\n");
    printf("|                                                                                                                      |\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                                                                                      |\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
}

void enrollment_header() {
	printf("\033[H");
	printf("\033[48;5;52m\033[38;5;15m");
	printf("\033[2J"); // Clear screen
	
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                                                                                      |\n");
    printf("|                                     P H I L T E C H   E N R O L L M E N T  F O R M                                   |\n");
    printf("|                                                                                                                      |\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                                                                                      |\n");
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
}

void loadingscreen() {
    int width = 20; // Width of the loading bar

    // Clear screen and set background to maroon with white text
    printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
    printf("\033[2J"); // Clear screen

    // Move cursor to the middle of the screen (approximately 12 lines down)
    printf("\033[12;0H");

    // Loading bar loop
    for (int i = 0; i <= 100; i += 5) {
        int progress = i / (100 / width); // Calculate number of "#" for progress

        // Display loading message and progress bar
        printf("\t\t\t\t\t------------------------------------------\n");
        printf("\t\t\t\t\t|          LOADING, PLEASE WAIT...       |\n");
        printf("\t\t\t\t\t------------------------------------------\n");
        printf("\t\t\t\t\t["); // Start of the loading bar
        for (int j = 0; j < width; j++) {
            if (j < progress) {
                printf("#"); // Filled part of the bar
            } else {
                printf(" "); // Unfilled part of the bar
            }
        }
        printf("] %d%%\r", i); // Display progress percentage with carriage return
        fflush(stdout); // Ensure the progress bar updates immediately
        usleep(100000); // Pause for 100 milliseconds

        // Clear the loading bar text for the next frame
        printf("\033[A\033[A\033[A"); // Move cursor up 3 lines to overwrite
    }

    // Completed loading bar
    printf("\t\t\t\t\t------------------------------------------\n");
    printf("\t\t\t\t\t|             LOADING COMPLETE!          |\n");
    printf("\t\t\t\t\t------------------------------------------\n");
    sleep(1);

    // Clear screen again and reset colors
    printf("\033[0m"); // Reset colors
    printf("\033[2J"); // Clear screen
    printf("\033[H"); // Move cursor to the top-left corner
}

void studentAttendance() {
    char studentName[100];
    char repeat;

    do {
        // Get student's name from user only once at the start
        if (repeat != 'y' && repeat != 'Y') {
            // Get student's name from user
            printf("\033[H"); // Move cursor to the top-left corner
            printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
            printf("\033[2J"); // Clear screen

            // Student details prompt
            printf("                    --------------------------------------------------------------------------------\n");
            printf("                   |                     Please enter the student's name                          |");
            printf("                    --------------------------------------------------------------------------------\n");
            printf("                    _________________________ \n");
            printf("                   | Enter student's name: ");
            fgets(studentName, sizeof(studentName), stdin);
            studentName[strcspn(studentName, "\n")] = 0; // Remove trailing newline
        }

        // Clear the screen
        printf("\033[H");
        printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
        printf("\033[2J"); // Clear screen

        // Print student info
        printf("                   -----------------------------------------------------------------------------\n");
        printf("                   |  Student: %-64s|\n", studentName);
        printf("                   -----------------------------------------------------------------------------\n");

        // Month Input Loop (Only September to May)
        int month;
        const char* monthNames[] = {
            "Invalid", "September", "October", "November", "December",
            "January", "February", "March", "April", "May"
        };

        while (1) {
            // Display numbered choices for months
            printf("                    ---------------------------------------------------------------------------\n");
            printf("                   |                               SELECT MONTH:                               |\n");
            printf("                   |---------------------------------------------------------------------------|\n");
            printf("                   |   1. September 2024 (09) | 2. October 2024 (10) | 3. November 2024 (11)   |\n");
            printf("                   |   4. December 2024 (12)  | 5. January 2025 (01) | 6. February 2025 (02)   |\n");
            printf("                   |   7. March 2025 (03)     | 8. April 2025 (04)   | 9. May 2025 (05)        |\n");
            printf("                    ---------------------------------------------------------------------------\n");
            printf("                   | Please select a month by entering the number (1-9): ");
            scanf("%d", &month);
			
            if (month >= 1 && month <= 9) {
                break; // Exit loop if valid month is selected
            } else {
                printf("\033[1;31mInvalid month selection! Please choose a valid month between 1 and 9.\033[0m\n");
            }
        }

        // Get current year
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int year = tm.tm_year + 1900; // tm_year is years since 1900

        // Define days of the week for display
        const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

        // Days in month (hardcoded for simplicity, check for leap years for February)
        int daysInMonth;
        switch (month) {
            case 6:
                daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
                break;
            case 4: case 9: case 11:
                daysInMonth = 30;
                break;
            default:
                daysInMonth = 31;
        }

        // Randomly generate attendance (1 for present, 0 for absent)
        srand(time(NULL));
        int attendance[daysInMonth];
        for (int i = 0; i < daysInMonth; i++) {
            attendance[i] = 1; // Initially set all to present
        }

        // Limit the number of absences (1-3 days per month)
        int absenceCount = rand() % 3 + 1; // Random number between 1 and 3
        for (int i = 0; absenceCount > 0 && i < daysInMonth; i++) {
            if (attendance[i] == 1 && rand() % 2 == 0) {
                attendance[i] = 0;
                absenceCount--;
            }
        }

        // Display the calendar header
        printf("\n");
        printf("                           Calendar for Year %d, %s\n", year, monthNames[month]);

        // Center and display day names
        printf("                           ");
        for (int i = 0; i < 7; i++) { 
            printf(" %s ", daysOfWeek[i]);
        }
        printf("\n");

        // Start the calendar from the first day of the month
        int startDay = (tm.tm_wday + 1) % 7; // Calculate which day the month starts on
        int presents = 0, absences = 0;

        // Print the calendar rows
        int currentDay = 1;
        for (int i = 0; i < startDay + daysInMonth; i++) {
            if (i % 7 == 0) {
                printf("                           "); // Center the calendar rows
            }

            if (i < startDay) {
                printf("     "); // Empty spaces before the first day
            } else {
                if (attendance[currentDay - 1] == 0) {
                    printf("\033[1;31m%2d   \033[15m", currentDay); // Red for absences
                    absences++;
                } else {
                    printf("\033[1;37m%2d   \033[15m", currentDay); // White for present
                    presents++;
                }
                currentDay++;
            }

            // Move to the next line after every 7 days (end of the week)
            if ((i + 1) % 7 == 0) {
                printf("\n");
            }
        }

        // Display attendance summary
        printf("\n\n");
        printf("                           Presents: %d\n", presents);
        printf("                           Absences: %d\n", absences);

        // Reset color
        printf("                    ---------------------------------------------------------------------------\n");
        printf("\033[15m");

        // Ask if the user wants to check another student's attendance
        printf("\n\033[48;5;52m\033[38;5;15m");
        printf("                    Do you want to check another student's attendance? (y/n): ");
        printf("\033[15m");
        getchar(); // Clear newline from buffer
        repeat = getchar();

        if (repeat == 'n' || repeat == 'N') {
            printf("\033[48;5;52m\033[38;5;15m");
            printf("\n                    Thank you, redirecting you now to the main menu!\n");
            printf("\033[15m");
            sleep(3);
        }

    } while (repeat == 'y' || repeat == 'Y'); // Repeat if the user enters 'y' or 'Y'
}

void teachersAttendance() {
    // Declare teacher name and subject
    char teacherName[100], subject[100];
    char repeat;

    do {
        // Get teacher's name and subject only once
        if (repeat != 'y' && repeat != 'Y') {
            // Get teacher's name and subject from user
            printf("\033[H"); // Move cursor to the top-left corner
            printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
            printf("\033[2J"); // Clear screen

            // Teacher details prompt
            printf("                    --------------------------------------------------------------------------------\n");
            printf("                   |                Please enter the teacher's name and subject details             |\n");
            printf("                    --------------------------------------------------------------------------------\n");
            printf("                    _________________________ \n");
            printf("                   | Enter teacher's name: ");
            fgets(teacherName, sizeof(teacherName), stdin);
            teacherName[strcspn(teacherName, "\n")] = 0; // Remove trailing newline

            // Ensure teacher's name is not empty
            while (teacherName[0] == '\0') {
                printf("\033[1;31mTeacher's name cannot be empty! Please enter again:\033[15m ");
                printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
                fgets(teacherName, sizeof(teacherName), stdin);
                teacherName[strcspn(teacherName, "\n")] = 0;
            }

            printf("                    _________________________ \n");
            printf("                   | Enter subject's name: ");
            fgets(subject, sizeof(subject), stdin);
            subject[strcspn(subject, "\n")] = 0; // Remove trailing newline

            // Ensure subject name is not empty
            while (subject[0] == '\0') {
                printf("\033[1;31mSubject's name cannot be empty! Please enter again:\033[15m ");
                printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
                fgets(subject, sizeof(subject), stdin);
                subject[strcspn(subject, "\n")] = 0;
            }
        }

        // Clear the screen
        printf("\033[H");
        printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
        printf("\033[2J"); // Clear screen

        // Print teacher and subject info
        printf("                   -----------------------------------------------------------------------------\n");
        printf("                   |  Teacher: %-64s|\n", teacherName);
        printf("                   |  Subject: %-64s|\n", subject);
        printf("                   -----------------------------------------------------------------------------\n");

        // Month Input Loop (Only September to May)
        int month;
        const char* monthNames[] = {
            "Invalid", "September", "October", "November", "December",
            "January", "February", "March", "April", "May"
        };

        while (1) {
            // Display numbered choices for months
            printf("                    ---------------------------------------------------------------------------\n");
            printf("                   |                               SELECT MONTH:                               |\n");
            printf("                   |---------------------------------------------------------------------------|\n");
            printf("                   |   1. September 2024 (09) | 2. October 2024 (10) | 3. November 2024 (11)   |\n");
            printf("                   |   4. December 2024 (12)  | 5. January 2025 (01) | 6. February 2025 (02)   |\n");
            printf("                   |   7. March 2025 (03)     | 8. April 2025 (04)   | 9. May 2025 (05)        |\n");
            printf("                    ---------------------------------------------------------------------------\n");
            printf("                   | Please select a month by entering the number (1-9): ");
            scanf("%d", &month);

            if (month >= 1 && month <= 9) {
                break; // Exit loop if valid month is selected
            } else {
                printf("\033[1;31mInvalid month selection! Please choose a valid month between 1 and 9.\033[15m\n");
            }
        }

        // Get current year
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int year = tm.tm_year + 1900; // tm_year is years since 1900

        // Define days of the week for display
        const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

        // Days in month (hardcoded for simplicity, check for leap years for February)
        int daysInMonth;
        switch (month) {
            case 6:
                daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
                break;
            case 4: case 9: case 11:
                daysInMonth = 30;
                break;
            default:
                daysInMonth = 31;
        }

        // Randomly generate attendance (1 for present, 0 for absent)
        srand(time(NULL));
        int attendance[daysInMonth];
        for (int i = 0; i < daysInMonth; i++) {
            attendance[i] = 1; // Initially set all to present
        }

        // Limit the number of absences (1-3 days per month)
        int absenceCount = rand() % 3 + 1; // Random number between 1 and 3
        for (int i = 0; absenceCount > 0 && i < daysInMonth; i++) {
            if (attendance[i] == 1 && rand() % 2 == 0) {
                attendance[i] = 0;
                absenceCount--;
            }
        }

        // Display the calendar header
        printf("\n\033[48;5;52m\033[38;5;15m");
        printf("\033[48;5;52m\033[38;5;15m                           Calendar for Year %d, %s\n", year, monthNames[month]);

        // Center and display day names
        printf("\033[48;5;52m\033[38;5;15m                           ");
        for (int i = 0; i < 7; i++) {
            printf("\033[48;5;52m\033[38;5;15m %s ", daysOfWeek[i]);
        }
        printf("\033[48;5;52m\033[38;5;15m\n");

        // Start the calendar from the first day of the month
        int startDay = (tm.tm_wday + 1) % 7; // Calculate which day the month starts on
        int presents = 0, absences = 0;

        // Print the calendar rows
        int currentDay = 1;
        for (int i = 0; i < startDay + daysInMonth; i++) {
            if (i % 7 == 0) {
                printf("\033[48;5;52m\033[38;5;15m                           "); // Center the calendar rows
            }

            if (i < startDay) {
                printf("\033[48;5;52m\033[38;5;15m     "); // Empty spaces before the first day
            } else {
                if (attendance[currentDay - 1] == 0) {
                    printf("\033[1;31m%2d   \033[15m ", currentDay); // Red for absences
                    absences++;
                } else {
                    printf("\033[1;37m%2d   \033[15m", currentDay); // White for present
                    presents++;
                }
                currentDay++;
            }

            // Move to the next line after every 7 days (end of the week)
            if ((i + 1) % 7 == 0) {
                printf("\033[48;5;52m\033[38;5;15m\n");
            }
        }

        // Display attendance summary
        printf("\033[48;5;52m\033[38;5;15m\n\n");
        printf("\033[48;5;52m\033[38;5;15m                           Presents: %d\n", presents);
        printf("\033[48;5;52m\033[38;5;15m                           Absences: %d\n", absences);

        // Reset color
        printf("\033[48;5;52m\033[38;5;15m");
        printf("\033[15m");

        // Ask if the user wants to check another teacher's attendance
        printf("\n\033[48;5;52m\033[38;5;15m");
        printf("\033[48;5;52m\033[38;5;15m                    Do you want to check another month's attendance? (y/n):");
        printf("\033[15m");

        // Handle invalid input for repeat
        while (1) {
            getchar(); // Clear newline from buffer
            repeat = getchar();
            if (repeat == 'y' || repeat == 'Y' || repeat == 'n' || repeat == 'N') {
                break;
            } else {
                printf("\033[1;31mINPUT INVALID! Please only type Y/y or N/n.\033[15m\n");
            }
        }

        if (repeat == 'n' || repeat == 'N') {
            printf("\033[48;5;52m\033[38;5;15m");
            printf("\n\033[48;5;52m\033[38;5;15m                    Thank you, redirecting you now to the main menu!\n");
            printf("\033[15m");
            sleep(3);
        }

    } while (repeat == 'y' || repeat == 'Y'); // Repeat if the user enters 'y' or 'Y'
}


float generateRandomGrade() {
    float grades[] = {1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5, 2.75, 3.0, 4.0, 5.0};
    int index = rand() % (sizeof(grades) / sizeof(grades[0]));
    return grades[index];
}

char* evaluateGrade(float grade) {
    if (grade == 5.0 || grade == 4.0) {
        return "FAILED";
    } else if (grade <= 3.0) {
        return "PASSED";
    } else {
        return "INCOMPLETE";
    }
}

void printSubjectDetails(char* code, char* description, float grade) {
    printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
    printf("                   | %-15s | %-40s |     %.2f      | %-12s |\n", 
           code, description, grade, evaluateGrade(grade));
    printf("\033[0m"); // Reset to default colors
}

float generateRandomGrade();
void printSubjectDetails(const char *code, const char *subject, float grade);

int isValidName(const char *name) {
    for (size_t i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int isValidNumber(const char *number) {
    for (size_t i = 0; number[i] != '\0'; i++) {
        if (!isdigit(number[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidSchoolYear(const char *schoolYear) {
    int length = strlen(schoolYear);
    if (length != 9 || schoolYear[4] != '-') {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        if (!isdigit(schoolYear[i]) || !isdigit(schoolYear[i + 5])) {
            return 0;
        }
    }
    return 1;
}

int isValidYearLevel(const char *yearLevel) {
    return (strcmp(yearLevel, "1") == 0 || strcmp(yearLevel, "2") == 0 || strcmp(yearLevel, "3") == 0 || strcmp(yearLevel, "4") == 0);
}

int isValidCourse(const char *course) {
    return (strcmp(course, "BSCS") == 0 || strcmp(course, "BSOA") == 0 || strcmp(course, "BTVTED") == 0);
}

int isValidStudentStatus(const char *status) {
    return (strcasecmp(status, "REGULAR") == 0 || strcasecmp(status, "NON-REGULAR") == 0);
}

void getInput(const char *prompt, char *buffer, size_t size, int (*validator)(const char *), const char *errorMessage) {
    do {
        printf("%s", prompt);
        fgets(buffer, size, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) {
            printf("Input cannot be empty. Please try again.\n");
        } else if (validator && !validator(buffer)) {
            printf("%s\n", errorMessage);
            memset(buffer, 0, size); // Clear the invalid input
        } else {
            break;
        }
    } while (1);
}

void eogRequest() {
    char course[100] = "", yearLevel[100] = "", studentStatus[20] = "", studentNumber[20] = "", studentName[100] = "", schoolYear[100] = "";
    float grades[18];
    char subjects[18][50] = {
        "UNDERSTANDING THE SELF", "READINGS IN PHIL. HISTORY", "PURPOSIVE COMMUNICATION",
        "MATHEMATICS IN THE MODERN WORLD", "INTRODUCTION TO COMPUTING", 
        "FUNDAMENTAL OF PROGRAMMING 1", "PHILTECH LIFE AND SPIRIT", "READINGS IN THE PHILIPPINE HISTORY", 
        "PHYSICAL FITNESS 1", "NATIONAL SERVICE TRAINING PROGRAM 1", "ETHICS", "WEB SYSTEM AND TECHNOLOGIES",
        "ART APPRECIATION", "INTERMEDIATE PROGRAMMING", "COMPUTER SYSTEM SERVICING", "PHYSICAL FITNESS 2",
        "NATIONAL TRAINING PROGRAM 2", "VISUAL GRAPHIC DESIGN"
    };
    char codes[18][10] = {
        "GE1", "GE2", "GE3", "GE4", "CC111", "CC112", "PLS", "PE1", "NSTP", "GE5",
        "WST", "CSS121", "PE2", "NSTP2", "VGD"
    };
    char repeat;

    do {
        printf("\033[H\033[48;5;52m\033[38;5;15m\033[2J"); // Clear screen with maroon background and white text

        printf("                    -------------------------------------------------------------------------------------------------\n");
        printf("                   |                                   EVALUATION OF GRADES REQUEST                                  |\n");
        printf("                    -------------------------------------------------------------------------------------------------\n");

        // Display previously entered details (if any)
        if (strlen(studentName) > 0) printf("Current Student Name: %s\n", studentName);
        if (strlen(studentNumber) > 0) printf("Current Student Number: %s\n", studentNumber);
        if (strlen(schoolYear) > 0) printf("Current School Year: %s\n", schoolYear);
        if (strlen(yearLevel) > 0) printf("Current Year Level: %s\n", yearLevel);
        if (strlen(course) > 0) printf("Current Course: %s\n", course);
        if (strlen(studentStatus) > 0) printf("Current Status: %s\n", studentStatus);

        // Get student details with validation
        getInput("                    Enter your student name: ", studentName, sizeof(studentName), isValidName, "Invalid name. Only alphabetic characters and spaces are allowed.");
        getInput("                    Enter your student number: ", studentNumber, sizeof(studentNumber), isValidNumber, "Invalid student number. Only numeric values are allowed.");
        getInput("                    Enter your school year (e.g., 2024-2025): ", schoolYear, sizeof(schoolYear), isValidSchoolYear, "Invalid school year format. Use YYYY-YYYY.");
        getInput("                    Enter your year level (1-4): ", yearLevel, sizeof(yearLevel), isValidYearLevel, "Invalid year level. Please enter 1, 2, 3, or 4.");
        getInput("                    Enter your course (BSCS, BSOA, BTVTED): ", course, sizeof(course), isValidCourse, "Invalid course. Please enter BSCS, BSOA, or BTVTED.");
        getInput("                    Enter your student status (REGULAR or Non-Regular): ", studentStatus, sizeof(studentStatus), isValidStudentStatus, "Invalid status. Please enter REGULAR or Non-Regular.");

        sleep(2);

        // Generate random grades for all subjects
        for (int i = 0; i < 18; i++) {
            grades[i] = generateRandomGrade();
        }
		printf("\033[H\033[48;5;52m\033[38;5;15m\033[2J"); // Clear screen with maroon background and white text
		
        printf("                    ---------------------------------------------------------------------------------------------\n");
        printf("                   | Student Name: %-26s       Status: %-33s  |\n", studentName, studentStatus);
        printf("                   | Student Number: %-24s       School Year: %-28s  |\n", studentNumber, schoolYear);
        printf("                   | Course: %-32s       Year Level: %-29s  |\n", course, yearLevel);
        printf("                   ---------------------------------------------------------------------------------------------\n");
        printf("                   |  SUBJECT CODE   |           DESCRIPTION                    |    GRADES     |  EVALUATION  |\n");
        printf("                   |-----------------|------------------------------------------|---------------|--------------|\n");

        // Print details of all subjects
        for (int i = 0; i < 18; i++) {
            printSubjectDetails(codes[i], subjects[i], grades[i]);
        }
        
        printf("\033[48;5;52m\033[38;5;15m");

        // Ask if the user wants to repeat
        printf("\n                    Do you want to evaluate another student? (y/n): ");
        getchar(); // Clear newline from buffer
        repeat = getchar();

        if (repeat == 'n' || repeat == 'N') {
            printf("\n \033[48;5;52m\033[38;5;15m                   Thank you, redirecting you now to the main menu!\n");
            printf("\033[48;5;52m\033[38;5;15m");
            sleep(3);
        }

    } while (repeat == 'y' || repeat == 'Y'); // Repeat if the user enters 'y' or 'Y'
    printf("\033[48;5;52m\033[38;5;15m");
}



// Function to validate if an email is in the correct format
int isValidEmail(char *email) {
    int atCount = 0, dotCount = 0;
    int len = strlen(email);

    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            atCount++;
        }
        if (email[i] == '.') {
            dotCount++;
        }
    }

    return (atCount == 1 && dotCount > 0);
}

// Function to validate contact number (only digits, length 10-15)
int isValidContactNumber(char *contactNumber) {
    int len = strlen(contactNumber);

    if (len < 10 || len > 15) return 0;

    for (int i = 0; i < len; i++) {
        if (!isdigit(contactNumber[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to validate date of birth format (dd/mm/yyyy)
int isValidDate(char *dateOfBirth) {
    int len = strlen(dateOfBirth);
    
    // Basic format validation (dd/mm/yyyy)
    if (len != 10 || dateOfBirth[2] != '/' || dateOfBirth[5] != '/') {
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if ((i != 2 && i != 5) && !isdigit(dateOfBirth[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to validate gender input (Male or Female)
int isValidGender(char *gender) {
    return (strcmp(gender, "Male") == 0 || strcmp(gender, "Female") == 0);
}

// Function to validate preferred course (BTVTED, BSOA, BSCS)
int isValidPreferredCourse(char *course) {
    return (strcmp(course, "BTVTED") == 0 || strcmp(course, "BSOA") == 0 || strcmp(course, "BSCS") == 0);
}

// Function to validate preferred schedule (Regular or Sunday Class)
int isValidPreferredSchedule(char *schedule) {
    return (strcmp(schedule, "Regular") == 0 || strcmp(schedule, "Sunday Class") == 0);
}

// Function to validate academic level (1 to 4)
int isValidAcademicLevel(char *level) {
    return (strcmp(level, "1") == 0 || strcmp(level, "2") == 0 || strcmp(level, "3") == 0 || strcmp(level, "4") == 0);
}

// Function to check if input contains only letters (for names)
int isValidName(char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// Function to check if input contains only digits (for age, year, etc.)
int isValidInteger(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to get valid string input (including spaces)
void getValidString(char *input, char *prompt, int maxLength, int (*validator)(char *)) {
    int valid = 0;
    while (!valid) {
        printf("%s", prompt);
        fgets(input, maxLength, stdin);
        input[strcspn(input, "\n")] = 0; // Remove trailing newline

        valid = (*validator)(input);
        if (!valid) {
            printf("Invalid input. Please try again.\n");
            sleep(1);
            printf("\033[H");
	    	printf("\033[48;5;52m\033[38;5;15m");
	    	printf("\033[2J"); // Clear screen
        }
    }
}

// Function to validate email input
void getValidEmailInput(char *email) {
    int valid = 0;
    enrollment_header();
    while (!valid) {
        getValidString(email, "| Enter your email: ", 50, isValidEmail);
        if (!isValidEmail(email)) {
            printf("The email should be in the format user@example.com.\n");
            sleep(1);
            printf("\033[H");
	   	 	printf("\033[48;5;52m\033[38;5;15m");
	    	printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

// Function to validate contact number input
void getValidContactNumberInput(char *contactNumber) {
	enrollment_header();
    int valid = 0;
    while (!valid) {
        getValidString(contactNumber, "| Enter your contact number: ", 20, isValidContactNumber);
        if (!isValidContactNumber(contactNumber)) {
            printf("The contact number should be numeric and between 10-15 digits.\n");
            sleep(1);
            printf("\033[H");
	    	printf("\033[48;5;52m\033[38;5;15m");
	   		printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

// Function to validate date of birth input
void getValidDateInput(char *dateOfBirth) {
	    enrollment_header();
    int valid = 0;
    while (!valid) {
        getValidString(dateOfBirth, "| Enter your date of birth (dd/mm/yyyy): ", 20, isValidDate);
        if (!isValidDate(dateOfBirth)) {
            printf("Invalid date format. The date should be in dd/mm/yyyy format.\n");
            sleep(1);
            printf("\033[H");
		    printf("\033[48;5;52m\033[38;5;15m");
		    printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

// Function to validate gender input
void getValidGenderInput(char *gender) {
	    enrollment_header();
    int valid = 0;
    while (!valid) {
        getValidString(gender, "| Enter your gender (Male/Female): ", 10, isValidGender);
        if (!isValidGender(gender)) {
            printf("Invalid gender. Please enter 'Male' or 'Female'.\n");
            sleep(1);
            printf("\033[H");
	    printf("\033[48;5;52m\033[38;5;15m");
	    printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

// Function to validate preferred course input
void getValidPreferredCourse(char *course) {
	    enrollment_header();
    int valid = 0;
    while (!valid) {
        getValidString(course, "| Enter your preferred course (BTVTED/BSOA/BSCS): ", 10, isValidPreferredCourse);
        if (!isValidPreferredCourse(course)) {
            printf("Invalid course. Please enter 'BTVTED', 'BSOA', or 'BSCS'.\n");
            sleep(1);
            printf("\033[H");
	    printf("\033[48;5;52m\033[38;5;15m");
	    printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

// Function to validate preferred schedule input
void getValidPreferredSchedule(char *schedule) {
	    enrollment_header();
    int valid = 0;
    while (!valid) {
        getValidString(schedule, "| Enter your preferred schedule (Regular/Sunday Class): ", 20, isValidPreferredSchedule);
        if (!isValidPreferredSchedule(schedule)) {
            printf("Invalid schedule. Please enter 'Regular' or 'Sunday Class'.\n");
            sleep(1);
            printf("\033[H");
	    printf("\033[48;5;52m\033[38;5;15m");
	    printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

// Function to validate academic level input
void getValidAcademicLevel(char *level) {
	    enrollment_header();
    int valid = 0;
    while (!valid) {
        getValidString(level, "| Enter your academic level (1-4): ", 10, isValidAcademicLevel);
        if (!isValidAcademicLevel(level)) {
            printf("Invalid academic level. Please enter a number between 1 and 4.\n");
            sleep(1);
            printf("\033[H");
	    printf("\033[48;5;52m\033[38;5;15m");
	    printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

// Function to validate name input
void getValidNameInput(char *name) {
	    enrollment_header();
    int valid = 0;
    while (!valid) {
        getValidString(name, "| Enter your full name: ", 100, isValidName);
        if (!isValidName(name)) {
            printf("The name should only contain letters and spaces.\n");
            sleep(1);
            printf("\033[H");
	    printf("\033[48;5;52m\033[38;5;15m");
	    printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

// Function to validate integer input (e.g., for year, age, etc.)
void getValidIntegerInput(char *input, char *prompt) {
    int valid = 0;
    while (!valid) {
        getValidString(input, prompt, 20, isValidInteger);
        if (!isValidInteger(input)) {
            printf("The input should be just integers.\n");
            sleep(1);
	    printf("\033[H");
	    printf("\033[48;5;52m\033[38;5;15m");
	    printf("\033[2J"); // Clear screen
        } else {
            valid = 1;
        }
    }
}

void enrollment() {
	
	printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    // Declare the variables
    char fullName[100], email[50], contactNumber[20], homeAddress[100], currentAddress[100];
    char gender[10], dateOfBirth[20], gmail[50], highSchoolName[100], highSchoolAddress[100];
    char yearOfGraduation[10], preferredCourse[10], preferredSchedule[20], academicLevel[20];
    char parentGuardianName[100], parentGuardianContact[20], howDidYouKnow[100];
    char editChoice[5];
    int editField;

		printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	    printf("|                                                                                                                      |\n");
	    printf("|                                     P H I L T E C H   E N R O L L M E N T  F O R M                                   |\n");
	    printf("|                                                                                                                      |\n");
	    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	    printf("|                                                                                                           [ 9 ] Back |\n");
	    printf("+----------------------------------------------------------------------------------------------------------------------+\n");

    // Collecting user information with validation
    getValidNameInput(fullName);
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    getValidEmailInput(email);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    getValidContactNumberInput(contactNumber);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    enrollment_header();
    getValidString(homeAddress, "Enter your home address: ", 100, isValidName);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    enrollment_header();
	getValidString(currentAddress, "Enter your current address: ", 100, isValidName);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    getValidGenderInput(gender);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    getValidDateInput(dateOfBirth);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
   
    enrollment_header();
    getValidString(gmail, "Enter your Gmail account: ", 50, isValidEmail);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    enrollment_header();
    getValidString(highSchoolName, "Enter your high school name: ", 100, isValidName);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    enrollment_header();
    getValidString(highSchoolAddress, "Enter your high school address: ", 100, isValidName);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    enrollment_header();
    getValidIntegerInput(yearOfGraduation, "Enter your year of graduation: ");
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    getValidPreferredCourse(preferredCourse);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    getValidPreferredSchedule(preferredSchedule);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    getValidAcademicLevel(academicLevel);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    enrollment_header();
    getValidString(parentGuardianName, "Enter your parent/guardian name: ", 100, isValidName);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    getValidContactNumberInput(parentGuardianContact);
    
    printf("\033[H");
    printf("\033[48;5;52m\033[38;5;15m");
    printf("\033[2J"); // Clear screen
    
    enrollment_header();
    getValidString(howDidYouKnow, "How did you know about this school?: ", 100, isValidName);

    // Clear the screen before showing the information
    printf("\033[2J");
    printf("\033[H"); 

    // Adding a delay before displaying the final information
    sleep(2);

    // Start displaying the collected information
    do {
		printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	    printf("|                                                                                                                      |\n");
	    printf("|                                     P H I L T E C H   E N R O L L M E N T  F O R M                                   |\n");
	    printf("|                                                                                                                      |\n");
	    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	    printf("|                                        S U B M I T T E D  I N F O R M A T I O N                           [ 9 ] Back |\n");
	    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
        printf("| 1 | Full Name:                %s\n", fullName);
        printf("| 2 | Email:                    %s\n", email);
        printf("| 3 | Contact Number:           %s\n", contactNumber);
        printf("| 4 | Home Address:             %s\n", homeAddress);
        printf("| 5 | Current Address:          %s\n", currentAddress);
        printf("| 6 | Gender:                   %s\n", gender);
        printf("| 7 | Date of Birth:            %s\n", dateOfBirth);
        printf("| 8 | Gmail Account:            %s\n", gmail);
        printf("| 9 | High School Name:         %s\n", highSchoolName);
        printf("|10 | High School Address:      %s\n", highSchoolAddress);
        printf("|11 | Year of Graduation:       %s\n", yearOfGraduation);
        printf("|12 | Preferred Course:         %s\n", preferredCourse);
        printf("|13 | Preferred Schedule:       %s\n", preferredSchedule);
        printf("|14 | Academic Level:           %s\n", academicLevel);
        printf("|15 | Parent/Guardian Name:     %s\n", parentGuardianName);
        printf("|16 | Parent/Guardian Contact:  %s\n", parentGuardianContact);
        printf("|17 | How Did You Know:         %s\n", howDidYouKnow);
        printf("+--------------------------------------------------------------------------------------------------------------------+\n");

        // Prompt to edit any field
        printf("\nWould you like to edit any information? Enter the field number to edit (or 0 to finish): ");
        fgets(editChoice, 5, stdin);
        editField = atoi(editChoice);

        // Logic to edit the specific field
        if (editField == 1) {
            getValidNameInput(fullName);
        } else if (editField == 2) {
            getValidEmailInput(email);
        } else if (editField == 3) {
            getValidContactNumberInput(contactNumber);
        } else if (editField == 4) {
            getValidString(homeAddress, "Enter your home address: ", 100, isValidName);
        } else if (editField == 5) {
            getValidString(currentAddress, "Enter your current address: ", 100, isValidName);
        } else if (editField == 6) {
            getValidGenderInput(gender);
        } else if (editField == 7) {
            getValidDateInput(dateOfBirth);
        } else if (editField == 8) {
            getValidString(gmail, "Enter your Gmail account: ", 50, isValidEmail);
        } else if (editField == 9) {
            getValidString(highSchoolName, "Enter your high school name: ", 100, isValidName);
        } else if (editField == 10) {
            getValidString(highSchoolAddress, "Enter your high school address: ", 100, isValidName);
        } else if (editField == 11) {
            getValidIntegerInput(yearOfGraduation, "Enter your year of graduation: ");
        } else if (editField == 12) {
            getValidPreferredCourse(preferredCourse);
        } else if (editField == 13) {
            getValidPreferredSchedule(preferredSchedule);
        } else if (editField == 14) {
            getValidAcademicLevel(academicLevel);
        } else if (editField == 15) {
            getValidString(parentGuardianName, "Enter your parent/guardian name: ", 100, isValidName);
        } else if (editField == 16) {
            getValidContactNumberInput(parentGuardianContact);
        } else if (editField == 17) {
            getValidString(howDidYouKnow, "How did you know about this school?: ", 100, isValidName);
        }
    } while (editField != 0); // End loop if user chooses to finish

    printf("Thank you for submitting your enrollment information.\n");
}

#define MAX_SCHEDULES 15
#define MAX_SECTIONS 16

struct Schedule {
    char room[20];
    char timeAndDay[30];
    char subjectCode[15];
    char instructor[30];
};

struct Course {
    char name[10];
    char section[MAX_SECTIONS][10];
    struct Schedule schedules[MAX_SCHEDULES];
    int scheduleCount;
};

void displaySchedule(struct Course course, char* section) {
    classroommanagement_header();
    printf("\n                   Section: %s \n", section);
    printf("                   +----------------------------------------------------------------------------------+\n");
    printf("                   |                                     SCHEDULES                                    |\n");
    printf("                   |-------------+-----------------------+-------------------+------------------------|\n");
    printf("                   |   ROOM/FL#  |       TIME & DAY      |   SUBJECT CODE    |       INSTRUCTOR       |\n");
    printf("                   |-------------+-----------------------+-------------------+------------------------|\n");
    for (int i = 0; i < course.scheduleCount; i++) {
        printf("                   | %-11s | %-21s | %-17s | %-22s |\n",
               course.schedules[i].room,
               course.schedules[i].timeAndDay,
               course.schedules[i].subjectCode,
               course.schedules[i].instructor);
        printf("                   |-------------+-----------------------+-------------------+------------------------|\n");
    }
    printf("                   +----------------------------------------------------------------------------------+\n");
}

void classroomManagement() {
    struct Course courses[3] = {
        {"BTVTED", {
            "1M1", "1M2", "1N1", "1N2",
            "2M1", "2M2", "2N1", "2N2",
            "3M1", "3M2", "3N1", "3N2",
            "4M1", "4M2", "4N1", "4N2"
        }, {
            {"MAIN 405", "TUE: 07:00AM-08:45AM", "PCK105", "MR. MIGUEL RIVERA"},
            {"MAIN 404", "TUE: 09:00AM-10:45AM", "TLE104", "MS. CHRISTINE TAN"},
            {"MAIN 404", "TUE: 11:15AM-12:00PM", "TLE104", "MS. CHRISTINE TAN"},
            {"MAIN 406", "TUE: 12:00PM-02:00PM", "GE106", "MR. PEDRO REYES"},
            {"ANNEX 107", "THU: 07:00AM-08:45PM", "FCC104", "MR. MARK GONZALES"},
            {"ANNEX 106", "THU: 09:00AM-10:45AM", "PCK103", "MS. JOANNA CRUZ"},
            {"ANNEX LAB", "SAT: 07:00AM-08:45AM", "MAJOR2", "MR. MIGUEL SANTOS"},
            {"ANNEX LAB", "SAT: 09:00AM-10:45PM", "MAJOR2", "MR. MIGUEL SANTOS"},
            {"ANNEX 104", "SAT: 11:15AM-02:00PM", "PATHFIT3", "MR. JULIAN SANTIAGO" }
        }, 9},
        {"BSCS", {
            "1M1", "1M2", "1N1", "1N2",
            "2M1", "2M2", "2N1", "2N2",
            "3M1", "3M2", "3N1", "3N2",
            "4M1", "4M2", "4N1", "4N2"
        }, {
            {"MAIN 402", "MON: 07:00AM-10:00AM", "SE311", "SIR. PEDRO SANTOS"},
            {"MAIN 402", "MON: 10:00AM-11:15AM", "AL312", "MS. MAYETTE REYES"},
            {"MAIN 403", "MON: 12:00PM-02:00PM", "SP321", "MS. ANGELICA GONZALES"},
            {"COMLAB 1", "TUE: 07:00AM-11:15AM", "CC316", "SIR. CHRISTOPER TAN"},
            {"ANNEX 102", "WED: 09:00AM-10:45AM", "IAS311", "SIR. ANGELO MARTINEZ"},
            {"ANNEX 104", "WED: 10:45AM-01:00PM", "ELEC311", "SIR. GABRIEL HERNANDEZ"}
        }, 6},
        {"BSOA", {
            "1M1", "1M2", "1N1", "1N2",
            "2M1", "2M2", "2N1", "2N2",
            "3M1", "3M2", "3N1", "3N2",
            "4M1", "4M2", "4N1", "4N2"
        }, {
            {"MAIN 404", "MON: 11:15AM-01:00PM", "PATHFIT1", "MR. MICHAEL ATIENZA"},
            {"MAIN 404", "MON: 01:00PM-02:45PM", "NSTP1", "MR. MICHAEL ATIENZA"},
            {"MAIN 404", "MON: 03:00PM-04:00PM", "NSTP1", "MR. MICHAEL ATIENZA"},
            {"MAIN 404", "MON: 04:00PM-04:45PM", "NSTP1", "MR. MICHAEL ATIENZA"},
            {"MAIN 402", "TUE: 01:00PM-02:45PM", "GE1", "MS. LEILA QUILLANO"},
            {"MAIN 402", "TUE: 03:00PM-04:00PM", "GE1", "MS. LEILA QUILLANO"},
            {"MAIN 402", "TUE: 04:00PM-04:45PM", "FIL101", "MS. YABUT"},
            {"MAIN 402", "TUE: 05:15PM-07:00PM", "FIL101", "MS. YABUT"},
            {"MAIN 410", "FRI: 10:00AM-10:45AM", "OACC102", "MR. MACARIO"},
            {"LAB CL2", "FRI: 11:15AM-02:45PM", "OACC102", "MR. MACARIO"},
            {"MAIN 405", "FRI: 04:00PM-04:45PM", "GE2", "MR. RODRIGUEZ"},
            {"MAIN 405", "SAT: 05:15PM-07:00PM", "GE2", "MR. RODRIGUEZ"}
        }, 12}
    };

    int courseChoice, yearLevelChoice, sectionChoice;

    while (1) {
        system("cls");  // Clear the screen
        
        classroommanagement_header();
        printf("\n                   Available courses:\n");
        printf("                   1. BTVTED\n");
        printf("                   2. BSCS\n");
        printf("                   3. BSOA\n");
        printf("                   Enter the number corresponding to your course: ");
        courseChoice = getch() - '0';  // Capture single key press

        if (courseChoice < 1 || courseChoice > 3) {
            // Invalid input for course
            classroommanagement_header();
            printf("\n                   Invalid course selection. Please try again.\n");
            sleep(1); // Sleep for 1 second
            system("cls");  // Clear the screen
            continue;  // Prompt the user again
        }
		
		classroommanagement_header();
        system("cls");  // Clear the screen

        while (1) {
        	classroommanagement_header();
            printf("\n                   Which year level?\n");
            printf("                   1. 1st Year\n");
            printf("                   2. 2nd Year\n");
            printf("                   3. 3rd Year\n");
            printf("                   4. 4th Year\n");
            printf("                   Enter the number corresponding to your year level: ");
            yearLevelChoice = getch() - '0';

            if (yearLevelChoice >= 1 && yearLevelChoice <= 4) {
                break;  // Valid input, exit the loop
            } else {
                // Invalid year level input
                classroommanagement_header();
                printf("\n                   Invalid year level selection. Please try again.\n");
                sleep(1); // Sleep for 1 second
                system("cls");  // Clear the screen
                continue;  // Prompt the user again
            }
        }

        system("cls");  // Clear the screen

        while (1) {
        	classroommanagement_header();
            printf("\n                   Available sections for %s Year %d:\n", courses[courseChoice - 1].name, yearLevelChoice);
            for (int i = 0; i < 4; i++) {
                printf("                   %d. %s\n", i + 1, courses[courseChoice - 1].section[(yearLevelChoice - 1) * 4 + i]);
            }
            printf("                   Enter the section number: ");
            sectionChoice = getch() - '0';

            if (sectionChoice >= 1 && sectionChoice <= 4) {
                break;  // Valid input, exit the loop
            } else {
                classroommanagement_header();
                printf("\n                   Invalid section selection. Please try again.\n");
                sleep(1); // Sleep for 1 second
                system("cls");  // Clear the screen
                continue;  // Prompt the user again
            }
        }

        system("cls");  // Clear the screen
		classroommanagement_header();
        // Display the schedule for the selected section
        displaySchedule(courses[courseChoice - 1], courses[courseChoice - 1].section[(yearLevelChoice - 1) * 4 + sectionChoice - 1]);
        sleep(5);
        break;  // Exit loop after displaying schedule
    }
}


void exitScreen() {
    int width = 20; // Width of the loading bar

    // Clear screen and set background to maroon with white text
    printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
    printf("\033[2J"); // Clear screen

    // Move cursor to the middle of the screen (about 10 lines down)
    printf("\033[12;0H");

    // Loading bar loop
    for (int i = 0; i <= 100; i += 5) {
        int progress = i / (100 / width); // Calculate number of "#" for progress

        // Ensure alignment matches the border's horizontal position
        printf("\t\t\t\t\t------------------------------------------\n");
        printf("\t\t\t\t\t|          EXITING, PLEASE WAIT...       |\n");
        printf("\t\t\t\t\t------------------------------------------\n");
        printf("\t\t\t\t\t["); // Start of the loading bar
        for (int j = 0; j < width; j++) {
            if (j < progress) {
                printf("#"); // Filled part of the bar
            } else {
                printf(" "); // Unfilled part of the bar
            }
        }
        printf("] %d%%\r", i); // Display progress percentage with carriage return
        fflush(stdout); // Ensure the progress bar updates immediately
        usleep(100000); // Pause for 100 milliseconds

        // Clear the loading bar text for the next frame
        printf("\033[A\033[A\033[A"); // Move cursor up 3 lines to overwrite
    }

    // Completed loading bar
    printf("\t\t\t\t\t------------------------------------------\n");
    printf("\t\t\t\t\t|          YOU HAVE A GREAT DAY!         |\n");
    printf("\t\t\t\t\t------------------------------------------\n");
    sleep(2);

    // Clear screen again and reset colors
    printf("\033[2J"); // Clear screen
    printf("\033[H"); // Move cursor to the top-left corner
    printf("\033[48;5;52m\033[38;5;15m"); // Set background to maroon, text to white again
}

int main() {
    loadingscreen();
    char choice;

    while (1) { // Infinite loop for the main menu
        // Clear the screen and reset colors for each loop
        printf("\033[H"); // Move cursor to the top-left corner
        printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
        printf("\033[2J"); // Clear screen

        // Display the menu
        printf("                   ---------------------------------------------------------------------------------\n");
        printf("                   |                    WELCOME TO PHILTECH MANAGEMENT SYSTEM!                     |\n");
        printf("                   |-------------------------------------------------------------------------------|\n");
        printf("                   |-------------------------------------------------------------------------------|\n");
        printf("                   |              [1]  STUDENT ATTENDANCE                                          |\n");
        printf("                   |-------------------------------------------------------------------------------|\n");
        printf("                   |              [2]  TEACHER'S ATTENDANCE                                        |\n");
        printf("                   |-------------------------------------------------------------------------------|\n");
        printf("                   |              [3]  ENROLLMENT                                                  |\n");
        printf("                   |-------------------------------------------------------------------------------|\n");
        printf("                   |              [4]  EOG REQUEST                                                 |\n");
        printf("                   |-------------------------------------------------------------------------------|\n");
        printf("                   |              [5]  CLASSROOM MANAGEMENT                                        |\n");
        printf("                   |-------------------------------------------------------------------------------|\n");
        printf("                   |              [0]  EXIT                                                        |\n");
        printf("                   |                                                                               |\n");
        printf("                   ---------------------------------------------------------------------------------\n");
        printf("\033[0m"); // Reset colors to default

        // Get user input
        choice = getch();

        // Check the input and take appropriate action
        switch (choice) {
            case '1':
                studentAttendance(); // Call the function, then return to the menu
                break;
            case '2':
                teachersAttendance(); // Call the function, then return to the menu
                break;
            case '3':
                enrollment(); // Call the function, then return to the menu
                break;
            case '4':
                eogRequest(); // Call the function, then return to the menu
                break;
            case '5':
                classroomManagement(); // Call the function, then return to the menu
                break;
            case '0':
                exitScreen(); // Exit screen before quitting
                return 0; // End the program
            default:
                // Invalid input message
                printf("\033[H"); // Move cursor to the top-left corner
                printf("\033[48;5;52m\033[38;5;15m"); // Background maroon, text white
                printf("\033[2J"); // Clear screen
                printf("\n\n\n\n\n");
                printf("\033[1;52m                                 INVALID INPUT. Please select only from the choices (0-5)!\n");
                printf("                                 Press any key to try again...\033[0m");
                getch(); // Wait for user to press a key before looping
                break;
        }
    }
}

