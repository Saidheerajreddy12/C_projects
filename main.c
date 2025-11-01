// Name : Sai Dheeraj Reddy Bobba
// Date : 11 - 10 -2025
//Batch : ECEP 25021E

//Description:
/*
This project is an Address Book Management System developed in C language.
It uses structures to store contact details and arrays for managing multiple records.
Various string functions, condition statements, loops, and pointers are used for input handling and validation.
Switch case statements are used for menu-driven options like adding, editing, searching, and deleting contacts.
The project also implements file handling to save and load contacts, ensuring data persistence across runs.
*/


#include "contact.h"

int main() 
{
    int choice;

    struct AddressBook addressBook;
	initialize(&addressBook);
    addressBook.contactCount = 0;

    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		createContact(&addressBook);                    // Function Calling
		break;
	    case 2:
		searchContact(&addressBook);                   // Function Calling
		break;
	    case 3:
		editContact(&addressBook);                    // Function Calling
		break;
	    case 4:
		deleteContact(&addressBook);                  // Function Calling
		break;
	    case 5:
		listContacts(&addressBook);                  // Function Calling
		break;
	    case 6:
		printf("Saving and Exiting...\n");         
		saveContactsToFile(&addressBook);            // Function Calling
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);

    return 0;
}
