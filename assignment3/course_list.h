// Scott Ewing
// CS 163
// Assignment 3
// 2/20/2014
//
// filename:
// course_list.h
//
// The course_list will create a hash table to store and retrieve courses
// entered into the sytem.
//
// This will create a hash table with each index of the hash table as a pointer
// to a node. These nodes will be a linear linked list of courses.
//

#include "course_class.h"

struct node
{
    node();
    ~node();
    course_class * course; // Each course is an object of the course_class class.
    node * next; // next pointer
};

class table
{
    public:
        table(int hash_table_size=5);
        ~table();
        int insert(char * key_value, course_class * & to_add); //This will 
                                                            //insert a course
        int retrieve(char * key_value, course_class * & found);//This will 
                                                    //retrieve a course based on
                                                    //key_value or the title.
        int retrieve_section(char * key_value, course_class * & found,int section);
                                    //This will retrieve a course and just 1
                                    //section.
        int display_all(); // displays all courses
        int remove(char * key_value, int section);//wrapper function to remove 
                                                  //a course
        int has_course(char * key_value); // checks if a course exists based on
                                          // key_value which is the title
        int has_section(char * key_value, int section); //Checks if course
                                // (based on key_value) has a specific section. 
                                
        int insert_section(char * key_value, course_class * to_add);//Inserts a 
                            //section to an existing course based on key_value. 

    private:
        node ** course_hash; // course_hash is a pointer to an array of pointers
        int hash_table_size; // the size of our hash table.
        int hash_function_course(char * key_value); // our hash function
        int remove_recursive(node * & ptr,int section, char * title); // Hidden 
                            //removal function, used by int remove(char* , int)
};

