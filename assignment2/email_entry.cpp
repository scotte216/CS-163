// Scott Ewing
// CS 163
// Assignment 2
//
// Filname:
// email_entry.cpp
//
// This is the class to describe the behavior and functions of a single email.
// Each email has a structure containing the details.

#include "email_entry.h"
using namespace std;


//email_details struct default constructor
email_details::email_details()
{
    name = NULL;
    address = NULL;
    subject = NULL;
    date = NULL;
    message = NULL;

}

//email_details struct default destructor
email_details::~email_details()
{
    if(!name) delete [] name;
    name = NULL;
 
    if(!address) delete [] address;
    address = NULL;

    if(!subject) delete [] subject;
    subject = NULL;

    if(!date) delete [] date;
    date = NULL;

    if(!message) delete [] message;
    message = NULL;
}


//default constructor: intializing all values to their zero-state.
email_entry::email_entry()
{
    //Doesn't seem to actually need anything here. Everything taken care of in
    //the struct deconstructor
}

//default destructor: returning all values to their zero-state.
email_entry::~email_entry()
{
   //Nothing to add here. ~email_details() takes care of it.
}


//This function is passed an email_details struct containing all the details of
//an email and deep copies it onto itself.
//Returns a 1 if successful, 0 otherwise.
int email_entry::create_entry(email_details new_email)
{
    if (!&new_email) return 0;

    email.name = new char[strlen(new_email.name)+1];
    strcpy(email.name,new_email.name);
    
    email.address = new char[strlen(new_email.address)+1];
    strcpy(email.address,new_email.address);
    
    email.subject = new char[strlen(new_email.subject)+1];
    strcpy(email.subject,new_email.subject);
    
    email.date = new char[strlen(new_email.date)+1];
    strcpy(email.date,new_email.date);
    
    email.message = new char[strlen(new_email.message)+1];
    strcpy(email.message,new_email.message);

    return 1;
}

// This is a wrapper function that will take a full email_entry object and copy
// it's contents here via the create_entry() function. Returns 1 for success, 0
// otherwise. 
int email_entry::copy_entry(const email_entry & to_add)
{
    //Assuming THIS instance is empty and not being overwritten
    return create_entry(to_add.email);
    
}


//This function will make a copy of the email and pass it back to the caller
//through the & found alias. Returns 1 for successful copy, 0 otherwise.
int email_entry::retrieve(email_entry & found)
{
    return found.create_entry(email);
}

//This function will display the contents of the email without formatting.
int email_entry::display()
{
    cout << email.name << endl
         << email.address << endl
         << email.subject << endl
         << email.date << endl
         << email.message << endl;

    return 1;
}
