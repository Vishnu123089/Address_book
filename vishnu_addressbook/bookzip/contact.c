/* Name : Vishnu Vardhan.E
   Date : 15-08-2024
   Description : contact.c */
#include "contact.h"
int validate_name(const char *name) {
    regex_t regex;
    const char *NAME_PATTERN = "^[A-Za-z]+([ .-][A-Za-z]+)*$"; // pattern to handle dots, spaces, and hyphens
    if (regcomp(&regex, NAME_PATTERN, REG_EXTENDED) != 0) {
        return 0; // Regex compilation failed
    }
    int result = regexec(&regex, name, 0, NULL, 0);
    regfree(&regex); // Free regex memory
    return (result == 0); // Return 1 if valid, 0 if invalid
}
int validate_email(const char *email) {
        regex_t regex;
        const char *EMAIL_PATTERN = "^[a-zA-Z0-9_]+[@][a-z]+[\\.][a-zA-Z]{2,3}$";
        if (regcomp(&regex, EMAIL_PATTERN, REG_EXTENDED) != 0) {
                return 0; // Regex compilation failed
        }
        int result = regexec(&regex, email, 0, NULL, 0);
        regfree(&regex); // Free regex memory
        return (result == 0); // Return 1 if valid, 0 if invalid
}

int validate_mobile(const char *mobile) {
        regex_t regex;
        const char *MOBILE_PATTERN = "^[0-9]{10}$";
        if (regcomp(&regex, MOBILE_PATTERN, REG_EXTENDED) != 0) {
                return 0; // Regex compilation failed
        }
        int result = regexec(&regex, mobile, 0, NULL, 0);
        regfree(&regex); // Free regex memory
        return (result == 0); // Return 1 if valid, 0 if invalid

}
void createContact(AddressBook *addressBook) {
        if (addressBook->contactCount >= MAX_CONTACTS) {
                printf("\033[0;31m❌ Address book is full!\033[0m\n");
                return;
        }

        int i;
        printf("\033[3;33m*HOW MANY CONTACTS DO YOU WANT TO ADD:*\033[0m\n");
        scanf("%d", &i);
        getchar(); // Consume newline left by scanf

        while (i--) {
                if (addressBook->contactCount >= MAX_CONTACTS) {
                        printf("\033[0;31m❌ Address book is full!\033[0m\n");
                        return;
                }

                Contact *ptr = &addressBook->contacts[addressBook->contactCount];
                //this points to the location in the contacts array where the next contact would be added.
                // Get and validate the name
                while (1) {
                        printf("\033[0;36mENTER THE NAME 👩🏻:\033[0m\n");
                        scanf("%[^\n]", ptr->name);
                        //getchar(); // Consume newline left by scanf
                        if (validate_name(ptr->name)) {
                                break;
                        } else {
                                printf("\033[0;31mError ❌: Name must contain characters only.\033[0m\n");
                        }
                }

                // Get and validate the email
                while (1) {
                        printf("\033[0;36mENTER MOBILE 📞 :\033[0m\n");
                        scanf("%s", ptr->mobile);
                        //ptr[10]='\0'
                        getchar(); // Consume newline left by scanf
                        if (validate_mobile(ptr->mobile)) {
                                break;
                        } else {
                                printf("\033[0;31mError ❌: Mobile number must be 10 digits.\033[0m\n");
                        }
                }
                while (1) {
                        printf("\033[0;36mENTER EMAIL 📧 :\033[0m\n");
                        scanf("%s", ptr->email);

                        getchar(); // Consume newline left by scanf
                        if (validate_email(ptr->email)) {
                                break;
                        } else {
                                printf("\033[0;31mError ❌: Invalid email format.\033[0m\n");
                        }
                }

                // Get and validate the mobile number

                addressBook->contactCount++; // Increment the contact count
                printf("Contact added. New count: %d\n", addressBook->contactCount);

                printf("\033[0;33mContact Added Successfully 💚...\033[0m\n");
                sleep(1); // Pause for 1 second
        }
}

// Function to edit a contact
void editContact(AddressBook *addressBook, int contactCount) {
    int indices[MAX_CONTACTS];
    int count = 0;
    int option;

    // Print the contact table
    printf("\033[0;34m+-------+-----------------------------+------------------------------+-----------------+\033[0m\n");
    printf("\033[0;37m| Index | NAME                        | E-MAIL                       | MOBILE          |\033[0m\n");
    printf("\033[0;34m+-------+-----------------------------+------------------------------+-----------------+\033[0m\n");
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("\033[0;37m| %-5d | %-27s | %-28s | %-15s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);
        printf("\033[0;34m+-------+-----------------------------+------------------------------+-----------------+\033[0m\n");
    }

    // Display menu
    printf("\033[5;35mSELECT FILTER OPTION:\033[0m\n");
    printf("\033[0;36m 1. EDIT BY NAME\033[0m\n");
    printf("\033[0;36m 2. EDIT BY EMAIL\033[0m\n");
    printf("\033[0;36m 3. EDIT BY MOBILE\033[0m\n");
    printf("\033[0;36m 4. EXIT\033[0m\n");
    scanf("%d", &option);
    getchar(); // Consume newline character left by scanf

    switch (option) {
        case 1: {
            // Edit by Name
            char name[NAME_LENGTH];
            printf("\033[0;34mENTER NAME:\033[0m\n");
            scanf("%[^\n]", name);
            getchar(); // Consume newline character left by scanf

            count = 0;
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].name, name) == 0) {
                    indices[count++] = i;  // Collect indices of contacts with the same name
                }
            }

            if (count == 1) {
                int index = indices[0];
                // Print contact details before edit
                printf("\n\033[0;32m--- CONTACT DETAILS BEFORE EDIT ---\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

                // Declare new variables
                char new_name[NAME_LENGTH] = "", new_email[EMAIL_LENGTH] = "", new_mobile[MOBILE_LENGTH] = "";

                printf("Enter new name (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_name);
                getchar(); // Consume newline character left by scanf
                if (new_name[0] != '\0') {
                    if (validate_name(new_name)) {
                        strcpy(addressBook->contacts[index].name, new_name);
                    } else {
                        printf("\033[0;31m❌ INVALID NAME!\033[0m\n");
                    }
                }

                printf("Enter new email (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_email);
                getchar(); // Consume newline character left by scanf
                if (new_email[0] != '\0') {
                    if (validate_email(new_email)) {
                        strcpy(addressBook->contacts[index].email, new_email);
                    } else {
                        printf("\033[0;31m❌ INVALID EMAIL!\033[0m\n");
                    }
                }

                printf("Enter new mobile number (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_mobile);
                getchar(); // Consume newline character left by scanf
                if (new_mobile[0] != '\0') {
                    if (validate_mobile(new_mobile)) {
                        strcpy(addressBook->contacts[index].mobile, new_mobile);
                    } else {
                        printf("\033[0;31m❌ INVALID MOBILE NUMBER!\033[0m\n");
                    }
                }

                // Print contact details after edit
                printf("\n\033[0;32m--- CONTACT DETAILS AFTER EDIT ---\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
            } else if (count > 1) {
                 printf("\033[0;36mMultiple contacts found with the name \"%s\". Here are the details:\033[0m\n", name);
                printf("\033[0;34m+-------+-----------------------------+------------------------------+-----------------+\033[0m\n");
                printf("\033[0;37m| Index | NAME                        | E-MAIL                       | MOBILE          |\033[0m\n");
                printf("\033[0;34m+-------+-----------------------------+------------------------------+-----------------+\033[0m\n");
                for (int i = 0; i < count; i++) {
                    int index = indices[i];
                    printf("\033[0;37m| %-5d | %-27s | %-28s | %-15s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                    printf("\033[0;34m+-------+-----------------------------+------------------------------+-----------------+\033[0m\n");
                }
                // Prompt user to select a contact from the displayed list
                printf("\033[0;32mPlease select the contact you want to edit by entering the index number.\033[0m\n");
                int selectedIndex;
                scanf("%d", &selectedIndex);
                getchar(); // Consume newline character left by scanf

                if (selectedIndex > 0 && selectedIndex <= count) {
                    int index = indices[selectedIndex - 1];
                    // Continue with the editing process for the selected contact
                    printf("\n\033[0;32m--- CONTACT DETAILS BEFORE EDIT ---\033[0m\n");
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

                    // Declare new variables
                    char new_name[NAME_LENGTH] = "", new_email[EMAIL_LENGTH] = "", new_mobile[MOBILE_LENGTH] = "";

                    printf("Enter new name (leave empty to keep unchanged): ");
                    scanf("%[^\n]", new_name);
                    getchar(); // Consume newline character left by scanf
                    if (new_name[0] != '\0') {
                        if (validate_name(new_name)) {
                            strcpy(addressBook->contacts[index].name, new_name);
                        } else {
                            printf("\033[0;31m❌ INVALID NAME!\033[0m\n");
                        }
                    }

                    printf("Enter new email (leave empty to keep unchanged): ");
                    scanf("%[^\n]", new_email);
                    getchar(); // Consume newline character left by scanf
                    if (new_email[0] != '\0') {
                        if (validate_email(new_email)) {
                            strcpy(addressBook->contacts[index].email, new_email);
                        } else {
                            printf("\033[0;31m❌ INVALID EMAIL!\033[0m\n");
                        }
                    }

                    printf("Enter new mobile number (leave empty to keep unchanged): ");
                    scanf("%[^\n]", new_mobile);
                    getchar(); // Consume newline character left by scanf
                    if (new_mobile[0] != '\0') {
                        if (validate_mobile(new_mobile)) {
                            strcpy(addressBook->contacts[index].mobile, new_mobile);
                        } else {
                            printf("\033[0;31m❌ INVALID MOBILE NUMBER!\033[0m\n");
                        }
                    }

                    // Print contact details after edit
                    printf("\n\033[0;32m--- CONTACT DETAILS AFTER EDIT ---\033[0m\n");
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
            }
            }   else {
                printf("\033[0;31mNo contacts found with the provided name.🫤\033[0m\n");
            }
            break;
        }
        case 2: {
            // Edit by Email
            char email[EMAIL_LENGTH];
            printf("\033[0;32mENTER EMAIL:\033[0m\n");
            scanf("%[^\n]", email);
            getchar(); // Consume newline character left by scanf

            count = 0;
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].email, email) == 0) {
                    indices[count++] = i;
                }
            }

            if (count == 1) {
                int index = indices[0];
                // Print contact details before edit
                printf("\n\033[0;32m--- CONTACT DETAILS BEFORE EDIT ---\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

                // Declare new variables
                char new_name[NAME_LENGTH] = "", new_email[EMAIL_LENGTH] = "", new_mobile[MOBILE_LENGTH] = "";

                printf("Enter new name (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_name);
                getchar(); // Consume newline character left by scanf
                if (new_name[0] != '\0') {
                    if (validate_name(new_name)) {
                        strcpy(addressBook->contacts[index].name, new_name);
                    } else {
                        printf("\033[0;31m❌ INVALID NAME!\033[0m\n");
                    }
                }

                printf("Enter new email (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_email);
                getchar(); // Consume newline character left by scanf
                if (new_email[0] != '\0') {
                    if (validate_email(new_email)) {
                        strcpy(addressBook->contacts[index].email, new_email);
                    } else {
                        printf("\033[0;31m❌ INVALID EMAIL!\033[0m\n");
                    }
                }

                printf("Enter new mobile number (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_mobile);
                getchar(); // Consume newline character left by scanf
                if (new_mobile[0] != '\0') {
                    if (validate_mobile(new_mobile)) {
                        strcpy(addressBook->contacts[index].mobile, new_mobile);
                    } else {
                        printf("\033[0;31m❌ INVALID MOBILE NUMBER!\033[0m\n");
                    }
                }

                // Print contact details after edit
                printf("\n\033[0;32m--- CONTACT DETAILS AFTER EDIT ---\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
            } else if (count > 1) {
                printf("\033[0;36mMultiple contacts found with the email \"%s\". Please select the contact you want to edit:\033[0m\n", email);
                editContact(addressBook, contactCount); // Call editContact again
            } else {
                printf("\033[0;31mNo contacts found with the provided email.🫤\033[0m\n");
            }
            break;
        }
        case 3: {
            // Edit by Mobile
            char mobile[MOBILE_LENGTH];
            printf("\033[0;32mENTER MOBILE NUMBER:\033[0m\n");
            scanf("%[^\n]", mobile);
            getchar(); // Consume newline character left by scanf

            count = 0;
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].mobile, mobile) == 0) {
                    indices[count++] = i;
                }
            }

            if (count == 1) {
                int index = indices[0];
                // Print contact details before edit
                printf("\n\033[0;32m--- CONTACT DETAILS BEFORE EDIT ---\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

                // Declare new variables
                char new_name[NAME_LENGTH] = "", new_email[EMAIL_LENGTH] = "", new_mobile[MOBILE_LENGTH] = "";

                printf("Enter new name (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_name);
                getchar(); // Consume newline character left by scanf
                if (new_name[0] != '\0') {
                    if (validate_name(new_name)) {
                        strcpy(addressBook->contacts[index].name, new_name);
                    } else {
                        printf("\033[0;31m❌ INVALID NAME!\033[0m\n");
                    }
                }

                printf("Enter new email (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_email);
                getchar(); // Consume newline character left by scanf
                if (new_email[0] != '\0') {
                    if (validate_email(new_email)) {
                        strcpy(addressBook->contacts[index].email, new_email);
                    } else {
                        printf("\033[0;31m❌ INVALID EMAIL!\033[0m\n");
                    }
                }

                printf("Enter new mobile number (leave empty to keep unchanged): ");
                scanf("%[^\n]", new_mobile);
                getchar(); // Consume newline character left by scanf
                if (new_mobile[0] != '\0') {
                    if (validate_mobile(new_mobile)) {
                        strcpy(addressBook->contacts[index].mobile, new_mobile);
                    } else {
                        printf("\033[0;31m❌ INVALID MOBILE NUMBER!\033[0m\n");
                    }
                }

                // Print contact details after edit
                printf("\n\033[0;32m--- CONTACT DETAILS AFTER EDIT ---\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
            } else if (count > 1) {
                printf("\033[0;36mMultiple contacts found with the mobile number \"%s\". Please select the contact you want to edit:\033[0m\n", mobile);
                editContact(addressBook, contactCount); // Call editContact again
            } else {
                printf("\033[0;31mNo contacts found with the provided mobile number.🫤\033[0m\n");
            }
            break;
        }
        case 4:
            printf("\033[0;31mExiting...❌\033[0m\n");
            break;
        default:
            printf("\033[0m;31mInvalid option. Please try again.❌\033[0m\n");
            break;
    }
}

void searchContact(AddressBook *addressBook) {
    int o;
    int indices[MAX_CONTACTS];
    int count;

    while (1) {
        printf("\033[5;35mSELECT OPTION TO VIEW THE CONTACT---\033[0m\n\033[0;36m1. ENTER NAME\n2. ENTER EMAIL\n3. ENTER MOBILE NUMBER\n4. EXIT\033[0m\n");
        scanf("%d", &o);
        getchar(); // Consume newline character left by scanf

        count = 0; // Reset count for each search

        switch (o) {
            case 1: {
                char name[50];
                printf("\033[0;34mENTER NAME:\033[0m\n");
                scanf("%[^\n]", name);
                getchar(); // Consume newline character left by scanf

                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, name) == 0) {
                        indices[count++] = i;
                    }
                }
                if (count == 1) {
                    // Only one contact found
                    int index = indices[0];
                    printf("\n\033[1;32m--- CONTACT DETAILS ---\033[0m\n");
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                } else if (count > 1) {
                    printf("\n\033[1;32m--- CONTACT DETAILS ---\033[0m\n");
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

                    for (int i = 0; i < count; i++) {
                        int index = indices[i];
                        printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                        printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    }

                    printf("\033[0;36mEnter 1 to filter by Mobile Number or 2 to filter by Email, or -1 to exit:\033[0m\n");
                    int filterOption;
                    scanf("%d", &filterOption);
                    getchar(); // Consume newline character left by scanf

                    if (filterOption == 1) {
                        char mobile[15];
                        printf("\033[0;34mENTER MOBILE NUMBER:\033[0m\n");
                        scanf("%[^\n]", mobile);
                        getchar(); // Consume newline character left by scanf

                        count = 0; // Reset count for the filtered results
                        for (int i = 0; i < addressBook->contactCount; i++) {
                            if (strcmp(addressBook->contacts[i].name, name) == 0 && strcmp(addressBook->contacts[i].mobile, mobile) == 0) {
                                indices[count++] = i;
                            }
                        }
                        if (count > 0) {
                            printf("\n\033[1;32m--- FILTERED CONTACTS ---\033[0m\n");
                            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                            printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

                            for (int i = 0; i < count; i++) {
                                int index = indices[i];
                                printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                            }
                        } else {
                            printf("\033[0;31m❌ NO CONTACTS FOUND WITH THAT MOBILE NUMBER.\033[0m\n");
                        }
                    } else if (filterOption == 2) {
                        char email[50];
                        printf("\033[0;34mENTER EMAIL:\033[0m\n");
                        scanf("%[^\n]", email);
                        getchar(); // Consume newline character left by scanf

                        count = 0; // Reset count for the filtered results
                        for (int i = 0; i < addressBook->contactCount; i++) {
                            if (strcmp(addressBook->contacts[i].name, name) == 0 && strcmp(addressBook->contacts[i].email, email) == 0) {
                                indices[count++] = i;
                            }
                        }
                        if (count > 0) {
                            printf("\n\033[1;32m--- FILTERED CONTACTS ---\033[0m\n");
                            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                            printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

                            for (int i = 0; i < count; i++) {
                                int index = indices[i];
                                printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", index + 1, addressBook->contacts[index].name, addressBook->contacts[index].email, addressBook->contacts[index].mobile);
                                printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                            }
                        } else {
                            printf("\033[0;31m❌ NO CONTACTS FOUND WITH THAT EMAIL.\033[0m\n");
                        }
                    } else if (filterOption == -1) {
                        printf("Exiting...\n");
                        return;
                    } else {
                        printf("\033[0;31m❌ INVALID OPTION!\033[0m\n");
                    }
                } else {
                    printf("\033[0;31m❌ NO CONTACTS FOUND WITH THAT NAME.\033[0m\n");
                }
                break;
            }
            case 2: {
                char email[50];
                printf("\033[0;34mENTER EMAIL:\033[0m\n");
                scanf("%[^\n]", email);
                getchar(); // Consume newline character left by scanf

                int found = 0;
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, email) == 0) {
                        if (!found) {
                            printf("\n\033[1;32m--- CONTACT DETAILS ---\033[0m\n");
                            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                            printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                        }
                        printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);
                        printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                        found = 1;
                    }
                }
                if (!found) {
                    printf("\033[0;31m❌ NO CONTACTS FOUND WITH THAT EMAIL.\033[0m\n");
                }
                break;
            }
            case 3: {
                char mobile[15];
                printf("\033[0;34mENTER MOBILE NUMBER:\033[0m\n");
                scanf("%[^\n]", mobile);
                getchar(); // Consume newline character left by scanf

                int found = 0;
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].mobile, mobile) == 0) {
                        if (!found) {
                            printf("\n\033[1;32m--- CONTACT DETAILS ---\033[0m\n");
                            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                            printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
                            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                        }
                        printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);
                        printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                        found = 1;
                    }
                }
                if (!found) {
                    printf("\033[0;31m❌ NO CONTACTS FOUND WITH THAT MOBILE NUMBER.\033[0m\n");
                }
                break;
            }
            case 4:
                   printf("\033[0;31mExiting...❌\033[0m\n");
                   return;
              
            default:
                printf("\033[0;31m❌ INVALID OPTION!\033[0m\n");
        }
    }
}

void deleteContact(AddressBook *addressBook) {
    int found = 0;
    int o;

    // Print table header
    printf("\033[0;34m+-------+-----------------------------+------------------------------+------------------+\033[0m\n");
    printf("\033[0;37m| Index | NAME                        | E-MAIL                       | MOBILE           |\033[0m\n");
    printf("\033[0;34m+-------+-----------------------------+------------------------------+------------------+\033[0m\n");

    // Print each contact as a row in the table
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("\033[0;37m| %-5d | %-27s | %-28s | %-16s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);
        if (i < addressBook->contactCount - 1) {
            printf("\033[0;34m+-------+-----------------------------+------------------------------+------------------+\033[0m\n");
        }
    }
    printf("\033[0;34m+-------+-----------------------------+------------------------------+------------------+\033[0m\n");

    // Prompt user to select an option
    printf("\033[5;35mSELECT OPTION TO DELETE THE CONTACT---\033[0m\n\033[0;36m1. ENTER NAME\n2. ENTER EMAIL\n3. ENTER MOBILE NUMBER\033[0m\n");
    scanf("%d", &o);
    getchar(); // Consume newline character left by scanf

    switch (o) {
        case 1: {
            char name[NAME_LENGTH];
            printf("\033[0;34mENTER NAME:\033[0m\n");
            scanf("%[^\n]", name);
            getchar(); // Consume newline character left by scanf

            printf("\n\033[1;32m---SEARCH RESULTS---\033[0m\n");
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
            printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].name, name) == 0) {
                    found = 1;
                    printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);
                    if (i < addressBook->contactCount - 1) {
                        printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    }
                }
            }
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

            if (found) {
                int index;
                printf("\033[0;36mEnter the index of the contact to delete:\033[0m\n");
                scanf("%d", &index);
                getchar(); // Consume newline character left by scanf
                if (index > 0 && index <= addressBook->contactCount) {
                    // Delete contact
                    index--; // Convert to zero-based index
                    for (int i = index; i < addressBook->contactCount - 1; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;
                    printf("\033[0;33mContact deleted successfully 💔...\033[0m\n");
                } else {
                    printf("\033[0;31m❌ INVALID INDEX!\033[0m\n");
                }
            } else {
                printf("\033[0;31m❌ NAME DOESN'T EXIST.....TRY AGAIN🤔\033[0m\n");
            }
            break;
        }
        case 2: {
            char email[EMAIL_LENGTH];
            printf("\033[0;34mENTER EMAIL:\033[0m\n");
            scanf("%[^\n]", email);
            getchar(); // Consume newline character left by scanf

            printf("\n\033[1;32m---SEARCH RESULTS---\033[0m\n");
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
            printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].email, email) == 0) {
                    found = 1;
                    printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);
                    if (i < addressBook->contactCount - 1) {  //this gives the row seperately except last row
                        printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    }
                }
            }
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

            if (found) {
                int index;
                printf("\033[0;36mEnter the index of the contact to delete:\033[0m\n");
                scanf("%d", &index);
                getchar(); // Consume newline character left by scanf
                if (index > 0 && index <= addressBook->contactCount) {
                    // Delete contact
                    index--; // Convert to zerobased index such that array this tells first element is 0th index
                    for (int i = index; i < addressBook->contactCount - 1; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];  //shifting all index left
                    }
                    addressBook->contactCount--; //decrease the contactcount of addressbook
                    printf("\033[0;33mContact deleted successfully 💔...\033[0m\n");
                } else {
                    printf("\033[0;31m❌ INVALID INDEX!\033[0m\n");
                }
            } else {
                printf("\033[0;31m❌ EMAIL DOESN'T EXIST.....TRY AGAIN🤔\033[0m\n");
            }
            break;
        }
        case 3: {
            char mobile[MOBILE_LENGTH];
            printf("\033[0;34mENTER MOBILE NUMBER:\033[0m\n");
            scanf("%[^\n]", mobile);
            getchar(); // Consume newline character left by scanf

            printf("\n\033[1;32m---SEARCH RESULTS---\033[0m\n");
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
            printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].mobile, mobile) == 0) {
                    found = 1;
                    printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);
                    if (i < addressBook->contactCount - 1) {
                        printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
                    }
                }
            }
            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

            if (found) {
                int index;
                printf("\033[0;36mEnter the index of the contact to delete:\033[0m\n");
                scanf("%d", &index);
                getchar(); // Consume newline character left by scanf
                if (index > 0 && index <= addressBook->contactCount) {
                    // Delete contact
                    index--; // Convert to zero-based index
                    for (int i = index; i < addressBook->contactCount - 1; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;
                    printf("\033[0;33mContact deleted successfully 💔...\033[0m\n");
                } else {
                    printf("\033[0;31m❌ INVALID INDEX!\033[0m\n");
                }
            } else {
                printf("\033[0;31m❌ MOBILE NUMBER DOESN'T EXIST.....TRY AGAIN🤔\033[0m\n");
            }
            break;
        }
        default:
            printf("\033[0;31m❌ INVALID OPTION!\033[0m\n");
            break;
    }
}
void swap_contacts(Contact *a, Contact *b) {
        Contact temp = *a;
        *a = *b;
        *b = temp;
}

void sort_contacts(AddressBook *addressBook, int criteria) {
        for (int i = 0; i < addressBook->contactCount - 1; i++) {
                for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
                        int compare = 0;
                        if (criteria == 1) {
                                compare = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
                        } else if (criteria == 2) {
                                compare = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
                        } else if (criteria == 3) {
                                compare = strcmp(addressBook->contacts[j].mobile, addressBook->contacts[j + 1].mobile);
                        }

                        if (compare > 0) {
                                swap_contacts(&addressBook->contacts[j], &addressBook->contacts[j + 1]);
                        }
                }
        }
}

void listContacts(AddressBook *addressBook, int sortCriteria) {
        if (addressBook->contactCount == 0) {
                printf("\033[0;31m❌ No contacts to display!\033[0m\n");
                return;
        }

        // Sort contacts based on the chosen criteria using bubble sort
        sort_contacts(addressBook, sortCriteria);


        // Display contacts in a table format
        printf("\033[1;32mDISPLAYING ALL CONTACTS....\033[0m\n");
        for (int i = 0; i <= 100; i++) {
                printf("\033[0;35mLoading [");
                for (int j = 1; j <= 100; j++) {
                        if (j <= i) {
                                printf("-");
                        } else {
                                printf(" ");
                        }
                }
                printf("]%d%%\033[0m", i);
                fflush(stdout);
                usleep(20000);  // Sleep for 20,000 microseconds (20 milliseconds)
                printf("\r");   // Move cursor to the beginning of the line

        }
       printf("\n");
        printf("\n\033[1;32m--- CONTACT DETAILS ---\033[0m\n");
    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
    printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

    // Print each contact as a row in the table
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);

            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
        }
}
void displayContacts(AddressBook *addressBook) {
        if (addressBook->contactCount == 0) {
                printf("\033[0;31m❌ No contacts to display!\033[0m\n");
                return;
        }
        // Display contacts in a table format
        printf("\033[1;32mDISPLAYING ALL CONTACTS....\033[0m\n");
        for (int i = 0; i <= 100; i++) {
                printf("\033[0;35mLoading [");
                for (int j = 1; j <= 100; j++) {
                        if (j <= i) {
                                printf("-");
                        } else {
                                printf(" ");
                        }
                }
                printf("]%d%%\033[0m", i);
                fflush(stdout);
                usleep(20000);  // Sleep for 20,000 microseconds (20 milliseconds)
                printf("\r");   // Move cursor to the beginning of the line
        }
        printf("\n");
         printf("\n\033[1;32m--- CONTACT DETAILS ---\033[0m\n");
    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
    printf("\033[0;37m| Index| Name                         | Email                        | Mobile           |\033[0m\n");
    printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");

    // Print each contact as a row in the table
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("\033[0;37m| %-4d | %-28s | %-28s | %-16s |\033[0m\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].email, addressBook->contacts[i].mobile);

            printf("\033[0;34m+------+------------------------------+------------------------------+------------------+\033[0m\n");
        }
}
