// Scott Ewing
// CS 163
// Assignment 3
// 2/20/2014
//
// filename:
// course_list.cpp
//
// This will create a hash table where each index of the hash table is a pointer
// to a node. Each node will represent a course and colisions are handled by
// creating a linear linked list of courses from each hash node

#include "course_list.h"
using namespace std;

//default node constructor
node::node()
{
    course = new course_class;
}

//default node destructor
node::~node()
{
    delete course;
}


//Table constructor, and size is being set as '5' from course_list.h
table::table(int size)
{
    hash_table_size = size;

    course_hash = new node * [hash_table_size];

    for (int i = 0; i < hash_table_size; ++i)
        course_hash[i] = NULL;
}

//Table destructor.
table::~table()
{
    if (!course_hash) return;

    for (int i = 0; i < hash_table_size; ++i)
    {
        node * temp;
        while (course_hash[i])
        {
            temp = course_hash[i];
            course_hash[i] = course_hash[i]->next;
            delete temp;
        }
    }
    delete [] course_hash;
}


//Insert a new course into the hash table.
int table::insert(char * key_value, course_class * & to_add)
{
    int hash = hash_function_course(key_value);
    node * temp = new node;

    to_add->retrieve(temp->course);
    temp->next = course_hash[hash];
    course_hash[hash] = temp;

    return 1;
}


//Insert a section to a course that already exists in the hash table.
int table::insert_section(char * key_value, course_class * to_add)
{
    int hash = hash_function_course(key_value);

    node * current = course_hash[hash];
    while (current)
    {
        if (current->course->course_match(key_value))
            return current->course->add_section(to_add);
        current = current -> next;
    }
    
    return 0;
}

//A simple check to determine if the hash table has a course already in the
//table.
int table::has_course(char * key_value)
{
    int hash = hash_function_course(key_value);

    node * current = course_hash[hash];

    while (current)
    {    
        if (current->course->course_match(key_value))
            return 1;
        current = current->next;
    }

    return 0;
}


//This will check if a course has a section already inside the hash table.
int table::has_section(char * key_value, int section)
{
    int hash = hash_function_course(key_value);

    node * current = course_hash[hash];

    while (current)
    {
        if (current->course->course_match(key_value)  && current->course->section_match(section))
            return 1;
        current = current->next;
    }

    return 0;
}


//This will retrieve course information and populate found based on the title of
//the course (key_value)
int table::retrieve(char * key_value, course_class * & found)
{
    int hash = hash_function_course(key_value);

    node * current = course_hash[hash];

    while (current)
    {
        if (current->course->course_match(key_value) )
            return  current->course->retrieve(found);
        current = current->next;
    }

    return 0;
}

//This function will retrieve a specific section for a course and popluate
//'found' with the details. 
int table::retrieve_section(char * key_value, course_class * & found,int section)
{
    int course_hash_result = hash_function_course(key_value);
    int result = 0;

    node * current = course_hash[course_hash_result];
    while (current)
    {
        if (current->course->section_match(section) && 
                current->course->course_match(key_value) )
        {    
            result = current->course->retrieve_section(found,section);

        }
        current = current->next;
    }
    return result;
}


//This function will display the details for all items in the hash table. No
//sorting happens. 
int table::display_all()
{
    int result = 0;
    node * current;
    for (int i = 0; i < hash_table_size; ++i)
    {
        current = course_hash[i];
        while (current)
        {
            current->course->display();
            current = current -> next;
            ++result;
        }
    }
    return result;
}


//This is our hash function to generate indices based on the key_value (course
//title). 
int table::hash_function_course(char * key_value)
{
    int result = 0;

    for (int i = 0; i < strlen(key_value) && i < 8; ++i)
    {
        result +=  key_value[i];
    }

    return result % hash_table_size;
}

//This is a wrapper function to remove a specific section from a course. It
//calls the recursive fucntion remove_recursive
int table::remove(char * key_value, int section)
{
    int result = 0;
    int hash = hash_function_course(key_value);
    
    result = remove_recursive(course_hash[hash],section,key_value);
    
    return result;
}

//This is the recursive remove function for removing a specific section from a
//course in the hash table.
int table::remove_recursive(node * & ptr,int section, char *title)
{
    if (!ptr) return 0;
    //if the title and section are round, remove the section.
    else if (ptr->course->course_match(title) && ptr->course->section_match(section))
    {
        int result = ptr->course->remove_section(section);
        if (!result)
            return 0;
        //a 2 is returned if it is the last section in a course, meaning the
        //course is now empty of section. If so, remove the course.
        else if(2 == result)
        {
            node * temp = ptr;
            ptr = ptr->next;
            delete temp;
        }

        return 1;

    }
    //otherwise go to the next smalller subproblem
    else
        return remove_recursive(ptr->next,section,title);
}
