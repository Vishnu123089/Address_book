/* Name : Vishnu Vardhan.E
   Date : 15-08-2024
   Description : main.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

int main() {
    AddressBook addressBook = { .contactCount = 0 };
    int choice, sortCriteria;
    int continueFlag = 1;

    // Load contacts from file at the start
    loadContactsFromFile(&addressBook);

    printf("\t\t\t\t\t\t\033[47;30m:::: ADDRESS BOOK 📔 :::::\033[0m\n");

    while (continueFlag) {
        printf("\n\033[5;33m📋 SELECT OPTION TO DO...\033[0m\n");
        printf("\033[1;35m1. \033[0;31mADD CONTACT \033[0m📱\n");
        printf("\033[1;35m2. \033[0;31mEDIT CONTACT \033[0m✏\n");
        printf("\033[1;35m3. \033[0;31mDISPLAY SPECIFIC CONTACT \033[0m🔍\n");
        printf("\033[1;35m4. \033[0;31mDELETE CONTACT \033[0m🗑️\n");
        printf("\033[1;35m5. \033[0;31mDISPLAY ALL CONTACTS \033[0m📋\n");
        printf("\033[1;35m6. \033[0;31mSORT CONTACTS \033[0m🔄\n");
        printf("\033[1;35m7. \033[0;31mEXIT \033[0m🚪\n");
        printf("\n\033[0;36mENTER YOUR CHOICE:\033[0m ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                editContact(&addressBook, addressBook.contactCount);
                break;
            case 3:
                searchContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                displayContacts(&addressBook);
                break;
            case 6:
                printf("\n\033[0;36mSELECT SORTING CRITERIA---\033[0m\n");
                printf("\033[0;35m1. By Name\033[0m\n");
                printf("\033[0;35m2. By Email\033[0m\n");
                printf("\033[0;35m3. By Mobile Number\033[0m\n");
                printf("\033[0;36mENTER YOUR CHOICE: \033[0m");
                scanf("%d", &sortCriteria);
                listContacts(&addressBook, sortCriteria);
                break;
            case 7:
                // Save contacts to file before exiting
                saveContactsToFile(&addressBook);
              //  printf("\n\033[1;31mEXITING ADDRESS BOOK...\033[0m\n");
               // printf("\033[1;36mGOODBYE! 👋\033[0m\n");
                continueFlag = 0;
                break;
            default:
                printf("\033[0;31mInvalid option! Please choose a valid option.🫤\033[0m\n");
                break;
        }

        if (continueFlag) {
            printf("\n\033[0;35mPRESS '1' - CONTINUE    '0' - EXIT\033[0m\n");
            scanf("%d", &continueFlag);
        }
	if(continueFlag == 0) 
            // Print exit message if use
	{
		 printf("\n\033[1;31mEXITING ADDRESS BOOK...\033[0m\n");
                printf("\033[1;36mGOODBYE! 👋\033[0m\n");
	}
    }

    return 0;
}

