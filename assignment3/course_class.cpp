// Scott Ewing
// CS 163
// Assignment 3
//
// filename:
// course_class.cpp
//
// This is the implimentation of our course class.
// Each course object has a LLL of sections associated with that class.

#include "course_class.h"
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

    while (section)
    {
        section_details * temp = section;
        section = section->next;
        delete temp;
    }
}

//default object constructor
course_class::course_class()
{
   course = new course_details; 
}

//default object destructor
course_class::~course_class()
{
    delete course;
    course = NULL;
}


// This function checks if this course matches title
int course_class::course_match(char * title)
{
    if (!strcmp(title,course->name))
        return 1;
    return 0;
}

//this function will populate 'found' with this course's details via the
//create_course function
int course_class::retrieve(course_class * &  found)
{
    return found->create_course(course);
}

// This will display this course's information as well as all section
// information.
int course_class::display()
{
    cout << "\nCourse name: " << course->name << endl
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
//This function performs a deep copy. It includes all section information from
//the LLL as well.
int course_class::create_course(course_details * new_course)
{
    if(!new_course) return 0;

    course->name = new char[strlen(new_course->name) + 1];
    strcpy(course->name,new_course->name);

    course->description = new char[strlen(new_course->description) + 1];
    strcpy(course->description,new_course->description);


    section_details * current = new_course->section;
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

//This function is similar to create_course in that it creates a deep copy of a
//course, but only extracts 1 section based on the input parameter section.
int course_class::retrieve_section(course_class * & found,int section)
{
    int result = 0;
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

//This should be used to add one section to an existing course. The section is
//added to the LLL of sections. 
int course_class::add_section(course_class * new_course)
{
    //return 0 if there is no new section information
    if (!new_course->course->section) return 0;

    section_details * temp = new section_details;
    temp->section_num = new_course->course->section->section_num;
    temp->section_notes = new char[strlen(new_course->course->section->section_notes) + 1];
    strcpy(temp->section_notes,new_course->course->section->section_notes);

    temp->next = course->section;
    course->section = temp;
   
    return 1;
}

//This function will determine if there is a match for section_num in the LLL of
//sections for this course.
int course_class::section_match(int section_num)
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


//This is a wrapper function for the removal of a specific section from this
//course. It will remove a specific section from the LLL of sections for this 
//course. 
int course_class::remove_section(int section)
{
    int result = remove_section(course->section,section);
    //It if was the last section in a course, so there are no sections
    //remaining, this will return a 2. Otherwise 1. 
    if (result && !course->section)
        result = 2;

    return result;
}

//This recursive function is used to remove the section in question. 
int course_class::remove_section(section_details * & ptr , int section)
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
