// post.h header file
// Scott Ewing
// 1/14/2014
// CS 163
// Assignment1
// this post.h file is for the post.cpp code.

#include <iostream>
#include <cctype>
#include <cstring>


struct node
{
    node();
    ~node();
    char * comment;
    int rating;
    node * next;
    char * keyword;
};

class post
{
    public:
        post();
        ~post();
        bool istopic(char topic[]); // responds with true/false if topic 
                                    //matches.
        int rate(char keyword[],int rating); // rates a comment based on keyword
                                            // Ratings are cumulative and
                                            // averaged
        int remove(char keyword[]); // removes a comment based on keyword
        int display(); // displays all comments and ratings
        int new_post(char new_comment[],char new_keyword[]); // posts a comment 
                                                            //with a keyword
        node * haskeyword(char keyword[]); // checks posts for keywords. Will 
                                        // return NULL for no matches, or a
                                        // pointer to the first keyword match
        int set_topic(char new_topic[]); // sets the topic of the thread   
        int show_topic(); // displays the topic of the thread. 
        
    private:
        char * topic; // name of the topic. Stored here rather than the nodes, 
                      // since it's only needed once. 
        node * head;
};
