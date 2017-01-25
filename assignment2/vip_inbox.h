// Scott Ewing
// CS 162
// Assignment 2
//
// Filename:
// vip_inbox.h
//
// This is the head file for the vip inbox class. It is a queue created with a
// circular linked list.

#include "email_entry.h"

//The data structure is a circular linked list.

struct vip_node
{
    email_entry email;
    vip_node * next;
};

class vip_inbox
{
    public:
        vip_inbox();//constructor
        ~vip_inbox();//destructor
        int display_all() const; // function to display all email in the list.
        int enqueue(const email_entry & to_add); // Adds an email entry to the 
                                                 //end of the queue
        int dequeue();//Removes the first email from the front of the queue.
        int peek(email_entry & found_at_front);//Returns to the calling function 
                                               //via the found_at_front alias 
                                               //the email found at the front of
                                               //the queue.
    private:
        vip_node * rear; // rear pointer to the CLL.
};
