// Scott Ewing
// CS 163
// Assignment 5
//
// filename:
// main.cpp
//
#include "question.h"
#include "graph.h"
#include <cstring>
#include <fstream>

using namespace std;

const int MAX = 200;//used for temporary text arrays
const int LAST = 5;//used for the last item in the menu


//prototypes
int load_data(graph &);
int load_edges(graph &);
int menu();
void menu_vertices(graph &);
void menu_depth(graph &);
void menu_take_quiz(graph &);


//Function to load vertices from test.txt. This doesn't load edges. Use
//load_edges for that.
int load_data(graph & my_quiz)
{
    question_data new_question;
    new_question.text = new char[MAX];

    ifstream file_in;

    char filename[] = "test.txt";
    file_in.open(filename);
    //expected format:
    //Question #|Question\n
    
    if (file_in)
    {
        file_in >> new_question.ID;
        file_in.ignore(MAX,'|');
        while(!file_in.eof())
        {
            file_in.get(new_question.text,MAX,'\n');
            file_in.ignore(MAX,'\n');

            if (!my_quiz.insert_vertex(new_question))
                cout << "Error adding question.\n";

            file_in >> new_question.ID;
            file_in.ignore(MAX,'|');
        }
        file_in.close();
        file_in.clear();

        cout << "\nQuestions loaded from: " << filename << ".\n";
    }
    else
    {
        cout << "\nError: " << filename << " not found.\n";
        filename[0]='\0';
    }
    
}


//This function loads the edge-lists for the previously loaded vertices.
int load_edges(graph & my_quiz)
{
    int source;
    int dest;
    char * text = new char[MAX];

    ifstream file_in;

    char filename[] = "edges.txt";
    file_in.open(filename);
    //expected format: Question source ID#|Question dest ID#|Text

    if (file_in)
    {
        file_in >> source;
        file_in.ignore(MAX,'|');

        while(!file_in.eof())
        {
            file_in >> dest;
            file_in.ignore(MAX,'|');

            file_in.get(text,MAX,'\n');
            file_in.ignore(MAX,'\n');

            if (!my_quiz.insert_edge(source,dest,text))
                cout << "Error inserting edge.\n";

            file_in >> source;
            file_in.ignore(MAX,'|');

        }
        file_in.close();
        file_in.clear();

        cout << "\nEdges loaded from: " << filename << ".\n";

    }
    else
    {
        cout << "\n Error: " << filename << " not found.\n";
        filename[0] = '\0';
    }

    delete [] text;
}


//This function displays our menu and returns the response number.
int menu()
{
    int response;

    do{

    cout << "\n-----------------\n"
         << "Please select an item from the menu below: \n"
         << "1) Display all questions\n"
         << "2) Display adjacent vertices to a question\n"
         << "3) Display the quiz using a depth first traversal\n"
         << "4) Take the quiz\n"
         << "5) Quit\n";
        
    cout<< "\nPlease select a menu option: ";
    cin >> response;
    cin.ignore(100,'\n');

    } while(1 > response || LAST < response);

    return response;
}


//This function is executed when the menu option to display adjacent vertices is
//selected.
void menu_vertices(graph & my_quiz)
{
    int vertex;
    cout << "Which question/vertex do you want to display the adjacency "
         << "list for? \nEnter a number 1 to " << my_quiz.get_size() << ": ";

    cin >> vertex;
    cin.ignore(100,'\n');

    if(!my_quiz.display_adjacent(vertex))
        cout << "That question/vertex has no adjacent questions/edges.\n";
}


//This function is executed when the depth-first menu option is selected.
void menu_depth(graph & my_quiz)
{
    if (!my_quiz.display_depth())
        cout << "Error displaying quiz depth-first.\n";
}

//This function is executed when the 'take quiz' menu option is selected.
void menu_take_quiz(graph & my_quiz)
{
    int question = 1;
    int response;

    while (-1 != my_quiz.display_question(question))
    {
        cin >> response;
        cin.ignore(100,'\n');

        int temp = my_quiz.answer_question(question,response);

        while (-1 == temp)
        {
            cout << "That number isn't valid. Please pick again.\n";
            cin >> response;
            cin.ignore(100,'\n');
            
            temp = my_quiz.answer_question(question,response); 
        }

        question = temp;
    }
}


//The main function
int main()
{
    graph my_quiz(11);//Do not change this number unless 
                      //you modify test.txt and edge.txt
    load_data(my_quiz);
    load_edges(my_quiz);


    cout << "Welcome to Assignment 5. This quiz is constructed using a Graph\n"
         << "data type. Each quiz question is a vertex. Each question has a\n"
         << "adjacency list of the possible responses which will take the\n"
         << "user to the appropriate next question.\n\n";

    int men_num = menu();

    while (men_num != LAST)
    {
        if (1 == men_num)
            my_quiz.display_all();
        else if(2 == men_num)
            menu_vertices(my_quiz);
        else if(3 == men_num)
            menu_depth(my_quiz);
        else if(4 == men_num)
            menu_take_quiz(my_quiz);

        men_num = menu();
    }

    cout << "\nThanks for playing! Y'all come back soon, now, hear?\n";
     
    return 0;
}
