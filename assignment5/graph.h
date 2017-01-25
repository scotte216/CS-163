// Scott Ewing
// CS 163
// Assignment 5
//
// filename: graph.h
//
#include "question.h"


//The node is used in the adjacency list. Each node represents an 'answer' to
//the question, and points to the appropriate next question.
struct node
{
    struct vertex * adjacent;
    char * text;
    node * next;
};


//Each vertex represents a question, as well as a pointer to the edge-list of
//responses that will take the user to the next appropriate question.
struct vertex
{
    question * data;
    node * head;
    bool visited;
    int num_edges;
};

class graph
{
    public:
        graph(int size);//Must be initialized with an int for # of questions
        ~graph();
        int display_all();//displays all questions in entered order
        int display_depth();//displays all questions using depth-first recursion
        int insert_vertex(question_data & to_add);//add a vertex
        int insert_edge(int current_vertex,int to_attach,char * text);//add edge
        int display_adjacent(int question_id);//displays adjacent vertices 
                                              //(wrapper function)
        int display_question(int question_id);//display a question and possible
                                              //responses
        int answer_question(int question_id,int answer); //answer a question 
                                                        //with one of the valid
                                                        //responses
        int get_size();//display the size of the adjacency list (or the total 
                       //# of questions on the test)

    private:
        vertex * adjacency_list;//Our adjacency list
        int list_size; //size of the adjacency list
        int find_index(int key_value);//returns index given a 
                                      //key-value/question ID #
        void delete_adjacent_node(node * & ptr); //recursive destruction used 
                                                 //by the default destructor
        void clear_visited_flags(); //clears the visited flags
        int display_adjacent(node * ptr);//recursive function for displaying 
                                         // adjacent vertices
        int display_depth(vertex * &);//Recursive call for depth-first display
};
