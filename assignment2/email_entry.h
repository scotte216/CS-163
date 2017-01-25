// Scott Ewing
// CS 163
// Assignment 2
//
// Filename: 
// email_entry.h
//
// This header file contains the prototypes for the email_entry class

#include <cstring>
#include <cctype>
#include <iostream>

#ifndef EMAIL_ENTRY
#define EMAIL_ENTRY

//Basic structure of an email.
struct email_details
{
    email_details();
    ~email_details();
    char * name;
    char * address;
    char * subject;
    char * date;
    char * message; 
};


class email_entry
{
    public:
        email_entry();//constructor
        ~email_entry();//destructor
        int create_entry(email_details new_email); //Deep-copies an email based on the details 
                                                   //passed in from the calling function. 
        int copy_entry(const email_entry & new_entry);//Deep copies an email based on an whole 
                                                      // email_entry object passed in from the 
                                                      // calling function 
        int retrieve(email_entry & found); //This will copy the details of THIS email back to 
                                           //'found' passed in from the calling function. 
        int display(); // this displays the contents of an email. 

    private:
        email_details email; // The details of an email, private to this object.

};
#endif
