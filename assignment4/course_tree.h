// Scott Ewing
// CS 163
// Assignment 4
//
// filename:
// course_tree.h
//
// The course_tree will create a binary search tree to store and retrieve 
// courses entered into the sytem.
//
// This will create a BST with each node of the BST holding a pointer
// to course object. 
//

#include "course_data.h"

struct node
{
    node();
    ~node();
    course_data * a_course; // Each course is an object of the course_data 
                            //class.
    node * left; // left pointer
    node * right; // right pointer.
};

class tree
{
    public:
        tree();
        ~tree();
        int insert(char * dept, int course_num, course_data * to_add); 
                                               //This will insert a course --
                                               //wrapper function
        int retrieve(char * dept, int course_num, course_data * & found);
                                              //This will retrieve a course
                                              // based on the department and
                                              // course number. -- wrapper
                                              // function 
        int retrieve(char * dept, int course_num, course_data * & found,
                int section);  //This will retrieve a course and just 1
                               //section. fucntion overload -- wrapper function
        int display_all(); // displays all courses -- wrapper function
        int remove(char * dept, int course_num, int section);
                                     //wrapper function to remove a course --
                                     //wrapper functio
        int has_course(char * dept, int course_num); 
                                    // checks if a course exists 
                                    //based on a department and course 
                                    //number -- wrapper function
        int has_section(char * dept, int course_num, int section); 
                          //Checks if course (based on department and 
                          //course number) has a specific section. -- wrapper
                          //function                     

    private:
        node * root; // This is the root pointer to our BST

        int remove_section_recursive(node * & ptr,char * dept, 
                int course_num, int section);//The recursive function to remove
                                       // a section from a course from the BST. 
        
        void display(node * ptr); //Displays entire BST recursively.
        int insert_node(node * &, char*, int, course_data *);
        int go_left(char*, int, course_data *); // Determines direction to go 
                    //at each node based on the department and course number

        void remove_all_recursive(node * &); // recursive function to remove all
                                       //nodes of the tree. 
        int retrieve_recursive(node *,char *, int, course_data *&); // retrieve
                                                        // a course recursively.
        int retrieve_recursive(node *,char *, int, int, course_data * &); 
                //Retrieve 1 section from a course recursively

        int has_course(node * ptr, char * dept, int course_num);//Determines if
                                                  // a course exists in the BST.
        int has_section(node * ptr, char * dept, int course_num,int section);
            //Determines if a section exists in a course in the BST.

        int insert_section(node * ptr, course_data * to_add);
                            //Inserts a section to an existing course 
                            //based on the department and course number
        int remove_node(node * &); // function to remove a node from the BST, 
                                   //checking all the various cases.
        node * in_order_swap(node * &); // recursive function to do an in-order
        // swap of a node, taking the next in-order node and moving it to a 
        // given location.
};
