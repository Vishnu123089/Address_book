/* Name : Vishnu Vardhan.E
   Date : 15-08-2024
   Description : contact.h */

#ifndef CONTACT_H
#define CONTACT_H

#include<stdio.h>
#include <string.h>
#include <regex.h>
#include <unistd.h> // For sleep()
#include<stdlib.h>

// Constants for maximum sizes
#define MAX_CONTACTS 100
#define NAME_LENGTH 100
#define EMAIL_LENGTH 50
#define MOBILE_LENGTH 11

// Contact structure
typedef struct {
    char name[NAME_LENGTH];
    char mobile[MOBILE_LENGTH];
    char email[EMAIL_LENGTH];
} Contact;

// AddressBook structure containing an array of contacts and a contact count
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

// Function declarations for contact operations
int validate_name(const char *name);
int validate_email(const char *email);
int validate_mobile(const char *mobile);
void createContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook, int contactCount);
void searchContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void sort_contacts(AddressBook *addressBook, int criteria);
void listContacts(AddressBook *addressBook, int sortCriteria);
void displayContacts(AddressBook *addressBook);
void swap_contacts(Contact *a, Contact *b);

#endif // CONTACT_H

