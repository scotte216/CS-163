// Scott Ewing
// CS 163
// Assignment 5
//
// Filename: question.cpp
//

#include "question.h"
using namespace std;

//The question_data constructor
question_data::question_data()
{
    text = NULL;
    answer = 0;
    answered = false;
    ID = -1;
}

//structor destructor
question_data::~question_data()
{
    if (text) delete [] text;
    text = NULL;
    
    answered = false;
    answer = 0;
    ID = -1;
}

//Default constructor, doesn't actually need to do anything. Handled by the
//struct's constructor.
question::question()
{
}

//Ditto!
question::~question()
{
}


//Displays details about this question.
void question::display()
{
    cout << "--------\n";
    cout << "ID#: " << data.ID << endl;
    cout << "Question: \n" << data.text << endl;

    cout << "Status: ";
    if (!data.answered)
        cout << "unanswered.\n";
    else
        cout << "answered.\n";
}


//Prompts just the text of the question without other details. 
void question::prompt_question()
{
    cout << data.text << endl;
}

//Takes the input 'ans' as an answer. Returns that value.
int question::answer(int ans)
{
    data.answered = true;
    data.answer = ans;
    return data.answer;
}

//Copies data from 'source' to this object.
int question::copy(question_data & source)
{
    data.text = new char[strlen(source.text) + 1];
    strcpy(data.text,source.text);
    data.ID = source.ID;

    return 1;
}


//Compares the number with object's ID.
int question::compare(int number)
{
    return data.ID == number;
}

//Accessor for the ID number of this question object.
int question::get_id()
{
    return data.ID;
}
