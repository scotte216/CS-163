// blog.h header file
// Scott Ewing
// 1/14/2014
// CS 163
// This is the header file for blog.cpp
//

#include <iostream>
#include <cctype>
#include <cstring>
#include "post.h"

struct topic
{
    post a_post;
    topic * next;
};


class blog
{
    public:
        blog();
        ~blog();

        //create a new post of comment [] to topic_name, supplying keyword[]
        //like  a tag to a post.
        int post(char topic_name[], char comment[],char keyword[]);

        //display all comments in topic_name
        int display(char topic_name[]);

        //Display all comments in all topics.
        int display();

        //rate a specific comment in topic_name via its keyword with rating.
        //Rating like an up-vote or down-vote and +1 or -1 is expected.
        int rate(char topic_name[],char keyword[], int rating);

        //remove a comments via keyword from topic_name
        int remove(char topic_name[], char keyword[]);

    private:
        topic * head;

};
