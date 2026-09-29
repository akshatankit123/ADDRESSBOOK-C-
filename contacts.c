#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"
#include "populate.h"

#include <ctype.h>


void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    FILE *fptr = fopen("file.txt", "r");


    if(fptr !=NULL)
    {
        fscanf(fptr,"%d",&addressBook->contactCount);
        printf("reading form file.txt\n");

        for(int i=0;i<addressBook->contactCount;i++)
        {
            fscanf(fptr,"%[^,],%[^,],%[^\n]\n",
                addressBook->contacts[i].name,
     addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
        }
    }
    else{
        populateAddressBook(addressBook);
    }
   

    fclose(fptr);

    
    
}
    


void savecontactstothefile(AddressBook *addressBook)
{
    FILE *fptr = fopen("File.txt", "w");

    if(fptr == NULL)
    {
        printf("File open failed\n");
        return;
    }

    fprintf(fptr, "%d\n",addressBook->contactCount);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr,"%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    printf("file saved\n");
    printf(" \n");

    fclose(fptr);
}
int validatePhone(AddressBook *addressBook, char phone[])
{
    if(strlen(phone) != 10)
        return 0;
           for(int i=0;i<10;i++)
    
        if(!isdigit(phone[i]))
        return 0;
    

    // Check duplicate
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
            return -1;
    }

    return 1;
}

int validateEmail(AddressBook *addressBook, char email[])
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
            return -1;
    }
    if(strchr(email,'@')==NULL)
    return -1;

    if(strchr(email,'.')==NULL)
    return -1;


    return 1;
}

void listContacts(AddressBook *addressBook)
{              
          printf("-----------------------------------------------------------------------\n");
          printf("|                                                                      |\n");
          printf("name \t \t phone no \t \t email id\t\n");
         printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
     { 
   

        printf("|%s \t  %s \t %s \t\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
      printf("-----------------------------------------------------------------------\n");
      printf("\n");
    }
      
}



int createContact(AddressBook *addressBook)
{

    if(addressBook->contactCount == MAX_CONTACTS)
    {
        printf("Address Book is full\n");
        return -1;
    }
    char str[50];
    char str2[50];

    printf("Enter Name : ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);

    printf("Enter Phone : ");
    scanf(" %[^\n]", str);
    if(validatePhone(addressBook,str)==1)
    {
     strcpy(addressBook->contacts[addressBook->contactCount].phone,str);
    }
    else
    {
        printf("error\n");
        printf("phone no already found or no. is not 10 digit\n");
        printf("please try again");
        printf("\n");
        return 1;
    }

    

    printf("Enter Email : ");
    scanf(" %[^\n]", str2);
  if( validateEmail(addressBook,str2)==1)
  {
    strcpy(addressBook->contacts[addressBook->contactCount].email,str2);
  }
  else
  {
    printf("error\n");
    printf("email id already found or invalid email id\n");
    printf("please try again\n");
    printf("\n");
    return 1; 
  }

    addressBook->contactCount++;

    printf("Contact created successfully.\n");
    savecontactstothefile(addressBook);
    printf("\n");
    return 0;

}

int searchContact(AddressBook *addressBook)
{
   printf("1.search by name\n");
   printf("2.search by phone no\n");
   printf("3.search by email\n");
   int option;
   scanf("%d",&option);
   if(option==1)
   {
    char str1[50];
    int count =0;
    int match[50];
    printf("enter the name that you want to search:  ");
    scanf(" %[^\n]",str1);
    for(int i=0;i< addressBook->contactCount ;i++)
    {
          if(strcmp(addressBook->contacts[i].name,str1)==0)
          {
            printf("name \t \t phone no \t \\t email id\t\n");
            printf("-----------------------------------------------------------------------\n");
            printf("%d %s \t %s \t %s \t \t\n",count+1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf("------------------------------------------------------------------------\n");
               
            match[count] = i;
            count++;
            
          }
    }
    if(count==0)
    {
    printf("name not found\n");
    return -1;
    }
    else if(count==1)
    {
      return match[0];
    }
    else
    { 
        int choice;
        printf("select contact 1 - %d:",count);
        printf(" ");
        scanf("%d",&choice);
        printf("\n");

        if(choice >= 1 &&  choice<= count )
        {
        return match[choice-1];
        }
        else
        {
            printf("invalid input");
            return -1;
        }


    }
   }
    else if(option==2)
   {
    char str2[50];
    int a=0;
    printf("enter the phone no. that you want to search:  ");
    scanf(" %[^\n]",str2);
    
    for(int i=0;i<addressBook->contactCount  ;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,str2)==0)
        { 
            printf("name \t \t phone no \t \t email id\t\n");
            printf("------------------------------------------------------------------------\n");
            printf("|%s \t %s \t \t %s \n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf("------------------------------------------------------------------------\n");
            a++;
            return i;
        }
    }
    if(a==0)
     printf("phone no. not found\n");
     return -1;
}

 else if(option==3)
   {
    char str3[50];
    int a =0;
    printf("enter the email id . that you want to search: ");
    scanf(" %[^\n]",str3);
    for(int i=0;i< addressBook->contactCount ;i++)
    {
        if(strcmp(addressBook->contacts[i].email,str3)==0)

        {
            printf("name \t \t phone no  \t \t email id\t\n");
            printf("------------------------------------------------------------------------\n");
            printf("%s \t %s \t %s \t\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf("------------------------------------------------------------------------\n");
            a++;
            return i;
        }
    }
     if(a==0)
     
     printf("email id not found\n");
     printf("\n");
     return -1;
   }
   else 

   printf("wrong input\n");
   printf("\n");
   return -1;
}

void editContact(AddressBook *addressBook)
{
   

    int index = searchContact(addressBook);
 if(index == -1)
 {
    printf("error\n");
    printf("\n");

 }
else
{



    int choice;

    printf("1.edit name\n");
    printf("2.edit phone no.\n");
    printf("3.edit email");
        
   printf(" \n");
    scanf("%d",&choice);

    switch (choice)
    {
    case 1 :
       printf("Enter the name that you want to edit: ");
        scanf(" %[^\n]",addressBook->contacts[index].name);
        printf("\n");
        printf("name editing done\n");
        savecontactstothefile(addressBook);
        printf("\n");
        break;

    case 2:
    printf("enter the phone no that you want to edit: ");
        char str1[50];
        scanf(" %[^\n]",str1);
        if(validatePhone(addressBook,str1)==1)
        {
          strcpy(addressBook->contacts[index].phone,str1);
        }
        else
        {
            printf("error\n");
        printf("phone no found or not 10 digit\n");
        printf("\n");
        break;
        }
        printf("\n");
        printf("phone no editing done\n");
        savecontactstothefile(addressBook);
        printf("\n");
        break;

    case 3:
    printf("enter the email id that you want to edit: ");
     char str2[50];
         scanf(" %[^\n]",str2);
         if(validateEmail(addressBook,str2)==1)
         {
           strcpy(addressBook->contacts[index].email,str2);
         }
         else
         {
            printf("error\n");
            printf("duplicate email id found");
            printf("\n");
            break;
         }
        
         printf("email id editing done\n");
         savecontactstothefile(addressBook);
         printf("\n");
         break;

    default :
          printf("invalid input\n");
          printf("\n");
          break;
    }
}
        
}



void deleteContact(AddressBook *addressBook)
{
   int index = searchContact(addressBook);
   if(index == -1)
   {
    printf("error");
    printf("\n");
   }
   else
   {

   for(int i = index; i<addressBook->contactCount-1;i++)
   {
      addressBook->contacts[i] = addressBook->contacts[i+1];
   }
   printf("contact deletd\n");
   
   addressBook->contactCount--;
   savecontactstothefile(addressBook);
}
}

void saveAndExit(AddressBook *addressBook)
{
    printf("Contacts saved. Exiting...\n");
    printf("\n");
    exit(0);
}
void Exit(AddressBook *AddressBook){
    printf("Exit");
    printf("\n");
    exit(0);
}
