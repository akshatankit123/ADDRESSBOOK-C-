#include<stdio.h>
#include "contacts.h"
#include "populate.h"

int main()
{
    AddressBook addressBook;
    int choice;
    
    initialize(&addressBook);

    do {
        printf("\nAddress Book Menu:\n");
        printf("1.Create contanct\n");
        printf("2.Search contact\n");
        printf("3.Edit contact\n");
        printf("4.Delete contact\n");
        printf("5.List all contacts\n");
        printf("6.Save the contacts \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and exiting....");
                savecontactstothefile(&addressBook);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}
