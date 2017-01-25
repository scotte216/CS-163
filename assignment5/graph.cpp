// Scott Ewing
// CS 163
// Assignment 5
//
// filename:
// graph.cpp
//

#include "graph.h"
using namespace std;

//default constructor, needs to know the size of the adjacency list
graph::graph(int size)
{
    list_size = size;

    adjacency_list = new vertex[list_size];

    for (int i = 0; i < list_size; ++i)
    {
        adjacency_list[i].data = NULL;
        adjacency_list[i].head = NULL;
        adjacency_list[i].visited = false;
        adjacency_list[i].num_edges = 0;
    }
}

//default destructor. Makes use of recursive function delete_adjacent_node
graph::~graph()
{
    for (int i = 0; i < list_size; ++i)
    {
        if (adjacency_list[i].head)
        {
            delete_adjacent_node(adjacency_list[i].head);
            adjacency_list[i].head = NULL;
        }
        if (adjacency_list[i].data)
        {
            delete adjacency_list[i].data;
        }
        adjacency_list[i].num_edges = 0;
    }

    delete [] adjacency_list;
}

//recursive function to delete edges.
void graph::delete_adjacent_node(node * & ptr)
{
    if (!ptr) return;

    delete_adjacent_node(ptr->next);

    if (ptr->text) delete [] ptr->text;
    ptr->text = NULL;

    ptr->adjacent = NULL;
    delete ptr;
    ptr = NULL;
}

//simple display for all vertices. 
int graph::display_all()
{
    for (int i = 0; i < list_size; ++i)
        if (adjacency_list[i].data)
            adjacency_list[i].data->display();
}


//Wrapper function to display all via Depth First Recursion. Uses
//display_depth(vertex * &)
//Returns 1 for success, 0 for an error.
int graph::display_depth()
{
    clear_visited_flags();

    return display_depth(adjacency_list);
}

//recursive function to display by depth.
int graph::display_depth(vertex * & vptr)
{
    if (!vptr) return 0;

    vptr->visited = true;
    vptr->data->display();

    node * temp = vptr->head;
    while (temp)
    {
        if (!temp->adjacent->visited)
            display_depth(temp->adjacent);//recursive call
        temp = temp->next;
    }
    return 1;
}

//Our Adjacency list will be already sized exactly the right size so we will
//just add data to the first available empty index
//returns 0 if it fails
int graph::insert_vertex(question_data & to_add)
{
    for (int i = 0; i < list_size; ++i)
        if (!adjacency_list[i].data)
        {
            adjacency_list[i].data = new question;
            adjacency_list[i].data->copy(to_add);
            return 1;
        }

    return 0;
}



//This function will insert an edge ont the adjacency list. current_vertex is
//the ID number of the vertex we want to start from. to_attach is the ID number
//of the vertex we want to attach to. text is the "answer" associated with this
//weighted edge. For example, if Vertex 1 is a yes/no question, one edge will
//have text "Yes" the other will have text "No" and they will link to the
//appropriate next question. 
int graph::insert_edge(int current_vertex,int to_attach, char * text)
{
    int result = 0;

    int source = find_index(current_vertex);
    int dest = find_index(to_attach);
    
    if (-1 != source && -1 != dest)
    {
        node * temp = new node;
        temp->next = adjacency_list[source].head;
        temp->adjacent = &adjacency_list[dest];

        temp->text = new char[strlen(text) + 1];
        strcpy(temp->text,text);

        adjacency_list[source].head = temp;

        //increment number edges
        ++adjacency_list[source].num_edges;
        result = 1;
    }

    return result;
}


//Finds the index of the adjacency_list based on the key_value (ID # in this
//case). Returns -1 if not found. 
int graph::find_index(int key_value)
{

    for (int i = 0; i < list_size; ++i)
        if (adjacency_list[i].data 
                && adjacency_list[i].data->compare(key_value))
            return i;

    return -1;
}


//Function to clear out the visited flags. 
void graph::clear_visited_flags()
{
    for (int i = 0; i < list_size; ++i)
        adjacency_list[i].visited = false;
}


//Wrapper function to display adjacent vertices. Uses recursive function 
//display_adjacent(node *)
int graph::display_adjacent(int question_id)
{
    int index = find_index(question_id);
    int result = 0;
    
    if (index != -1)
        result = display_adjacent(adjacency_list[index].head);

    return result;
}

//recursive function to display adjacent vertices.
int graph::display_adjacent(node * ptr)
{
    if (!ptr) return 0;

    ptr->adjacent->data->display();
    display_adjacent(ptr->next);

    return 1;
}

//Function to display a question from a vertex as well as all the responses (the
//text of which are held in the weighted edge list. 
//Returns -1 on the last question -- usually a farewell message.
int graph::display_question(int question_id)
{
    int index = find_index(question_id);
    int result = 0;

    if (index != -1)
    {
        vertex curr_question = adjacency_list[index];
        curr_question.data->prompt_question();

        //if question has no edges, it is the last question on the quiz. usually
        //this last 'question' should just be a farewell message.
        if (!curr_question.head)
            result = -1; //lets calling program we've reached the last question.
        //Traverse edge-list and extract text data.
        else
        {
            node * current = curr_question.head;
            int counter = 1;
            while (current)
            {
                cout << counter++ << ") " << current->text << endl;
                current = current->next;
            }
            result = 1;
        }
    }

    return result;
}

//This fucntion will return the question_id/key_value of the vertex that
//corresponds to a given answer #. Answer # represent which node in the LLL/edge
//list the answer resides with the first node being 1, second node 2, etc. 
int graph::answer_question(int question_id,int answer)
{
    int index = find_index(question_id);
    int result = -1;

    if (index != -1)
    {
        if (answer < 1 || answer > adjacency_list[index].num_edges)
            result = -1; // error: bad answer
        else
        {
            node * current = adjacency_list[index].head;
            
            //Current will never be null if answer is less than or equal to
            //num_edges
            for (int i = 1; i < answer; ++i)
                current = current->next;

            result = current->adjacent->data->get_id();

            adjacency_list[index].data->answer(answer);
        }
    }

    return result;
}


//Simple accessor to display the size of the adjacency list.
int graph::get_size()
{
    return list_size;
}
