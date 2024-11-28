/* Name : Vishnu Vardhan.E
   Date : 15-08-2024
   Description : file.c */

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

// Save contacts to file in CSV format
void saveContactsToFile(AddressBook *addressBook) {
    FILE *ptr = fopen("addressbookfile.csv", "w");
    if (ptr == NULL) {
        perror("Error opening file for saving");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(ptr, "%s,%s,%s\n", addressBook->contacts[i].name,
                                   addressBook->contacts[i].email,
                                   addressBook->contacts[i].mobile);
    }
    fclose(ptr);
    printf("Contacts saved successfully.\n");
}

// Load contacts from file in CSV format
void loadContactsFromFile(AddressBook *addressBook) {
    if (addressBook == NULL) {
        fprintf(stderr, "Error: AddressBook pointer is NULL.\n");
        return;
    }

    FILE *ptr = fopen("addressbookfile.csv", "r");
    if (ptr == NULL) {
        perror("Error opening file for loading");
        return;
    }

    addressBook->contactCount = 0; // Reset contact count before loading
    Contact details;

    while (fscanf(ptr, "%49[^,],%99[^,],%14[^\n]\n", details.name, details.email, details.mobile) == 3) {
        if (addressBook->contactCount >= MAX_CONTACTS) {
            printf("Warning: Maximum number of contacts reached.\n");
            break;
        }
        addressBook->contacts[addressBook->contactCount++] = details;
    }

    if (ferror(ptr)) {
        perror("Error reading file");
    }
    fclose(ptr);
    printf("Number of contacts loaded: %d\n", addressBook->contactCount);
}

