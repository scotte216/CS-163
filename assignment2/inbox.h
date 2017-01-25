//Scott Ewing
//CS 163
//Assignment 2
//
//
//filename:
//inbox.h
//
//This is the header file for the inbox class. This class is a Stack ADT using
//flexible arrays.
//

#include "email_entry.h"

const int SIZE=5; //size of each array in each node of the LLL.

struct inbox_node
{
    inbox_node();
    ~inbox_node();
    email_entry * emails;
    inbox_node * next;
};

//our inbox class is a stack
class inbox
{
    public:
        inbox();//stack constructor
        ~inbox();//stack destructor
        int display_all();//display all items in the stack.
        int peek(email_entry &);// pass the top entry of the stack back 
                                //to the calling 
                                //function
        int push(const email_entry &); //add a new item to the top of the stack
        int pop(); // remove the top item from the stack. 

    private:
        inbox_node * head; // head pointer for the LLL.
        int top; // the index of the next place to push. It's is set to zero 
                 //by the constructor. When it is MAX the array is full.
        

};
