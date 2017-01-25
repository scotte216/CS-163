// Scott Ewing
// CS 163
// Assignment 3
//
// Filename:
// main.cpp
//
// This is the interface for the table ADT for assignment 3.
//
#include "course_class.h" // this is our .h file for the course class of data.
#include "course_list.h" // this is our .h file for our Hash Table ADT
#include <fstream>

using namespace std;

const int MAX = 300; // max size for all text fields
const int LAST = 6; // menu size constant

// Main.cpp function prototypes
bool prompt(const char * prompt);
void load_classes(table &);
void retrieve_course(table & my_table);
void retrieve_section(table & my_table);
void remove_section(table & my_table);


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

//This function loads all the class details from a file into the course list. 
void load_courses(table & my_list)
{
    // This sets up the temporary pointers to extract data from the file and
    // load into the table object my_list.
    course_details * temp = new course_details;

    temp->name = new char[MAX];
    temp->description = new char[MAX];
    
    temp->section = new section_details;
    temp->section->section_notes = new char[MAX];

    ifstream file_in;// creating our file input variable.

    char filename[] = "courses.txt";//default filename.
    file_in.open(filename);
    //expecting format of Name|Description|Section #|Section Notes\n

    if (file_in)
    {
        file_in.get(temp->name,MAX,'|');
        file_in.ignore(MAX,'|');
        while (!file_in.eof()) 
        {

            file_in.get(temp->description,MAX,'|');
            file_in.ignore(MAX,'|');

            file_in >> temp->section->section_num;
            file_in.ignore(MAX,'|');
  
            file_in.get(temp->section->section_notes,MAX,'\n');
            file_in.ignore(MAX,'\n');

            course_class * test_course = new course_class;
            if (!test_course->create_course(temp))
                cout << "\nError in creating a new course\n";
            
            //check if course and section is already in the list. If so, do nothing. 
            // If there the section doesn't exist, add section. 
            // othewise, add new course.
            if (my_list.has_section(temp->name,temp->section->section_num))
            {
                cout << "\nCourse and section already exists.\n";
            }
            else if (my_list.has_course(temp->name))
            {
                if (!my_list.insert_section(temp->name,test_course))
                    cout << "\nError in adding a section to the course list.\n";
            }
            else 
            {
                if (!my_list.insert(temp->name,test_course))
                    cout << "\nError in adding course to the course list.\n";
            }
            //Clearing out our temporary objects for the next pass through the
            //file_in loading.
            delete test_course;
            delete temp->section;
            temp->section = new section_details;
            temp->section->section_notes = new char[MAX];

            file_in.get(temp->name,MAX,'|');
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
void retrieve_course(table & my_table)
{
    char * search_title = new char[MAX];
    course_class * found_course = new course_class;

    do 
    {
        cout << "\nPlease enter a course number and title to search for "
             << "(ex. CS 163 Data Structures): ";

        cin.get(search_title,MAX,'\n');
        cin.ignore(MAX,'\n');

        //if the course is not found, display message
        if (!my_table.retrieve(search_title,found_course))
            cout << '\"' << search_title << "\" not found.\n";
        //otherwise, display course & section information (all sections)
        else
        {
            cout << '\"' << search_title << "\" found:\n";
            found_course->display();
        }
        
    } while (prompt("Would you like to search for a different course? (Y/N) "));

    delete [] search_title;
    delete found_course;
}

//Function to retrieve a course information and associated information just
//about one section. 
void retrieve_section(table & my_table)
{
    char * search_title = new char[MAX];
    int section = 0;
    course_class * found_course = new course_class;

    do 
    {
        cout << "\nPlease enter a course number and title to search for "
             << "(ex. CS 163 Data Structures): ";

        cin.get(search_title,MAX,'\n');
        cin.ignore(MAX,'\n');

        cout << "\nPlease enter a section number: ";
        cin >> section;
        cin.ignore(MAX,'\n');

        //If the course and specific section aren't found, display error.
        if (!my_table.retrieve_section(search_title,found_course,section))
            cout << '\"' << search_title << "\" section " << section<< " not found.\n";
        //else, display section and course information for just 1 section. 
        else
        {
            cout << '\"' << search_title << "\" section " << section << "  found:\n";
            found_course->display();
        }
        
    } while (prompt("Would you like to search for a different course and section? (Y/N) "));

    delete [] search_title;
    delete found_course;

}



//Removing a section from a course. 
void remove_section(table & my_table)
{
    char * search_title = new char[MAX];
    int section = 0;

    do
    {
        cout << "\nPlease enter a course and title to remove (ex. CS 163 Data Structures): ";
        cin.get(search_title,MAX,'\n');
        cin.ignore(MAX,'\n');
        cout << "\nPlease enter a section you'd like to remove: ";
        cin >> section;
        cin.ignore(MAX,'\n');
        
        //Check if the section and course exists, error if it doesn't
        if (!my_table.remove(search_title,section))
            cout << '\n' << search_title << "\" section " << section << " not found.\n";
        //Otherwise, the course/section is removed. 
        else
        {
            cout << '\n' << search_title << "\" section " << section << " removed.\n";

        }

    }while (prompt("Would you like to remove another course and section? (Y/N) "));

    delete [] search_title;
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


//This is the main function of assignment 3. It resolves what action to take
//depending on the menu option selected by the user. Generally users will want
//to use option 1 first to load the courses.txt file.
int main()
{
    table my_course_list;

    int mennum=menu();

    while (mennum != LAST)
    {
        if (1 == mennum)
            load_courses(my_course_list);
        else if (2 == mennum)
        {
            if (!my_course_list.display_all())
                cout << "No courses loaded.\n";
        }
        else if (3 == mennum)
            retrieve_course(my_course_list);
        else if (4 == mennum)
            retrieve_section(my_course_list);
        else if (5 == mennum)
            remove_section(my_course_list);

        mennum=menu();
    }

    cout << "\nThanks for using this system. Come back again!\n";

    return 0;
}
