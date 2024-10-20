#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{

    int count = addressBook -> contactCount;
    FILE *fptr;

    fptr = fopen("data.csv", "w");
    
    if(fptr == NULL)
    {
        perror("ERROR ");
    }
    
    //print Contact count to File
    fprintf(fptr, "%d\n", count);
    
    //Print/Store all the contact to FIle
    for(int i = 0; i < count; i++)
    {
        fprintf(fptr, "%s, %s, %s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
    }

    fclose(fptr);
    
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr;
    fptr = fopen("data.csv", "r");
    
    if(fptr == NULL)
    {
        perror("ERROR ");
    }
    
    //Read/Load the Contact count from the file
    fscanf(fptr, "%d\n", &addressBook -> contactCount);

    //Read/Load all the contact from the File
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        fscanf(fptr, "%[^,], %[^,], %[^\n]\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email); 
    }

    fclose(fptr);
    
}

