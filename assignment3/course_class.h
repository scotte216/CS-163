// Scott Ewing
// CS 163
// Assignment 3
//
// filename: 
// course_class.h
//
// This is the header file for the data class of a course.
#include <cstring>
#include <cctype>
#include <iostream>

#ifndef COURSE_CLASS
#define COURSE_CLASS

struct section_details
{
    section_details();
    ~section_details();
    int section_num; // ex: 1
    char * section_notes;// ex: This section is Monday at noon.
    section_details * next;//Next pointer to the next section.
};

struct course_details
{
    course_details();
    ~course_details();
    char * name; // ex: CS163 Data Structures
    char * description; // ex: This course will teach you fun data structures!
    section_details * section; // This is  a pointer to a LLL of all the sections.
};


class course_class
{
    public:
        course_class();
        ~course_class();
        int retrieve(course_class * & found); // returns the details of this 
                                            //course to 'found' 
        int retrieve_section(course_class * & found, int section); // returns the 
                                            //details of this course section 
                                            //to found.
        int display(); // displays this course
//        int copy_course(course_class * & to_add); 
                            //copies the details of this course into to_add 
        int create_course(course_details * new_course); //creates a new course 
                                                    //copied from the given 
                                                    //details
        int add_section(course_class * new_course);//creates a new section
                                                   // to an existing course
        int course_match(char * title); // checks if title matches this course
        int section_match(int section); // checks if section exists in this course
        int remove_section(int section); // wrapper function to  remove section from course.

    private:
        course_details * course; // details of this course, private to the object
        int remove_section(section_details * & ptr , int section); // recursive 
                                        // function to remove section from course. 

};

#endif
