// Scott Ewing
// CS 163
// Assignment 4
//
// Filename:
// main.cpp
//
// This is the interface for the BST ADT for assignment 4.
//
#include "course_data.h" // this is our .h file for the course class of data.
#include "course_tree.h" // this is our .h file for our Binary Search Tree ADT
#include <fstream>
#include <cstring>

using namespace std;

const int MAX = 300; // max size for all text fields
const int LAST = 6; // menu size constant

// Main.cpp function prototypes
bool prompt(const char * prompt);
void load_classes(tree &);
void retrieve_course(tree & my_tree);
void retrieve_section(tree & my_tree);
void remove_section(tree & my_tree);


//This is a simple prompt function, expecting y or n and outputting true/false
bool prompt(const char * prompt)
{
    char response;
    cout << prompt;
    cin >> response;
    cin.ignore(100,'\n');

    response = toupper(response);

    return ('Y' == response);
        
}

//This function loads all the class details from a file into the course tree. 
void load_courses(tree & my_tree)
{
    // This sets up the temporary pointers to extract data from the file and
    // load into the tree object my_tree.
    course_details * temp = new course_details;

    temp->dept = new char[MAX];
    temp->name = new char[MAX];
    temp->description = new char[MAX];
    
    temp->section = new section_details;
    temp->section->section_notes = new char[MAX];

    ifstream file_in;// creating our file input variable.

    char filename[] = "courses.txt";//default filename.
    file_in.open(filename);
    //expecting format of:
    //Department|Course Number|Course Name|Description|Section #|Section Notes\n

    if (file_in)
    {
        file_in.get(temp->dept,MAX,'|');
        file_in.ignore(MAX,'|');
        while (!file_in.eof()) 
        {

            file_in >> temp->course_num;
            file_in.ignore(MAX,'|');
  
            file_in.get(temp->name,MAX,'|');
            file_in.ignore(MAX,'|');

            file_in.get(temp->description,MAX,'|');
            file_in.ignore(MAX,'|');

            file_in >> temp->section->section_num;
            file_in.ignore(MAX,'|');
  
            file_in.get(temp->section->section_notes,MAX,'\n');
            file_in.ignore(MAX,'\n');

            //Package the details into an object
            course_data * test_course = new course_data;
            if (!test_course->create_course(temp))
                cout << "\nError in creating a new course\n";
            
            //check if course and section is already in the tree. 
            // If so, do nothing. 
            // othewise, add new course.
            if (my_tree.has_section(temp->dept,temp->course_num,temp->section->section_num))
            {
                cout << "\nCourse and section already exists.\n";
            }
            else 
            {
                if (!my_tree.insert(temp->dept,temp->course_num,test_course))
                    cout << "\nError in adding course to the course list.\n";
            }

            //Clearing out our temporary objects for the next pass through the
            //file_in loading.
            delete test_course;
            delete temp->section;
            temp->section = new section_details;
            temp->section->section_notes = new char[MAX];

            file_in.get(temp->dept,MAX,'|');
            file_in.ignore(MAX,'|');
        }

        file_in.close();
        file_in.clear();

        cout << "\nData loaded from: " << filename << ".\n";
    }
    else
    {
        cout << "\nERROR: " << filename << " not found.\n";
        filename[0]='\0';
    }
    delete temp;
}

//Retrieval function to find and display a course and all associated section
//information. 
void retrieve_course(tree & my_tree)
{
    char * department = new char[MAX];
    int course_number;
    course_data * found_course = new course_data;

    do 
    {
        cout << "\nPlease enter a department to search for "
             << "(ex. CS): ";

        cin.get(department,MAX,'\n');
        cin.ignore(MAX,'\n');
        
        cout << "\nPlease enter the course number to search for "
             << "(ex. 163): ";

        cin >> course_number;
        cin.ignore(MAX,'\n');

        //if the course is not found, display message
        if (!my_tree.retrieve(department,course_number,found_course))
            cout << '\"' << department << ' ' << course_number
                 << "\" not found.\n";
        //otherwise, display course & section information (all sections)
        else
        {
            cout << '\"' << department << ' ' << course_number << "\" found:\n";
            found_course->display();
        }
        
        //Deleting and re-creating the data for another pass through.
        delete found_course;
        found_course = new course_data;
    } while (prompt("Would you like to search for a different course? (Y/N) "));

    delete [] department;
    delete found_course;
}

//Function to retrieve a course information and associated information just
//about one section. 
void retrieve_section(tree & my_tree)
{
    char * department = new char[MAX];
    int course_number = 0;
    int section = 0;
    course_data * found_course = new course_data;

    do 
    {
        cout << "\nPlease enter a department to search for "
             << "(ex. CS): ";

        cin.get(department,MAX,'\n');
        cin.ignore(MAX,'\n');
        
        cout << "\nPlease enter the course number to search for "
             << "(ex. 163): ";

        cin >> course_number;
        cin.ignore(MAX,'\n');

        cout << "\nPlease enter a section number: ";
        cin >> section;
        cin.ignore(MAX,'\n');

        //If the course and specific section aren't found, display error.
        if (!my_tree.retrieve(department,course_number,found_course,section))
            cout << '\"' << department << ' ' << course_number 
                 <<  "\" section " << section << " not found.\n";
        //else, display section and course information for just 1 section. 
        else
        {
            cout << '\"' << department << ' ' << course_number
                 << "\" section " << section << "\"  found:\n";
            found_course->display();
        }

        //Deleting the data for another pass through.
        delete found_course;
        found_course = new course_data; 

    } while (prompt("Would you like to search for a" 
               " different course and section? (Y/N) "));

    delete [] department;
    delete found_course;

}



//Removing a section from a course. If all sections for a course are removed,
//the entire course is removed.
void remove_section(tree & my_tree)
{
    char * department = new char[MAX];
    int course_number;
    int section = 0;

    do
    {
        cout << "\nPlease enter the department of the class to delete "
             << "(ex. CS): ";

        cin.get(department,MAX,'\n');
        cin.ignore(MAX,'\n');

        cout << "\nPlease enter the course number of the section to delete "
             << "(ex. 163): ";

        cin >> course_number;
        cin.ignore(MAX,'\n');

        cout << "\nPlease enter a section number to delete: ";
        cin >> section;
        cin.ignore(MAX,'\n');

        
        //Check if the section and course exists, error if it doesn't
        if (!my_tree.remove(department,course_number,section))
            cout << "\n\"" << department << ' ' << course_number 
                 << "\" section " << section << " not found.\n";
        //Otherwise, the course/section is removed. 
        else
        {
            cout << "\n\"" << department << ' ' << course_number  
                 << "\" section " << section << " removed.\n";

        }

    }while (prompt("Would you like to remove another"
               " course and section? (Y/N) "));

    delete [] department;
}


//Menu function to display options of the program. 
int menu()
{
    int response;

    do{

    cout << "Please select an item from the menu below: \n"
         << "1) Load all courses and sections\n"
         << "2) Show all courses and section information\n"
         << "3) Retrieve information about a course.\n"
         << "4) Retrieve information about a course and section.\n"
         << "5) Remove a section from a course.\n"
         << "6) Quit\n";
        
    cout<< "\nPlease select a menu option: ";
    cin >> response;
    cin.ignore(100,'\n');

    } while(1 > response || LAST < response);

    return response;

}


//This is the main function of assignment 4. It resolves what action to take
//depending on the menu option selected by the user. Generally users will want
//to use option 1 first to load the courses.txt file.
int main()
{
    tree my_course_tree;

    int mennum=menu();

    while (mennum != LAST)
    {
        if (1 == mennum)
            load_courses(my_course_tree);
        else if (2 == mennum)
        {
            if (!my_course_tree.display_all())
                cout << "No courses loaded.\n";
        }
        else if (3 == mennum)
            retrieve_course(my_course_tree);
        else if (4 == mennum)
            retrieve_section(my_course_tree);
        else if (5 == mennum)
            remove_section(my_course_tree);

        mennum=menu();
    }

    cout << "\nThanks for using this system. Come back again!\n";

    return 0;
}
