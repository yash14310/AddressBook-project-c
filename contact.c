#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int  i;

//Print Function
void print(int i, AddressBook *addressBook)
{
    printf("%-15s\t %-12s\t %-15s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
}

//List FUnction
void listContacts(AddressBook *addressBook) 
{
    //Print all the contact 
    printf("%-15s\t %-12s\t %-15s\n", "Name", "Phone", "Email");
    for(i = 0; i < addressBook -> contactCount; i++)
    {
        print(i, addressBook);
    }
    
}


void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
 
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}


void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


//Create Contact Function
void createContact(AddressBook *addressBook)
{
    int flag = 1, success = 1;
    int i = addressBook -> contactCount;
	/* Define the logic to create a Contacts */

    //NAME SECTION
    while(success == 1)
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", addressBook -> contacts[i].name);
        int j = 0;
        //Check The Entered String contains only character
        while(addressBook -> contacts[i].name[j] != '\0')
        {   
            if((addressBook -> contacts[i].name[j]  >= 'a' && addressBook -> contacts[i].name[j]  <= 'z') ||( addressBook -> contacts[i].name[j] >= 'A' && addressBook -> contacts[i].name[j] <= 'Z') || addressBook -> contacts[i].name[j] == ' ')
            {
                flag = 1;
            }
            else
            {
                flag = 0;
                break;
            }
            j++;
        }

    //if Name format is not correct Display prompt messsage and Ask for Name Again
        if(flag == 0)
        {     
            printf("Enter Only Characters\n");
        }
        else
        {
            success = 0;
        }
    }


    if(flag == 1)
    {
        //PHONE SECTION

        success = 1;
        int same = 0, j = 0;
        char *duplicate;
       
        while(success == 1)
        {
            printf("Enter Phone: ");
            scanf(" %[^\n]", addressBook -> contacts[i].phone);
        
        
            while(addressBook -> contacts[i].phone[j] != '\0')
            {   
                //CHECK THE PHONE IS BETWEEN '0' TO '9'  and It is 10 digit
                if(addressBook -> contacts[i].phone[j]  >= '0' && addressBook -> contacts[i].phone[j]  <= '9' && strlen(addressBook -> contacts[i].phone) == 10)
                {
                    flag = 1;
                    success = 0;
                }
                else
                {   
                    flag = 0;
                }
                j++;
            }
        
        //if Phone number format is not correct Display prompt message and Ask for Phone Number Again
            if(flag == 0)
            {
                //The PHONE SHOULD BE ONLY 10 DIGIT 
                printf("Enter 10 Digits Only\n");
            }
            else if(flag != 0)
            { 
                //Check if the Entered Number is already there    
                for(j = 0; j < addressBook -> contactCount - 1; j++)
                {
                    duplicate = strstr(addressBook -> contacts[j].phone, addressBook -> contacts[i].phone);
            
                    //if Same phone Number FOund Print the Existing contact
                    if(duplicate)
                    {   
                        same = 1;
                        printf("Contact Number Already Exist\n");
                        print(j, addressBook);
                    }
                }   
            }
        }
        if(same == 0 && flag == 1)
        {
            success = 1;
            //EMAIL SECTION
            //Take the Input for the Email from USER

            while(success == 1)
            {
                printf("Enter email: ");
                scanf(" %[^\n]", addressBook -> contacts[i].email);
                j = 0;
                flag = 0;
                
                //CHeck '@' is present or not in email            
                while( addressBook -> contacts[i].email[j] != '\0')
                {   
                    //CHECK '@' IS PRESENT OR NOT IN EMAIL 
                    //printf("%c is now email char & Flag  = %d\n", addressBook -> contacts[i].email[j], flag);
                    if(addressBook -> contacts[i].email[j] == '@')
                    {   
                        //Store Index of '@'
                        int postofat = j;

                        //CHECK '.com' IS PRESENT OR NOT IN EMAIL 
                        char *com = strstr(addressBook -> contacts[i].email, ".com");
                        if(com != NULL && (com - addressBook -> contacts[i].email == strlen(addressBook -> contacts[i].email) - 4))
                        {   
                            //CHECK FOR THE CHARACTER BEFORE '@'
                            if(addressBook -> contacts[i].email[postofat - 1])
                            {    
                                //CHECK FOR THE CHARACTER BETWEEN '@' & '.com' [ Atleast 1 char should be there ]
                                if(addressBook -> contacts[i].email[postofat + 1] != '.')
                                {
                                    
                                    //if All COndition satisfied Flag = 1
                                    flag = 1;
                                }
                            }   
                        }
                    }       
                    j++;
                }
        
                //If FLAG = 0, Invalid Input
                if(flag == 0)
                {
                    printf("Invalid Email Format\nSample Format: xyz123@gmail.com\n");
                }
                else
                {
                    success = 0;
                    printf("Contact Added Succesfully!\n");
                    addressBook -> contactCount++;
                }
            }
        
            
        }
       
    }

}

//Search Contact Function
void searchContact(AddressBook *addressBook) 
{
    /* Logic for search */
    int option, flag = 0, count = 0;
    char search[100];
    char *found;
    printf("Choose:\n 1.Search by Name\n 2.Search by Phone\n 3.Search by Email\n");
    scanf("%d", &option);

    switch(option)
    {
        case 1:
            printf("Enter Name: ");
            scanf(" %[^\n]", search);
            for(i = 0; i < addressBook -> contactCount; i++)
            {
                found = strstr(addressBook -> contacts[i].name, search);
                if(found)
                {
                    print(i, addressBook);
                    flag = 1;
                    count++;
                }
            }
            if(count > 1)
            {
                printf("\nEnter Phone Number: ");
                scanf(" %[^\n]", search);
                
                for(i = 0; i < addressBook -> contactCount; i++)
                {
                    found = strstr(addressBook -> contacts[i].phone, search);
                
                    if(found)
                    {
                        print(i, addressBook);
                    }
                }
            }
            break;
   
        case 2:
            count = 0;
            printf("Enter Phone: ");
            scanf(" %[^\n]", search);
            for(i = 0; i < addressBook -> contactCount; i++)
            {
                found = strstr(addressBook -> contacts[i].phone, search);
                if(found)
                {
                    print(i, addressBook);
                    flag = 1;
                    count++;
                }
            }
            break;
        case 3:
            count = 0;
            printf("Enter Email: ");
            scanf(" %[^\n]", search);
            for(i = 0; i < addressBook -> contactCount; i++)
            {
                found = strstr(addressBook -> contacts[i].email, search);
                if(found)
                {
                    print(i, addressBook);
                    flag = 1;
                    count++;
                }
            }
            if(count > 1)
            {
                printf("\nEnter Phone : ");
                scanf(" %[^\n]", search);

                for(i = 0; i < addressBook -> contactCount; i++)
                {
                    found = strstr(addressBook -> contacts[i].phone, search);

                    if(found)
                    {
                        print(i, addressBook);
                    }
                }
                
            }
            break;
    }
    if(flag == 0)
    {
        printf("Contact Not Found\n");
    }   
}

//Edit COntact Function
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int option, index, count = 0, flag = 0;
    char edit[100], *found;
    printf("Choose:\n 1.Edit by Name\n 2.Edit by Phone\n 3.Edit by Email\n");
    scanf("%d", &option);
    
    //EDIT Function
    void edit_by(int option)
    {

         switch(option)
         {
             case 1:
                 printf("Enter Name: ");
                 scanf(" %[^\n]", addressBook -> contacts[index].name);
                 printf("Name Changed Successfully!\n");
                 break;
             case 2: 
                 printf("Enter Phone: ");
                 scanf(" %[^\n]", addressBook -> contacts[index].phone);
                 printf("Number Changed Successfully!\n");
                 break;
             case 3:
                 printf("Enter Email: ");
                 scanf(" %[^\n]", addressBook -> contacts[index].email);
                 printf("Email Changed Succesfully!\n");
                 break;
         }
    }
    // -x-x-x-x-
    
    switch(option)
    {
        case 1:
            printf("Enter Name: ");
            scanf(" %[^\n]", edit);
            for(i = 0; i < addressBook -> contactCount; i++)
            {
                found = strstr(addressBook -> contacts[i].name, edit);
               
                if(found)
                {
                    flag = 1;
                    index = i;
                    print(index, addressBook);  //Print Elements
                    count++;
                }
            }
            if(count > 1)
            {
                printf("Enter Phone: ");
                scanf(" %[^\n]", edit);
                for(i = 0; i < addressBook -> contactCount; i++)
                {
                    found = strstr(addressBook -> contacts[i].phone, edit);
                    
                    if(found)
                    {
                        index = i;
                        print(index, addressBook);
                        printf("Choose\n 1.Edit Name\n 2.Edit Phone\n 3.Edit Email\n");
                        scanf("%d", &option);
                        edit_by(option);
                    }

                }
            }
            else if(count == 1)
            {
                printf("Choose\n 1.Edit Name\n 2.Edit Phone\n 3.Edit Email\n");
                scanf("%d", &option);
                edit_by(option);
            }
            break;

        case 2:
            printf("Enter Phone: ");
            scanf(" %[^\n]", edit);
            for(i = 0; i < addressBook -> contactCount; i++)
            {
                found = strstr(addressBook -> contacts[i].phone, edit);
               
                if(found)
                {
                    index = i;
                    flag = 1;
                    print(index, addressBook);
                    printf("Choose\n 1.Edit Name\n 2.Edit Phone\n 3.Edit Email\n");
                    scanf("%d", &option);
                    edit_by(option);
                }
            }
            break;

        case 3:
            printf("Enter Email: ");
            scanf(" %[^\n]", edit);
            for(i = 0; i < addressBook -> contactCount; i++)
            {
                found = strstr(addressBook -> contacts[i].email, edit);
            
                if(found)
                {
                    index = i;
                    flag = 1;
                    print(index, addressBook);
                    count++;
                }
            }
            if(count > 1)
            {
                printf("Enter Phone: ");
                scanf(" %[^\n]", edit);
                for(i = 0; i < addressBook -> contactCount; i++)
                {
                    found = strstr(addressBook -> contacts[i].phone, edit);
                    
                    if(found)
                    {
                        index = i;
                        print(index, addressBook);
                        printf("Choose\n 1.Edit Name\n 2.Edit Phone\n 3.Edit Email\n");
                        scanf("%d", &option);
                        edit_by(option);
                    }

                }
            }
            else
            {
                printf("Choose\n 1.Edit Name\n 2.Edit Phone\n 3.Edit Email\n");
                scanf("%d", &option);
                edit_by(option);
            }
            break;
    }
    
    if(flag == 0)
    {
        printf("Contact Not Found!\n");
    } 
}

//Delete Contact Function 
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int option;
    int index = 0, count = 0, flag = 0;
    char delete[100], *found;
    printf("Choose:\n 1.Delete by Name\n 2.Delete by Phone\n 3.Delete by Email\n");
    scanf("%d", &option);

    //Delete Function
    void delete_func(int index)
    {
        while(index < addressBook -> contactCount)
        {
            strcpy(addressBook -> contacts[index].name, addressBook -> contacts[index + 1].name);
            strcpy(addressBook -> contacts[index].phone, addressBook -> contacts[index + 1].phone);
            strcpy(addressBook -> contacts[index].email, addressBook -> contacts[index + 1].email);
            index++;
        }
    }  

    //Let user choose Delete by Name/Phone/Email
    switch(option)    
    {
    case 1:
        printf("Enter Name: ");
        scanf(" %[^\n]", delete);
        
        for(i = 0; i < addressBook -> contactCount; i++)
        {
            //search Name in the contacts
            found = strstr(addressBook -> contacts[i].name, delete);
            
            //if name found make flag = 1 and store index 
            if(found)
            {
                index = i;
                flag = 1;
                print(index, addressBook);
                count++;
            }
        }
        
        //if Duplicate name ask user to enter Phone number
        if(count > 1)
        {
            printf("Enter Phone: ");
            scanf(" %[^\n]", delete);
            for(i = 0; i < addressBook -> contactCount; i++)
            {
                //search phone is contacts
                found = strstr(addressBook -> contacts[i].phone, delete);
                
                //if number found call the delete function
                if(found)
                {
                    index = i;
                    flag = 1;
                    delete_func(index);
                    printf("Contact Deleted Successfully!\n");
                }

            }
         
        }
        //if Name is unique call delete function directly
        else
        {
            delete_func(index);
            printf("Contact Deleted Successfully!\n");
        }
        break;
    case 2:
        printf("Enter Phone: ");
        scanf(" %[^\n]", delete);
        
        //Search the phone number entered by user in contacts
        for(i = 0; i < addressBook -> contactCount; i++)
        {
            found = strstr(addressBook -> contacts[i].phone, delete);
                
            //if number found call the delete function
            if(found)
            { 
                index = i;
                flag = 1;
                print(index, addressBook);
                delete_func(index);
                printf("Contact Deleted Successfully!\n");
            }

         }
        break;
    case 3:
        printf("Enter Email: ");
        scanf(" %[^\n]", delete);
        
        //Search email entered by user in contacts
        for(i = 0; i < addressBook -> contactCount; i++)
        {
            found = strstr(addressBook -> contacts[i].email, delete);
        
            if(found)
            {
                index = i;
                flag = 1;
                print(index, addressBook);
                count++;
            }
        }
        
        //if duplicate email found ask user to enter the Phone
        if(count > 1)
        {
            printf("Enter Phone: ");
            scanf(" %[^\n]", delete);
            for(i = 0; i < addressBook -> contactCount; i++)
            {
                found = strstr(addressBook -> contacts[i].phone, delete);
                
                //if phone found call delete function
                if(found)
                {
                    index = i;
                    delete_func(index);
                    printf("Contact Deleted Successsfully!\n");
                }

            }

        }

        //if email is unique call delete function
        else
        {
            delete_func(index);
            printf("Contact Deleted Succesfully!\n");
        }
       
        break;
    }

    //if The user entered information not present in contact display below prompt message
    if(flag == 0)
    {
        printf("Contact Not Found!\n");
    }
}
