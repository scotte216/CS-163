// Scott Ewing
// CS 163
// Assignment 4
//
// filename: 
// course_data.h
//
// This is the header file for the data class of a course.
// Each course object has course_details as well as a LLL of each section with
// section details. 
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
    char * dept; //ex: CS
    int course_num;// ex: 163
    char * name; // ex: Data Structures
    char * description; // ex: This course will teach you fun data 
                        //structures!
    section_details * section; // This is  a pointer to a LLL of all 
                               //the sections.
};


class course_data
{
    public:
        course_data();
        ~course_data();
        int retrieve(course_data * & found); // returns the details of this 
                                            //course to 'found' 
        int retrieve(course_data * & found, int section); // returns the 
                                            //details of this course section
                                            //to found.
        int display(); // displays this course
        int create_course(course_details * source_course); 
                                            //creates a new course 
                                            //copied from the given details
        int add_section(course_data * source_course);//creates a new section
                                        // to an existing course
        int course_match(char * title); // checks if title 
                                        //matches this course
        int section_match(int section); // checks if section exists in 
                                        //this course
        int remove_section(int section); // wrapper function to remove 
                                         //section from course.
        int dept_match(char * dept_to_check); // Checks if there is a match
                                              //of this course to the department
        int course_num_match(int number_to_check);//Checks if the course num
                                                  //matches

    private:
        course_details * course; // details of this course, private to 
                                    //the object
        int remove_section(section_details * & ptr , int section); 
                        // recursive function to remove section from course.

};

#endif
