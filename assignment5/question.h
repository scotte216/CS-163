// Scott Ewing
// CS 163
// Assignment 5
//
// filename:question.h
//
#include <iostream>
#include <cctype>
#include <cstring>

#ifndef QUESTION
#define QUESTION

//Each question object has a question_data structure. all answers are ints

struct question_data
{
    question_data();
    ~question_data();
    char * text; // text of the question.
    bool answered; // has this question been answered or not
    int answer; // The answer to the question
    int ID;//question ID number
};


class question
{
    public:
        question();
        ~question();
        void display(); // displays the question details
        int copy(question_data & source); // copies the source object to here.
        int answer(int ans); // accepts ans as the answer to the question
        void prompt_question(); // displays the question for the quiz
        int compare(int number);//compares number to this object's ID
        int get_id(); // returns the ID # for this question.

    private:
        question_data data;//the question_data object
};

#endif
