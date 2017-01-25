// Scott Ewing
// CS 163
// Assignment 2
//
// filename:
// vip_inbox.cpp
//
// This is the vip inbox class. It is a queue that creates a circular linked
// list.

#include "vip_inbox.h"
//#include <iostream>

using namespace std;

//The devault constructor
vip_inbox::vip_inbox()
{
    rear = NULL;
}

//The default destructor
vip_inbox::~vip_inbox()
{
    if (!rear) return;

    vip_node * current = rear->next;
    rear->next = NULL;
    while (current)
    {
        vip_node * temp = current;
        current = current->next;
        delete temp;
        temp = NULL;
    }
}


//Displays the contents of the entire queue
int vip_inbox::display_all() const
{
    if (!rear) return 0;

    vip_node * front = rear->next;
    vip_node * current = front;
    rear->next = NULL;
    while (current)
    {
        current->email.display();
        current=current->next;
    }

    rear->next = front;
    return 1;
}

//This will enqueue an email to the rear of the list. The email is passed in via
//the to_add alias and passed off to the email_entry to deep copy.
int vip_inbox::enqueue(const email_entry & to_add)
{
    vip_node * temp = new vip_node;
    if (!rear)
    {
        rear = temp;
        rear->next = temp;
    }
    else
    {
        temp->next = rear->next;
        rear->next = temp;
        rear = temp;
    }
    return rear->email.copy_entry(to_add);
}

//This will dequeue the email at the front of the list. It doesn't display the
//item before dequeueing.
int vip_inbox::dequeue()
{
    // no list!
    if (!rear) return 0;

    //Only 1 item in the list
    if (rear == rear->next)
    {
        delete rear;
        rear = NULL;
    }
    // delete the front entry.
    else
    {
        vip_node * temp = rear->next;
        rear ->next = temp->next;
        delete temp;
    }
    return 1;
}

//This function will pass the details of the email at the front back to the
//calling fucntion via the found_at_front alias.
int vip_inbox::peek(email_entry & found_at_front)
{
    // no list, error!
    if (!rear) return 0;

    return found_at_front.copy_entry(rear->next->email);
    
}
