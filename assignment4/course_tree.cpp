// Scott Ewing
// CS 163
// Assignment 4
//
// filename:
// course_tree.cpp
//
// This will create a BST where each node is a pointer to a course

#include "course_tree.h"
using namespace std;

//default node constructor
node::node()
{
    a_course = new course_data;
    left = NULL;
    right = NULL;
}

//default node destructor
node::~node()
{
    delete a_course;
    left = NULL;
    right = NULL;
}


//Table constructor
tree::tree()
{
    root = NULL;
}

//Table destructor. Wrapper for the remove-all recursive function
tree::~tree()
{
   remove_all_recursive(root);
}

//Recursive function to remove all nodes in the BST.
void tree::remove_all_recursive(node * & root)
{
    if (!root) return;

    remove_all_recursive(root->left);
    remove_all_recursive(root->right);
    
    delete root;
    root = NULL;
}


//Wrapper function for inserting a course into the BST based on department and
//course number. 
int tree::insert(char * dept, int course_num, course_data * to_add)
{
    return insert_node(root, dept,course_num,to_add);
}


//Recursive function for adding a course to the BST using the department and
//course number.
int tree::insert_node(node * & ptr, char * dept, int course_num, 
        course_data * to_add)
{
    //Simple case. Adding a course.
    if (!ptr)
    {
        //node constructor sets right/left to NULL
        ptr = new node;
        to_add->retrieve(ptr->a_course);
        return 1;
    }
    // Go left or right, or does the course already exist and just adding a
    // section?
    else if (-1 == go_left(dept,course_num,ptr->a_course) )
        return insert_node(ptr->left, dept,course_num,to_add);

    // else right condition
    else if (1 == go_left(dept,course_num,ptr->a_course) )
        return insert_node(ptr->right,dept,course_num,to_add);

    //Else we are at the course and need to insert a section to that course.
    else 
        return insert_section(ptr,to_add);
}

// A simple subroutine to determing direction we should go at any given 
// node. A -1 means go left, a 1 means go right and a 0 means the course
// exists at this node. This is based on Department first, then course number.
int tree::go_left(char * dept, int course_num, course_data * data)
{
    int result;

    if ( 0 > data->dept_match(dept) )
        result = -1;
    else if (0 < data->dept_match(dept)) 
        result = 1;
    else
        result = data->course_num_match(course_num);

    return result;
}


//Insert a section to a course that already exists in the binary tree
int tree::insert_section(node * ptr, course_data * to_add)
{
    return ptr->a_course->add_section(to_add);
}

//This will retrieve course information and populate found based on the 
//department and  course number. This is a wrapper function.
int tree::retrieve(char * dept, int course_num, course_data * & found)
{
    return retrieve_recursive(root,dept,course_num,found);
}

//recursive function for retrieving the course.
int tree::retrieve_recursive(node * ptr, char * dept, 
        int course_num, course_data * & found)
{
    //empty list or not found, return 0
    if (!ptr) return 0;
    
    //Go left?
    else if (-1 == go_left(dept,course_num,ptr->a_course) )
        return retrieve_recursive(ptr->left,dept,course_num,found);
    
    //Go right?
    else if (1 == go_left(dept,course_num,ptr->a_course) )
        return retrieve_recursive(ptr->right,dept,course_num,found);
    
    //Else, we're here at the course! Retrieve course.
    else
        return ptr->a_course->retrieve(found);
}

//This wrapper function will retrieve a specific section for a course and 
//popluate 'found' with the details. 
int tree::retrieve(char * dept, int course_num, course_data * & found, 
        int section)
{
    return retrieve_recursive(root,dept,course_num,section,found);
}

//This is the recursive function for retrieving a specific section from a course
//in the BST
int tree::retrieve_recursive(node * ptr,char * dept,int course_num,
        int section,course_data * & found)
{
    //Not found or empty list, return 0
    if (!ptr) return 0;

    //Go left?
    else if (-1 == go_left(dept,course_num,ptr->a_course) )
        return retrieve_recursive(ptr->left,dept,course_num,section,found);
    
    //Go right?
    else if(1 == go_left(dept,course_num,ptr->a_course) )
        return retrieve_recursive(ptr->right,dept,course_num,section,found);
    
    //Else we're here at the course! Retrieve the section!
    else
        return ptr->a_course->retrieve(found,section);
}

//This function will display the details of the courses in the BST. 
//This is a wrapper function.
int tree::display_all()
{
    if (!root) return 0;

    display(root);

    return 1;
}

//This is the recursive function to display all nodes in order.
void tree::display(node * ptr)
{
    if (!ptr);
    else
    {
        display(ptr->left);
        ptr->a_course->display();
        display(ptr->right);
    }
}


//This is a wrapper function to remove a specific section from a course. It
//calls the recursive function remove_section_recursive
int tree::remove(char * dept, int course_num, int section)
{
    return remove_section_recursive(root,dept,course_num,section);
}


//This is the recursive remove function for removing a specific section 
//from a course in the BST.
int tree::remove_section_recursive(node * & ptr,char * dept, int course_num, 
        int section)
{
    //Empty tree or course not found, return 0.
    if (!ptr) return 0;

    //Go left?
    else if (-1 == go_left(dept,course_num,ptr->a_course))
        return remove_section_recursive(ptr->left,dept,course_num,section);

    //Go right?
    else if (1 == go_left(dept,course_num,ptr->a_course))
        return remove_section_recursive(ptr->right,dept,course_num,section);

    //Else found the course, remove section!
    else 
    {
       int result = ptr->a_course->remove_section(section);
       //If it's the last course in a section, remove the course entirely via
       //remove_node
       if (2 == result)
           result = remove_node(ptr);

       return result;
    }
}


//This function will remove a node from the BST entirely
int tree::remove_node(node * & ptr)
{

    //so we don't dereference a null pointer. This case should never be invoked.
    if (!ptr) return 0;
    
    //if the node is a leaf, delete the node
    else if (!ptr->left && !ptr->right)
    {
        delete ptr;
        ptr = NULL;
    }

    //else if there is one leaf on the left
    else if (!ptr->right)
    {
        node * temp = ptr;
        ptr = ptr->left;
        delete temp;
    }
    //else if there is on leaf  on the right
    else if (!ptr->left)
    {
        node * temp = ptr;
        ptr = ptr->right;
        delete temp;
    }
    //else we need to find the in-order successor and replace this node with
    //that one. 
    else
    {
        //special case, right node is the in-order successor.
        if (!ptr->right->left)
        {
            node * temp = ptr;
            ptr = ptr->right;
            ptr->left = temp->left;
            delete temp;
        }
        //else find that successor and move it here.
        else
        {
            node * temp = ptr;
            ptr = in_order_swap(ptr->right);
            ptr->right = temp->right;
            ptr->left = temp->left;
            delete temp;
        }
    }
    return 1;
}


//Recursive function to find the in-order successor, remove it from the tree and
//pass back it's node pointer.
node * tree::in_order_swap(node * & ptr)
{
    //If the left poniter is null, we're at the in-order succesor
    if (!ptr->left)
    {
        //make a pointer to this node
        node * temp = ptr;

        //modify the ptr (an alias from the previous node's left) to point to
        //this node's right
        ptr = ptr->right;
        return temp;
    }
    //else keep moving left until we reach the left-most node.
    else
        return in_order_swap(ptr->left);
}

//A simple check to determine if the BST has a course already in the tree.
//This is a wrapper function
int tree::has_course(char * dept, int course_num)
{
    return has_course(root,dept,course_num);
}

//recursive function to check if the BST has a course.
int tree::has_course(node * ptr, char * dept, int course_num)
{
    //empty tree or no match, return 0
    if (!ptr) return 0;

    //Go left?
    else if (-1 == go_left(dept,course_num,ptr->a_course))
        return has_course(ptr->left,dept,course_num);

    // go right?
    else if (1 == go_left(dept,course_num,ptr->a_course))
        return has_course(ptr->right,dept,course_num);

    //Else we've found the course and return 1!
    else
        return 1;
    
}

//This will check if a course has a section already inside the BST.
//This is a wrapper function
int tree::has_section(char * dept, int course_num, int section)
{
    return has_section(root,dept,course_num,section);
}

//This is a recusrive function to determing if a section inside a course exists
//in the BST. 
int tree::has_section(node * ptr, char * dept, int course_num,int section)
{
    //Empty tree or course not found, return 0
    if (!ptr) return 0;

    //Go left?
    else if (-1 == go_left(dept,course_num,ptr->a_course))
        return has_section(ptr->left,dept,course_num,section);

    //Go right?
    else if (1 == go_left(dept,course_num,ptr->a_course))
        return has_section(ptr->right,dept,course_num,section);

    //Else we've found the course! Return result from the section-match check.
    else
        return ptr->a_course->section_match(section);
}

