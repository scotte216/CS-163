//Scott Ewing
//CS163
//Assignment 1
//main.cpp
//This is the client program for testing the modules coded in Assignment one.
//The two modules it depends on are blog.cpp/.h and post.cpp/.h.
#include "blog.h"
using namespace std;

const int SIZE = 100; // temporary size for arrays to send data to the ADT. 
                      //Only used in the main shell, not in any of the data 
                      //structures.
const int LAST = 6; // used for the menu, to determine how large it is.

// A simple again function
bool again(char message[])
{
    char response;
    cout << message;
    cin >> response;
    cin.ignore(100,'\n');

    response=toupper(response);

    return (response == 'Y');

}

int menu()
{
    int response;

    do{

    cout << "Please select an item from the menu below: \n"
         << "1) Add a comment to a topic\n"
         << "2) Delete a comment from a topic\n"
         << "3) Show all comments for a topic\n"
         << "4) Show all comments for all topics\n"
         << "5) Rate a comment for a topic\n"
         << "6) Quit\n";
    cin >> response;
    cin.ignore(100,'\n');

    } while(1 > response || LAST < response);

    return response;

}
void menu_delete_comment(blog & my_blog)
{
    char topic[SIZE];
    char keyword[SIZE];

    cout << "Delete comment from which topic? ";
    cin.get(topic,SIZE,'\n');
    cin.ignore(100,'\n');

    cout << "What keyword or tag does the comment have? ";
    cin.get(keyword,SIZE,'\n');
    cin.ignore(100,'\n');

    if (!my_blog.remove(topic,keyword))
            cout << "Error removing comment.\n";

}

void menu_show_comments(blog & my_blog)
{
    char topic[SIZE];

    cout << "Which topic do you want to see the comments of? ";
    cin.get(topic,SIZE,'\n');
    cin.ignore(100,'\n');

    if (!my_blog.display(topic))
        cout << "Error displaying " << topic << ".\n";
}

void menu_show_all(blog & my_blog)
{
    if (!my_blog.display())
        cout << "Error displaying blog.\n";
}

void menu_rate(blog & my_blog)
{
    char topic[SIZE];
    char keyword[SIZE];
    int rating = 0;

    cout << "Rate comment from which topic? ";
    cin.get(topic,SIZE,'\n');
    cin.ignore(100,'\n');

    cout << "What keyword or tag does the comment have? ";
    cin.get(keyword,SIZE,'\n');
    cin.ignore(100,'\n');

    do{

        cout << "How do you rate the comment? (+1 or -1) ";
        cin >> rating;
        cin.ignore(100,'\n');
    } while((1 != rating) && (-1 != rating));

    if (!my_blog.rate(topic,keyword,rating))
            cout << "Error posting rating to comment.\n";
}

void menu_add_comments(blog & my_blog)
{
    char comment[SIZE];
    char topic[SIZE];
    char keyword[SIZE];
    int rating = 0;
  
    int error = 1;
    do 
    {
        error = 1;

        cout << "What topic would you like to post about? ";
        cin.get(topic,SIZE,'\n');
        cin.ignore(100,'\n');

        cout << "Please enter your comment: ";
        cin.get(comment,SIZE,'\n');
        cin.ignore(100,'\n');

        cout << "Enter a keyword or tag for this post: ";
        cin.get(keyword,SIZE,'\n');
        cin.ignore(100,'\n');

        error *= my_blog.post(topic,comment,keyword);

        if (!error)
            cout << "Error creating this post.\n";

    } while(error && again("Would you like to enter another comment? "));

}

int main()
{
    blog my_blog;

    int mennum=menu();

    while (mennum != LAST)
    {
        if (1 == mennum)
            menu_add_comments(my_blog);
        else if (2 == mennum)
            menu_delete_comment(my_blog);
        else if (3 == mennum)
            menu_show_comments(my_blog);
        else if (4 == mennum)
            menu_show_all(my_blog);
        else if (5 == mennum)
            menu_rate(my_blog);

        mennum=menu();
    }

    cout << "\nThanks for using this system. Come back again!\n";

    return 0;
}
