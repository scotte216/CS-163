// Scott Ewing
// CS 163
// Assignment 2
// 
// Filename:
// inbox.cpp
//
// This is the class for the inbox. It is a stack using a flexible array
// structure.


#include "inbox.h"
using namespace std;

//default struct inbox_node constructor
inbox_node::inbox_node()
{
    emails = new email_entry[SIZE];
    next = NULL;
}


//default struct inbox_node destructor
inbox_node::~inbox_node()
{
    delete [] emails;
    next = NULL;
}

//default inbox class constructor
inbox::inbox()
{
    head = NULL;
    top = 0;
}


//default inbox class destructor
inbox::~inbox()
{
    top = 0;
    while (head)
    {
        inbox_node * temp = head;
        head = head->next;
        delete temp;
    }
}


// This function will display all emails in the inbox
int inbox::display_all()
{
    if (!head) return 0;

    //If we get this far, we have at least one node, with 'top' number of 
    //elements.
    for (int i = top-1; i >= 0; --i)
        head->emails[i].display();

    // Now we want to continue through remaining nodes if they exist. They will
    // all be full so we use SIZE instead of top.
    inbox_node * current = head->next;
    while (current)
    {
        for (int i = SIZE-1; i >= 0 ; --i)
        {
            current->emails[i].display();
        }
        current = current->next;
    }

    return 1;
}


//This function will take the top-most email and pass it back to the calling
//routine via the found_at_top alias.
int inbox::peek(email_entry & found_at_top)
{
    if (!head) return 0;

    found_at_top.copy_entry(head->emails[top-1]);
    return 1;
}

//This function will push a new email onto the stack.
int inbox::push(const email_entry & to_add)
{
    
    //if there is nothing in the list yet:
    if (!head)
    {    
        head = new inbox_node;
        top = 0;
    }
    //there is a node at the head, but it's full, create a new node
    else if (SIZE == top)
    {
        inbox_node * temp = head;
        head = new inbox_node;
        top = 0;
        head->next = temp;
    }
    //There's already a node and it's not full
    head->emails[top++].copy_entry(to_add);
    return 1;
}


//This function will pop an email off the stack. Note: it does not display the
//mail first.
int inbox::pop()
{
    //if there is no list, return 0
    if (!head) return 0;
    
    //decrement the top counter
    --top;

    //if top is 0, then it's the last item in the array.
    if (0 == top)
    {
        inbox_node * temp = head;
        head = head->next;
        delete temp;
        top = SIZE;
    }

    return 1;
}
