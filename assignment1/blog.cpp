// The .cpp file for the blog class.
// Scott Ewing
// CS 163
// 1/14/2014
// blog.cpp
// Any outputs will be 0 for failed function or 1 for success.
// This file is dependent on post.cpp/.h
//

#include "blog.h"


using namespace std;

//default constructor
blog::blog()
{
    head = NULL;
}

//default destructor
blog::~blog()
{
    while(head)
    {
        topic * temp = head;
        head = head->next;
        delete temp;
    }
}

//Add a new comment to a topic and give it a keyword, like a tag.
int blog::post(char topic_name[], char comment[],char keyword[])
{
    int error = 1;
    //case 1 no topics yet
    if (!head)
    {
        head = new topic;
        error *= head->a_post.set_topic(topic_name);
        error *= head->a_post.new_post(comment,keyword);
    }
    //If there are topics then we need to find out if the topic of the post
    //exists.
    else
    {
        topic * current = head;
        topic * previous = NULL;
        //traverse through the list until topic[] is true  or the end of the
        //list is reached. Bring a previous along behind.
        while (current && !current->a_post.istopic(topic_name))
        {
            previous = current;
            current = current->next;
        }
        //At this point we are either at the end or the topic is matched.
        //if current exists, then we have a match .If current == NULL then we
        //don't have a match and need to make a new topic
        if (!current)
        {
            previous->next = new topic;
            current = previous->next;
            error *= current->a_post.set_topic(topic_name);
        }
        error *= current->a_post.new_post(comment,keyword);
    }
    return error;
}

//Display all comments from topic_name
int blog::display(char topic_name[])
{
    if (!head) return 0;

    topic * current = head;

    //traverse until we find the topic in question
    while (current)
    {
        if (current->a_post.istopic(topic_name))
        {
            return current->a_post.display();
        }
        current = current->next;
    }
    return 0;
}

//This function will display all topics and comments
int blog::display()
{
    int error = 1;
    if (!head) return 0;

    topic * current = head;
    while(current)
    {
        //Traverse through all topics, display the topic title and then have
        //each topic display all their comments.
        error *= current->a_post.show_topic();
        error *= current->a_post.display();
        current = current ->next;
    }

    return error;
}

//rate a comment based on keyword in topic_named with rating. Rating is expected
//to be +1 or -1 like an upvote or downvote.
int blog::rate(char topic_name[],char keyword[], int rating)
{
    if (!head) return 0;

    topic * current = head;
    //Trying a slightly different method here. Rather than finding the matching
    //topic and starting a new alternation, We'll just traverse and if we find a
    //topic, execute the command and return 1
    while (current)
    {
        if (current->a_post.istopic(topic_name))
        {
            return current->a_post.rate(keyword,rating);
        }
        current = current->next;
    }
    //if we get here, we found no matches
    return 0;

}

//This will remove a comment via keyword from topic_name
int blog::remove(char topic_name[], char keyword[])
{
    int error = 0;
    if (!head) return 0;

    topic * current = head;
    topic * previous = NULL;
    while (current)
    {
        if (current->a_post.istopic(topic_name))
        {
            // If successful, returns a 1. If the last node in the list is
            // deleted then it will return a 2.
            error = current->a_post.remove(keyword);
            if (2 == error)
            {
                //if the topic is the first item in the list
                if (current == head)
                {
                    head = head->next;
                    delete current;
                }
                // it's somewhere else in the list of topics.
                else 
                {
                    previous->next = current->next;
                    current->next = NULL;
                    delete current;
                }
                return 1;
            }
            else 
                return error;
        }
        previous = current;
        current = current->next;
    }

    // item not found.
    return 0;
}

