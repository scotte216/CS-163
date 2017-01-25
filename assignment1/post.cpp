// Scott Ewing
// post.cpp file 
// Ths is the cpp file for the data members in the post class
// CS 163
// 1/14/2014
// This post.cpp code is used by blog.cpp. The outputs are 0 for any failed
// fuction or 1 (or 2) for any successes.

#include "post.h"
using namespace std;

//default constructor for the node
node::node()
{
    comment = NULL;
    rating = 0;
    keyword = NULL;
    next = NULL;
}

//default destructor for the node
node::~node()
{
    if (comment) delete [] comment;
    if (keyword) delete [] keyword;
    rating = 0;
    next = NULL;
}


//Initializes data to zero equilent
post::post()
{
    head = NULL;
    topic = NULL;
}

//Deconstructor for the post data
post::~post()
{
    while(head)
    {
        node * temp = head;
        head = head->next;
        delete temp;
    }
    if (topic) delete [] topic;
}

//A boolean to determine if this topic is the topic to match. Used by the blog
//class to find the right topic.
bool post::istopic(char topic_to_match[])
{
    if (!head) return false;

    if (!strcmp(topic,topic_to_match))
        return true;
    return false;
}

// This will determine if the keyword_to_match is used by one or more of the
// comments in this data set. It will return the number of matches.
node * post::haskeyword(char keyword_to_match[])
{
    if (!head) return NULL;

    node * current = head;
    while (current)
    {
        if (!strcmp(current->keyword,keyword_to_match))
            return current;
        current = current->next;
    }
    return NULL;
}

//This will add a new rating to a commment post based on a keyword.
//ratings of -1 or +1 are expected.
int post::rate(char keyword_to_match[],int new_rating)
{

    //If there is no list, or if the rating value isn't valid, return 0.
    if (!(-1==new_rating || 1==new_rating) || !head) return 0;

    //Since we use the value from haskeyword several times we store it in a
    //temporary variable.
    node * haskey = haskeyword(keyword_to_match);

    //If there is a pointer to a post with the keyword...
    if (haskey)
    {
        //adjust the rating
        haskey->rating = haskey->rating + new_rating;
        return 1;
    }
    else
        return 0;
}

//This will remove the node matching keyword
int post::remove(char keyword_to_match[])
{
    if (!head) return 0;

    node * haskey = haskeyword(keyword_to_match);

    //if there is a pointer to a node with the keyword, remove the node
    
    //case 1, the head node is the one to be removed
    if (haskey == head)
    {
        head = head->next;
        delete haskey;
        haskey = NULL;

    }
    //case 2, some other node is to be removed
    else if (haskey)
    {
        node * current = head;
        //traverse until the node before the one to be removed.
        while (! (current->next == haskey))
            current =current ->next;

        current->next = haskey->next;
        delete haskey;
        haskey = NULL;
    }

    //special case: the last item in the LLL has been deleted.
    if (!head) return 2;

    return 1;
}

//this function will traverse the list and display each node.
int post::display()
{
    if (!head) return 0;

    node * current = head;
    while (current)
    {
        cout << current->comment << endl
             << current->rating << endl
             << current->keyword << endl;
        current = current->next;
    }
    cout << "--------------\n";
    return 1;
}

//this wil create a new post and add it to the list.
int post::new_post(char new_comment[],char new_keyword[])
{
    node * current;
    //case 1 -- empty list
    if (!head)
    {
        head = new node;
        current = head;
    }
    //case 2 -- a list already exists
    else
    {
        current = head;
        
        while(current->next) 
            current = current->next;
        
        current->next = new node;
        current = current->next;
    }

    //Copy the keyword and comment into the current node
    current->comment = new char[strlen(new_comment)+1];
    strcpy(current->comment,new_comment);

    current->keyword = new char[strlen(new_keyword)+1];
    strcpy(current->keyword,new_keyword);

    return 1;
}

//This function will name the topic of the thread
int post::set_topic(char new_topic[])
{
    topic = new char[strlen(new_topic)+1];
    strcpy(topic,new_topic);
    return 1;
}

//This function will show the post's topic
int post::show_topic()
{
    if (!topic) return 0;
    cout << topic << endl;
    return 1;
}
