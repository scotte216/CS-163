// Scott Ewing
// CS 163
// Assignment 4
//
// filename:
// course_data.cpp
//
// This is the implimentation of our course class.
// Each course object has a LLL of sections associated with that class.

#include "course_data.h"
using namespace std;

//section details default constructor
section_details::section_details()
{
    section_num = 0;
    section_notes = NULL;
    next = NULL;
}


// section details default destructor
section_details::~section_details()
{
    section_num = 0;
    next = NULL;
    if (section_notes) delete [] section_notes;
    section_notes = NULL;
}


//course struct default constructor
course_details::course_details()
{
    dept = NULL;
    course_num = 0;
    name = NULL;
    description = NULL;
    section = NULL;
}

//course struct default destructor
course_details::~course_details()
{
    if (name) delete [] name;
    name = NULL;

    if (description) delete [] description;
    description = NULL;

    if (dept) delete [] dept;

    course_num = 0;

    while (section)
    {
        section_details * temp = section;
        section = section->next;
        delete temp;
    }
}

//default object constructor
course_data::course_data()
{
   course = new course_details; 
}

//default object destructor
course_data::~course_data()
{
    delete course;
    course = NULL;
}


// This function checks if this course matches title
// Returns 1 for a match, 0 if there is not a match.
int course_data::course_match(char * title)
{
    if (!strcmp(title,course->name))
        return 1;
    return 0;
}

//this function will populate 'found' with this course's details via the
//create_course function
int course_data::retrieve(course_data * &  found)
{
    return found->create_course(course);
}

// This will display this course's information as well as all section
// information.
int course_data::display()
{
    cout << "\nDepartment: " << course->dept << endl
         << "Course number: " << course->course_num << endl
         << "Course name: " << course->name << endl
         << "Description: " << course->description << endl
         << "Sections: " << endl;
    
    section_details * current = course->section;

    while (current)
    {
        cout << "Section " << current->section_num
             << " details: " << current->section_notes << endl;
        current = current->next;
    }

    return 1;
}


//creates a new course. This function is run when a course title/description
//doesn't already exist. If just adding a section, use add_section().
//This function performs a deep copy. It includes all section information 
//from the LLL as well.
int course_data::create_course(course_details * source_course)
{
    if(!source_course) return 0;

    course->dept = new char[strlen(source_course->dept) + 1];
    strcpy(course->dept,source_course->dept);

    course->course_num = source_course->course_num;

    course->name = new char[strlen(source_course->name) + 1];
    strcpy(course->name,source_course->name);

    course->description = new char[strlen(source_course->description) + 1];
    strcpy(course->description,source_course->description);


    section_details * current = source_course->section;
    while (current)
    {
        section_details * temp = new section_details;
        
        temp->section_num = current->section_num;
        temp->section_notes = new char[strlen(current->section_notes) + 1];
        strcpy(temp->section_notes,current->section_notes);

        temp->next = course->section;
        course->section = temp;
       
        current = current->next;
    }    
    return 1;
}

//This function is similar to create_course in that it creates a deep copy 
//of this course to found, but only extracts 1 section based on the input 
//parameter section.
int course_data::retrieve(course_data * & found,int section)
{
    int result = 0;

    found->course->dept = new char[strlen(course->dept)+1];
    strcpy(found->course->dept,course->dept);
    
    found->course->course_num = course->course_num;

    found->course->name = new char[strlen(course->name) + 1];
    strcpy(found->course->name,course->name);

    found->course->description = new char[strlen(course->description) + 1];
    strcpy(found->course->description,course->description);


    section_details * current = course->section;
    while (current)
    {
        if (current->section_num == section)
        {
            section_details * temp = new section_details;
        
            temp->section_num = current->section_num;
            temp->section_notes = new char[strlen(current->section_notes) + 1];
            strcpy(temp->section_notes,current->section_notes);

            found->course->section = temp;
            result = 1;
        }
        current = current->next;
    }    
    return result;
}

//This should be used to add one section to an existing course. The section 
//is added to the LLL of sections. 
int course_data::add_section(course_data * source_course)
{
    //return 0 if there is no new section information
    if (!source_course->course->section) return 0;

    section_details * temp = new section_details;

    temp->section_num = source_course->course->section->section_num;

    temp->section_notes = new char[strlen(source_course->
            course->section->section_notes) + 1];

    strcpy(temp->section_notes,source_course->course->section->section_notes);

    temp->next = course->section;
    course->section = temp;
   
    return 1;
}

//This function will determine if there is a match for section_num in the
//LLL of sections for this course.
int course_data::section_match(int section_num)
{
    int result = 0;
    section_details * current = course->section;
    while (current)
    {
        if (section_num == current->section_num)
            result = 1;
        current = current->next;
    }

    return result;
}


//returns the result of a strmatch of deparments since dept is a private 
//data member. 
int course_data::dept_match(char * dept_to_check)
{
    return strcmp(dept_to_check,course->dept);
}


//comparision of course numbers. If the number_to_check is greater than this
//course_num, return 1, if it's less than, return -1, and if they match return 0
int course_data::course_num_match(int number_to_check)
{
    if ( number_to_check > course->course_num)
        return 1;

    else if (number_to_check < course->course_num)
        return -1;
    else
        return 0;
}


//This is a wrapper function for the removal of a specific section from this
//course. It will remove a specific section from the LLL of sections for 
//this course. If it removes the last section of a course, returns a 2, else
//returns a 1.
int course_data::remove_section(int section)
{
    int result = remove_section(course->section,section);
    //It if was the last section in a course, so there are no sections
    //remaining, this will return a 2. Otherwise 1. 
    if (result && !course->section)
        result = 2;

    return result;
}


//This recursive function is used to remove the section in question. 
int course_data::remove_section(section_details * & ptr , int section)
{
    if (!ptr) return 0;
    else if (ptr->section_num == section) 
    {
        section_details * temp = ptr;
        ptr = ptr->next;
        delete temp;
        return 1;
    }
    else
        return remove_section(ptr->next,section);

}
