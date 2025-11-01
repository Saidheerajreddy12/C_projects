#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//List Contacts Function (Listing all the contacts)

void listContacts(struct AddressBook *addressBook) 
{
   if (addressBook->contactCount == 0) 
   {
        printf("No contacts available.\n");
        return;
   }
        printf("\t\t--- Contacts List ---\n\n");
        for(int i = 0; i < addressBook -> contactCount; i++)
        {
                printf("\t.........................................\n");
                printf("\n\tContact %d:\n", i + 1);

                printf("\n\tName     : %s\n", addressBook -> contacts[i].name);
                printf("\tPhone no : %s\n", addressBook -> contacts[i].phone);
                printf("\tEmail    : %s\n\n", addressBook -> contacts[i].email);
        }
                printf("\t..........................................\n");
}
    

void initialize(struct AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);  

    // Load contacts from file to overwrite 
    loadContactsFromFile(addressBook);
}

void saveAndExit(struct AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file before exit
    exit(EXIT_SUCCESS);               // Exit the program
}


//Mobile Number Validation Checking 

int validate_num(char *mob)
{
    int i;
    for (i = 0; mob[i] != '\0'; i++)
    {
        if (mob[i] < '0' || mob[i] > '9')
        {
            return 0; 
        }
    }
    return 1; 
}


// Checking the Duplicate of the number 

int PhoneNumberDuplicate(struct AddressBook *addressBook, char *phone) 
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
            return 1; 
        }
    }
    return 0; 
}


// Mail Validation Checking

int validate_mails(char *mail)
{
    int lower=0,digit=0;
    for (int i = 0; mail[i] != '\0'; i++)
    {
        char ch = mail[i];
        if (ch >= 'a' && ch <= 'z') 
        {
            lower = 1;
        }
        if (ch >= '0' && ch <= '9') 
        {
            digit = 1;
        }
        if (lower && digit) 
        {
            break;
        }
    }
  return (lower && digit && strchr(mail, '@') != NULL) && (strstr(mail, ".com") != NULL);         //returning the characters
}


//Create Contact Function

void createContact(struct AddressBook *addressBook)
{
char a[30], mob[20], mail[100];

    printf("Enter name: ");
    scanf("%s", a);
    getchar();

    while (1)
    {
        printf("Enter the 10-digit number: ");
        scanf("%s", mob);
        getchar();
        if (strlen(mob) != 10 || !validate_num(mob))                                 //checking length of mobile number
        {
            printf("Invalid number. Please enter 10 digits.\n");
        }
        else if (PhoneNumberDuplicate(addressBook, mob))                            //checking duplicate of mobile number
        {
            printf("Phone Number Already Exists. Try different number.\n");
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        printf("Enter Email Id : ");
        scanf("%s", mail);
        getchar();
        
        if (!validate_mails(mail))                                            //Function calling
        {
            printf("Invalid email.\n");
        }
        else
        {
            break;
        }
    }
   
    if (addressBook->contactCount < 100)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].name, a);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, mob);
        strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
        addressBook->contactCount++;
        printf("Contact saved\n");
    }
    
}


// Searching the contact

void searchContact(struct AddressBook *addressBook) 
{
    int opt;
    char search[50];
    int found = 0;

    printf("1. Search by name\n2. Search by mobile\n3. Search by email\nSelect one option : ");
    scanf("%d", &opt);
    
 if (opt < 1 || opt > 3)
 {
        printf("Invalid option. Try again.\n");
        return;
 }
    
    printf("Enter : ");
    scanf("%s", search);

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int flag = 0;
        if (opt == 1 && strcmp(addressBook->contacts[i].name, search) == 0) flag = 1;               //using stringcompare function(strcmp)
        if (opt == 2 && strcmp(addressBook->contacts[i].phone, search) == 0) flag = 1;
        if (opt == 3 && strcmp(addressBook->contacts[i].email, search) == 0) flag = 1;
        if (flag) 
        {
             printf("\nContact found\n");

            printf("\nName: %s\nPhone: %s\nEmail: %s\n", 
                addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            found = 1;
            
        }
    }
    if (!found) 
    {
    printf("Contact not found.\n");
    }
}



//Editing of the contact

void editContact(struct AddressBook *addressBook)
{
    char searchName[50];
    printf("Enter name to edit: ");
    scanf("%s", searchName);

    int matched[100], count = 0;

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, searchName) == 0) 
        {
            matched[count] = i;
             count++;
        }
    }

    if (count == 0) 
    {
        printf("No contact found with that name.\n");
        return;
    }

    int find;
    if (count == 1) 
    {
        find = matched[0];
    } 
    else 
    {
        printf("Multiple contacts found:\n");                              //Multiple contacts found of same name
        for (int i = 0; i < count; i++) 
        {
            int c = matched[i];
            printf("%d. Phone: %s, Email: %s\n",
                   i+1,
                   addressBook->contacts[c].phone,
                   addressBook->contacts[c].email);
        }
        printf("Choose contact number to edit: ");
        int choice;
        scanf("%d", &choice);
        if (choice < 1 || choice > count) 
        {
            printf("Invalid choice.\n");
            return;
        }
        find = matched[choice - 1];
    }

    while (1) 
    {
        printf("Edit\n");

        printf("1. Name\n2. Phone\n3. Email\n4. Exit\nChoice: ");
        int option;
        scanf("%d", &option);
        if (option == 4) 
        break;

        char ch[100];
        switch (option) 
        {
            case 1:
                printf("New name: ");
                scanf("%s", ch);
                strcpy(addressBook->contacts[find].name, ch);
                break;

            case 2:
                do 
                {
                    printf("New 10-digit phone: ");
                    scanf("%s", ch);
                    if (strlen(ch) == 10 && validate_num(ch) &&
                        (!PhoneNumberDuplicate(addressBook, ch) ||
                         strcmp(addressBook->contacts[find].phone, ch) == 0)) 
                    {
                        strcpy(addressBook->contacts[find].phone, ch);
                        break;
                    }
                    printf("Invalid or duplicate phone. Try again.\n");
                } 
                while (1);
                break;

            case 3:
                do 
                {
                    printf("New email: ");
                    scanf("%s", ch);
                    if (validate_mails(ch)) 
                    {
                        strcpy(addressBook->contacts[find].email, ch);
                        break;
                    }
                    printf("Invalid email. Try again.\n");
                } while (1);
                break;

            default:
                printf("Invalid choice.\n");
        }

        printf("Updated: Name: %s, Phone: %s, Email: %s\n",                                //Updating The Contact with the changes
               addressBook->contacts[find].name,
               addressBook->contacts[find].phone,
               addressBook->contacts[find].email);
    }
}


//Deletion of the contact

void deleteContact(struct AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts to delete.\n");
        return;
    }

    printf("Search the contact you want to delete:\n");
    searchContact(addressBook);                                                        //Function calling

    char name[50];
    printf("Enter the name of the contact to delete: ");
    scanf("%s", name);

    int matchednames[100];
    int count = 0;

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0) 
        {
            matchednames[count++] = i;
        }
    }

    if (count == 0) 
    {
        printf("No contact found with that name.\n");
        return;
    }

    int deletefirstmatched = matchednames[0];
    if (count > 1) 
    {
        printf("Multiple contacts found:\n");                                    //Incase of multiple contacts found with Same Name

        for (int i = 0; i < count; i++) 
        {
            int contactpos = matchednames[i];
            printf("%d. Phone: %s, Email: %s\n", i + 1,
                   addressBook->contacts[contactpos].phone,
                   addressBook->contacts[contactpos].email);
        }

        printf("Choose contact number to delete: ");
        int opt;
        scanf("%d", &opt);

        if (opt < 1 || opt > count) 
        {
            printf("Invalid choice.\n");
            return;
        }
        deletefirstmatched = matchednames[opt - 1];
    }

    for (int i = deletefirstmatched; i < addressBook->contactCount - 1; i++) 
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");                                //Deletion successfull
}